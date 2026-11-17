/*
 * masked.c : first-order (2-share) masked ML-KEM-512 decapsulation for
 * PicoRV32 + kyber_ise (+ keccak_ise for the public hashing).
 *
 * Sharing                                      used for
 *   arithmetic mod q   x = x0 + x1 mod q        s_hat, decryption, re-encryption
 *   Boolean            x = x0 ^ x1              message, coins, Keccak states, z,
 *                                               compressed coefficients
 *   arithmetic mod 2^k (transient)              compression / decoding
 *
 * Gadgets (first order)
 *   sec_and   : ISW/Trichina AND with one fresh random word
 *   sec_add   : Kogge-Stone adder on Boolean shares built from sec_and
 *               (Coron, Grossschaedl, Tibouchi, Vadnala, FSE 2015)
 *   compress  : shares mod q -> refreshed shares mod 2^k -> exact multiply-shift
 *               (constants verified exhaustively over [0, 2q)) -> sec_add -> bits
 *   b2a_bit   : one Boolean-masked bit -> arithmetic shares mod q
 *   masked Keccak-f[1600] : linear layers per share, chi with sec_and
 *
 * The final re-encryption check is computed as a masked OR over all
 * coefficient differences; only that single pass/fail bit is unmasked (as in
 * Bos et al., TCHES 2021(4), and Heinz et al., TCHES 2022(2)), and the shared
 * secret is unmasked when it leaves the function.
 * Randomness: xoshiro128** seeded by masked_seed() as a stand-in for a TRNG.
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

/* ------------------------------------------------------------------ randomness */
static uint32_t xs[4] = {0x9e3779b9u, 0x243f6a88u, 0xb7e15162u, 0x8aed2a6bu};
static inline uint32_t rotl32(uint32_t x, int k) { return (x << k) | (x >> (32 - k)); }
#if defined(MASK_ZERO)
/* control experiment for the leakage assessment: all masks zero (no masking) */
uint32_t mrand32(void) { return 0; }
void masked_seed(uint32_t s) { (void)s; }
#elif defined(MASK_HW_RNG) && !defined(ISE_NATIVE_EMU)
/* hardware masking PRNG in kyber_ise (krng): one custom instruction per word */
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
static inline uint64_t mrand64(void) { return ((uint64_t)mrand32() << 32) | mrand32(); }
/* uniform mod q by multiply-shift (constant time; bias < q / 2^32) */
static inline uint16_t mrandq(void) { return (uint16_t)(((uint64_t)mrand32() * Q) >> 32); }


/* ------------------------------------------------------------------ gadgets */
/* Optimisation barrier: hides a value from the compiler so that it cannot
 * re-associate share computations (e.g. rewrite (a0 & b) ^ (a1 & b) as
 * (a0 ^ a1) & b, which would recombine the shares). */
