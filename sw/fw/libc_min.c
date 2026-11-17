#include <stddef.h>
#include <stdint.h>
void *memcpy(void *d, const void *s, size_t n) { uint8_t *a = d; const uint8_t *b = s; while (n--) *a++ = *b++; return d; }
void *memset(void *d, int c, size_t n) { uint8_t *a = d; while (n--) *a++ = (uint8_t)c; return d; }
int memcmp(const void *x, const void *y, size_t n) { const uint8_t *a = x, *b = y; for (; n; n--, a++, b++) if (*a != *b) return *a - *b; return 0; }
/* 64-bit division helpers normally provided by compiler-rt (not on the X25519 path) */
static uint64_t udivmod64(uint64_t n, uint64_t d, uint64_t *rem)
{
    uint64_t q = 0, r = 0; int i = 63;
    while (i > 0 && !((n >> i) & 1u)) i--;          /* skip leading zero bits */
    for (; i >= 0; i--) { r = (r << 1) | ((n >> i) & 1u); if (r >= d) { r -= d; q |= (uint64_t)1 << i; } }
    if (rem) *rem = r;
    return q;
}
uint64_t __udivdi3(uint64_t n, uint64_t d) { return udivmod64(n, d, 0); }
uint64_t __umoddi3(uint64_t n, uint64_t d) { uint64_t r; udivmod64(n, d, &r); return r; }
int64_t __divdi3(int64_t n, int64_t d)
{
    int neg = (n < 0) ^ (d < 0);
    uint64_t q = udivmod64(n < 0 ? (uint64_t)-n : (uint64_t)n, d < 0 ? (uint64_t)-d : (uint64_t)d, 0);
    return neg ? -(int64_t)q : (int64_t)q;
}
int64_t __moddi3(int64_t n, int64_t d)
{
    uint64_t r;
    udivmod64(n < 0 ? (uint64_t)-n : (uint64_t)n, d < 0 ? (uint64_t)-d : (uint64_t)d, &r);
    return n < 0 ? -(int64_t)r : (int64_t)r;
}
