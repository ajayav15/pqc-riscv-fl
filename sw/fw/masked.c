/*
 * masked.c : first-order (2-share) masked ML-KEM-512 decapsulation for
 * PicoRV32 + kyber_ise, hardened against transition and glitch leakage
 * (version 2; the value-model-only version 1 is kept in masked_v1.c).
 *
 * Sharing                                      used for
 *   arithmetic mod q   x = x0 + x1 mod q        s_hat, decryption, re-encryption
 *   Boolean            x = x0 ^ x1              message, coins, Keccak states, z,
 *                                               compressed coefficients
 *   arithmetic mod 2^k (transient)              compression / decoding
 *
 * Why version 2. On a scalar core, two values handled by consecutive
 * instructions, or written one after the other into the same register, latch
 * or bus, combine in the power consumption (transition leakage), and glitches
 * in the combinational logic between those latches combine them as well. The
 * C compiler of version 1 interleaved the two shares freely, so the gadgets
 * passed TVLA under a value model but failed under a transition model.
 *
 * Structure of version 2 (the leakage rules R1 to R3 are in masked_asm.S):
 *   * every computation on one share runs in a per-share "kernel" that only
 *     reads and writes that share's arrays in memory (plus fresh randomness and
 *     public data). Kernels run through share_run(), which afterwards clears
 *     all caller-saved registers, the ALU, PCPI and multiplier operand latches,
 *     the store-data bus and the kernel's stack frame;
 *   * the only gadget that needs both shares at once, the ISW AND, is written in
 *     assembly (msk_and32p) with clearing instructions between share crossings;
 *   * no secret-dependent division (the multi-cycle divider keeps its operands),
 *     branches or memory addresses: reductions mod q are branch-free Barrett /
 *     conditional subtractions;
 *   * a register, array or stack slot that held one share never receives the
 *     other share of the same value.
 * The C code outside kernels only touches pointers, loop counters, public data
 * and fresh random words.
 *
 * Gadgets (first order): ISW AND, Kogge-Stone secure adder (Coron et al., FSE
 * 2015), compression via arithmetic shares mod 2^k and exact multiply-shift
 * constants (analysis/masked_constants.py), bit-wise B2A, masked Keccak with
 * chi from ISW ANDs, masked OR for the re-encryption check. Only the final
 * pass/fail bit is unmasked (Bos et al., TCHES 2021(4)); the shared secret is
 * unmasked when it leaves masked_dec().
 */
#include <stdint.h>
#include <string.h>
#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include "indcpa.h"
#include "symmetric.h"
#include "ise.h"
#include "ise_poly.h"
#include "masked.h"

#define Q KYBER_Q
#define NI __attribute__((noinline))

/* ------------------------------------------------------------------ randomness */
static uint32_t xs[4] = {0x9e3779b9u, 0x243f6a88u, 0xb7e15162u, 0x8aed2a6bu};
static inline uint32_t rotl32(uint32_t x, int k) { return (x << k) | (x >> (32 - k)); }
#if defined(MASK_ZERO)
/* control experiment for the leakage assessment: all masks zero (no masking) */
uint32_t mrand32(void) { return 0; }
void masked_seed(uint32_t s) { (void)s; }
#elif defined(MASK_HW_RNG) && !defined(ISE_NATIVE_EMU)
uint32_t mrand32(void) { uint32_t r; KRNG(r); return r; }
void masked_seed(uint32_t s) { KSEED(s ? s : 1u); }
#else
uint32_t mrand32(void)
{
    uint32_t r = rotl32(xs[1] * 5u, 7) * 9u, t = xs[1] << 9;
    xs[2] ^= xs[0]; xs[3] ^= xs[1]; xs[1] ^= xs[2]; xs[0] ^= xs[3];
    xs[2] ^= t; xs[3] = rotl32(xs[3], 11);
    return r;
}
void masked_seed(uint32_t s)
{
    unsigned i;
    xs[0] ^= s; xs[1] ^= s * 0x85ebca6bu; xs[2] ^= ~s; xs[3] ^= s << 7;
    for (i = 0; i < 16; i++) (void)mrand32();
}
#endif
/* inlined fresh mask word for the gadgets */
#if defined(MASK_ZERO)
#define MRND() 0u
#elif defined(MASK_HW_RNG) && !defined(ISE_NATIVE_EMU)
static inline uint32_t mrnd_hw(void) { uint32_t r; KRNG(r); return r; }
#define MRND() mrnd_hw()
#else
#define MRND() mrand32()
#endif
/* uniform mod q by multiply-shift (constant time; bias < q / 2^32) */
static inline uint32_t mrandq(void) { return (uint32_t)(((uint64_t)MRND() * Q) >> 32); }

/* ------------------------------------------------------------------ primitives */
void msk_and32p(uint32_t *z0, uint32_t *z1, const uint32_t *x0, const uint32_t *x1,
                const uint32_t *y0, const uint32_t *y1, uint32_t r);
void share_run(void (*fn)(void *), void *arg, unsigned clear_bytes);
#if defined(ISE_NATIVE_EMU) || !defined(__riscv)
/* native build (functional tests): same semantics in C */
void msk_and32p(uint32_t *z0, uint32_t *z1, const uint32_t *x0, const uint32_t *x1,
                const uint32_t *y0, const uint32_t *y1, uint32_t r)
{
    uint32_t a0 = *x0, a1 = *x1, b0 = *y0, b1 = *y1;
    uint32_t t = r ^ (a0 & b1) ^ (a1 & b0);
    *z0 = (a0 & b0) ^ r;
    *z1 = (a1 & b1) ^ t;
}
void share_run(void (*fn)(void *), void *arg, unsigned clear_bytes) { (void)clear_bytes; fn(arg); }
#endif
#define KCLR 0       /* stack bytes cleared after a kernel: kernels run through RUN have no
                       * stack frame (checked by sw/check_kernels.py); the others pass their size */
