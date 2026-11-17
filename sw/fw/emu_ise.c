/* host emulation of kyber_ise (functional, no timing) */
#include <stdint.h>
#define Q 3329u
static uint32_t Z, B, CFG, LFSR = 0xACE12468u, DUMMY;
static uint32_t mm(uint32_t a, uint32_t b) { uint32_t p = a * b, t = (uint32_t)(((uint64_t)p * 5039u) >> 24), r = p - t * Q; return r >= Q ? r - Q : r; }
static uint32_t ad(uint32_t a, uint32_t b) { uint32_t s = a + b; return s >= Q ? s - Q : s; }
static uint32_t sb(uint32_t a, uint32_t b) { return a >= b ? a - b : a + Q - b; }
#define LO(x) ((x) & 0xFFFu)
#define HI(x) (((x) >> 16) & 0xFFFu)
#define PK(l, h) (((uint32_t)(h) << 16) | (l))
uint32_t emu_ise(int f3, int f7, uint32_t a, uint32_t b)
{
    LFSR = (LFSR & 1u) ? ((LFSR >> 1) ^ 0x80200003u) : (LFSR >> 1);
    switch (f3) {
    case 0: { uint32_t t0 = mm(Z, LO(b)), t1 = mm(Z, HI(b));
              B = PK(sb(LO(a), t0), sb(HI(a), t1)); return PK(ad(LO(a), t0), ad(HI(a), t1)); }
    case 1: case 3: return B;
    case 2: B = PK(mm(Z, sb(LO(a), LO(b))), mm(Z, sb(HI(a), HI(b))));
            return PK(ad(LO(a), LO(b)), ad(HI(a), HI(b)));
    case 4: return PK(ad(mm(LO(a), LO(b)), mm(Z, mm(HI(a), HI(b)))), ad(mm(LO(a), HI(b)), mm(HI(a), LO(b))));
    case 5: return PK(mm(Z, LO(a)), mm(Z, HI(a)));
    case 6: return (f7 & 32) ? PK(sb(LO(a), LO(b)), sb(HI(a), HI(b))) : PK(ad(LO(a), LO(b)), ad(HI(a), HI(b)));
    default:
        switch (f7) {
        case 0: Z = a & 0xFFFu; return 0;
        case 1: CFG = a; return 0;
        case 2: LFSR = a ? a : 1u; return 0;
        case 3: return LFSR;
        case 5: { static uint32_t x = 0x9e3779b9u; x ^= x << 13; x ^= x >> 17; x ^= x << 5; return x; }
        default: return DUMMY;
        }
    }
}
