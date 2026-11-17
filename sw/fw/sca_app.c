/*
 * sca_app.c : side-channel measurement firmware for the FPGA target
 * (fpga/rtl/soc_top.v). Binary protocol over UART (115200 8N1); every command
 * is one byte followed by its payload; the reply starts with the lower-case
 * command byte. The scope trigger (0x3000_0000) is high only around the
 * operation being measured.
 *
 *   'K' coins[64]        keypair (derandomised); reply 'k' pk[800]
 *   'M' mode[1]          0 unprotected, 1 hiding (dummy + shuffle + DVFS request),
 *                        2 first-order masking; reply 'm'
 *   'D' ct[768]          decapsulation in the current mode (triggered);
 *                        reply 'd' ss[32]
 *   'B' u[8]             secret-key base multiplication window, as in the
 *                        gate-level CPA: KZETA, KBMUL(s_0, u_0), KBMUL(s_1, u_1),
 *                        KADDQ (triggered); u = two packed coefficient pairs;
 *                        reply 'b'
 *   'T' target[1] cls[1] TVLA gadget (0..5 as in sw/fw/tvla.c), class 0 fixed /
 *                        1 random, inputs generated on the device (triggered);
 *                        reply 't'
 *   'S' seed[4]          reseed the masking PRNG (from a host TRNG); reply 's'
 * After reset the firmware sends 'R' once it is ready to receive.
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "params.h"
#include "kem.h"
#include "platform.h"
#include "ise.h"
#include "ise_poly.h"
#include "masked.h"

#define UART_TX (*(volatile uint32_t *)0x10000000u)
#define UART_RX (*(volatile uint32_t *)0x10000004u)
#define TRIG    (*(volatile uint32_t *)0x30000000u)

static uint8_t getb(void) { uint32_t v; do v = UART_RX; while (!(v & 0x100u)); return (uint8_t)v; }
static void putb(uint8_t c) { UART_TX = c; }
static void getn(uint8_t *p, unsigned n) { while (n--) *p++ = getb(); }
static void putn(const uint8_t *p, unsigned n) { while (n--) putb(*p++); }

static uint64_t ps = 0x853C49E6748FEA9Bull;   /* public PRNG (inputs of random TVLA class) */
static uint32_t pr(void) { ps ^= ps << 13; ps ^= ps >> 7; ps ^= ps << 17; return (uint32_t)ps; }
void randombytes(uint8_t *o, size_t n) { size_t i; for (i = 0; i < n; i++) o[i] = (uint8_t)pr(); }

static uint8_t pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES], ct[CRYPTO_CIPHERTEXTBYTES];
static uint8_t ss[32], coins[64];
static msk_t msk;
static unsigned mode;
static uint32_t s_words[2];      /* packed (s0, s1) of the first coefficient pair, k = 0 and 1 */

/* TVLA gadgets (sw/fw/masked.c, built with -DTVLA_API) */
void tv_decode(const uint16_t *w0, const uint16_t *w1, unsigned n, uint32_t *b0, uint32_t *b1);
void tv_cbd(const uint8_t *b0, const uint8_t *b1, unsigned n, unsigned eta, uint16_t *x0, uint16_t *x1);
void tv_keccak_plain(uint64_t a[25], unsigned nr);
extern unsigned masked_keccak_nr;
static uint16_t w[8], w0[8], w1[8], x0[8], x1[8];
static uint8_t in[8], in0[8], in1[8];
static uint64_t a0[25], a1[25], a[25];
static uint32_t b0, b1;
static const uint16_t FIXW[8] = {17, 1200, 2000, 3000, 833, 2496, 5, 1664};

