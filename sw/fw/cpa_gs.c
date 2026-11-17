/*
 * cpa_gs.c : CPA trace firmware for the glitch-aware gate-level simulator
 * (sim/gsim). The measured window is the secret-dependent step of the
 * decapsulation used throughout the CPA evaluation: KZETA, KBMUL(s_0, u_0),
 * KBMUL(s_1, u_1), KADDQ on the first coefficient pair of s_hat[0] and
 * s_hat[1], with fresh random u for every trace (printed as 16 hex digits per
 * trace so that the analysis knows the public input). The secret comes from a
 * derandomised key pair; its first coefficient is printed once ("S=").
 * CHOSEN=1 uses chosen ciphertexts whose other lanes are zero, so that the
 * registers of the multiplier hold 0 before each product of interest (on a
 * continuously running core their previous contents otherwise depend on other
 * secret coefficients).
 *   MODE 0 unprotected, MODE 1 hiding (dummy operations + issue shuffle; the
 *   DVFS request is modelled on the traces, see sim/sca.py:observe)
 */
#include <stdint.h>
#include <stddef.h>
#include "params.h"
#include "kem.h"
#include "platform.h"
#include "ise.h"
#ifndef NTR
#define NTR 1000
#endif
#ifndef MODE
#define MODE 0
#endif
#ifndef CHOSEN
#define CHOSEN 0     /* 1: chosen ciphertext with zero lanes (u0 = (0, r), u1 = 0) */
#endif
static uint64_t ps = 0x9E3779B97F4A7C15ull;
static uint32_t pr(void) { ps ^= ps << 13; ps ^= ps >> 7; ps ^= ps << 17; return (uint32_t)ps; }
void randombytes(uint8_t *o, size_t n) { size_t i; for (i = 0; i < n; i++) o[i] = (uint8_t)pr(); }
static uint8_t pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES], coins[64];
static volatile uint32_t s_words[2], u_words[2], sink;
static void puthex(uint32_t v) { const char *h = "0123456789abcdef"; int i; for (i = 28; i >= 0; i -= 4) pf_putc(h[(v >> i) & 15u]); }
static uint32_t randq2(void)
{
    uint32_t a = (uint32_t)(((uint64_t)pr() * KYBER_Q) >> 32), b = (uint32_t)(((uint64_t)pr() * KYBER_Q) >> 32);
    return a | (b << 16);
}
__attribute__((noinline)) static void measure(void)
{
    uint32_t r0, r1, r;
    uint32_t s0 = s_words[0], s1 = s_words[1], u0 = u_words[0], u1 = u_words[1];
    OUT_MARK = 0x4C01u;
    KZETA(17u);
    KBMUL(r0, s0, u0);
    KBMUL(r1, s1, u1);
    KADDQ(r, r0, r1);
    OUT_MARK = 0x4C00u;
    sink = r;
}
int main(void)
{
    unsigned t, i;
    for (i = 0; i < 64; i++) coins[i] = (uint8_t)(i * 37 + 11);
    crypto_kem_keypair_derand(pk, sk, coins);
    {
        const uint8_t *p = sk, *q = sk + KYBER_POLYBYTES;
        s_words[0] = (uint32_t)(p[0] | ((p[1] & 0x0F) << 8)) | ((uint32_t)((p[1] >> 4) | (p[2] << 4)) << 16);
        s_words[1] = (uint32_t)(q[0] | ((q[1] & 0x0F) << 8)) | ((uint32_t)((q[1] >> 4) | (q[2] << 4)) << 16);
    }
    pf_puts("S="); puthex(s_words[0]); pf_puts("\n");
#if MODE == 1
    KCFG(CFG_DUMMY | CFG_SHUFFLE | CFG_DVFS | CFG_TH(8) | CFG_MASK(3));
#endif
    for (t = 0; t < NTR; t++) {
#if CHOSEN
        u_words[0] = randq2() & 0x0FFF0000u; u_words[1] = 0;
#else
        u_words[0] = randq2(); u_words[1] = randq2();
#endif
        puthex(u_words[0]); puthex(u_words[1]); pf_putc('\n');
        measure();
    }
    pf_puts("DONE\n");
    pf_exit(0);
    return 0;
}
