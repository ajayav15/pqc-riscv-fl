/*
 * bench.c : cycle benchmarks and known-answer cross-check for ML-KEM-512 on
 * PicoRV32 (reference C) and PicoRV32 + kyber_ise.
 * The same file builds natively (ISE_NATIVE_EMU) to produce the expected
 * checksums, so the RTL run is checked bit for bit against the reference.
 */
#include <stdint.h>
#include <string.h>
#include "params.h"
#include "kem.h"
#include "indcpa.h"
#include "poly.h"
#include "polyvec.h"
#include "platform.h"
#ifdef USE_ISE
#include "ise.h"
#include "ise_poly.h"
#endif

/* ---------- deterministic randomness (benchmark only, not a TRNG) ---------- */
static uint64_t rng_s = 0x9E3779B97F4A7C15ull;
static uint32_t xr(void) { rng_s ^= rng_s << 13; rng_s ^= rng_s >> 7; rng_s ^= rng_s << 17; return (uint32_t)rng_s; }
void randombytes(uint8_t *out, size_t n) { size_t i; for (i = 0; i < n; i++) out[i] = (uint8_t)xr(); }

static uint32_t fnv(const uint8_t *p, unsigned n, uint32_t h)
{ unsigned i; for (i = 0; i < n; i++) { h ^= p[i]; h *= 16777619u; } return h; }

/* ---------- first-order arithmetic masking of the secret-dependent linear core ---------- */
/* m = v - INTT(s o NTT(u)) with s split as s = s1 + s2 (mod q), each share processed separately.
 * This is the part of decapsulation that touches the long-term key; a complete masked
 * decapsulation additionally needs masked compression, hashing and re-encryption.      */
static uint16_t uq(void) { uint32_t r; do { r = xr() & 0xFFFu; } while (r >= KYBER_Q); return (uint16_t)r; }

static void dec_core(uint8_t m[KYBER_INDCPA_MSGBYTES], const uint8_t *c, const uint8_t *sk, int masked)
{
    polyvec b, s1, s2;
    poly v, mp, mp2;
    unsigned i, j;
    polyvec_decompress(&b, c);
    poly_decompress(&v, c + KYBER_POLYVECCOMPRESSEDBYTES);
    polyvec_frombytes(&s1, sk);
    polyvec_ntt(&b);
    if (!masked) {
        polyvec_basemul_acc_montgomery(&mp, &s1, &b);
        poly_invntt_tomont(&mp);
    } else {
        for (i = 0; i < KYBER_K; i++)
            for (j = 0; j < KYBER_N; j++) {
                int16_t r = (int16_t)uq();
                int16_t d = (int16_t)(s1.vec[i].coeffs[j] - r);
                if (d < 0) d += KYBER_Q;
                s2.vec[i].coeffs[j] = r;          /* share 2 */
                s1.vec[i].coeffs[j] = d;          /* share 1 */
            }
        polyvec_basemul_acc_montgomery(&mp, &s1, &b);
        polyvec_basemul_acc_montgomery(&mp2, &s2, &b);
        poly_invntt_tomont(&mp);
        poly_invntt_tomont(&mp2);
        poly_add(&mp, &mp, &mp2);               /* recombination before decode (unmasked decode) */
    }
    poly_sub(&mp, &v, &mp);
    poly_reduce(&mp);
    poly_tomsg(m, &mp);
}

static uint8_t pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
static uint8_t ct[CRYPTO_CIPHERTEXTBYTES], ss1[CRYPTO_BYTES], ss2[CRYPTO_BYTES];
static uint8_t coins[2 * KYBER_SYMBYTES];

#define T0()    (t = rdcycle())
#define T1(tag) pf_kv(tag, rdcycle() - t)

static void run_suite(const char *pfx)
{
    uint32_t t, h;
    poly a;
    polyvec pa, pb;
    uint8_t m1[32], m2[32];
    unsigned i, j;

    for (i = 0; i < KYBER_K; i++)
        for (j = 0; j < KYBER_N; j++) { pa.vec[i].coeffs[j] = (int16_t)uq(); pb.vec[i].coeffs[j] = (int16_t)uq(); }
    for (j = 0; j < KYBER_N; j++) a.coeffs[j] = (int16_t)uq();

    pf_puts(pfx);
    T0(); poly_ntt(&a);                                   T1("ntt");
    for (j = 0; j < KYBER_N; j++) a.coeffs[j] = (int16_t)uq();   /* fresh canonical input */
    T0(); poly_invntt_tomont(&a);                         T1("invntt");
    T0(); polyvec_basemul_acc_montgomery(&a, &pa, &pb);   T1("basemul_acc");

    for (i = 0; i < sizeof coins; i++) coins[i] = (uint8_t)(i * 7 + 1);
    T0(); crypto_kem_keypair_derand(pk, sk, coins);       T1("keypair");
    T0(); crypto_kem_enc_derand(ct, ss1, pk, coins + 32); T1("encaps");
    T0(); crypto_kem_dec(ss2, ct, sk);                    T1("decaps");
    h = fnv(pk, sizeof pk, 2166136261u);
    h = fnv(sk, sizeof sk, h);
    h = fnv(ct, sizeof ct, h);
    h = fnv(ss1, sizeof ss1, h);
    pf_kx("kat_fnv", h);
    pf_kv("ss_match", memcmp(ss1, ss2, CRYPTO_BYTES) == 0);

    T0(); dec_core(m1, ct, sk, 0);                        T1("dec_core");
    T0(); dec_core(m2, ct, sk, 1);                        T1("dec_core_masked");
    pf_kv("masked_ok", memcmp(m1, m2, 32) == 0);
}

int main(void)
{
#ifdef USE_ISE
    run_suite("[ise]\n");
    /* adaptive mitigation engaged (what the controller sets on an alarm) */
    KSEED(0x1234567u);
    KCFG(CFG_DUMMY | CFG_SHUFFLE | CFG_DVFS | CFG_TH(8) | CFG_MASK(3));
    ise_sw_shuffle = 1;
    run_suite("[ise_mitig]\n");
    { uint32_t d; KSTAT(d); pf_kv("dummy_ops", d); }
    KCFG(0); ise_sw_shuffle = 0;
#else
    run_suite("[ref]\n");
#endif
    pf_puts("DONE\n");
    pf_exit(0);
    return 0;
}