#define RUN(fn, st) share_run((void (*)(void *))(fn), (void *)(st), KCLR)
#define RUN2(fn, st) do { (st)->sh = 0; RUN(fn, st); (st)->sh = 1; RUN(fn, st); } while (0)

static inline void and32(uint32_t *z, uint32_t *x, uint32_t *y)
{   /* operands are share pairs stored as w[0], w[1] */
    msk_and32p(&z[0], &z[1], &x[0], &x[1], &y[0], &y[1], MRND());
}
static inline void and64(uint64_t *z, uint64_t *x, uint64_t *y)
{   /* 64-bit share pairs w[0], w[1]: low and high words separately */
    uint32_t *Z = (uint32_t *)z, *X = (uint32_t *)x, *Y = (uint32_t *)y;
    msk_and32p(&Z[0], &Z[2], &X[0], &X[2], &Y[0], &Y[2], MRND());
    msk_and32p(&Z[1], &Z[3], &X[1], &X[3], &Y[1], &Y[3], MRND());
}

/* branch-free mod-q helpers for values that are already shares */
#if defined(__GNUC__)
#define OPQ(v) __asm__ volatile("" : "+r"(v))   /* hides v from the optimizer (no select / branch) */
#else
#define OPQ(v) ((void)0)
#endif
static inline uint32_t csubq(uint32_t a)
{
    uint32_t t = a - Q, m = (uint32_t)((int32_t)t >> 31);
    OPQ(m);
    return t + (m & Q);
}
static inline uint32_t addq(uint32_t a, uint32_t b) { return csubq(a + b); }            /* a, b < q */
static inline uint32_t subq(uint32_t a, uint32_t b) { return csubq(a + Q - b); }        /* a, b < q */
/* x mod q for x < 2^23, Barrett with m = floor(2^32 / q), no divider */
static inline uint32_t redq(uint32_t x)
{
    uint32_t t = (uint32_t)(((uint64_t)x * 1290167u) >> 32);
    return csubq(csubq(x - t * Q));
}

/* ------------------------------------------------------------------ secure adder + compression */
/* compress_d(a0 + a1 mod q) = floor((x 2^d + 1664) / q) mod 2^d as Boolean shares.
 * y = a0 + a1 in [0, 2q) gives the same value mod 2^d; floor(.. / q) is the exact
 * multiply-shift ((y 2^d + 1664) * M) >> S (analysis/masked_constants.py).
 * The arithmetic shares are re-shared mod 2^W (W = 32 or 64) with a fresh R,
 * multiplied share-wise, turned into Boolean sharings x = (Z0 ^ r1, r1) and
 * y = (r2, Z1 ^ r2) of the two summands, and added with a Kogge-Stone adder on
 * Boolean shares (Coron et al., FSE 2015) whose ANDs are msk_and32p:
 *     g = x & y; p = x ^ y
 *     for i = 1, 2, 4, .. < k:  g ^= p & (g << i);  p &= p << i
 *     z = x ^ y ^ (g << 1),  c = (z >> S) mod 2^d
 * The linear steps of one share are fused into four kernels (pre, hg1, upd,
 * post), so one compression costs 4 + 2 log2(k) kernel runs.
 * post also performs the consumer's first step (mode 1: insert the bit into a
 * message share; mode 2: prepare the masked OR of the re-encryption check). */
#define CMP_DEF(W, T)                                                                           \
typedef struct {                                                                                \
    T x[2], y[2], p[2], g[2], hg[2], hp[2], u[2];                                               \
    const uint16_t *src[2];          /* the two arithmetic shares mod q */                      \
    uint8_t *dst[2]; unsigned dbit;  /* mode 1 */                                               \
    uint32_t pubc, *acc, *na, *nd;   /* mode 2 */                                               \
    uint32_t c[2];                                                                              \
    T R, r1, r2, M;                                                                             \
    unsigned d, S, k, i, sh, mode;                                                              \
} cmp##W##_t;                                                                                   \
static NI void cmp##W##_pre(cmp##W##_t *s)                                                      \
{                                                                                               \
    unsigned sh = s->sh;                                                                        \
    T a = *s->src[sh];                                                                          \
    if (sh == 0) {                                                                              \
        T Z = (((a + s->R) << s->d) + 1664u) * s->M;                                            \
        s->x[0] = Z ^ s->r1; s->y[0] = s->r2;                                                   \
    } else {                                                                                    \
        T Z = ((a - s->R) << s->d) * s->M;                                                      \
        s->x[1] = s->r1; s->y[1] = Z ^ s->r2;                                                   \
    }                                                                                           \
    s->p[sh] = s->x[sh] ^ s->y[sh];                                                             \
}                                                                                               \
static NI void cmp##W##_hg1(cmp##W##_t *s) { s->hg[s->sh] = s->g[s->sh] << 1; }                 \
static NI void cmp##W##_upd(cmp##W##_t *s)                                                      \
{                                                                                               \
    unsigned sh = s->sh, i = s->i;                                                              \
    T g = s->g[sh] ^ s->u[sh];                                                                  \
    s->g[sh] = g;                                                                               \
    s->hp[sh] = s->p[sh] << i;                                                                  \
    s->hg[sh] = 2 * i < W ? g << (2 * i) : 0;                                                   \
}                                                                                               \
static NI void cmp##W##_post(cmp##W##_t *s)                                                     \
{                                                                                               \
    unsigned sh = s->sh;                                                                        \
    T z = s->x[sh] ^ s->y[sh] ^ (s->g[sh] << 1);                                                \
    uint32_t c = (uint32_t)(z >> s->S) & ((1u << s->d) - 1u);                                   \
    s->c[sh] = c;                                                                               \
    if (s->mode == 1) s->dst[sh][s->dbit >> 3] |= (uint8_t)(c << (s->dbit & 7));                \
    if (s->mode == 2) {                                                                         \
        uint32_t dd = sh ? c : c ^ s->pubc;                                                     \
        s->na[sh] = sh ? s->acc[1] : ~s->acc[0];                                                \
        s->nd[sh] = sh ? dd : ~dd;                                                              \
    }                                                                                           \
}
CMP_DEF(32, uint32_t)
CMP_DEF(64, uint64_t)

