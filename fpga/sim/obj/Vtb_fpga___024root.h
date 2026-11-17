// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_fpga.h for the primary calling header

#ifndef VERILATED_VTB_FPGA___024ROOT_H_
#define VERILATED_VTB_FPGA___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_fpga__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_fpga___024root final {
  public:

    // TRIVIALLY CONSTRUCTIBLE STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        ::CData/*0:0*/ tb_fpga__DOT__clk;
        ::CData/*0:0*/ tb_fpga__DOT__resetn;
        ::CData/*0:0*/ tb_fpga__DOT__host_tx;
        ::CData/*7:0*/ tb_fpga__DOT__recvb__Vstatic__b;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__trigger;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__led;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__mem_ready;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__tx_start;
        ::CData/*7:0*/ tb_fpga__DOT__dut__DOT__tx_data;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__rx_full;
        ::CData/*7:0*/ tb_fpga__DOT__dut__DOT__rx_byte;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ram_pend;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__trap;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_read;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_write;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wstrb;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid;
        ::CData/*4:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_wr;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready;
        ::CData/*1:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state;
        ::CData/*1:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lui;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_auipc;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_beq;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bne;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_blt;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bge;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bltu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bgeu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lw;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lbu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lhu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sb;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sh;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sw;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_addi;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slti;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltiu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xori;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ori;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_andi;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slli;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srli;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srai;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_add;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sub;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sll;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slt;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xor;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srl;
    };
    struct {
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sra;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_or;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_and;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycleh;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstrh;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ecall_ebreak;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_fence;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_getq;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap;
        ::CData/*4:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rd;
        ::CData/*4:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs1;
        ::CData/*4:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs2;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_pseudo_trigger;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__compressed_instr;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal_jalr_addi_add_sub;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_slti_blt_slt;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_sltiu_bltu_sltu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_lbu_lhu_lw;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_compare;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh;
        ::CData/*7:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__latched_stalu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__latched_compr;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lh;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lb;
        ::CData/*4:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__latched_rd;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__do_waitirq;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wr;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_ready;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_div;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_divu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_rem;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_remu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait_q;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__start;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__outsign;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mul;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__shift_out;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wr;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wait;
    };
    struct {
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__is_ise;
        ::CData/*2:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__op;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__mm_v;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__mm_tag;
        ::CData/*4:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__done;
        ::CData/*4:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__issued;
        ::CData/*1:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__rot;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__swp;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__ndummy;
        ::CData/*2:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy;
        ::CData/*2:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__pick;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok;
        ::CData/*1:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__state;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_valid;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_tag;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_v;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_tag;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_v;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_tag;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__txd;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_valid;
        ::CData/*7:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_data;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit;
        ::CData/*1:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__sync;
        ::CData/*3:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy;
        ::CData/*7:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wr;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wait;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__kise__DOT__is_kk;
        ::CData/*4:0*/ tb_fpga__DOT__dut__DOT__kise__DOT__rnd;
        ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__kise__DOT__busy;
        ::CData/*0:0*/ __Vdfg_Regularize_1135;
        ::CData/*0:0*/ __Vdfg_Regularize_1137;
        ::CData/*0:0*/ __Vtrigprevexpr___TOP__tb_fpga__DOT__clk__0;
        ::CData/*0:0*/ __Vtrigprevexpr___TOP__tb_fpga__DOT__dut__DOT__u_uart__DOT__txd__0;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_12__madd;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_11__madd;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_10__madd;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_9__madd;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_8__msub;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_7__msub;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_6__madd;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_5__madd;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_3__madd;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_2__madd;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_1__msub;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_0__msub;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__zreg;
        ::SData/*10:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__cfg;
        ::SData/*12:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s;
        ::SData/*12:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t;
        ::SData/*12:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__a0;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__a1;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__b0;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__b1;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__mm_x;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__mm_y;
        ::SData/*11:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_r;
        ::SData/*12:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_t;
    };
    struct {
        ::SData/*13:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_r0;
        ::SData/*15:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt;
        ::SData/*9:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh;
        ::SData/*15:0*/ tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt;
        ::IData/*31:0*/ tb_fpga__DOT__sendb__Vstatic__k;
        ::IData/*31:0*/ tb_fpga__DOT__recvb__Vstatic__k;
        ::IData/*31:0*/ tb_fpga__DOT__errs;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__mem_rdata;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ram_q;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wdata;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wdata;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__timer;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_rd;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_word;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__current_pc;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_q;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs1;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs2;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_rd;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____VlemCond_4;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__lfsr;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__breg;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__xs0;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__xs1;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__xs2;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__xs3;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__xr7;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__xa2;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__xa3;
        ::IData/*23:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_p;
        ::IData/*23:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_p;
        ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_rd;
        ::VlWide<50>/*1599:0*/ tb_fpga__DOT__dut__DOT__kise__DOT__st;
        ::IData/*31:0*/ __Vdfg_Regularize_1139;
        ::IData/*31:0*/ __Vi;
        ::QData/*63:0*/ tb_fpga__DOT__trig_cyc;
        ::QData/*63:0*/ tb_fpga__DOT__cyc;
        ::QData/*63:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle;
        ::QData/*63:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr;
        ::QData/*62:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor;
        ::QData/*32:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rs1;
        ::QData/*32:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rs2;
        ::QData/*63:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rd;
        ::QData/*63:0*/ __Vdfg_Regularize_1105;
        ::QData/*63:0*/ __Vdfg_Regularize_1106;
        ::QData/*63:0*/ __Vdfg_Regularize_1107;
        ::QData/*63:0*/ __Vdfg_Regularize_1108;
    };
    struct {
        ::QData/*63:0*/ __Vdfg_Regularize_1109;
        ::QData/*63:0*/ __Vdfg_Regularize_1110;
        ::QData/*63:0*/ __Vdfg_Regularize_1111;
        ::QData/*63:0*/ __Vdfg_Regularize_1112;
        ::QData/*63:0*/ __Vdfg_Regularize_1113;
        ::QData/*63:0*/ __Vdfg_Regularize_1114;
        ::QData/*63:0*/ __Vdfg_Regularize_1115;
        ::QData/*63:0*/ __Vdfg_Regularize_1116;
        ::QData/*63:0*/ __Vdfg_Regularize_1117;
        ::QData/*63:0*/ __Vdfg_Regularize_1118;
        ::QData/*63:0*/ __Vdfg_Regularize_1119;
        ::QData/*63:0*/ __Vdfg_Regularize_1120;
        ::QData/*63:0*/ __Vdfg_Regularize_1121;
        ::QData/*63:0*/ __Vdfg_Regularize_1122;
        ::QData/*63:0*/ __Vdfg_Regularize_1123;
        ::QData/*63:0*/ __Vdfg_Regularize_1124;
        ::QData/*63:0*/ __Vdfg_Regularize_1125;
        ::QData/*63:0*/ __Vdfg_Regularize_1126;
        ::QData/*63:0*/ __Vdfg_Regularize_1127;
        ::QData/*63:0*/ __Vdfg_Regularize_1128;
        ::QData/*63:0*/ __Vdfg_Regularize_1129;
        ::VlUnpacked<::CData/*7:0*/, 1664> tb_fpga__DOT__vec;
        ::VlUnpacked<::IData/*31:0*/, 32768> tb_fpga__DOT__dut__DOT__ram;
        ::VlUnpacked<::IData/*31:0*/, 32> tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs;
        ::VlUnpacked<::SData/*11:0*/, 5> tb_fpga__DOT__dut__DOT__ise__DOT__slot;
        ::VlUnpacked<::QData/*63:0*/, 1> __VstlTriggered;
        ::VlUnpacked<::QData/*63:0*/, 1> __VicoTriggered;
        ::VlUnpacked<::QData/*63:0*/, 1> __VactTriggered;
        ::VlUnpacked<::QData/*63:0*/, 1> __VactTriggeredAcc;
        ::VlUnpacked<::QData/*63:0*/, 1> __VnbaTriggered;
    };

    // NOT TRIVIALLY CONSTRUCTIBLE STATE
    union {
        struct {
            ::VlDelayScheduler __VdlySched;
            ::VlTriggerScheduler __VtrigSched_h6ba11e6d__0;
            ::VlTriggerScheduler __VtrigSched_hbf79de5d__0;
        } __Vnontrivs;
    };

    // INTERNAL VARIABLES
    Vtb_fpga__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_fpga___024root(Vtb_fpga__Syms* symsp, const char* namep);
    ~Vtb_fpga___024root();
    VL_UNCOPYABLE(Vtb_fpga___024root);
    VL_UNMOVABLE(Vtb_fpga___024root);

    // INTERNAL METHODS
};


#endif  // guard
