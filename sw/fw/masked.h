#pragma once
#include <stdint.h>
#include "params.h"
#include "poly.h"
#include "polyvec.h"

typedef struct {
    poly s0[KYBER_K], s1[KYBER_K];   /* arithmetic shares of s_hat (mod q, NTT domain) */
    uint8_t z0[32], z1[32];          /* Boolean shares of the implicit-rejection key z */
    uint8_t h[32];                   /* H(pk), public */
    const uint8_t *pk;               /* public key, public */
} msk_t;

uint32_t mrand32(void);
void masked_seed(uint32_t s);
void msk_init(msk_t *k, const uint8_t sk[KYBER_SECRETKEYBYTES]);
int masked_dec(uint8_t ss[KYBER_SSBYTES], const uint8_t ct[KYBER_CIPHERTEXTBYTES], msk_t *k);
void masked_keccak_f1600(uint64_t a0[25], uint64_t a1[25]);
