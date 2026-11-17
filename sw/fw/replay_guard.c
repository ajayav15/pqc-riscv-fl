/*
 * replay_guard.c : protocol-level repetition check in front of decapsulation.
 *
 * Averaging attacks (REP) replay one ciphertext, or "near-replay" ciphertexts
 * that keep the coefficients processed in the attacked step and change the
 * rest, so that the trace segment of interest repeats. Ciphertexts from honest
 * encapsulations are pseudorandom, so a 4-coefficient block of u (40 bits)
 * practically never reappears at the same position.
 *
 * The guard keeps 32-bit fingerprints of the 128 blocks of u (c1) of the last
 * RG_N ciphertexts and compares the new ciphertext block by block (same
 * position). It also keeps a fingerprint of the whole ciphertext and the
 * shared secret that was returned for it:
 *   RG_FRESH    no block seen before                 -> decapsulate
 *   RG_RESEND   the whole ciphertext was seen before -> return the cached
 *               shared secret without decapsulating (a retransmission costs
 *               no new trace; an exact replay gives the attacker nothing)
 *   RG_NEAR     some blocks repeat, ciphertext differs -> decapsulate and
 *               raise the alarm (same input to the controller as the detector)
 * Memory: RG_N * (128 * 4 + 4 + 32) bytes = 4.4 KiB for RG_N = 8.
 */
#include <stdint.h>
#include <string.h>
#include "replay_guard.h"

#define RG_B 128                  /* 4-coefficient blocks of c1 = 640 bytes (k = 2, du = 10) */
static uint32_t rg_h[RG_B][RG_N];  /* fingerprints, position-major: one cache line per block */
static uint32_t rg_full[RG_N];
static uint32_t rg_ss[RG_N][8];
static unsigned rg_pos, rg_cnt;
unsigned rg_last_matches;

static inline uint32_t fmix(uint32_t h) { h ^= h >> 16; h *= 0x85EBCA6Bu; h ^= h >> 13; h *= 0xC2B2AE35u; h ^= h >> 16; return h; }

int replay_guard(const uint8_t *ct, unsigned ctlen, uint8_t ss_cached[32])
{
    uint32_t full = 0x811C9DC5u, matches = 0;
    unsigned b, k, slot = rg_pos;
    const uint8_t *p = ct;
    /* whole-ciphertext fingerprint first (resend check) */
    {   /* the receive buffer is word aligned */
        const uint32_t *w = (const uint32_t *)ct;
        for (b = 0; b < ctlen / 4; b++) full = (full ^ w[b]) * 0x01000193u;
    }
    full = fmix(full);
    for (k = 0; k < rg_cnt; k++)
        if (rg_full[k] == full) {
            uint32_t *o = (uint32_t *)ss_cached;
            for (b = 0; b < 8; b++) o[b] = rg_ss[k][b];
            rg_last_matches = RG_B;
            return RG_RESEND;
        }
    /* block fingerprints: compare with the same position of the stored
     * ciphertexts (branch-free over the RG_N slots) and overwrite the oldest */
    for (b = 0; b < RG_B; b++, p += 5) {
        uint32_t h = ((uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24)
                     ^ ((uint32_t)p[4] * 0x9E3779B1u);
        uint32_t *row = rg_h[b], m = 0;
#pragma clang loop unroll(full)
        for (k = 0; k < RG_N; k++) m |= (row[k] == h);
        matches += m;
        row[slot] = h;
    }
    /* slots not yet filled hold 0; a block whose fingerprint is 0 could match
     * them: count only once the history is full or the fingerprint is nonzero */
    if (rg_cnt < RG_N && matches) {
        matches = 0;
        for (b = 0, p = ct; b < RG_B; b++, p += 5) {
            uint32_t h = rg_h[b][slot];
            for (k = 0; k < rg_cnt; k++) {
                unsigned s2 = (slot + RG_N - 1 - k) % RG_N;
                if (rg_h[b][s2] == h) { matches++; break; }
            }
        }
    }
    rg_last_matches = matches;
    rg_full[slot] = full;
    rg_pos = (rg_pos + 1) % RG_N;
    if (rg_cnt < RG_N) rg_cnt++;
    return matches ? RG_NEAR : RG_FRESH;
}

/* store the shared secret returned for the ciphertext registered last */
void replay_guard_store(const uint8_t ss[32])
{
    const uint32_t *s = (const uint32_t *)ss;
    unsigned b, slot = (rg_pos + RG_N - 1) % RG_N;
    for (b = 0; b < 8; b++) rg_ss[slot][b] = s[b];
}
