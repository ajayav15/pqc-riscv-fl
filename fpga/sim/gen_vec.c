/* native test vector for the FPGA protocol test: coins -> pk, ct, ss (hex bytes, one per line) */
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "params.h"
#include "kem.h"
void randombytes(uint8_t *o, size_t n) { size_t i; for (i = 0; i < n; i++) o[i] = 0; }
int main(int argc, char **argv)
{
    uint8_t coins[64], pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES], ct[CRYPTO_CIPHERTEXTBYTES], ss[32];
    unsigned i;
    for (i = 0; i < 64; i++) coins[i] = (uint8_t)(i * 7 + 1);
    crypto_kem_keypair_derand(pk, sk, coins);
    crypto_kem_enc_derand(ct, ss, pk, coins + 32);
    if (argc > 1) {   /* --s0: low coefficient of the first pair of s_hat[0] (CPA target) */
        printf("%d\n", sk[0] | ((sk[1] & 0x0F) << 8));
        return 0;
    }
    for (i = 0; i < 64; i++) printf("%02x\n", coins[i]);
    for (i = 0; i < sizeof pk; i++) printf("%02x\n", pk[i]);
    for (i = 0; i < sizeof ct; i++) printf("%02x\n", ct[i]);
    for (i = 0; i < 32; i++) printf("%02x\n", ss[i]);
    return 0;
}