#if defined(__GNUC__)
#define OPQ(v) __asm__ volatile("" : "+r"(v))
#else
#define OPQ(v) ((void)0)
#endif
static inline void sec_and32(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1, uint32_t *z0, uint32_t *z1)
{
    uint32_t r = mrand32(), u, t, a, b;
    OPQ(x0); OPQ(x1); OPQ(y0); OPQ(y1); OPQ(r);
    u = x0 & y1; OPQ(u);
    t = r ^ u;   OPQ(t);
    u = x1 & y0; OPQ(u);
    t = t ^ u;   OPQ(t);
    a = x0 & y0; OPQ(a);
    a = a ^ r;   OPQ(a);
    b = x1 & y1; OPQ(b);
    b = b ^ t;   OPQ(b);
    *z0 = a; *z1 = b;
}
static inline void sec_and64(uint64_t x0, uint64_t x1, uint64_t y0, uint64_t y1, uint64_t *z0, uint64_t *z1)
{
    uint32_t l0, l1, h0, h1;
    sec_and32((uint32_t)x0, (uint32_t)x1, (uint32_t)y0, (uint32_t)y1, &l0, &l1);
    sec_and32((uint32_t)(x0 >> 32), (uint32_t)(x1 >> 32), (uint32_t)(y0 >> 32), (uint32_t)(y1 >> 32), &h0, &h1);
    *z0 = ((uint64_t)h0 << 32) | l0;
    *z1 = ((uint64_t)h1 << 32) | l1;
}
/* (z0 ^ z1) = (x0 ^ x1) + (y0 ^ y1) mod 2^k, Kogge-Stone */
static void sec_add32(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1, uint32_t *z0, uint32_t *z1, unsigned k)
{
    uint32_t p0 = x0 ^ y0, p1 = x1 ^ y1, g0, g1, h0, h1, u0, u1;
    unsigned i;
    sec_and32(x0, x1, y0, y1, &g0, &g1);
    for (i = 1; i < k; i <<= 1) {
        h0 = g0 << i; h1 = g1 << i;
        sec_and32(p0, p1, h0, h1, &u0, &u1);
        g0 ^= u0; g1 ^= u1;
        if ((i << 1) < k) {
            h0 = p0 << i; h1 = p1 << i;
            sec_and32(p0, p1, h0, h1, &p0, &p1);
        }
    }
    *z0 = x0 ^ y0 ^ (g0 << 1);
    *z1 = x1 ^ y1 ^ (g1 << 1);
}
static void sec_add64(uint64_t x0, uint64_t x1, uint64_t y0, uint64_t y1, uint64_t *z0, uint64_t *z1, unsigned k)
{
    uint64_t p0 = x0 ^ y0, p1 = x1 ^ y1, g0, g1, h0, h1, u0, u1;
    unsigned i;
    sec_and64(x0, x1, y0, y1, &g0, &g1);
    for (i = 1; i < k; i <<= 1) {
        h0 = g0 << i; h1 = g1 << i;
        sec_and64(p0, p1, h0, h1, &u0, &u1);
        g0 ^= u0; g1 ^= u1;
        if ((i << 1) < k) {
            h0 = p0 << i; h1 = p1 << i;
            sec_and64(p0, p1, h0, h1, &p0, &p1);
        }
    }
    *z0 = x0 ^ y0 ^ (g0 << 1);
    *z1 = x1 ^ y1 ^ (g1 << 1);
}

/* compress_d(a0 + a1 mod q) = floor((x 2^d + 1664) / q) mod 2^d as Boolean shares.
 * y = a0 + a1 in [0, 2q) gives the same value mod 2^d; floor(.. / q) is the exact
 * multiply-shift ((y 2^d + 1664) * M) >> S (see analysis/masked_constants.py). */
static void compress32(uint16_t a0, uint16_t a1, unsigned d, unsigned S, uint32_t M, uint32_t *c0, uint32_t *c1)
{
    uint32_t R = mrand32(), r1 = mrand32(), r2 = mrand32(), s0, s1;
    uint32_t A0 = (uint32_t)a0 + R, A1 = (uint32_t)a1 - R;               /* shares mod 2^32 */
    uint32_t Z0 = ((A0 << d) + 1664u) * M, Z1 = (A1 << d) * M;
    sec_add32(Z0 ^ r1, r1, r2, Z1 ^ r2, &s0, &s1, S + d);
    *c0 = (s0 >> S) & ((1u << d) - 1u);
    *c1 = (s1 >> S) & ((1u << d) - 1u);
}
static void compress64(uint16_t a0, uint16_t a1, unsigned d, unsigned S, uint64_t M, uint32_t *c0, uint32_t *c1)
{
    uint64_t R = mrand64(), r1 = mrand64(), r2 = mrand64(), s0, s1;
    uint64_t A0 = (uint64_t)a0 + R, A1 = (uint64_t)a1 - R;
    uint64_t Z0 = ((A0 << d) + 1664u) * M, Z1 = (A1 << d) * M;
    sec_add64(Z0 ^ r1, r1, r2, Z1 ^ r2, &s0, &s1, S + d);
    *c0 = (uint32_t)(s0 >> S) & ((1u << d) - 1u);
    *c1 = (uint32_t)(s1 >> S) & ((1u << d) - 1u);
}

/* one Boolean-masked bit b0 ^ b1 -> arithmetic shares mod q:
 * x = b1 + (1 - 2 b1) b0, with b0 first arithmetically masked by r0 */