__attribute__((noinline)) static void tv_prepare(unsigned tgt, unsigned cls)
{
    unsigned j;
    if (tgt <= 1)
        for (j = 0; j < 8; j++) {
            uint16_t r = (uint16_t)(((uint64_t)mrand32() * KYBER_Q) >> 32);
            w[j] = cls ? (uint16_t)(((uint64_t)pr() * KYBER_Q) >> 32) : FIXW[j];
            w1[j] = r; w0[j] = (uint16_t)((w[j] + KYBER_Q - r) % KYBER_Q);
        }
    else if (tgt <= 3)
        for (j = 0; j < 25; j++) {
            uint64_t v = j < 4 ? (cls ? ((uint64_t)pr() << 32 | pr()) : 0x0123456789ABCDEFull * (j + 1)) : 0;
            uint64_t m = (uint64_t)mrand32() << 32 | mrand32();
            a[j] = v; a1[j] = m; a0[j] = v ^ m;
        }
    else
        for (j = 0; j < 4; j++) {
            uint8_t m = (uint8_t)mrand32();
            in[j] = cls ? (uint8_t)pr() : (uint8_t)(0x5A + 37 * j);
            in1[j] = m; in0[j] = in[j] ^ m;
        }
    if (!(tgt & 1)) { for (j = 0; j < 8; j++) { w[j] = 0; in[j] = 0; } for (j = 0; j < 25; j++) a[j] = 0; }
}
__attribute__((noinline)) static void tv_measure(unsigned tgt)
{
    unsigned j;
    TRIG = 1;
    switch (tgt) {
    case 0: tv_decode(w0, w1, 8, &b0, &b1); break;
    case 1: for (j = 0, b0 = 0; j < 8; j++) b0 |= ((((uint32_t)w[j] << 1) + 1664u) * 315u >> 20 & 1u) << j; break;
    case 2: masked_keccak_f1600(a0, a1); break;
    case 3: tv_keccak_plain(a, 2); break;
    case 4: tv_cbd(in0, in1, 8, 2, x0, x1); break;
    default:
        for (j = 0; j < 8; j++) {
            uint32_t bits = (in[j >> 1] >> (4 * (j & 1))) & 0xFu;
            x0[j] = (uint16_t)(((bits & 1) + ((bits >> 1) & 1) + KYBER_Q - ((bits >> 2) & 1) - ((bits >> 3) & 1)) % KYBER_Q);
        }
    }
    TRIG = 0;
}

static void set_mode(unsigned m)
{
    mode = m;
    if (m == 1) { KCFG(CFG_DUMMY | CFG_SHUFFLE | CFG_DVFS | CFG_TH(8) | CFG_MASK(3)); ise_sw_shuffle = 1; }
    else        { KCFG(0); ise_sw_shuffle = 0; }
}

int main(void)
{
    masked_seed(0x13579BDFu);
    masked_keccak_nr = 2;          /* TVLA Keccak target: 2 rounds (restored for decapsulation) */
    putb('R');                     /* ready banner (host may ignore it) */
    for (;;) {
        uint8_t cmd = getb();
        switch (cmd) {
        case 'K':
            getn(coins, 64);
            crypto_kem_keypair_derand(pk, sk, coins);
            msk_init(&msk, sk);
            {   /* first coefficient pair of s_hat[0] and s_hat[1] for the 'B' window */
                const uint8_t *p = sk, *q = sk + KYBER_POLYBYTES;
                s_words[0] = (uint32_t)(p[0] | ((p[1] & 0x0F) << 8)) | ((uint32_t)((p[1] >> 4) | (p[2] << 4)) << 16);
                s_words[1] = (uint32_t)(q[0] | ((q[1] & 0x0F) << 8)) | ((uint32_t)((q[1] >> 4) | (q[2] << 4)) << 16);
            }
            putb('k'); putn(pk, sizeof pk);
            break;
        case 'M':
            set_mode(getb()); putb('m');
            break;
        case 'S': {
            uint8_t s[4]; getn(s, 4);
            masked_seed((uint32_t)s[0] | (uint32_t)s[1] << 8 | (uint32_t)s[2] << 16 | (uint32_t)s[3] << 24);
            putb('s');
            break; }
        case 'D':
            getn(ct, sizeof ct);
            masked_keccak_nr = 24;
            TRIG = 1;
            if (mode == 2) (void)masked_dec(ss, ct, &msk);
            else crypto_kem_dec(ss, ct, sk);
            TRIG = 0;
            masked_keccak_nr = 2;
            putb('d'); putn(ss, 32);
            break;
        case 'B': {
            uint8_t u[8]; uint32_t u0, u1, r0, r1, r;
            getn(u, 8);
            u0 = (uint32_t)u[0] | (uint32_t)u[1] << 8 | (uint32_t)u[2] << 16 | (uint32_t)u[3] << 24;
            u1 = (uint32_t)u[4] | (uint32_t)u[5] << 8 | (uint32_t)u[6] << 16 | (uint32_t)u[7] << 24;
            TRIG = 1;
            KZETA(17u);
            KBMUL(r0, s_words[0], u0);
            KBMUL(r1, s_words[1], u1);
            KADDQ(r, r0, r1);
            TRIG = 0;
            (void)r;
            putb('b');
            break; }
        case 'T': {
            unsigned tgt = getb(), cls = getb();
            tv_prepare(tgt, cls);
            tv_measure(tgt);
            putb('t');
            break; }
        default:
            putb('?');
        }
    }
    return 0;
}
