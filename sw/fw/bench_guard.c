/* cycle cost and behaviour of the replay guard (replay_guard.c): a stream of
 * pseudorandom ciphertexts with one exact resend and one near-replay campaign
 * that keeps the first 16 bytes of c1 and changes the rest */
#include <stdint.h>
#include "platform.h"
#include "replay_guard.h"
static uint64_t ps = 0x243F6A8885A308D3ull;
static uint32_t pr(void) { ps ^= ps << 13; ps ^= ps >> 7; ps ^= ps << 17; return (uint32_t)ps; }
static uint8_t ct[768] __attribute__((aligned(4))), keep[768], ss[32] __attribute__((aligned(4)));
int main(void)
{
    unsigned i, j, nfresh = 0, nres = 0, nnear = 0, fp = 0;
    uint32_t cyc = 0, cmax = 0;
    for (i = 0; i < 200; i++) {
        int kind = (i == 50) ? 1 : (i >= 120 && i < 130) ? 2 : 0;   /* 1 resend of #49, 2 near-replay */
        if (kind == 1) for (j = 0; j < 768; j++) ct[j] = keep[j];
        else {
            for (j = 0; j < 768; j++) ct[j] = (uint8_t)pr();
            if (kind == 2) for (j = 0; j < 16; j++) ct[j] = (uint8_t)(0x5A ^ j);
        }
        if (i == 49) for (j = 0; j < 768; j++) keep[j] = ct[j];
        uint32_t t = rdcycle();
        int r = replay_guard(ct, 768, ss);
        if (r != RG_RESEND) replay_guard_store(ss);
        t = rdcycle() - t;
        cyc += t; if (t > cmax) cmax = t;
        if (r == RG_FRESH) nfresh++; else if (r == RG_RESEND) nres++; else nnear++;
        if (kind == 0 && r != RG_FRESH) fp++;
    }
    pf_kv("rg_fresh", nfresh); pf_kv("rg_resend", nres); pf_kv("rg_near", nnear); pf_kv("rg_false", fp);
    pf_kv("rg_avg_cycles", cyc / 200); pf_kv("rg_max_cycles", cmax);
    pf_puts("DONE\n"); pf_exit(0); return 0;
}