static void compress32(cmp32_t *s, unsigned d, unsigned S, uint32_t M)
{
    s->d = d; s->S = S; s->M = M; s->k = S + d;
    s->R = MRND(); s->r1 = MRND(); s->r2 = MRND();
    RUN2(cmp32_pre, s);
    and32(s->g, s->x, s->y);
    RUN2(cmp32_hg1, s);
    for (s->i = 1; s->i < s->k; s->i <<= 1) {
        and32(s->u, s->p, s->hg);
        RUN2(cmp32_upd, s);
        if ((s->i << 1) < s->k) and32(s->p, s->p, s->hp);
    }
    RUN2(cmp32_post, s);
}
static void compress64(cmp64_t *s, unsigned d, unsigned S, uint64_t M)
{
    s->d = d; s->S = S; s->M = M; s->k = S + d;
    s->R = ((uint64_t)MRND() << 32) | MRND();
    s->r1 = ((uint64_t)MRND() << 32) | MRND();
    s->r2 = ((uint64_t)MRND() << 32) | MRND();
    RUN2(cmp64_pre, s);
    and64(s->g, s->x, s->y);
    RUN2(cmp64_hg1, s);
    for (s->i = 1; s->i < s->k; s->i <<= 1) {
        and64(s->u, s->p, s->hg);
        RUN2(cmp64_upd, s);
        if ((s->i << 1) < s->k) and64(s->p, s->p, s->hp);
    }
    RUN2(cmp64_post, s);
}

/* ------------------------------------------------------------------ B2A of bits */
/* n Boolean-masked bits (b0[i] ^ b1[i]) -> arithmetic shares mod q (x0[i] + x1[i]).
 * x = b1 + (1 - 2 b1) b0 with b0 first arithmetically masked: a0 = b0 + r0,
 * a1 = -r0. Three kernels so that no kernel sees two shares of one value:
 *   A {b0, r0}          -> a0, a1
 *   B {b1, a0, r}       -> x0 = b1 + (1 - 2 b1) a0 + r
 *   C {b1, a1, r}       -> x1 = (1 - 2 b1) a1 - r                               */
#define B2A_MAX 1024
typedef struct {
    const uint8_t *b0, *b1;            /* bit streams (little endian), bit offset off */
    unsigned off, n;
    uint16_t a0[B2A_MAX], a1[B2A_MAX], r0[B2A_MAX], r[B2A_MAX];
    uint16_t x0[B2A_MAX], x1[B2A_MAX];
} b2a_t;
static inline uint32_t bit_at(const uint8_t *b, unsigned i) { return (b[i >> 3] >> (i & 7)) & 1u; }
static NI void b2a_A(b2a_t *s)
{
    unsigned i;
    for (i = 0; i < s->n; i++) {
        uint32_t r0 = s->r0[i];
        s->a0[i] = (uint16_t)csubq(bit_at(s->b0, s->off + i) + r0);
        s->a1[i] = (uint16_t)csubq(Q - r0);
    }
}
static inline uint32_t cneg(uint32_t a, uint32_t m) { OPQ(m); return (csubq(Q - a) & m) | (a & ~m); }  /* m ? -a : a */
static NI void b2a_B(b2a_t *s)
{
    unsigned i;
    for (i = 0; i < s->n; i++) {
        uint32_t b1 = bit_at(s->b1, s->off + i), m = 0u - b1;
        s->x0[i] = (uint16_t)addq(addq(b1, cneg(s->a0[i], m)), s->r[i]);
    }
}
static NI void b2a_C(b2a_t *s)
{
    unsigned i;
    for (i = 0; i < s->n; i++) {
        uint32_t b1 = bit_at(s->b1, s->off + i), m = 0u - b1;
        s->x1[i] = (uint16_t)subq(cneg(s->a1[i], m), s->r[i]);
    }
}
static void b2a_bits(b2a_t *s, const uint8_t *b0, const uint8_t *b1, unsigned off, unsigned n)
{
    unsigned i;
    s->b0 = b0; s->b1 = b1; s->off = off; s->n = n;
    for (i = 0; i < n; i++) { s->r0[i] = (uint16_t)mrandq(); s->r[i] = (uint16_t)mrandq(); }
    RUN(b2a_A, s);
    RUN(b2a_B, s);
    RUN(b2a_C, s);
}

/* masked CBD_eta: coefficient i = sum of eta bits - sum of the next eta bits */
typedef struct { b2a_t *t; int16_t *r[2]; unsigned n, eta, sh; } cbdacc_t;
static NI void cbd_acc(cbdacc_t *s)
{
    unsigned i, j, e = s->eta;
    const uint16_t *x = s->sh ? s->t->x1 : s->t->x0;
    for (i = 0; i < s->n; i++) {
        uint32_t acc = 0;
        for (j = 0; j < e; j++) acc = addq(acc, x[2 * e * i + j]);
        for (j = 0; j < e; j++) acc = subq(acc, x[2 * e * i + e + j]);
        s->r[s->sh][i] = (int16_t)acc;
    }
}
static b2a_t b2a_ws;
static void masked_cbd_n(int16_t *r0, int16_t *r1, const uint8_t *b0, const uint8_t *b1, unsigned n, unsigned eta)
{
    unsigned c, per = B2A_MAX / (2 * eta);        /* coefficients per B2A batch */
    cbdacc_t a;
    for (c = 0; c < n; c += per) {
        unsigned m = n - c < per ? n - c : per;
        b2a_bits(&b2a_ws, b0, b1, 2 * eta * c, 2 * eta * m);
        a.t = &b2a_ws; a.r[0] = r0 + c; a.r[1] = r1 + c; a.n = m; a.eta = eta;
        RUN2(cbd_acc, &a);
    }
}

