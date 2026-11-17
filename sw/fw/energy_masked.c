/* Gate-level energy of unmasked vs first-order masked decapsulation on
 * PicoRV32 + kyber_ise + keccak_ise (windows 5 and 6, see bench_energy.c). */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "params.h"
#include "kem.h"
#include "platform.h"
#include "masked.h"
static uint64_t rs = 0x243F6A8885A308D3ull;
static uint32_t xr(void) { rs ^= rs << 13; rs ^= rs >> 7; rs ^= rs << 17; return (uint32_t)rs; }
void randombytes(uint8_t *o, size_t n) { size_t i; for (i = 0; i < n; i++) o[i] = (uint8_t)xr(); }
static uint8_t pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES], ct[CRYPTO_CIPHERTEXTBYTES];
static uint8_t ss1[32], ss2[32], ss3[32], coins[64];
static msk_t msk;
#define WIN(id, stmt) do { OUT_MARK = 0x100u + (id); stmt; OUT_MARK = 0x200u + (id); } while (0)
int main(void)
{
    unsigned i;
    for (i = 0; i < 64; i++) coins[i] = (uint8_t)(i * 7 + 1);
    masked_seed(0xA5A5F00Du);
    crypto_kem_keypair_derand(pk, sk, coins);
    crypto_kem_enc_derand(ct, ss1, pk, coins + 32);
    msk_init(&msk, sk);
    WIN(5, crypto_kem_dec(ss2, ct, sk));
    WIN(6, (void)masked_dec(ss3, ct, &msk));
    pf_exit(memcmp(ss1, ss2, 32) || memcmp(ss1, ss3, 32) ? 1u : 0u);
    return 0;
}
