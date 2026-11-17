/*
 * ise.h : inline-assembly wrappers for the kyber_ise custom instructions
 * (custom-0 opcode 0x0B, R-type). See rtl/kyber_ise.v for semantics.
 */
#pragma once
#include <stdint.h>

#ifdef ISE_NATIVE_EMU
/* host-side functional emulation (bit-exact with sw/golden.py) for testing */
uint32_t emu_ise(int f3, int f7, uint32_t a, uint32_t b);
#define ISE_R(f3, f7, rd, a, b) ((rd) = emu_ise(f3, f7, (uint32_t)(a), (uint32_t)(b)))
#define ISE_R0(f3, f7, rd)      ((rd) = emu_ise(f3, f7, 0, 0))
#define ISE_W(f3, f7, a)        ((void)emu_ise(f3, f7, (uint32_t)(a), 0))
#else

#define ISE_R(f3, f7, rd, a, b) \
    __asm__ volatile(".insn r 0x0B, " #f3 ", " #f7 ", %0, %1, %2" : "=r"(rd) : "r"(a), "r"(b))
#define ISE_R0(f3, f7, rd) \
    __asm__ volatile(".insn r 0x0B, " #f3 ", " #f7 ", %0, x0, x0" : "=r"(rd))
#define ISE_W(f3, f7, a) \
    __asm__ volatile(".insn r 0x0B, " #f3 ", " #f7 ", x0, %0, x0" : : "r"(a))
#endif

#define KCT_A(rd, a, b)  ISE_R(0, 0, rd, a, b)
#define KCT_B(rd)        ISE_R0(1, 0, rd)
#define KGS_A(rd, a, b)  ISE_R(2, 0, rd, a, b)
#define KGS_B(rd)        ISE_R0(3, 0, rd)
#define KBMUL(rd, a, b)  ISE_R(4, 0, rd, a, b)
#define KMULZ(rd, a)     ISE_R(5, 0, rd, a, 0)
#define KADDQ(rd, a, b)  ISE_R(6, 0, rd, a, b)
#define KSUBQ(rd, a, b)  ISE_R(6, 32, rd, a, b)
#define KZETA(z)         ISE_W(7, 0, z)
#define KCFG(c)          ISE_W(7, 1, c)
#define KSEED(s)         ISE_W(7, 2, s)
#define KRND(rd)         ISE_R0(7, 3, rd)
#define KSTAT(rd)        ISE_R0(7, 4, rd)
#define KRNG(rd)         ISE_R0(7, 5, rd)

/* CFG fields */
#define CFG_DUMMY      (1u << 0)
#define CFG_SHUFFLE    (1u << 1)
#define CFG_DVFS       (1u << 2)
#define CFG_TH(t)      (((t) & 15u) << 4)
#define CFG_MASK(m)    (((m) & 7u) << 8)

/* ---- keccak_ise (custom-1 opcode 0x2B): 1600-bit state, 24-cycle permutation ---- */
#ifndef ISE_NATIVE_EMU
#define KK_SWAP(rd, w) __asm__ volatile(".insn r 0x2B, 0, 0, %0, %1, x0" : "=r"(rd) : "r"(w) : "memory")
#define KK_PERM()       __asm__ volatile(".insn r 0x2B, 2, 0, x0, x0, x0" : : : "memory")
#endif
