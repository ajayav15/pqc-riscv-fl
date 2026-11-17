/* First-order leakage assessment (fixed vs random) of the masking gadgets on the
 * RTL core: the testbench (-DLEAKTRACE) records the simulated leakage inside each
 * MARK 0x4C01 / 0x4C00 window; the class of every trace is printed ('0' fixed,
 * '1' random). Shares are freshly randomized for every trace, outside the window.
 *   TARGET 0  masked decoding of 8 coefficients     1  same, unmasked
 *          2  masked Keccak-f, 2 rounds              3  same, unmasked
 *          4  masked CBD (eta = 2), 8 coefficients   5  same, unmasked
 *          6  masked compress_10 + OR step of the re-encryption check (NDEC coefficients)
 *          7  masked compress_4 + OR step (NDEC coefficients) + final OR folding
 *          8  masked sponge G(m || h), KNR-round permutation
 *          9  share-wise ISE base multiplication, NBM coefficient pairs per share
 * (targets 6 to 9 exist for the hardened masking, masked.c, only)            */
#include <stdint.h>
#include <stddef.h>
#include "params.h"
#include "platform.h"
#include "masked.h"
#ifndef TARGET
#define TARGET 0
#endif
#ifndef NTR
#define NTR 4000
#endif
#ifndef NDEC
#define NDEC 8              /* coefficients decoded per trace (targets 0, 1) */
#endif
#ifndef NCBD
#define NCBD 8              /* CBD coefficients per trace (targets 4, 5) */
#endif
#ifndef KNR
#define KNR 2               /* Keccak rounds per trace (targets 2, 3) */
#endif
void tv_decode(const uint16_t *w0, const uint16_t *w1, unsigned n, uint32_t *b0, uint32_t *b1);
void tv_cbd(const uint8_t *b0, const uint8_t *b1, unsigned n, unsigned eta, uint16_t *x0, uint16_t *x1);
void tv_keccak_plain(uint64_t a[25], unsigned nr);
void tv_cmp10(const uint16_t *w0, const uint16_t *w1, unsigned n, uint32_t pubc, uint32_t acc[2]);
void tv_cmp4(const uint16_t *w0, const uint16_t *w1, unsigned n, uint32_t pubc, uint32_t acc[2]);
void tv_sponge(uint8_t out0[64], uint8_t out1[64], const uint8_t m0[32], const uint8_t m1[32], const uint8_t h[32]);
void tv_basemul(const uint32_t *s0, const uint32_t *s1, const uint32_t *u, unsigned n, uint32_t *r0, uint32_t *r1);
#ifndef NBM
#define NBM 8
#endif
extern unsigned masked_keccak_nr;

#ifndef SEED
#define SEED 0
#endif
static uint64_t ps = 0x853C49E6748FEA9Bull ^ ((uint64_t)SEED << 17);   /* public PRNG: classes and random inputs */
static uint32_t pr(void) { ps ^= ps << 13; ps ^= ps >> 7; ps ^= ps << 17; return (uint32_t)ps; }
void randombytes(uint8_t *o, size_t n) { size_t i; for (i = 0; i < n; i++) o[i] = (uint8_t)pr(); }
#define WIN_ON()  (OUT_MARK = 0x4C01u)
#define WIN_OFF() (OUT_MARK = 0x4C00u)

static volatile uint32_t sink;
static const uint16_t FIXW[8] = {17, 1200, 2000, 3000, 833, 2496, 5, 1664};
/* inputs live in memory only: nothing class-dependent is held in registers when
 * the measurement window opens (a callee-saved register holding the class bit
 * or an unmasked input would otherwise be saved inside the window) */
static uint16_t w[8], w0[8], w1[8], x0[8], x1[8];
static uint8_t in[8], in0[8], in1[8];
static uint64_t a0[25], a1[25], a[25];
static uint32_t b0, b1;
static uint32_t acc[2];
static uint8_t m[32], m0[32], m1[32], hpub[32], g0[64], g1[64];
static uint32_t sw[256], sw0[256], sw1[256], uw[256], rw0[NBM], rw1[NBM];
static uint32_t pack2(uint32_t lo, uint32_t hi) { return lo | (hi << 16); }
static uint32_t randq(void) { return (uint32_t)(((uint64_t)pr() * KYBER_Q) >> 32); }
static uint32_t mrandq_(void) { return (uint32_t)(((uint64_t)mrand32() * KYBER_Q) >> 32); }

