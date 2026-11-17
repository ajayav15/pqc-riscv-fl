/* Cycle profiling of ML-KEM-512 KeyGen / Encaps / Decaps on PicoRV32.
 * MARK 1 / MARK 0 gate the testbench PC profiler (tb_soc.v, -DPROFILE).
 * PROF_OP selects the operation: 0 keypair, 1 encaps, 2 decaps. */
#include <stdint.h>
#include <stddef.h>
#include "params.h"
#include "kem.h"
#include "platform.h"
#ifndef PROF_OP
#define PROF_OP 0
#endif
static uint64_t rs = 0x9E3779B97F4A7C15ull;
static uint32_t xr(void) { rs ^= rs << 13; rs ^= rs >> 7; rs ^= rs << 17; return (uint32_t)rs; }
void randombytes(uint8_t *o, size_t n) { size_t i; for (i = 0; i < n; i++) o[i] = (uint8_t)xr(); }
static uint8_t pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES], ct[CRYPTO_CIPHERTEXTBYTES];
static uint8_t ss1[CRYPTO_BYTES], ss2[CRYPTO_BYTES], coins[64];
int main(void)
{
    unsigned i;
    for (i = 0; i < 64; i++) coins[i] = (uint8_t)(i * 7 + 1);
    if (PROF_OP == 0) OUT_MARK = 1;
    crypto_kem_keypair_derand(pk, sk, coins);
    if (PROF_OP == 0) OUT_MARK = 0;
    if (PROF_OP == 1) OUT_MARK = 1;
    crypto_kem_enc_derand(ct, ss1, pk, coins + 32);
    if (PROF_OP == 1) OUT_MARK = 0;
    if (PROF_OP == 2) OUT_MARK = 1;
    crypto_kem_dec(ss2, ct, sk);
    if (PROF_OP == 2) OUT_MARK = 0;
    pf_puts("DONE\n");
    pf_exit(0);
    return 0;
}