/* ------------------------------------------------------------------ masked Keccak */
static const uint64_t RC[24] = {
    0x0000000000000001ull, 0x0000000000008082ull, 0x800000000000808Aull, 0x8000000080008000ull,
    0x000000000000808Bull, 0x0000000080000001ull, 0x8000000080008081ull, 0x8000000000008009ull,
    0x000000000000008Aull, 0x0000000000000088ull, 0x0000000080008009ull, 0x000000008000000Aull,
    0x000000008000808Bull, 0x800000000000008Bull, 0x8000000000008089ull, 0x8000000000008003ull,
    0x8000000000008002ull, 0x8000000000000080ull, 0x000000000000800Aull, 0x800000008000000Aull,
    0x8000000080008081ull, 0x8000000000008080ull, 0x0000000080000001ull, 0x8000000080008008ull};
#define ROL(v, n) ((n) ? (((v) << (n)) | ((v) >> ((64 - (n)) & 63))) : (v))

/* theta, rho, pi of one share, fully unrolled (constant rotations) */
static inline void lin(const uint64_t *A, uint64_t *B)
{
    uint64_t c0 = A[0] ^ A[5] ^ A[10] ^ A[15] ^ A[20], c1 = A[1] ^ A[6] ^ A[11] ^ A[16] ^ A[21];
    uint64_t c2 = A[2] ^ A[7] ^ A[12] ^ A[17] ^ A[22], c3 = A[3] ^ A[8] ^ A[13] ^ A[18] ^ A[23];
    uint64_t c4 = A[4] ^ A[9] ^ A[14] ^ A[19] ^ A[24];
    uint64_t d0 = c4 ^ ROL(c1, 1), d1 = c0 ^ ROL(c2, 1), d2 = c1 ^ ROL(c3, 1), d3 = c2 ^ ROL(c4, 1), d4 = c3 ^ ROL(c0, 1);
    B[0] = ROL(A[0] ^ d0, 0);   B[16] = ROL(A[5] ^ d0, 36); B[7] = ROL(A[10] ^ d0, 3);
    B[23] = ROL(A[15] ^ d0, 41); B[14] = ROL(A[20] ^ d0, 18);
    B[10] = ROL(A[1] ^ d1, 1);  B[1] = ROL(A[6] ^ d1, 44);  B[17] = ROL(A[11] ^ d1, 10);
    B[8] = ROL(A[16] ^ d1, 45); B[24] = ROL(A[21] ^ d1, 2);
    B[20] = ROL(A[2] ^ d2, 62); B[11] = ROL(A[7] ^ d2, 6);  B[2] = ROL(A[12] ^ d2, 43);
    B[18] = ROL(A[17] ^ d2, 15); B[9] = ROL(A[22] ^ d2, 61);
    B[5] = ROL(A[3] ^ d3, 28);  B[21] = ROL(A[8] ^ d3, 55); B[12] = ROL(A[13] ^ d3, 25);
    B[3] = ROL(A[18] ^ d3, 21); B[19] = ROL(A[23] ^ d3, 56);
    B[15] = ROL(A[4] ^ d4, 27); B[6] = ROL(A[9] ^ d4, 20);  B[22] = ROL(A[14] ^ d4, 39);
    B[13] = ROL(A[19] ^ d4, 8); B[4] = ROL(A[24] ^ d4, 14);
}
/* round state; chi lane i: a_i = b_i ^ (~b_{i+1} & b_{i+2}) within each plane.
 * nb holds the sharing (~b0, b1) of ~b, t the AND results. */
typedef struct { uint64_t *a[2]; uint64_t b[2][25], nb[2][25], t[2][25]; unsigned r, sh; } kround_t;
static NI void kr_lin(kround_t *s)
{
    unsigned i, sh = s->sh;
    lin(s->a[sh], s->b[sh]);
    for (i = 0; i < 25; i++) s->nb[sh][i] = sh ? s->b[sh][i] : ~s->b[sh][i];
}
static NI void kr_fin(kround_t *s)
{
    unsigned i, sh = s->sh;
    for (i = 0; i < 25; i++) s->a[sh][i] = s->b[sh][i] ^ s->t[sh][i];
    if (sh == 0) s->a[0][0] ^= RC[s->r];
}
static const uint8_t NXT1[25] = {1, 2, 3, 4, 0, 6, 7, 8, 9, 5, 11, 12, 13, 14, 10, 16, 17, 18, 19, 15, 21, 22, 23, 24, 20};
static const uint8_t NXT2[25] = {2, 3, 4, 0, 1, 7, 8, 9, 5, 6, 12, 13, 14, 10, 11, 17, 18, 19, 15, 16, 22, 23, 24, 20, 21};
unsigned masked_keccak_nr = 24;     /* reduced only by the TVLA firmware */
static kround_t kr_ws;
void masked_keccak_f1600(uint64_t a0[25], uint64_t a1[25])
{
    kround_t *s = &kr_ws;
    unsigned i;
    s->a[0] = a0; s->a[1] = a1;
    for (s->r = 0; s->r < masked_keccak_nr; s->r++) {
        s->sh = 0; share_run((void (*)(void *))kr_lin, s, 64);
        s->sh = 1; share_run((void (*)(void *))kr_lin, s, 64);
        for (i = 0; i < 25; i++) {
            uint32_t *T0 = (uint32_t *)&s->t[0][i], *T1 = (uint32_t *)&s->t[1][i];
            uint32_t *X0 = (uint32_t *)&s->nb[0][NXT1[i]], *X1 = (uint32_t *)&s->nb[1][NXT1[i]];
            uint32_t *Y0 = (uint32_t *)&s->b[0][NXT2[i]], *Y1 = (uint32_t *)&s->b[1][NXT2[i]];
            msk_and32p(&T0[0], &T1[0], &X0[0], &X1[0], &Y0[0], &Y1[0], MRND());
            msk_and32p(&T0[1], &T1[1], &X0[1], &X1[1], &Y0[1], &Y1[1], MRND());
        }
        RUN2(kr_fin, s);
    }
}

