/*
 * detector.c : on-node side-channel anomaly detector for RV32IM (no FPU).
 * Same 38 features as fl/scenarios.py + fl/datasets.py, computed in fixed
 * point on one L = 128 sample power-sensor window, followed by the int8 MLP
 * (38 -> 32 -> 16 -> 1) exported from the federated model (det_model.h).
 *
 *   det_window(x) -> anomaly score in Q8 (0..256 ~ sigmoid 0..1)
 *
 * Feature scaling: f_norm = (f - mu) / sd with the node's benign calibration,
 * then int8 with scale 1/16 (+-8 sd). Weights are int8 per tensor with a
 * power-of-two-free integer requantisation (scale ratios exported as Q16).
 */
#include <stdint.h>
#include "det_model.h"
#ifdef DET_PROF
#include "platform.h"
uint32_t det_prof[8]; static uint32_t det_t0;
#define PT(i) do { uint32_t _t = rdcycle(); det_prof[i] += _t - det_t0; det_t0 = _t; } while (0)
#define PT0() (det_t0 = rdcycle())
#else
#define PT(i) ((void)0)
#define PT0() ((void)0)
#endif

#define L 128
#define NB 8
#define NDS 16
#define RD 32
#define HW 8

static int64_t isqrt64(uint64_t v)
{
    uint64_t r = 0, b = (uint64_t)1 << 62;
    while (b > v) b >>= 2;
    while (b) {
        if (v >= r + b) { v -= r + b; r = (r >> 1) + b; } else r >>= 1;
        b >>= 2;
    }
    return (int64_t)r;
}

/* ---------------- 128-point radix-2 complex FFT, Q15 twiddles ---------------- */
static const int16_t tw_cos[64] = {
#include "det_twiddle_cos.h"
};
static const int16_t tw_sin[64] = {
#include "det_twiddle_sin.h"
};

static void fft128(int32_t *re, int32_t *im)
{
    unsigned i, j, k, m, len;
    for (i = 1, j = 0; i < L; i++) {             /* bit reversal */
        unsigned bit = L >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) { int32_t t = re[i]; re[i] = re[j]; re[j] = t; t = im[i]; im[i] = im[j]; im[j] = t; }
    }
    for (len = 2; len <= L; len <<= 1) {
        unsigned half = len >> 1, step = L / len;
        for (i = 0; i < L; i += len)
            for (k = 0, m = 0; k < half; k++, m += step) {
                int32_t c = tw_cos[m], s = tw_sin[m];
                int32_t xr = re[i + k + half], xi = im[i + k + half];
                int32_t tr = (int32_t)(((int64_t)xr * c + (int64_t)xi * s) >> 15);
                int32_t ti = (int32_t)(((int64_t)xi * c - (int64_t)xr * s) >> 15);
                re[i + k + half] = (re[i + k] - tr) >> 1; im[i + k + half] = (im[i + k] - ti) >> 1;
                re[i + k] = (re[i + k] + tr) >> 1;        im[i + k] = (im[i + k] + ti) >> 1;
            }
    }
}

/* ---------------- state kept between windows ---------------- */
static int16_t prev[L];
static int8_t hist[HW][RD];
static unsigned nhist;

/* num * 2^sh / den with the RV32M 32-bit divider: both operands are scaled
 * down together until they fit, keeping >= 14 significant bits of den.   */
static int32_t qdiv(int64_t num, int64_t den, int sh)
{
    int neg = 0;
    if (den == 0) return 0;
    if (den < 0) { den = -den; num = -num; }
    if (num < 0) { num = -num; neg = 1; }
    while (den >= ((int64_t)1 << 15) || num >= ((int64_t)1 << (30 - sh))) { den >>= 1; num >>= 1; }
    if (den == 0) return neg ? -0x7fffffff : 0x7fffffff;
    int32_t q = (int32_t)(((int32_t)num << sh) / (int32_t)den);
    return neg ? -q : q;
}

/* correlation of two mean-removed vectors, Q12 */
static int32_t corr_q12(const int32_t *a, const int32_t *b, unsigned n)
{
    int64_t ab = 0, aa = 0, bb = 0;
    unsigned i;
    for (i = 0; i < n; i++) { ab += (int64_t)a[i] * b[i]; aa += (int64_t)a[i] * a[i]; bb += (int64_t)b[i] * b[i]; }
    int64_t d = isqrt64((uint64_t)aa) * isqrt64((uint64_t)bb);
    return qdiv(ab, d, 12);
}

