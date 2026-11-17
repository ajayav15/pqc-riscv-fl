/*
 * masked_asm.S : share-separating primitives for the transition- and
 * glitch-robust first-order masking of masked.c (PicoRV32, RV32IM).
 *
 * Leakage rules enforced here (see masked.c):
 *   R1  two shares of one secret are never operands of the same or of two
 *       consecutive instructions: a clearing instruction (add x0,x0,x0) zeroes
 *       the operand latches reg_op1/reg_op2 (= PCPI rs1/rs2), the ALU and reg_out
 *   R2  a register that held one share is zeroed before it can receive the other
 *   R3  the store-data register mem_wdata is zeroed between share stores
 *
 * void msk_and32p(uint32_t *z0, uint32_t *z1, const uint32_t *x0, const uint32_t *x1,
 *                 const uint32_t *y0, const uint32_t *y1, uint32_t r)
 *   ISW / Trichina AND: z0 ^ z1 = (x0 ^ x1) & (y0 ^ y1), one fresh mask r.
 *   All loads precede the first store, so z may alias x or y.
 *
 * void share_run(void (*fn)(void *), void *arg, unsigned clear_bytes)
 *   calls fn(arg), then zeroes all caller-saved registers, the ALU and
 *   multiplier operand latches, mem_wdata and clear_bytes of stack below sp
 *   (the callee's frame). Every per-share kernel of masked.c runs through it.
 */
    .text
    .globl msk_and32p
    .type msk_and32p, @function
msk_and32p:
    lw   t0, 0(a2)          # x0
    lw   t1, 0(a5)          # y1
    and  t2, t0, t1         # x0 & y1
    xor  t2, t2, a6         # r ^ x0 y1
    add  zero, zero, zero
    lw   t3, 0(a3)          # x1
    lw   t4, 0(a4)          # y0
    and  t5, t3, t4         # x1 & y0
    xor  t2, t2, t5         # t = r ^ x0 y1 ^ x1 y0
    add  zero, zero, zero
    and  t6, t0, t4         # x0 & y0
    xor  t6, t6, a6         # z0 = x0 y0 ^ r
    add  zero, zero, zero
    sw   t6, 0(a0)
    li   t6, 0
    and  a7, t3, t1         # x1 & y1
    xor  a7, a7, t2         # z1 = x1 y1 ^ t
    add  zero, zero, zero
    sw   zero, -4(sp)       # mem_wdata: z0 -> 0 -> z1
    sw   a7, 0(a1)
    sw   zero, -4(sp)
    li   t0, 0
    li   t1, 0
    li   t2, 0
    li   t3, 0
    li   t4, 0
    li   t5, 0
    li   a6, 0
    li   a7, 0
    add  zero, zero, zero
    ret
    .size msk_and32p, .-msk_and32p

    .globl share_run
    .type share_run, @function
share_run:
    addi sp, sp, -16
    sw   ra, 12(sp)
    sw   a2, 8(sp)
    mv   t0, a0
    mv   a0, a1
    jalr ra, 0(t0)
    li   a0, 0
    li   a1, 0
    li   a2, 0
    li   a3, 0
    li   a4, 0
    li   a5, 0
    li   a6, 0
    li   a7, 0
    li   t3, 0
    li   t4, 0
    li   t5, 0
    li   t6, 0
    add  zero, zero, zero
    mul  zero, zero, zero   # multiplier operand latches
    add  zero, zero, zero
    lw   t0, 8(sp)          # bytes to clear below this frame
    mv   t1, sp
    sub  t2, sp, t0
1:  bgeu t2, t1, 2f
    sw   zero, 0(t2)
    addi t2, t2, 4
    j    1b
2:  li   t0, 0
    li   t1, 0
    li   t2, 0
    sw   zero, 8(sp)
    lw   ra, 12(sp)
    addi sp, sp, 16
    ret
    .size share_run, .-share_run