/* masked sponge: secret-shared input segment (sec0/sec1, slen) followed by a
 * public segment (pub, plen); output shares out0/out1 */
typedef struct {
    uint64_t s[2][25];
    const uint8_t *sec[2], *pub;
    uint8_t *out[2];
    size_t slen, plen, from, to, pos;      /* byte range [from, to) of the input / output */
    unsigned rate, sh;
    uint8_t dsep;
} sponge_t;
static NI void sp_zero(sponge_t *s) { memset(s->s[s->sh], 0, sizeof s->s[0]); }
static NI void sp_absorb(sponge_t *s)
{   /* input bytes [from, to) into lanes starting at byte position pos */
    size_t i, p = s->pos;
    uint64_t *st = s->s[s->sh];
    for (i = s->from; i < s->to; i++, p++) {
        uint8_t v = i < s->slen ? s->sec[s->sh][i] : (s->sh ? 0 : s->pub[i - s->slen]);
        st[p / 8] ^= (uint64_t)v << (8 * (p % 8));
    }
}
static NI void sp_pad(sponge_t *s)
{
    if (s->sh == 0) {
        s->s[0][s->pos / 8] ^= (uint64_t)s->dsep << (8 * (s->pos % 8));
        s->s[0][(s->rate - 1) / 8] ^= 1ull << 63;
    }
}
static NI void sp_squeeze(sponge_t *s)
{
    size_t i, p = s->pos;
    for (i = s->from; i < s->to; i++, p++) s->out[s->sh][i] = (uint8_t)(s->s[s->sh][p / 8] >> (8 * (p % 8)));
}
static sponge_t sp_ws;
static void masked_sponge(uint8_t *out0, uint8_t *out1, size_t outlen, unsigned rate, uint8_t dsep,
                          const uint8_t *sec0, const uint8_t *sec1, size_t slen,
                          const uint8_t *pub, size_t plen)
{
    sponge_t *s = &sp_ws;
    size_t total = slen + plen, done = 0;
    s->sec[0] = sec0; s->sec[1] = sec1; s->pub = pub; s->slen = slen; s->plen = plen;
    s->out[0] = out0; s->out[1] = out1; s->rate = rate; s->dsep = dsep;
    RUN2(sp_zero, s);
    while (total - done >= rate) {
        s->from = done; s->to = done + rate; s->pos = 0;
        RUN2(sp_absorb, s);
        masked_keccak_f1600(s->s[0], s->s[1]);
        done += rate;
    }
    s->from = done; s->to = total; s->pos = 0;
    RUN2(sp_absorb, s);
    s->pos = total - done;
    RUN2(sp_pad, s);
    masked_keccak_f1600(s->s[0], s->s[1]);
    for (done = 0; done < outlen; ) {
        size_t n = outlen - done < rate ? outlen - done : rate;
        s->from = done; s->to = done + n; s->pos = 0;
        RUN2(sp_squeeze, s);
        done += n;
        if (done < outlen) masked_keccak_f1600(s->s[0], s->s[1]);
    }
}

/* ------------------------------------------------------------------ key handling */
void msk_init(msk_t *k, const uint8_t sk[KYBER_SECRETKEYBYTES])
{   /* one-time sharing of the long-term key (outside the attacked operation) */
    unsigned i, j;
    polyvec s;
    polyvec_frombytes(&s, sk);
    for (i = 0; i < KYBER_K; i++)
        for (j = 0; j < KYBER_N; j++) {
            uint32_t v = (uint16_t)s.vec[i].coeffs[j], r = mrandq();
            if ((int16_t)v < 0) v += Q;
            v %= Q;
            k->s1[i].coeffs[j] = (int16_t)r;
            k->s0[i].coeffs[j] = (int16_t)subq(v, r);
        }
    k->pk = sk + KYBER_INDCPA_SECRETKEYBYTES;
    memcpy(k->h, sk + KYBER_SECRETKEYBYTES - 2 * KYBER_SYMBYTES, 32);
    for (i = 0; i < 32; i++) {
        uint8_t r = (uint8_t)MRND();
        k->z1[i] = r;
        k->z0[i] = sk[KYBER_SECRETKEYBYTES - KYBER_SYMBYTES + i] ^ r;
    }
    memset(&s, 0, sizeof s);
}
/* fresh masks for the stored key before every decapsulation */
typedef struct { msk_t *k; uint16_t r[KYBER_K * KYBER_N]; uint8_t rz[32]; unsigned sh; } refresh_t;
static NI void k_refresh(refresh_t *s)
{
    unsigned i, j;
    poly *p = s->sh ? s->k->s1 : s->k->s0;
    uint8_t *z = s->sh ? s->k->z1 : s->k->z0;
    for (i = 0; i < KYBER_K; i++)
        for (j = 0; j < KYBER_N; j++) {
            uint32_t r = s->r[i * KYBER_N + j], c = (uint16_t)p[i].coeffs[j];
            p[i].coeffs[j] = (int16_t)(s->sh ? subq(c, r) : addq(c, r));
        }
    for (i = 0; i < 32; i++) z[i] ^= s->rz[i];
}

