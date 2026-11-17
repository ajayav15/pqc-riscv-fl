/* Gate-level energy firmware. Every operation runs inside a measurement window
 * opened with MARK 0x100+id and closed with MARK 0x200+id; the gate-level
 * testbench (tb_soc.v -DGATE -DCOVWIN) zeroes the per-net toggle counters at
 * the opening mark and dumps them at the closing mark.
 *   id: 0 NTT, 1 INTT, 2 basemul_acc (K=2), 3 KeyGen, 4 Encaps, 5 Decaps
 *   MITIG (ISE build only): adaptive mitigation engaged during the operations */
#include <stdint.h>
#include <stddef.h>
#include "params.h"
#include "kem.h"
#include "poly.h"
#include "polyvec.h"
#include "platform.h"
#ifdef USE_ISE
#include "ise.h"
#include "ise_poly.h"
#endif
static uint64_t rs = 0x243F6A8885A308D3ull;
static uint32_t xr(void) { rs ^= rs << 13; rs ^= rs >> 7; rs ^= rs << 17; return (uint32_t)rs; }
void randombytes(uint8_t *o, size_t n) { size_t i; for (i = 0; i < n; i++) o[i] = (uint8_t)xr(); }
static uint16_t uq(void) { uint32_t r; do r = xr() & 0xFFFu; while (r >= KYBER_Q); return (uint16_t)r; }

static poly a, acc;
static polyvec pa, pb;
static uint8_t pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES], ct[CRYPTO_CIPHERTEXTBYTES];
static uint8_t ss1[CRYPTO_BYTES], ss2[CRYPTO_BYTES], coins[64];

#define WIN(id, stmt) do { OUT_MARK = 0x100u + (id); stmt; OUT_MARK = 0x200u + (id); } while (0)

int main(void)
{
    unsigned i, j;
    for (j = 0; j < KYBER_N; j++) a.coeffs[j] = (int16_t)uq();
    for (i = 0; i < KYBER_K; i++)
        for (j = 0; j < KYBER_N; j++) { pa.vec[i].coeffs[j] = (int16_t)uq(); pb.vec[i].coeffs[j] = (int16_t)uq(); }
    for (i = 0; i < 64; i++) coins[i] = (uint8_t)(i * 7 + 1);
#if defined(USE_ISE) && defined(MITIG)
    KSEED(0x1234567u);
    KCFG(CFG_DUMMY | CFG_SHUFFLE | CFG_DVFS | CFG_TH(8) | CFG_MASK(3));
    ise_sw_shuffle = 1;
#endif
    WIN(0, poly_ntt(&a));
    WIN(1, poly_invntt_tomont(&a));
    WIN(2, polyvec_basemul_acc_montgomery(&acc, &pa, &pb));
    WIN(3, crypto_kem_keypair_derand(pk, sk, coins));
    WIN(4, crypto_kem_enc_derand(ct, ss1, pk, coins + 32));
    WIN(5, crypto_kem_dec(ss2, ct, sk));
    for (i = 0; i < CRYPTO_BYTES; i++) if (ss1[i] != ss2[i]) pf_exit(1);
    pf_exit(0);
    return 0;
}
