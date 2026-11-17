/* Functional check of masked_dec against crypto_kem_dec: valid ciphertexts and
 * tampered ones (implicit rejection), fresh masks every call. Builds natively
 * (ISE_NATIVE_EMU) and for the RTL. */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "params.h"
#include "kem.h"
#include "platform.h"
#include "masked.h"

static uint64_t rs = 0x2545F4914F6CDD1Dull;
static uint32_t xr(void) { rs ^= rs << 13; rs ^= rs >> 7; rs ^= rs << 17; return (uint32_t)rs; }
void randombytes(uint8_t *o, size_t n) { size_t i; for (i = 0; i < n; i++) o[i] = (uint8_t)xr(); }

#ifndef NTRIALS
#define NTRIALS 40
#endif
static uint8_t pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES], ct[CRYPTO_CIPHERTEXTBYTES];
static uint8_t ss_e[32], ss_ref[32], ss_m[32];
static msk_t msk;

int main(void)
{
    unsigned t, ok = 0, rej_ok = 0, nrej = 0, i;
    uint32_t c0, c_ref = 0, c_m = 0;
    masked_seed(0xC0FFEEu);
    crypto_kem_keypair(pk, sk);
    msk_init(&msk, sk);
    for (t = 0; t < NTRIALS; t++) {
        int tamper = t & 1, fail;
        crypto_kem_enc(ct, ss_e, pk);
        if (tamper) { ct[xr() % CRYPTO_CIPHERTEXTBYTES] ^= (uint8_t)(1u << (xr() & 7)); nrej++; }
        c0 = rdcycle(); crypto_kem_dec(ss_ref, ct, sk); c_ref += rdcycle() - c0;
        c0 = rdcycle(); fail = masked_dec(ss_m, ct, &msk); c_m += rdcycle() - c0;
        if (memcmp(ss_ref, ss_m, 32) == 0) ok++;
        if (tamper && fail && memcmp(ss_m, ss_e, 32) != 0) rej_ok++;
        if (!tamper && (fail || memcmp(ss_m, ss_e, 32) != 0)) { pf_puts("valid ct mismatch\n"); }
    }
    pf_kv("trials", NTRIALS);
    pf_kv("masked_equals_ref", ok);
    pf_kv("tampered", nrej);
    pf_kv("tampered_rejected", rej_ok);
    pf_kv("avg_dec_cycles", c_ref / NTRIALS);
    pf_kv("avg_masked_dec_cycles", c_m / NTRIALS);
    for (i = 0; i < 1; i++) {}
    pf_puts("DONE\n");
    pf_exit(ok == NTRIALS && rej_ok == nrej ? 0 : 1);
    return 0;
}