/* ------------------------------------------------------------------ decapsulation */
static struct {
    polyvec b, at[KYBER_K], pkpv, sp[2], ep[2], u[2];
    poly v, w[2], epp[2], vv[2], mm[2];
    uint8_t m[2][32], g[2][64], j[2][32];
    uint32_t acc[2], na[2], nd[2], t[2];
    cmp32_t c32; cmp64_t c64; refresh_t rf;
    msk_t *k;
    unsigned sh, idx, i, sft;
} D;

static NI void k_dec_mul(void *unused)
{   /* w_sh = INTT(s_sh o NTT(u)) for one share */
    (void)unused;
    unsigned sh = D.sh;
    ise_polyvec_basemul_acc(&D.w[sh], sh ? (const polyvec *)D.k->s1 : (const polyvec *)D.k->s0, &D.b);
    ise_invntt(D.w[sh].coeffs);
}
static NI void k_dec_sub(void *unused)
{   /* w = v - w: share 0 gets v - w0, share 1 gets -w1 */
    (void)unused;
    unsigned j, sh = D.sh;
    for (j = 0; j < KYBER_N; j++) {
        uint32_t wj = (uint16_t)D.w[sh].coeffs[j];
        uint32_t vj = sh ? 0 : (uint16_t)((D.v.coeffs[j] % Q + Q) % Q);   /* public */
        D.w[sh].coeffs[j] = (int16_t)subq(vj, wj);
    }
}
static NI void k_clear_m(void *unused) { (void)unused; memset(D.m[D.sh], 0, 32); }
static NI void k_reenc_mul(void *unused)
{   /* NTT of the noise and the products of the re-encryption, one share */
    (void)unused;
    unsigned i, sh = D.sh;
    for (i = 0; i < KYBER_K; i++) ise_ntt(D.sp[sh].vec[i].coeffs);
    for (i = 0; i < KYBER_K; i++) {
        ise_polyvec_basemul_acc(&D.u[sh].vec[i], &D.at[i], &D.sp[sh]);
        ise_invntt(D.u[sh].vec[i].coeffs);
        poly *u = &D.u[sh].vec[i], *e = &D.ep[sh].vec[i];
        unsigned j;
        for (j = 0; j < KYBER_N; j++) u->coeffs[j] = (int16_t)addq((uint16_t)u->coeffs[j], (uint16_t)e->coeffs[j]);
    }
    ise_polyvec_basemul_acc(&D.vv[sh], &D.pkpv, &D.sp[sh]);
    ise_invntt(D.vv[sh].coeffs);
}
static NI void k_msg(void *unused)
{   /* vv_sh += epp_sh + 1665 * m_sh (Decompress_1 of the B2A'd message bits) */
    (void)unused;
    unsigned j, sh = D.sh;
    const uint16_t *x = sh ? b2a_ws.x1 : b2a_ws.x0;
    for (j = 0; j < KYBER_N; j++) {
        uint32_t c = addq((uint16_t)D.vv[sh].coeffs[j], (uint16_t)D.epp[sh].coeffs[j]);
        D.vv[sh].coeffs[j] = (int16_t)addq(c, redq((uint32_t)x[j] * 1665u));
    }
}
/* masked OR: acc |= d with d = (c0 ^ pubc, c1) = ~(~acc & ~d); the operands
 * are prepared by the compression's post kernel (mode 2) or by k_or_fold */
static NI void k_or_fold(void *unused)
{   /* final OR-reduction of the accumulator: d = acc >> sft */
    (void)unused;
    unsigned sh = D.sh;
    uint32_t d = D.acc[sh] >> D.sft;
    D.na[sh] = sh ? D.acc[1] : ~D.acc[0];
    D.nd[sh] = sh ? d : ~d;
}
static NI void k_or_post(void *unused)
{
    (void)unused;
    D.acc[D.sh] = D.sh ? D.t[1] : ~D.t[0];
}
#define RUND(fn) do { D.sh = 0; share_run((void (*)(void *))(fn), 0, KCLR); \
                      D.sh = 1; share_run((void (*)(void *))(fn), 0, KCLR); } while (0)
#define RUND_BIG(fn) do { D.sh = 0; share_run((void (*)(void *))(fn), 0, 128); \
                          D.sh = 1; share_run((void (*)(void *))(fn), 0, 128); } while (0)
static void acc_or_step(void) { and32(D.t, D.na, D.nd); RUND(k_or_post); }
/* the pass/fail bit, still shared: t_sh = acc_sh & 1 (the higher accumulator bits hold
 * partial ORs of the comparison and must stay masked) */
static NI void k_acc_bit(void *unused) { (void)unused; D.t[D.sh] = D.acc[D.sh] & 1u; }