static int8_t q8(int64_t f_q12, int idx)
{
    /* (f - mu) / sd * 16, mu and inv_sd in Q12 from det_model.h */
    int64_t z = ((f_q12 - det_mu[idx]) * det_isd[idx]) >> 20;   /* Q12*Q12 >> 20 = *16 */
    if (z > 127) z = 127;
    if (z < -127) z = -127;
    return (int8_t)z;
}

static int32_t relu_rq(int32_t acc, int32_t m_q16)
{
    int64_t v = ((int64_t)acc * m_q16) >> 16;
    if (v < 0) v = 0;
    if (v > 127) v = 127;
    return (int32_t)v;
}

int32_t det_window(const int16_t *x, int32_t log_rate_q12, int32_t reject)
{
    int32_t xc[L], re[L], im[L], tm[L], pc[L];
    int64_t f[DET_NIN];
    int64_t s1 = 0, s2 = 0, s3 = 0, s4 = 0, mad = 0;
    int32_t mx = x[0], mn = x[0];
    unsigned i, j, k;

    PT0();
    /* --- moments (x in sensor LSB; features in Q12 of LSB units) --- */
    for (i = 0; i < L; i++) {
        s1 += x[i];
        if (x[i] > mx) mx = x[i];
        if (x[i] < mn) mn = x[i];
        if (i) mad += x[i] > x[i - 1] ? x[i] - x[i - 1] : x[i - 1] - x[i];
    }
    int32_t mean_q4 = (int32_t)((s1 << 4) >> 7);                /* / L (L = 128) */
    for (i = 0; i < L; i++) {
        int32_t d = ((int32_t)x[i] << 4) - mean_q4;          /* Q4 */
        xc[i] = d;
        int64_t d2 = (int64_t)d * d;
        s2 += d2; s3 += (d2 * d) >> 4; s4 += (d2 * d2) >> 8;
    }
    int64_t var_q8 = s2 >> 7;                                /* Q8, / L */
    int64_t sd_q4 = isqrt64((uint64_t)var_q8);
    f[0] = (int64_t)mean_q4 << 8;
    f[1] = sd_q4 << 8;
    f[2] = qdiv(mad, L - 1, 12);
    f[3] = (int64_t)mx << 12;
    f[4] = (int64_t)mn << 12;
    {   /* skew = m3/sd^3, kurt = m4/sd^4 */
        int64_t sd3 = (var_q8 * sd_q4) >> 4;                 /* Q8 */
        int64_t m3 = s3 >> 7, m4 = s4 >> 7;                 /* Q8, / L */
        f[5] = qdiv(m3, sd3, 12);
        f[6] = qdiv(qdiv(m4, var_q8, 8), var_q8, 12);   /* m4 / var^2, Q12 */
    }
    PT(0);
    /* --- spectrum: relative energy in 8 bands of bins 1..64 --- */
    for (i = 0; i < L; i++) { re[i] = xc[i] << 8; im[i] = 0; }
    fft128(re, im);
    {
        int64_t band[NB] = {0}, tot = 0;
        for (k = 1; k <= 64; k++) {
            int64_t p = ((int64_t)re[k] * re[k] + (int64_t)im[k] * im[k]) >> 8;
            band[(k - 1) / 8] += p; tot += p;
        }
        for (j = 0; j < NB; j++) f[7 + j] = qdiv(band[j], tot, 12);
    }
    PT(1);
    /* --- correlation with the benign template and the previous window --- */
    for (i = 0; i < L; i++) { tm[i] = det_tpl[i]; pc[i] = prev[i]; }
    {
        int64_t mt = 0, mp = 0;
        for (i = 0; i < L; i++) { mt += tm[i]; mp += pc[i]; }
        int32_t mt_l = (int32_t)(mt >> 7), mp_l = (int32_t)((mp << 4) >> 7);   /* hoisted means */
        for (i = 0; i < L; i++) { tm[i] -= mt_l; pc[i] = (pc[i] << 4) - mp_l; }
    }
    f[15] = corr_q12(xc, tm, L);
    f[16] = corr_q12(xc, pc, L);
    PT(2);
    /* --- 16-point downsampled waveform (block means) --- */
    for (j = 0; j < NDS; j++) {
        int64_t a = 0;
        for (i = j * (L / NDS); i < (j + 1) * (L / NDS); i++) a += x[i];
        f[17 + j] = (a << 12) >> 3;                          /* / (L / NDS) = 8 */
    }
    PT(3);
    /* --- residual after regressing on the template; 32 block means; history --- */
    {
        int64_t xt = 0, tt = 0;
        int32_t r[RD];
        int8_t rq[RD];
        for (i = 0; i < L; i++) { xt += (int64_t)xc[i] * tm[i]; tt += (int64_t)tm[i] * tm[i]; }
        int64_t a_q16 = qdiv(xt, tt, 16);
        int64_t rs = 0, rss = 0;
        for (j = 0; j < RD; j++) {
            int64_t acc = 0;
            for (i = j * (L / RD); i < (j + 1) * (L / RD); i++)
                acc += xc[i] - ((a_q16 * tm[i]) >> 16);
            r[j] = (int32_t)(acc >> 2);                      /* / (L / RD) = 4 */
            rs += r[j];
        }
        int32_t rmean = (int32_t)(rs >> 5);
        for (j = 0; j < RD; j++) { r[j] -= rmean; rss += (int64_t)r[j] * r[j]; }
        int64_t rsd = isqrt64((uint64_t)(rss >> 5));
        int64_t rinv = rsd ? (int64_t)(0x80000000u / (uint32_t)rsd) << 6 : 0;   /* 2^37/rsd: Q32 reciprocal * 32 */
        for (j = 0; j < RD; j++) {
            int64_t v = ((int64_t)r[j] * rinv) >> 32;           /* unit-sd residual, scale 32 */
            rq[j] = (int8_t)(v > 127 ? 127 : (v < -127 ? -127 : v));
        }
        int64_t csum = 0, cmax = -((int64_t)1 << 40), coh = 0;
        int32_t msum[RD];
        for (j = 0; j < RD; j++) msum[j] = rq[j];
        for (k = 0; k < nhist; k++) {
            int64_t c = 0;
            for (j = 0; j < RD; j++) { c += rq[j] * hist[k][j]; msum[j] += hist[k][j]; }
            c = (c << 12) >> 15;                             /* / (32 * 32 * RD) */
            csum += c; if (c > cmax) cmax = c;
        }
        for (j = 0; j < RD; j++) coh += (int64_t)msum[j] * msum[j];
        f[33] = nhist ? (int32_t)csum / (int32_t)nhist : 0;
        f[34] = nhist ? cmax : 0;
        f[35] = qdiv(coh, (int64_t)(nhist + 1) * (nhist + 1) * 32 * 32 * RD, 12);
        /* push into the history ring */
        if (nhist < HW) nhist++;
        for (k = nhist - 1; k > 0; k--) for (j = 0; j < RD; j++) hist[k][j] = hist[k - 1][j];
        for (j = 0; j < RD; j++) hist[0][j] = rq[j];
    }
    PT(4);
    f[36] = log_rate_q12;
    f[37] = (int64_t)reject << 12;
    for (i = 0; i < L; i++) prev[i] = x[i];

    /* --- int8 MLP --- */
    int8_t in[DET_NIN];
    int32_t h1[DET_H1], h2[DET_H2];
    for (i = 0; i < DET_NIN; i++) in[i] = q8(f[i], (int)i);
    PT(5);
    for (j = 0; j < DET_H1; j++) {
        int32_t acc = det_b1[j];
        for (i = 0; i < DET_NIN; i++) acc += in[i] * det_W1[i][j];
        h1[j] = relu_rq(acc, det_m1);
    }
    for (j = 0; j < DET_H2; j++) {
        int32_t acc = det_b2[j];
        for (i = 0; i < DET_H1; i++) acc += h1[i] * det_W2[i][j];
        h2[j] = relu_rq(acc, det_m2);
    }
    int32_t acc = det_b3;
    for (i = 0; i < DET_H2; i++) acc += h2[i] * det_W3[i];
    PT(6);
    return acc;     /* logit in the int32 domain of layer 3; > det_thr => anomalous */
}