__attribute__((noinline)) static void prepare(unsigned cls)
{
    unsigned j;
    if (TARGET <= 1) {
        for (j = 0; j < 8; j++) {
            uint16_t r = (uint16_t)(((uint64_t)mrand32() * KYBER_Q) >> 32);
            w[j] = cls ? (uint16_t)(((uint64_t)pr() * KYBER_Q) >> 32) : FIXW[j];
            w1[j] = r; w0[j] = (uint16_t)((w[j] + KYBER_Q - r) % KYBER_Q);
        }
    } else if (TARGET <= 3) {
        for (j = 0; j < 25; j++) {
            uint64_t v = j < 4 ? (cls ? ((uint64_t)pr() << 32 | pr()) : 0x0123456789ABCDEFull * (j + 1)) : 0;
            uint64_t m = (uint64_t)mrand32() << 32 | mrand32();
            a[j] = v; a1[j] = m; a0[j] = v ^ m;
        }
    } else if (TARGET >= 6) {
        if (TARGET <= 7) {
            for (j = 0; j < 8; j++) {
                uint16_t r = (uint16_t)mrandq_();
                w[j] = cls ? (uint16_t)randq() : FIXW[j];
                w1[j] = r; w0[j] = (uint16_t)((w[j] + KYBER_Q - r) % KYBER_Q);
            }
            acc[1] = mrand32(); acc[0] = acc[1];               /* masked accumulator = 0 */
        } else if (TARGET == 8) {
            for (j = 0; j < 32; j++) {
                uint8_t r = (uint8_t)mrand32();
                m[j] = cls ? (uint8_t)pr() : (uint8_t)(0xA5 ^ (17 * j));
                m1[j] = r; m0[j] = m[j] ^ r;
                hpub[j] = (uint8_t)(0x3C + 11 * j);            /* public, same for all traces */
            }
        } else {
            for (j = 0; j < 256; j++) {
                if ((j & 127) >= NBM) continue;                 /* only the words the gadget reads */
                uint32_t lo = cls ? randq() : (uint32_t)FIXW[j & 7], hi = cls ? randq() : (uint32_t)FIXW[(j + 3) & 7];
                uint32_t rl = mrandq_(), rh = mrandq_();
                sw[j] = pack2(lo, hi);
                sw1[j] = pack2(rl, rh);
                sw0[j] = pack2((lo + KYBER_Q - rl) % KYBER_Q, (hi + KYBER_Q - rh) % KYBER_Q);
                uw[j] = pack2((97u * j + 5) % KYBER_Q, (131u * j + 7) % KYBER_Q);   /* public */
            }
        }
        for (j = 0; j < 8; j++) w[j] = 0;
        for (j = 0; j < 32; j++) m[j] = 0;
        for (j = 0; j < 256; j++) if ((j & 127) < NBM) sw[j] = 0;
        return;
    } else {
        for (j = 0; j < 4; j++) {
            uint8_t m = (uint8_t)mrand32();
            in[j] = cls ? (uint8_t)pr() : (uint8_t)(0x5A + 37 * j);
            in1[j] = m; in0[j] = in[j] ^ m;
        }
    }
    if (TARGET & 1) {               /* unmasked targets: the masked inputs are not needed */
        for (j = 0; j < 8; j++) { w0[j] = w1[j] = 0; }
    } else {                        /* masked targets: wipe the unmasked copy */
        for (j = 0; j < 8; j++) { w[j] = 0; in[j] = 0; }
        for (j = 0; j < 25; j++) a[j] = 0;
    }
}

/* scrub the core state before a window opens: prepare() handled the unmasked
 * inputs, and registers, operand latches (reg_op1/reg_op2 = PCPI rs1/rs2,
 * reg_out, alu_out_q), the multiplier operands and the store-data bus would
 * otherwise still hold values derived from them when the gadget starts */
static inline void scrub(void)
{
#if defined(__riscv)
    __asm__ volatile(
        "li t0, 0\n li t1, 0\n li t2, 0\n li t3, 0\n li t4, 0\n li t5, 0\n li t6, 0\n"
        "li a0, 0\n li a1, 0\n li a2, 0\n li a3, 0\n li a4, 0\n li a5, 0\n li a6, 0\n li a7, 0\n"
        "add zero, zero, zero\n mul zero, zero, zero\n add zero, zero, zero\n sw zero, -4(sp)\n"
        ::: "t0", "t1", "t2", "t3", "t4", "t5", "t6", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "memory");
#endif
}

__attribute__((noinline)) static void measure(void)
{
    unsigned j;
    scrub();
    if (TARGET == 0) { WIN_ON(); tv_decode(w0, w1, NDEC, &b0, &b1); WIN_OFF(); }
    else if (TARGET == 1) {
        WIN_ON();
        for (j = 0, b0 = 0; j < NDEC; j++) b0 |= ((((uint32_t)w[j] << 1) + 1664u) * 315u >> 20 & 1u) << j;
        WIN_OFF();
    }
    else if (TARGET == 2) { WIN_ON(); masked_keccak_f1600(a0, a1); WIN_OFF(); }
    else if (TARGET == 3) { WIN_ON(); tv_keccak_plain(a, KNR); WIN_OFF(); }
    else if (TARGET == 6) { WIN_ON(); tv_cmp10(w0, w1, NDEC, 0x155u, acc); WIN_OFF(); }
    else if (TARGET == 7) { WIN_ON(); tv_cmp4(w0, w1, NDEC, 0x9u, acc); WIN_OFF(); }
    else if (TARGET == 8) { WIN_ON(); tv_sponge(g0, g1, m0, m1, hpub); WIN_OFF(); }
    else if (TARGET == 9) { WIN_ON(); tv_basemul(sw0, sw1, uw, NBM, rw0, rw1); WIN_OFF(); }
    else if (TARGET == 4) { WIN_ON(); tv_cbd(in0, in1, NCBD, 2, x0, x1); WIN_OFF(); }
    else {
        WIN_ON();
        for (j = 0; j < NCBD; j++) {
            uint32_t bits = (in[j >> 1] >> (4 * (j & 1))) & 0xFu;
            x0[j] = (uint16_t)(((bits & 1) + ((bits >> 1) & 1) + KYBER_Q - ((bits >> 2) & 1) - ((bits >> 3) & 1)) % KYBER_Q);
        }
        WIN_OFF();
    }
}

int main(void)
{
    unsigned t;
    masked_seed(0x5EED1234u ^ (uint32_t)SEED * 0x9E3779B9u);
    masked_keccak_nr = KNR;
    for (t = 0; t < NTR; t++) {
        unsigned cls = pr() & 1u;
        pf_putc((char)('0' + cls));
        prepare(cls);
        measure();
    }
    sink = b0 ^ b1 ^ x0[0] ^ x1[0] ^ (uint32_t)a0[0] ^ acc[0] ^ acc[1] ^ g0[0] ^ g1[0] ^ rw0[0] ^ rw1[0];
    pf_puts("\nDONE\n");
    pf_exit(0);
    return 0;
}