/* masked decapsulation; returns the unmasked pass/fail bit (1 = rejected) */
int masked_dec(uint8_t ss[KYBER_SSBYTES], const uint8_t ct[KYBER_CIPHERTEXTBYTES], msk_t *k)
{
    unsigned i, j;
    uint8_t nonce = 0;

    D.k = k;
    /* ---- fresh masks for the stored key ---- */
    D.rf.k = k;
    for (i = 0; i < KYBER_K * KYBER_N; i++) D.rf.r[i] = (uint16_t)mrandq();
    for (i = 0; i < 32; i++) D.rf.rz[i] = (uint8_t)MRND();
    D.rf.sh = 0; share_run((void (*)(void *))k_refresh, &D.rf, KCLR);
    D.rf.sh = 1; share_run((void (*)(void *))k_refresh, &D.rf, KCLR);
    /* ---- masked IND-CPA decryption: w = v - INTT(s_hat o NTT(u)) ---- */
    polyvec_decompress(&D.b, ct);                                  /* public */
    poly_decompress(&D.v, ct + KYBER_POLYVECCOMPRESSEDBYTES);
    for (i = 0; i < KYBER_K; i++) ise_ntt(D.b.vec[i].coeffs);
    RUND_BIG(k_dec_mul);
    RUND(k_dec_sub);
    /* ---- masked decoding to message bits ---- */
    RUND(k_clear_m);
    D.c32.mode = 1; D.c32.dst[0] = D.m[0]; D.c32.dst[1] = D.m[1];
    for (D.idx = 0; D.idx < KYBER_N; D.idx++) {
        D.c32.src[0] = (const uint16_t *)&D.w[0].coeffs[D.idx];
        D.c32.src[1] = (const uint16_t *)&D.w[1].coeffs[D.idx];
        D.c32.dbit = D.idx;
        compress32(&D.c32, 1, 20, 315u);
    }
    /* ---- (K', r) = G(m || H(pk)) ---- */
    masked_sponge(D.g[0], D.g[1], 64, SHA3_512_RATE, 0x06, D.m[0], D.m[1], 32, k->h, 32);
    /* ---- masked re-encryption ---- */
    polyvec_frombytes(&D.pkpv, k->pk);                             /* public */
    gen_matrix(D.at, k->pk + KYBER_POLYVECBYTES, 1);
    {
        static uint8_t o0[KYBER_ETA1 * KYBER_N / 4], o1[KYBER_ETA1 * KYBER_N / 4];
        for (i = 0; i < KYBER_K; i++) {
            masked_sponge(o0, o1, KYBER_ETA1 * KYBER_N / 4, SHAKE256_RATE, 0x1F, D.g[0] + 32, D.g[1] + 32, 32, &nonce, 1);
            nonce++;
            masked_cbd_n(D.sp[0].vec[i].coeffs, D.sp[1].vec[i].coeffs, o0, o1, KYBER_N, KYBER_ETA1);
        }
        for (i = 0; i < KYBER_K; i++) {
            masked_sponge(o0, o1, KYBER_ETA2 * KYBER_N / 4, SHAKE256_RATE, 0x1F, D.g[0] + 32, D.g[1] + 32, 32, &nonce, 1);
            nonce++;
            masked_cbd_n(D.ep[0].vec[i].coeffs, D.ep[1].vec[i].coeffs, o0, o1, KYBER_N, KYBER_ETA2);
        }
        masked_sponge(o0, o1, KYBER_ETA2 * KYBER_N / 4, SHAKE256_RATE, 0x1F, D.g[0] + 32, D.g[1] + 32, 32, &nonce, 1);
        nonce++;
        masked_cbd_n(D.epp[0].coeffs, D.epp[1].coeffs, o0, o1, KYBER_N, KYBER_ETA2);
    }
    RUND_BIG(k_reenc_mul);
    b2a_bits(&b2a_ws, D.m[0], D.m[1], 0, KYBER_N);                 /* Decompress_1(m) */
    RUND(k_msg);
    /* ---- masked compression + comparison with the public ciphertext ---- */
    D.acc[0] = 0; D.acc[1] = 0;
    D.c64.mode = 2; D.c64.acc = D.acc; D.c64.na = D.na; D.c64.nd = D.nd;
    D.c32.mode = 2; D.c32.acc = D.acc; D.c32.na = D.na; D.c32.nd = D.nd;
    for (D.i = 0; D.i < KYBER_K; D.i++)
        for (D.idx = 0; D.idx < KYBER_N; D.idx++) {
            unsigned bit = 10 * (KYBER_N * D.i + D.idx), byte = bit >> 3, sh = bit & 7;
            D.c64.pubc = ((uint32_t)ct[byte] | ((uint32_t)ct[byte + 1] << 8) | ((uint32_t)ct[byte + 2] << 16)) >> sh & 0x3FFu;
            D.c64.src[0] = (const uint16_t *)&D.u[0].vec[D.i].coeffs[D.idx];
            D.c64.src[1] = (const uint16_t *)&D.u[1].vec[D.i].coeffs[D.idx];
            compress64(&D.c64, 10, 33, 2580335ull);
            acc_or_step();
        }
    for (D.idx = 0; D.idx < KYBER_N; D.idx++) {
        D.c32.pubc = (ct[KYBER_POLYVECCOMPRESSEDBYTES + (D.idx >> 1)] >> (4 * (D.idx & 1))) & 0xFu;
        D.c32.src[0] = (const uint16_t *)&D.vv[0].coeffs[D.idx];
        D.c32.src[1] = (const uint16_t *)&D.vv[1].coeffs[D.idx];
        compress32(&D.c32, 4, 26, 20159u);
        acc_or_step();
    }
    for (D.sft = 16; D.sft; D.sft >>= 1) { RUND(k_or_fold); acc_or_step(); }
    {
        int fail;
        RUND(k_acc_bit);
        fail = (int)(D.t[0] ^ D.t[1]);                             /* the only unmasked intermediate */
        uint32_t sel = 0u - (uint32_t)fail;
        masked_sponge(D.j[0], D.j[1], 32, SHAKE256_RATE, 0x1F, k->z0, k->z1, 32, ct, KYBER_CIPHERTEXTBYTES);
        for (j = 0; j < 32; j++)
            ss[j] = (uint8_t)(((D.j[0][j] ^ D.j[1][j]) & sel) | ((D.g[0][j] ^ D.g[1][j]) & ~sel));
        return fail;
    }
}

