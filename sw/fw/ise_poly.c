/*
 * ise_poly.c : ML-KEM polynomial arithmetic on the kyber_ise extension.
 *
 * Coefficients stay in the reference int16_t layout; two adjacent
 * coefficients form one 32-bit word, which is exactly the packed operand
 * format of the ISE, so plain lw/sw move butterfly operands.
 * All values handled here are canonical in [0, q) and in the plain
 * (non-Montgomery) domain, so poly_tomont() becomes the identity.
 */
#include <stdint.h>
#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include "ise.h"
#include "ise_tables.h"
#include "ise_poly.h"

volatile uint32_t ise_sw_shuffle = 0;   /* set by the mitigation controller */

/* lane-wise x + ((x >> 15) & q) without carry leaking across lanes */
static inline uint32_t canon2(uint32_t x)
{
    uint32_t m = (x >> 15) & 0x00010001u;
    return x + m * KYBER_Q - ((m & 1u) << 16);
}

void ise_ntt(int16_t r[256])
{
    uint32_t *w = (uint32_t *)r;
    unsigned len, start, j, k = 1;
    for (j = 0; j < 128; j++) w[j] = canon2(w[j]);

    if (!ise_sw_shuffle) {
        for (len = 64; len >= 1; len >>= 1) {
            for (start = 0; start < 128; start += 2 * len) {
                KZETA((uint32_t)ise_zetas[k++]);
                uint32_t *p = w + start, *e = w + start + len;
                for (; p < e; p++) {
                    uint32_t x, y;
                    KCT_A(x, p[0], p[len]);
                    KCT_B(y);
                    p[0] = x; p[len] = y;
                }
            }
        }
    } else {
        /* randomised butterfly order inside every group */
        for (len = 64; len >= 1; len >>= 1) {
            for (start = 0; start < 128; start += 2 * len) {
                uint32_t off;
                KZETA((uint32_t)ise_zetas[k++]);
                KRND(off);
                for (j = 0; j < len; j++) {
                    uint32_t i = start + ((j + off) & (len - 1));
                    uint32_t x, y;
                    KCT_A(x, w[i], w[i + len]);
                    KCT_B(y);
                    w[i] = x; w[i + len] = y;
                }
            }
        }
    }
}

void ise_invntt(int16_t r[256])
{
    uint32_t *w = (uint32_t *)r;
    unsigned len, start, j;
    int k = 127;
    for (len = 1; len <= 64; len <<= 1) {
        for (start = 0; start < 128; start += 2 * len) {
            uint32_t off = 0;
            KZETA((uint32_t)ise_izetas[k--]);
            if (ise_sw_shuffle) KRND(off);
            for (j = 0; j < len; j++) {
                uint32_t i = start + ((j + off) & (len - 1));
                uint32_t x, y;
                KGS_A(x, w[i], w[i + len]);
                KGS_B(y);
                w[i] = x; w[i + len] = y;
            }
        }
    }
    KZETA(3303u);                    /* 128^-1 mod q */
    for (j = 0; j < 128; j++) {
        uint32_t x;
        KMULZ(x, w[j]);
        w[j] = x;
    }
}

/* r = sum_i a[i] o b[i] in the NTT domain */
void ise_polyvec_basemul_acc(poly *r, const polyvec *a, const polyvec *b)
{
    uint32_t *rw = (uint32_t *)r->coeffs;
    unsigned i, k;
    for (i = 0; i < 128; i++) {
        uint32_t acc, t;
        KZETA((uint32_t)ise_bmzetas[i]);
        KBMUL(acc, ((const uint32_t *)a->vec[0].coeffs)[i],
                   ((const uint32_t *)b->vec[0].coeffs)[i]);
        for (k = 1; k < KYBER_K; k++) {
            KBMUL(t, ((const uint32_t *)a->vec[k].coeffs)[i],
                     ((const uint32_t *)b->vec[k].coeffs)[i]);
            KADDQ(acc, acc, t);
        }
        rw[i] = acc;
    }
}