static inline void b2a_bit(uint32_t b0, uint32_t b1, uint16_t *x0, uint16_t *x1)
{
    uint32_t r0 = mrandq(), r = mrandq();
    uint32_t a0 = (b0 + r0) % Q, a1 = (Q - r0) % Q;     /* a0 + a1 = b0 (mod q), canonical */
    uint32_t m = 0u - (b1 & 1u);                         /* all ones if b1 = 1 (branch-free) */
    uint32_t n0 = (Q - a0) % Q, n1 = (Q - a1) % Q;       /* -a0, -a1 mod q */
    uint32_t t0 = (b1 + ((n0 & m) | (a0 & ~m))) % Q;     /* b1 + (1 - 2 b1) a0 */
    uint32_t t1 = (n1 & m) | (a1 & ~m);                  /* (1 - 2 b1) a1      */
    t0 = (t0 + r) % Q;                                   /* refresh */
    t1 = (t1 + Q - r) % Q;
    *x0 = (uint16_t)t0; *x1 = (uint16_t)t1;
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
static void lin(const uint64_t *A, uint64_t *B)
{
    uint64_t c0 = A[0] ^ A[5] ^ A[10] ^ A[15] ^ A[20], c1 = A[1] ^ A[6] ^ A[11] ^ A[16] ^ A[21];
    uint64_t c2 = A[2] ^ A[7] ^ A[12] ^ A[17] ^ A[22], c3 = A[3] ^ A[8] ^ A[13] ^ A[18] ^ A[23];
    uint64_t c4 = A[4] ^ A[9] ^ A[14] ^ A[19] ^ A[24];
    uint64_t d0 = c4 ^ ROL(c1, 1), d1 = c0 ^ ROL(c2, 1), d2 = c1 ^ ROL(c3, 1), d3 = c2 ^ ROL(c4, 1), d4 = c3 ^ ROL(c0, 1);
    B[0] = ROL(A[0] ^ d0, 0);
    B[16] = ROL(A[5] ^ d0, 36);
    B[7] = ROL(A[10] ^ d0, 3);
    B[23] = ROL(A[15] ^ d0, 41);
    B[14] = ROL(A[20] ^ d0, 18);
    B[10] = ROL(A[1] ^ d1, 1);
    B[1] = ROL(A[6] ^ d1, 44);
    B[17] = ROL(A[11] ^ d1, 10);
    B[8] = ROL(A[16] ^ d1, 45);
    B[24] = ROL(A[21] ^ d1, 2);
    B[20] = ROL(A[2] ^ d2, 62);
    B[11] = ROL(A[7] ^ d2, 6);
    B[2] = ROL(A[12] ^ d2, 43);
    B[18] = ROL(A[17] ^ d2, 15);
    B[9] = ROL(A[22] ^ d2, 61);
    B[5] = ROL(A[3] ^ d3, 28);
    B[21] = ROL(A[8] ^ d3, 55);
    B[12] = ROL(A[13] ^ d3, 25);
    B[3] = ROL(A[18] ^ d3, 21);
    B[19] = ROL(A[23] ^ d3, 56);
    B[15] = ROL(A[4] ^ d4, 27);
    B[6] = ROL(A[9] ^ d4, 20);
    B[22] = ROL(A[14] ^ d4, 39);
    B[13] = ROL(A[19] ^ d4, 8);
    B[4] = ROL(A[24] ^ d4, 14);
}
unsigned masked_keccak_nr = 24;     /* reduced only by the TVLA firmware */
void masked_keccak_f1600(uint64_t a0[25], uint64_t a1[25])
{
    uint64_t b0[25], b1[25], t0, t1;
    unsigned r;
    for (r = 0; r < masked_keccak_nr; r++) {
        lin(a0, b0);
        lin(a1, b1);
        sec_and64(~b0[1], b1[1], b0[2], b1[2], &t0, &t1); a0[0] = b0[0] ^ t0; a1[0] = b1[0] ^ t1;
        sec_and64(~b0[2], b1[2], b0[3], b1[3], &t0, &t1); a0[1] = b0[1] ^ t0; a1[1] = b1[1] ^ t1;
        sec_and64(~b0[3], b1[3], b0[4], b1[4], &t0, &t1); a0[2] = b0[2] ^ t0; a1[2] = b1[2] ^ t1;
        sec_and64(~b0[4], b1[4], b0[0], b1[0], &t0, &t1); a0[3] = b0[3] ^ t0; a1[3] = b1[3] ^ t1;
        sec_and64(~b0[0], b1[0], b0[1], b1[1], &t0, &t1); a0[4] = b0[4] ^ t0; a1[4] = b1[4] ^ t1;
        sec_and64(~b0[6], b1[6], b0[7], b1[7], &t0, &t1); a0[5] = b0[5] ^ t0; a1[5] = b1[5] ^ t1;
        sec_and64(~b0[7], b1[7], b0[8], b1[8], &t0, &t1); a0[6] = b0[6] ^ t0; a1[6] = b1[6] ^ t1;
        sec_and64(~b0[8], b1[8], b0[9], b1[9], &t0, &t1); a0[7] = b0[7] ^ t0; a1[7] = b1[7] ^ t1;
        sec_and64(~b0[9], b1[9], b0[5], b1[5], &t0, &t1); a0[8] = b0[8] ^ t0; a1[8] = b1[8] ^ t1;
        sec_and64(~b0[5], b1[5], b0[6], b1[6], &t0, &t1); a0[9] = b0[9] ^ t0; a1[9] = b1[9] ^ t1;
        sec_and64(~b0[11], b1[11], b0[12], b1[12], &t0, &t1); a0[10] = b0[10] ^ t0; a1[10] = b1[10] ^ t1;
        sec_and64(~b0[12], b1[12], b0[13], b1[13], &t0, &t1); a0[11] = b0[11] ^ t0; a1[11] = b1[11] ^ t1;
        sec_and64(~b0[13], b1[13], b0[14], b1[14], &t0, &t1); a0[12] = b0[12] ^ t0; a1[12] = b1[12] ^ t1;
        sec_and64(~b0[14], b1[14], b0[10], b1[10], &t0, &t1); a0[13] = b0[13] ^ t0; a1[13] = b1[13] ^ t1;
        sec_and64(~b0[10], b1[10], b0[11], b1[11], &t0, &t1); a0[14] = b0[14] ^ t0; a1[14] = b1[14] ^ t1;
        sec_and64(~b0[16], b1[16], b0[17], b1[17], &t0, &t1); a0[15] = b0[15] ^ t0; a1[15] = b1[15] ^ t1;
        sec_and64(~b0[17], b1[17], b0[18], b1[18], &t0, &t1); a0[16] = b0[16] ^ t0; a1[16] = b1[16] ^ t1;
        sec_and64(~b0[18], b1[18], b0[19], b1[19], &t0, &t1); a0[17] = b0[17] ^ t0; a1[17] = b1[17] ^ t1;
        sec_and64(~b0[19], b1[19], b0[15], b1[15], &t0, &t1); a0[18] = b0[18] ^ t0; a1[18] = b1[18] ^ t1;
        sec_and64(~b0[15], b1[15], b0[16], b1[16], &t0, &t1); a0[19] = b0[19] ^ t0; a1[19] = b1[19] ^ t1;
        sec_and64(~b0[21], b1[21], b0[22], b1[22], &t0, &t1); a0[20] = b0[20] ^ t0; a1[20] = b1[20] ^ t1;
        sec_and64(~b0[22], b1[22], b0[23], b1[23], &t0, &t1); a0[21] = b0[21] ^ t0; a1[21] = b1[21] ^ t1;
        sec_and64(~b0[23], b1[23], b0[24], b1[24], &t0, &t1); a0[22] = b0[22] ^ t0; a1[22] = b1[22] ^ t1;
        sec_and64(~b0[24], b1[24], b0[20], b1[20], &t0, &t1); a0[23] = b0[23] ^ t0; a1[23] = b1[23] ^ t1;
        sec_and64(~b0[20], b1[20], b0[21], b1[21], &t0, &t1); a0[24] = b0[24] ^ t0; a1[24] = b1[24] ^ t1;
        a0[0] ^= RC[r];
    }
}

/* masked sponge over a single absorbed input (in1 == NULL: public input part).
 * The input is given as up to two segments: (sec0/sec1, slen) secret-shared
 * followed by (pub, plen) public; output shares out0/out1. */
static void masked_sponge(uint8_t *out0, uint8_t *out1, size_t outlen, unsigned rate, uint8_t dsep,
                          const uint8_t *sec0, const uint8_t *sec1, size_t slen,
                          const uint8_t *pub, size_t plen)
{
    uint64_t s0[25], s1[25];
    size_t i, pos = 0, total = slen + plen;
    memset(s0, 0, sizeof s0); memset(s1, 0, sizeof s1);
    for (i = 0; i < total; i++) {
        uint8_t v0 = i < slen ? sec0[i] : pub[i - slen], v1 = i < slen ? sec1[i] : 0;
        s0[pos / 8] ^= (uint64_t)v0 << (8 * (pos % 8));
        s1[pos / 8] ^= (uint64_t)v1 << (8 * (pos % 8));
        if (++pos == rate) { masked_keccak_f1600(s0, s1); pos = 0; }
    }
    s0[pos / 8] ^= (uint64_t)dsep << (8 * (pos % 8));
    s0[(rate - 1) / 8] ^= 1ull << 63;
    masked_keccak_f1600(s0, s1);
    pos = 0;
    for (i = 0; i < outlen; i++) {
        if (pos == rate) { masked_keccak_f1600(s0, s1); pos = 0; }
        out0[i] = (uint8_t)(s0[pos / 8] >> (8 * (pos % 8)));
        out1[i] = (uint8_t)(s1[pos / 8] >> (8 * (pos % 8)));
        pos++;
    }
}

/* ------------------------------------------------------------------ arithmetic shares */
static inline uint16_t addq(uint32_t a, uint32_t b) { a += b; return (uint16_t)(a >= Q ? a - Q : a); }
static inline uint16_t subq(uint32_t a, uint32_t b) { return (uint16_t)(a >= b ? a - b : a + Q - b); }
static void poly_addq(poly *r, const poly *a, const poly *b)
{ unsigned i; for (i = 0; i < KYBER_N; i++) r->coeffs[i] = (int16_t)addq((uint16_t)a->coeffs[i], (uint16_t)b->coeffs[i]); }

/* masked CBD_eta from Boolean-masked bytes (bit stream, little endian) */
static void masked_cbd(poly *r0, poly *r1, const uint8_t *b0, const uint8_t *b1, unsigned eta)
{
    unsigned i, j;
    for (i = 0; i < KYBER_N; i++) {
        uint32_t s0 = 0, s1 = 0;
        for (j = 0; j < 2 * eta; j++) {
            unsigned bit = 2 * eta * i + j;
            uint16_t x0, x1;
            b2a_bit((b0[bit >> 3] >> (bit & 7)) & 1u, (b1[bit >> 3] >> (bit & 7)) & 1u, &x0, &x1);
            if (j < eta) { s0 = addq(s0, x0); s1 = addq(s1, x1); }
            else         { s0 = subq(s0, x0); s1 = subq(s1, x1); }
        }
        r0->coeffs[i] = (int16_t)s0; r1->coeffs[i] = (int16_t)s1;
    }
}
static void masked_noise(poly *r0, poly *r1, const uint8_t c0[32], const uint8_t c1[32], uint8_t nonce, unsigned eta)
{
    uint8_t o0[KYBER_ETA1 * KYBER_N / 4], o1[KYBER_ETA1 * KYBER_N / 4];
    masked_sponge(o0, o1, eta * KYBER_N / 4, SHAKE256_RATE, 0x1F, c0, c1, 32, &nonce, 1);
    masked_cbd(r0, r1, o0, o1, eta);
}

/* ------------------------------------------------------------------ key handling */
void msk_init(msk_t *k, const uint8_t sk[KYBER_SECRETKEYBYTES])
{
    unsigned i, j;
    polyvec s;
    polyvec_frombytes(&s, sk);
    for (i = 0; i < KYBER_K; i++)
        for (j = 0; j < KYBER_N; j++) {
            uint16_t v = (uint16_t)s.vec[i].coeffs[j], r = mrandq();
            if ((int16_t)v < 0) v += Q;
            v %= Q;
            k->s1[i].coeffs[j] = (int16_t)r;
            k->s0[i].coeffs[j] = (int16_t)subq(v, r);
        }
    k->pk = sk + KYBER_INDCPA_SECRETKEYBYTES;
    memcpy(k->h, sk + KYBER_SECRETKEYBYTES - 2 * KYBER_SYMBYTES, 32);
    for (i = 0; i < 32; i++) {
        uint8_t r = (uint8_t)mrand32();
        k->z1[i] = r;
        k->z0[i] = sk[KYBER_SECRETKEYBYTES - KYBER_SYMBYTES + i] ^ r;
    }
    memset(&s, 0, sizeof s);
}
static void msk_refresh(msk_t *k)
{
    unsigned i, j;
    for (i = 0; i < KYBER_K; i++)
        for (j = 0; j < KYBER_N; j++) {
            uint16_t r = mrandq();
            k->s0[i].coeffs[j] = (int16_t)addq((uint16_t)k->s0[i].coeffs[j], r);
            k->s1[i].coeffs[j] = (int16_t)subq((uint16_t)k->s1[i].coeffs[j], r);
        }
    for (i = 0; i < 32; i++) { uint8_t r = (uint8_t)mrand32(); k->z0[i] ^= r; k->z1[i] ^= r; }
}

/* masked OR accumulation of coefficient differences */
static inline void acc_or(uint32_t *a0, uint32_t *a1, uint32_t d0, uint32_t d1)
{   /* a | d = ~(~a & ~d) */
    uint32_t t0, t1;
    sec_and32(~*a0, *a1, ~d0, d1, &t0, &t1);
    *a0 = ~t0; *a1 = t1;
}

/* masked decapsulation; returns the unmasked pass/fail bit (1 = rejected) */
int masked_dec(uint8_t ss[KYBER_SSBYTES], const uint8_t ct[KYBER_CIPHERTEXTBYTES], msk_t *k)
{
    static polyvec b, s0h, s1h, at[KYBER_K], pkpv, sp0, sp1, ep0, ep1, u0, u1;
    static poly v, w0, w1, epp0, epp1, vv0, vv1, mm0, mm1;
    uint8_t m0[32], m1[32], g0[64], g1[64], j0[32], j1[32];
    uint32_t acc0 = 0, acc1 = 0, c0, c1, pubc;
    unsigned i, j;
    uint8_t nonce = 0;

    msk_refresh(k);
    /* ---- masked IND-CPA decryption: w = v - INTT(s_hat o NTT(u)) ---- */
    polyvec_decompress(&b, ct);
    poly_decompress(&v, ct + KYBER_POLYVECCOMPRESSEDBYTES);
    for (i = 0; i < KYBER_K; i++) ise_ntt(b.vec[i].coeffs);
    ise_polyvec_basemul_acc(&w0, (const polyvec *)k->s0, &b);
    ise_polyvec_basemul_acc(&w1, (const polyvec *)k->s1, &b);
    ise_invntt(w0.coeffs); ise_invntt(w1.coeffs);
    for (j = 0; j < KYBER_N; j++) {
        uint16_t vj = (uint16_t)((v.coeffs[j] % Q + Q) % Q);
        w0.coeffs[j] = (int16_t)subq(vj, (uint16_t)w0.coeffs[j]);
        w1.coeffs[j] = (int16_t)subq(0, (uint16_t)w1.coeffs[j]);
    }
    /* ---- masked decoding to message bits ---- */
    memset(m0, 0, 32); memset(m1, 0, 32);
    for (j = 0; j < KYBER_N; j++) {
        compress32((uint16_t)w0.coeffs[j], (uint16_t)w1.coeffs[j], 1, 20, 315u, &c0, &c1);
        m0[j >> 3] |= (uint8_t)(c0 << (j & 7));
        m1[j >> 3] |= (uint8_t)(c1 << (j & 7));
    }
    /* ---- (K', r) = G(m || H(pk)) ---- */
    masked_sponge(g0, g1, 64, SHA3_512_RATE, 0x06, m0, m1, 32, k->h, 32);
    /* ---- masked re-encryption ---- */
    polyvec_frombytes(&pkpv, k->pk);
    gen_matrix(at, k->pk + KYBER_POLYVECBYTES, 1);
    for (i = 0; i < KYBER_K; i++) masked_noise(&sp0.vec[i], &sp1.vec[i], g0 + 32, g1 + 32, nonce++, KYBER_ETA1);
    for (i = 0; i < KYBER_K; i++) masked_noise(&ep0.vec[i], &ep1.vec[i], g0 + 32, g1 + 32, nonce++, KYBER_ETA2);
    masked_noise(&epp0, &epp1, g0 + 32, g1 + 32, nonce++, KYBER_ETA2);
    for (i = 0; i < KYBER_K; i++) { ise_ntt(sp0.vec[i].coeffs); ise_ntt(sp1.vec[i].coeffs); }
    for (i = 0; i < KYBER_K; i++) {
        ise_polyvec_basemul_acc(&u0.vec[i], &at[i], &sp0);
        ise_polyvec_basemul_acc(&u1.vec[i], &at[i], &sp1);
        ise_invntt(u0.vec[i].coeffs); ise_invntt(u1.vec[i].coeffs);
        poly_addq(&u0.vec[i], &u0.vec[i], &ep0.vec[i]);
        poly_addq(&u1.vec[i], &u1.vec[i], &ep1.vec[i]);
    }
    ise_polyvec_basemul_acc(&vv0, &pkpv, &sp0);
    ise_polyvec_basemul_acc(&vv1, &pkpv, &sp1);
    ise_invntt(vv0.coeffs); ise_invntt(vv1.coeffs);
    for (j = 0; j < KYBER_N; j++) {                      /* Decompress_1(m) = 1665 m */
        uint16_t x0, x1;
        b2a_bit((m0[j >> 3] >> (j & 7)) & 1u, (m1[j >> 3] >> (j & 7)) & 1u, &x0, &x1);
        mm0.coeffs[j] = (int16_t)((uint32_t)x0 * 1665u % Q);
        mm1.coeffs[j] = (int16_t)((uint32_t)x1 * 1665u % Q);
    }
    poly_addq(&vv0, &vv0, &epp0); poly_addq(&vv1, &vv1, &epp1);
    poly_addq(&vv0, &vv0, &mm0);  poly_addq(&vv1, &vv1, &mm1);
    /* ---- masked compression + comparison with the public ciphertext ---- */
    for (i = 0; i < KYBER_K; i++)
        for (j = 0; j < KYBER_N; j++) {
            unsigned bit = 10 * (KYBER_N * i + j), byte = bit >> 3, sh = bit & 7;
            pubc = ((uint32_t)ct[byte] | ((uint32_t)ct[byte + 1] << 8) | ((uint32_t)ct[byte + 2] << 16)) >> sh & 0x3FFu;
            compress64((uint16_t)u0.vec[i].coeffs[j], (uint16_t)u1.vec[i].coeffs[j], 10, 33, 2580335ull, &c0, &c1);
            acc_or(&acc0, &acc1, c0 ^ pubc, c1);
        }
    for (j = 0; j < KYBER_N; j++) {
        pubc = (ct[KYBER_POLYVECCOMPRESSEDBYTES + (j >> 1)] >> (4 * (j & 1))) & 0xFu;
        compress32((uint16_t)vv0.coeffs[j], (uint16_t)vv1.coeffs[j], 4, 26, 20159u, &c0, &c1);
        acc_or(&acc0, &acc1, c0 ^ pubc, c1);
    }
    for (i = 16; i; i >>= 1) acc_or(&acc0, &acc1, acc0 >> i, acc1 >> i);
    {
        int fail = (int)((acc0 ^ acc1) & 1u);            /* the only unmasked intermediate */
        masked_sponge(j0, j1, 32, SHAKE256_RATE, 0x1F, k->z0, k->z1, 32, ct, KYBER_CIPHERTEXTBYTES);
        for (i = 0; i < 32; i++) ss[i] = fail ? (uint8_t)(j0[i] ^ j1[i]) : (uint8_t)(g0[i] ^ g1[i]);
        return fail;
    }
}

#ifdef TVLA_API
/* entry points for the leakage-assessment firmware (sw/fw/tvla.c) */
void tv_decode(const uint16_t *w0, const uint16_t *w1, unsigned n, uint32_t *b0, uint32_t *b1)
{
    unsigned j;
    uint32_t c0, c1;
    *b0 = *b1 = 0;
    for (j = 0; j < n; j++) {
        compress32(w0[j], w1[j], 1, 20, 315u, &c0, &c1);
        *b0 |= c0 << j; *b1 |= c1 << j;
    }
}
void tv_cbd(const uint8_t *b0, const uint8_t *b1, unsigned n, unsigned eta, uint16_t *x0, uint16_t *x1)
{
    unsigned i, j;
    for (i = 0; i < n; i++) {
        uint32_t s0 = 0, s1 = 0;
        for (j = 0; j < 2 * eta; j++) {
            unsigned bit = 2 * eta * i + j;
            uint16_t y0, y1;
            b2a_bit((b0[bit >> 3] >> (bit & 7)) & 1u, (b1[bit >> 3] >> (bit & 7)) & 1u, &y0, &y1);
            if (j < eta) { s0 = addq(s0, y0); s1 = addq(s1, y1); }
            else         { s0 = subq(s0, y0); s1 = subq(s1, y1); }
        }
        x0[i] = (uint16_t)s0; x1[i] = (uint16_t)s1;
    }
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
#endif