#ifdef TVLA_API
/* entry points for the leakage-assessment firmware (sw/fw/tvla.c) */
static cmp32_t tv_c;
typedef struct { uint32_t *b[2]; unsigned sh; } tvdec_t;
static NI void tv_clr(tvdec_t *s) { *s->b[s->sh] = 0; }
void tv_decode(const uint16_t *w0, const uint16_t *w1, unsigned n, uint32_t *b0, uint32_t *b1)
{
    static tvdec_t s;
    unsigned j;
    s.b[0] = b0; s.b[1] = b1;
    RUN2(tv_clr, &s);
    tv_c.mode = 1; tv_c.dst[0] = (uint8_t *)b0; tv_c.dst[1] = (uint8_t *)b1;
    for (j = 0; j < n; j++) {
        tv_c.src[0] = &w0[j]; tv_c.src[1] = &w1[j]; tv_c.dbit = j;
        compress32(&tv_c, 1, 20, 315u);
    }
}
void tv_cbd(const uint8_t *b0, const uint8_t *b1, unsigned n, unsigned eta, uint16_t *x0, uint16_t *x1)
{
    masked_cbd_n((int16_t *)x0, (int16_t *)x1, b0, b1, n, eta);
}
/* the same Keccak rounds without masking (for the unmasked reference traces) */
void tv_keccak_plain(uint64_t a[25], unsigned nr)
{
    uint64_t b[25];
    unsigned r, x, y;
    for (r = 0; r < nr; r++) {
        lin(a, b);
        for (y = 0; y < 25; y += 5)
            for (x = 0; x < 5; x++)
                a[x + y] = b[x + y] ^ (~b[(x + 1) % 5 + y] & b[(x + 2) % 5 + y]);
        a[0] ^= RC[r];
    }
}
/* ---- further gadgets of the decapsulation (TVLA targets 6 to 9) ---- */
/* masked compress_10 of n coefficients, each followed by one step of the masked
 * OR accumulation of the re-encryption check against the public value pubc */
static uint32_t *tv_out;
static NI void tv_acc_out(void *unused) { (void)unused; tv_out[D.sh] = D.acc[D.sh]; }   /* one share per kernel */
static NI void tv_acc_in(void *unused) { (void)unused; D.acc[D.sh] = tv_out[D.sh]; }
void tv_cmp10(const uint16_t *w0, const uint16_t *w1, unsigned n, uint32_t pubc, uint32_t acc[2])
{
    tv_out = acc; RUND(tv_acc_in);
    D.c64.mode = 2; D.c64.acc = D.acc; D.c64.na = D.na; D.c64.nd = D.nd;
    for (D.idx = 0; D.idx < n; D.idx++) {
        D.c64.pubc = pubc;
        D.c64.src[0] = &w0[D.idx]; D.c64.src[1] = &w1[D.idx];
        compress64(&D.c64, 10, 33, 2580335ull);
        acc_or_step();
    }
    tv_out = acc; RUND(tv_acc_out);
}
/* masked compress_4 + OR step for n coefficients, then the final OR folding of
 * the accumulator (everything up to the single unmasked pass/fail bit) */
void tv_cmp4(const uint16_t *w0, const uint16_t *w1, unsigned n, uint32_t pubc, uint32_t acc[2])
{
    tv_out = acc; RUND(tv_acc_in);
    D.c32.mode = 2; D.c32.acc = D.acc; D.c32.na = D.na; D.c32.nd = D.nd;
    for (D.idx = 0; D.idx < n; D.idx++) {
        D.c32.pubc = pubc;
        D.c32.src[0] = &w0[D.idx]; D.c32.src[1] = &w1[D.idx];
        compress32(&D.c32, 4, 26, 20159u);
        acc_or_step();
    }
    for (D.sft = 16; D.sft; D.sft >>= 1) { RUND(k_or_fold); acc_or_step(); }
    tv_out = acc; RUND(tv_acc_out);
}
/* masked sponge G(m || h): 32 secret bytes, 32 public bytes, 64 output bytes
 * (the permutation runs masked_keccak_nr rounds, set by the caller) */
void tv_sponge(uint8_t out0[64], uint8_t out1[64], const uint8_t m0[32], const uint8_t m1[32], const uint8_t h[32])
{
    masked_sponge(out0, out1, 64, SHA3_512_RATE, 0x06, m0, m1, 32, h, 32);
}
/* share-wise base multiplication on the Kyber ISE (the kernel of k_dec_mul):
 * share 0 then share 1 run through share_run, so the state the ISE keeps
 * between instructions (operand, slot and multiplier registers) passes from
 * one share's kernel to the other's */
extern const uint16_t ise_bmzetas[128];
typedef struct { const uint32_t *s[2]; const uint32_t *u; uint32_t *r[2]; unsigned n, sh; } tvbm_t;
static NI void tv_bm_k(tvbm_t *t)
{
    unsigned i;
    const uint32_t *s = t->s[t->sh];
    uint32_t *r = t->r[t->sh];
    for (i = 0; i < t->n; i++) {
        uint32_t acc, x;
        KZETA((uint32_t)ise_bmzetas[i]);
        KBMUL(acc, s[i], t->u[i]);
        KBMUL(x, s[128 + i], t->u[128 + i]);
        KADDQ(acc, acc, x);
        r[i] = acc;
    }
}
void tv_basemul(const uint32_t *s0, const uint32_t *s1, const uint32_t *u, unsigned n, uint32_t *r0, uint32_t *r1)
{
    static tvbm_t t;
    t.s[0] = s0; t.s[1] = s1; t.u = u; t.r[0] = r0; t.r[1] = r1; t.n = n;
    RUN2(tv_bm_k, &t);
}
#endif

