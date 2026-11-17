#pragma once
#include <stdint.h>

#if defined(__riscv)
#define OUT_CHAR  (*(volatile uint32_t *)0x10000000u)
#define OUT_EXIT  (*(volatile uint32_t *)0x20000000u)
#define OUT_MARK  (*(volatile uint32_t *)0x30000000u)   /* trace window marker for the testbench */
#define OUT_LEAK  (*(volatile uint32_t *)0x30000004u)   /* "probe": report a value to the testbench */
static inline uint32_t rdcycle(void) { uint32_t c; __asm__ volatile("rdcycle %0" : "=r"(c)); return c; }
static inline void pf_putc(char c) { OUT_CHAR = (uint32_t)c; }
static inline void pf_exit(uint32_t code) { OUT_EXIT = code; for (;;) {} }
#else
#include <stdio.h>
#include <stdlib.h>
static inline uint32_t rdcycle(void) { return 0; }
static inline void pf_putc(char c) { putchar(c); }
static inline void pf_exit(uint32_t code) { exit((int)code); }
#endif

static inline void pf_puts(const char *s) { while (*s) pf_putc(*s++); }
static inline void pf_putu(uint32_t v)
{
    char b[11]; int i = 10; b[i] = 0;
    do { b[--i] = (char)('0' + v % 10u); v /= 10u; } while (v);
    pf_puts(&b[i]);
}
static inline void pf_puthex(uint32_t v)
{
    const char *h = "0123456789abcdef"; int i;
    for (i = 28; i >= 0; i -= 4) pf_putc(h[(v >> i) & 15u]);
}
static inline void pf_kv(const char *k, uint32_t v) { pf_puts(k); pf_puts("="); pf_putu(v); pf_puts("\n"); }
static inline void pf_kx(const char *k, uint32_t v) { pf_puts(k); pf_puts("=0x"); pf_puthex(v); pf_puts("\n"); }
