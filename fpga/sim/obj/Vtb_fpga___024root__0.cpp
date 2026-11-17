// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_fpga.h for the primary calling header

#include "Vtb_fpga__pch.h"

VlCoroutine Vtb_fpga___024root___eval_initial__TOP__Vtiming__0(Vtb_fpga___024root* vlSelf);
VlCoroutine Vtb_fpga___024root___eval_initial__TOP__Vtiming__1(Vtb_fpga___024root* vlSelf);

void Vtb_fpga___024root___eval_initial(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_initial\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_initial__TOP
        VL_READMEM_N(true, 8, 1664, 0, "vec.hex"s,  &(vlSelfRef.tb_fpga__DOT__vec)
                     , 0, ~0ULL);
        VL_READMEM_N(true, 32, 32768, 0, "../../sw/build/sca_app.hex"s
                     ,  &(vlSelfRef.tb_fpga__DOT__dut__DOT__ram)
                     , 0, ~0ULL);
    }
    Vtb_fpga___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_fpga___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

void Vtb_fpga___024root___eval_sample(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_sample\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_fpga___024root___dump_triggers__ico(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag);
#endif  // VL_DEBUG

bool Vtb_fpga___024root___eval_ico(Vtb_fpga___024root* vlSelf, ::CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_ico\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (::IData)((::IData)(firstIteration)));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_fpga___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    return (0U);
}

void Vtb_fpga___024root___timing_ready(Vtb_fpga___024root* vlSelf);
void Vtb_fpga___024root___trigger_orInto__act_vec_vec(::VlUnpacked<::QData/*63:0*/, 1> &out, const ::VlUnpacked<::QData/*63:0*/, 1> &in);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_fpga___024root___dump_triggers__act(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag);
#endif  // VL_DEBUG
bool Vtb_fpga___024root___trigger_anySet__act(const ::VlUnpacked<::QData/*63:0*/, 1> &in);
void Vtb_fpga___024root___timing_resume(Vtb_fpga___024root* vlSelf);

bool Vtb_fpga___024root___eval_act(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_act\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::CData/*0:0*/ __VactExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__act
        vlSelfRef.__VactTriggered[0U] = (::QData)((::IData)(
                                                            ((vlSelfRef.__Vnontrivs.__VdlySched.awaitingCurrentTime() 
                                                              << 2U) 
                                                             | ((((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd)) 
                                                                  & (::IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_fpga__DOT__dut__DOT__u_uart__DOT__txd__0)) 
                                                                 << 1U) 
                                                                | ((::IData)(vlSelfRef.tb_fpga__DOT__clk) 
                                                                   & (~ (::IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_fpga__DOT__clk__0)))))));
        vlSelfRef.__Vtrigprevexpr___TOP__tb_fpga__DOT__clk__0 
            = vlSelfRef.tb_fpga__DOT__clk;
        vlSelfRef.__Vtrigprevexpr___TOP__tb_fpga__DOT__dut__DOT__u_uart__DOT__txd__0 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd;
    }
    Vtb_fpga___024root___timing_ready(vlSelf);
    Vtb_fpga___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_fpga___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_fpga___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_fpga___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_fpga___024root___timing_resume(vlSelf);
        {
            // Inlined CFunc: _eval_body__act
            if ((((3ULL & vlSelfRef.__VactTriggered[0U])) != 0ULL)) {
                {
                    // Inlined CFunc: _act_comb__TOP__0
                    ::CData/*0:0*/ __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1103;
                    __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1103 = 0;
                    ::CData/*0:0*/ __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1138;
                    __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1138 = 0;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done 
                        = ((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
                           & (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst) 
                               & (3U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) 
                              | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer) 
                                 & ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state)) 
                                    & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata) 
                                       | (::IData)(vlSelfRef.__Vdfg_Regularize_1135))))));
                    __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1138 
                        = ((~ (0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) 
                           & (::IData)(vlSelfRef.tb_fpga__DOT__resetn));
                    __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1103 
                        = (((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
                            & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid)) 
                           & (0x02000033U == (0xfe00007fU 
                                              & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_write 
                        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata) 
                           & __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1138);
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_read 
                        = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch) 
                            | (::IData)(vlSelfRef.__Vdfg_Regularize_1135)) 
                           & __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1138);
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh 
                        = (::IData)((((0x00001000U 
                                       == (0x00007000U 
                                           & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                                      & __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1103) 
                                     & (0U != (7U & 
                                               (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                >> 0x0000000cU)))));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu 
                        = (::IData)((((0x00002000U 
                                       == (0x00007000U 
                                           & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                                      & __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1103) 
                                     & ((0U != (7U 
                                                & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                   >> 0x0000000cU))) 
                                        & (1U != (7U 
                                                  & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                     >> 0x0000000cU))))));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh 
                        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh) 
                           | ((::IData)((((0x00003000U 
                                           == (0x00007000U 
                                               & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                                          & __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1103) 
                                         & (((0U != 
                                              (7U & 
                                               (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                >> 0x0000000cU))) 
                                             & (1U 
                                                != 
                                                (7U 
                                                 & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                    >> 0x0000000cU)))) 
                                            & (2U != 
                                               (7U 
                                                & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                   >> 0x0000000cU)))))) 
                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mul 
                        = ((::IData)(((0U == (0x00007000U 
                                              & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                                      & __Vinline_0__eval_body__act___Vinline_0__act_comb__TOP__0___Vdfg_Regularize_1103)) 
                           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh));
                }
            }
        }
    }
    return (__VactExecute);
}

bool Vtb_fpga___024root___eval_inact(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_inact\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__Vnontrivs.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("tb_fpga.v", 3, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_fpga___024root___nba_sequent__TOP__0(Vtb_fpga___024root* vlSelf);
void Vtb_fpga___024root___trigger_clear__act(::VlUnpacked<::QData/*63:0*/, 1> &out);

bool Vtb_fpga___024root___eval_nba(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_nba\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_fpga___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        {
            // Inlined CFunc: _eval_body__nba
            if ((((1ULL & vlSelfRef.__VnbaTriggered[0U])) != 0ULL)) {
                Vtb_fpga___024root___nba_sequent__TOP__0(vlSelf);
            }
            if ((((3ULL & vlSelfRef.__VnbaTriggered[0U])) != 0ULL)) {
                {
                    // Inlined CFunc: _nba_comb__TOP__0
                    ::CData/*0:0*/ __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1103;
                    __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1103 = 0;
                    ::CData/*0:0*/ __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1138;
                    __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1138 = 0;
                    __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1103 
                        = (((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
                            & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid)) 
                           & (0x02000033U == (0xfe00007fU 
                                              & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)));
                    __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1138 
                        = ((~ (0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) 
                           & (::IData)(vlSelfRef.tb_fpga__DOT__resetn));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done 
                        = ((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
                           & (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst) 
                               & (3U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) 
                              | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer) 
                                 & ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state)) 
                                    & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata) 
                                       | (::IData)(vlSelfRef.__Vdfg_Regularize_1135))))));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh 
                        = (::IData)((((0x00001000U 
                                       == (0x00007000U 
                                           & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                                      & __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1103) 
                                     & (0U != (7U & 
                                               (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                >> 0x0000000cU)))));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu 
                        = (::IData)((((0x00002000U 
                                       == (0x00007000U 
                                           & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                                      & __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1103) 
                                     & ((0U != (7U 
                                                & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                   >> 0x0000000cU))) 
                                        & (1U != (7U 
                                                  & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                     >> 0x0000000cU))))));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_write 
                        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata) 
                           & __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1138);
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_read 
                        = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch) 
                            | (::IData)(vlSelfRef.__Vdfg_Regularize_1135)) 
                           & __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1138);
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh 
                        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh) 
                           | ((::IData)((((0x00003000U 
                                           == (0x00007000U 
                                               & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                                          & __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1103) 
                                         & (((0U != 
                                              (7U & 
                                               (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                >> 0x0000000cU))) 
                                             & (1U 
                                                != 
                                                (7U 
                                                 & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                    >> 0x0000000cU)))) 
                                            & (2U != 
                                               (7U 
                                                & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                   >> 0x0000000cU)))))) 
                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mul 
                        = ((::IData)(((0U == (0x00007000U 
                                              & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                                      & __Vinline_0__eval_body__nba___Vinline_0__nba_comb__TOP__0___Vdfg_Regularize_1103)) 
                           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh));
                }
            }
        }
        Vtb_fpga___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

bool Vtb_fpga___024root___eval_obs(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_obs\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

bool Vtb_fpga___024root___eval_react(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_react\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    return (0U);
}

void Vtb_fpga___024root___eval_postponed(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_postponed\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(Vtb_fpga___024root* vlSelf, const char* __VeventDescription);
void Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(Vtb_fpga___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_fpga___024root___eval_initial__TOP__Vtiming__0(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::CData/*7:0*/ tb_fpga__DOT__sendb__Vstatic__b;
    tb_fpga__DOT__sendb__Vstatic__b = 0;
    ::IData/*31:0*/ tb_fpga__DOT__i;
    tb_fpga__DOT__i = 0;
    ::IData/*31:0*/ tb_fpga__DOT__m;
    tb_fpga__DOT__m = 0;
    ::CData/*7:0*/ tb_fpga__DOT__b;
    tb_fpga__DOT__b = 0;
    ::IData/*31:0*/ tb_fpga__DOT__unnamedblk1_6__DOT____Vrepeat5;
    tb_fpga__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__recvb__b_0;
    __Vtask_tb_fpga__DOT__recvb__b_0 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_1;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_1 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_2;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_2 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_3;
    __Vtask_tb_fpga__DOT__sendb__b_3 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_4;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_4 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_5;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_5 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_6;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_6 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_7;
    __Vtask_tb_fpga__DOT__sendb__b_7 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_8;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_8 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_9;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_9 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_10;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_10 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__recvb__b_11;
    __Vtask_tb_fpga__DOT__recvb__b_11 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_12;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_12 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_13;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_13 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__recvb__b_14;
    __Vtask_tb_fpga__DOT__recvb__b_14 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_15;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_15 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_16;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_16 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_17;
    __Vtask_tb_fpga__DOT__sendb__b_17 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_18;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_18 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_19;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_19 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_20;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_20 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_21;
    __Vtask_tb_fpga__DOT__sendb__b_21 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_22;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_22 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_23;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_23 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_24;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_24 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__recvb__b_25;
    __Vtask_tb_fpga__DOT__recvb__b_25 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_26;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_26 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_27;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_27 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_28;
    __Vtask_tb_fpga__DOT__sendb__b_28 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_29;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_29 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_30;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_30 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_31;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_31 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_32;
    __Vtask_tb_fpga__DOT__sendb__b_32 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_33;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_33 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_34;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_34 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_35;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_35 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__recvb__b_36;
    __Vtask_tb_fpga__DOT__recvb__b_36 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_37;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_37 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_38;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_38 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__recvb__b_39;
    __Vtask_tb_fpga__DOT__recvb__b_39 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_40;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_40 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_41;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_41 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_42;
    __Vtask_tb_fpga__DOT__sendb__b_42 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_43;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_43 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_44;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_44 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_45;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_45 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_46;
    __Vtask_tb_fpga__DOT__sendb__b_46 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_47;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_47 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_48;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_48 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_49;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_49 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__recvb__b_50;
    __Vtask_tb_fpga__DOT__recvb__b_50 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_51;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_51 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_52;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_52 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_53;
    __Vtask_tb_fpga__DOT__sendb__b_53 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_54;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_54 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_55;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_55 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_56;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_56 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_57;
    __Vtask_tb_fpga__DOT__sendb__b_57 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_58;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_58 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_59;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_59 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_60;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_60 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__recvb__b_61;
    __Vtask_tb_fpga__DOT__recvb__b_61 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_62;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_62 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_63;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_63 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_64;
    __Vtask_tb_fpga__DOT__sendb__b_64 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_65;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_65 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_66;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_66 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_67;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_67 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_68;
    __Vtask_tb_fpga__DOT__sendb__b_68 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_69;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_69 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_70;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_70 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_71;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_71 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__sendb__b_72;
    __Vtask_tb_fpga__DOT__sendb__b_72 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_73;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_73 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_74;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_74 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_75;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_75 = 0;
    ::CData/*7:0*/ __Vtask_tb_fpga__DOT__recvb__b_76;
    __Vtask_tb_fpga__DOT__recvb__b_76 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_77;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_77 = 0;
    ::IData/*31:0*/ __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_78;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_78 = 0;
    // Body
    vlSelfRef.tb_fpga__DOT__trig_cyc = 0ULL;
    tb_fpga__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0x00000014U;
    while (VL_LTS_III(32, 0U, tb_fpga__DOT__unnamedblk1_6__DOT____Vrepeat5)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         34);
        tb_fpga__DOT__unnamedblk1_6__DOT____Vrepeat5 
            = (tb_fpga__DOT__unnamedblk1_6__DOT____Vrepeat5 
               - (::IData)(1U));
    }
    vlSelfRef.tb_fpga__DOT__resetn = 1U;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_1 = 0U;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_2 = 0U;
    Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(vlSelf, 
                                                   "@(negedge tb_fpga.dut.u_uart.txd)");
    co_await vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(negedge tb_fpga.dut.u_uart.txd)", 
                                                                     "tb_fpga.v", 
                                                                     22);
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_1 = 0x0000000cU;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_1)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         22);
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_1 
            = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_1 
               - (::IData)(1U));
    }
    vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 0U;
    while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k)) {
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b = 
            (((~ ((::IData)(1U) << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))) 
              & (::IData)(vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b)) 
             | (0x00ffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd) 
                           << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))));
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_2 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_2)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             23);
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_2 
                = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_2 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 
            ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k);
    }
    __Vtask_tb_fpga__DOT__recvb__b_0 = vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b;
    tb_fpga__DOT__b = __Vtask_tb_fpga__DOT__recvb__b_0;
    if ((0x52U != (::IData)(tb_fpga__DOT__b))) {
        vlSelfRef.tb_fpga__DOT__errs = ((::IData)(1U) 
                                        + vlSelfRef.tb_fpga__DOT__errs);
    }
    __Vtask_tb_fpga__DOT__sendb__b_3 = 0x4bU;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_4 = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_5 = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_6 = 0U;
    tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_3;
    vlSelfRef.tb_fpga__DOT__host_tx = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_4 = 8U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_4)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         17);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_4 
            = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_4 
               - (::IData)(1U));
    }
    vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
    while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
        vlSelfRef.tb_fpga__DOT__host_tx = (1U & ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                 >> 
                                                 (7U 
                                                  & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_5 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_5)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             18);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_5 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_5 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 
            ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
    }
    vlSelfRef.tb_fpga__DOT__host_tx = 1U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_6 = 0x00000010U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_6)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         19);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_6 
            = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_6 
               - (::IData)(1U));
    }
    tb_fpga__DOT__i = 0U;
    while (VL_GTS_III(32, 0x00000040U, tb_fpga__DOT__i)) {
        __Vtask_tb_fpga__DOT__sendb__b_7 = ((0x067fU 
                                             >= (0x000007ffU 
                                                 & tb_fpga__DOT__i))
                                             ? vlSelfRef.tb_fpga__DOT__vec
                                            [(0x000007ffU 
                                              & tb_fpga__DOT__i)]
                                             : 0U);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_8 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_9 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_10 = 0U;
        tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_7;
        vlSelfRef.tb_fpga__DOT__host_tx = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_8 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_8)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             17);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_8 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_8 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__host_tx = (1U & 
                                               ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                >> 
                                                (7U 
                                                 & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_9 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_9)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                18);
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_9 
                    = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_9 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
        }
        vlSelfRef.tb_fpga__DOT__host_tx = 1U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_10 = 0x00000010U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_10)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             19);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_10 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_10 
                   - (::IData)(1U));
        }
        tb_fpga__DOT__i = ((::IData)(1U) + tb_fpga__DOT__i);
    }
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_12 = 0U;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_13 = 0U;
    Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(vlSelf, 
                                                   "@(negedge tb_fpga.dut.u_uart.txd)");
    co_await vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(negedge tb_fpga.dut.u_uart.txd)", 
                                                                     "tb_fpga.v", 
                                                                     22);
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_12 = 0x0000000cU;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_12)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         22);
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_12 
            = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_12 
               - (::IData)(1U));
    }
    vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 0U;
    while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k)) {
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b = 
            (((~ ((::IData)(1U) << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))) 
              & (::IData)(vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b)) 
             | (0x00ffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd) 
                           << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))));
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_13 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_13)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             23);
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_13 
                = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_13 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 
            ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k);
    }
    __Vtask_tb_fpga__DOT__recvb__b_11 = vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b;
    tb_fpga__DOT__b = __Vtask_tb_fpga__DOT__recvb__b_11;
    if ((0x6bU != (::IData)(tb_fpga__DOT__b))) {
        vlSelfRef.tb_fpga__DOT__errs = ((::IData)(1U) 
                                        + vlSelfRef.tb_fpga__DOT__errs);
    }
    tb_fpga__DOT__i = 0U;
    while (VL_GTS_III(32, 0x00000320U, tb_fpga__DOT__i)) {
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_15 = 0U;
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_16 = 0U;
        Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(vlSelf, 
                                                       "@(negedge tb_fpga.dut.u_uart.txd)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(negedge tb_fpga.dut.u_uart.txd)", 
                                                                         "tb_fpga.v", 
                                                                         22);
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_15 = 0x0000000cU;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_15)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             22);
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_15 
                = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_15 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b 
                = (((~ ((::IData)(1U) << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))) 
                    & (::IData)(vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b)) 
                   | (0x00ffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd) 
                                 << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))));
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_16 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_16)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                23);
                __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_16 
                    = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_16 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k);
        }
        __Vtask_tb_fpga__DOT__recvb__b_14 = vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b;
        tb_fpga__DOT__b = __Vtask_tb_fpga__DOT__recvb__b_14;
        if (((::IData)(tb_fpga__DOT__b) != ((0x067fU 
                                             >= (0x000007ffU 
                                                 & ((::IData)(0x0040U) 
                                                    + tb_fpga__DOT__i)))
                                             ? vlSelfRef.tb_fpga__DOT__vec
                                            [(0x000007ffU 
                                              & ((::IData)(0x0040U) 
                                                 + tb_fpga__DOT__i))]
                                             : 0U))) {
            vlSelfRef.tb_fpga__DOT__errs = ((::IData)(1U) 
                                            + vlSelfRef.tb_fpga__DOT__errs);
        }
        tb_fpga__DOT__i = ((::IData)(1U) + tb_fpga__DOT__i);
    }
    VL_WRITEF_NX("keygen done, pk mismatches so far: %0d\n",1
                 , '~',32,vlSelfRef.tb_fpga__DOT__errs);
    VL_FFLUSH_MT();tb_fpga__DOT__m = 0U;
    while (VL_GTS_III(32, 3U, tb_fpga__DOT__m)) {
        __Vtask_tb_fpga__DOT__sendb__b_17 = 0x4dU;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_18 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_19 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_20 = 0U;
        tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_17;
        vlSelfRef.tb_fpga__DOT__host_tx = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_18 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_18)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             17);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_18 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_18 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__host_tx = (1U & 
                                               ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                >> 
                                                (7U 
                                                 & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_19 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_19)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                18);
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_19 
                    = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_19 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
        }
        vlSelfRef.tb_fpga__DOT__host_tx = 1U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_20 = 0x00000010U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_20)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             19);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_20 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_20 
                   - (::IData)(1U));
        }
        __Vtask_tb_fpga__DOT__sendb__b_21 = (0x000000ffU 
                                             & tb_fpga__DOT__m);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_22 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_23 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_24 = 0U;
        tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_21;
        vlSelfRef.tb_fpga__DOT__host_tx = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_22 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_22)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             17);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_22 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_22 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__host_tx = (1U & 
                                               ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                >> 
                                                (7U 
                                                 & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_23 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_23)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                18);
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_23 
                    = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_23 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
        }
        vlSelfRef.tb_fpga__DOT__host_tx = 1U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_24 = 0x00000010U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_24)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             19);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_24 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_24 
                   - (::IData)(1U));
        }
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_26 = 0U;
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_27 = 0U;
        Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(vlSelf, 
                                                       "@(negedge tb_fpga.dut.u_uart.txd)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(negedge tb_fpga.dut.u_uart.txd)", 
                                                                         "tb_fpga.v", 
                                                                         22);
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_26 = 0x0000000cU;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_26)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             22);
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_26 
                = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_26 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b 
                = (((~ ((::IData)(1U) << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))) 
                    & (::IData)(vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b)) 
                   | (0x00ffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd) 
                                 << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))));
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_27 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_27)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                23);
                __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_27 
                    = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_27 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k);
        }
        __Vtask_tb_fpga__DOT__recvb__b_25 = vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b;
        tb_fpga__DOT__b = __Vtask_tb_fpga__DOT__recvb__b_25;
        vlSelfRef.tb_fpga__DOT__trig_cyc = 0ULL;
        __Vtask_tb_fpga__DOT__sendb__b_28 = 0x44U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_29 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_30 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_31 = 0U;
        tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_28;
        vlSelfRef.tb_fpga__DOT__host_tx = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_29 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_29)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             17);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_29 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_29 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__host_tx = (1U & 
                                               ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                >> 
                                                (7U 
                                                 & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_30 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_30)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                18);
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_30 
                    = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_30 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
        }
        vlSelfRef.tb_fpga__DOT__host_tx = 1U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_31 = 0x00000010U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_31)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             19);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_31 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_31 
                   - (::IData)(1U));
        }
        tb_fpga__DOT__i = 0U;
        while (VL_GTS_III(32, 0x00000300U, tb_fpga__DOT__i)) {
            __Vtask_tb_fpga__DOT__sendb__b_32 = ((0x067fU 
                                                  >= 
                                                  (0x000007ffU 
                                                   & ((::IData)(0x0360U) 
                                                      + tb_fpga__DOT__i)))
                                                  ? vlSelfRef.tb_fpga__DOT__vec
                                                 [(0x000007ffU 
                                                   & ((::IData)(0x0360U) 
                                                      + tb_fpga__DOT__i))]
                                                  : 0U);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_33 = 0U;
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_34 = 0U;
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_35 = 0U;
            tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_32;
            vlSelfRef.tb_fpga__DOT__host_tx = 0U;
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_33 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_33)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                17);
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_33 
                    = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_33 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
            while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
                vlSelfRef.tb_fpga__DOT__host_tx = (1U 
                                                   & ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                      >> 
                                                      (7U 
                                                       & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_34 = 8U;
                while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_34)) {
                    Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                                   "@(posedge tb_fpga.clk)");
                    co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                18);
                    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_34 
                        = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_34 
                           - (::IData)(1U));
                }
                vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k 
                    = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
            }
            vlSelfRef.tb_fpga__DOT__host_tx = 1U;
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_35 = 0x00000010U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_35)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                19);
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_35 
                    = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_35 
                       - (::IData)(1U));
            }
            tb_fpga__DOT__i = ((::IData)(1U) + tb_fpga__DOT__i);
        }
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_37 = 0U;
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_38 = 0U;
        Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(vlSelf, 
                                                       "@(negedge tb_fpga.dut.u_uart.txd)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(negedge tb_fpga.dut.u_uart.txd)", 
                                                                         "tb_fpga.v", 
                                                                         22);
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_37 = 0x0000000cU;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_37)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             22);
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_37 
                = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_37 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b 
                = (((~ ((::IData)(1U) << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))) 
                    & (::IData)(vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b)) 
                   | (0x00ffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd) 
                                 << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))));
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_38 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_38)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                23);
                __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_38 
                    = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_38 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k);
        }
        __Vtask_tb_fpga__DOT__recvb__b_36 = vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b;
        tb_fpga__DOT__b = __Vtask_tb_fpga__DOT__recvb__b_36;
        if ((0x64U != (::IData)(tb_fpga__DOT__b))) {
            vlSelfRef.tb_fpga__DOT__errs = ((::IData)(1U) 
                                            + vlSelfRef.tb_fpga__DOT__errs);
        }
        tb_fpga__DOT__i = 0U;
        while (VL_GTS_III(32, 0x00000020U, tb_fpga__DOT__i)) {
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_40 = 0U;
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_41 = 0U;
            Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(vlSelf, 
                                                           "@(negedge tb_fpga.dut.u_uart.txd)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(negedge tb_fpga.dut.u_uart.txd)", 
                                                                             "tb_fpga.v", 
                                                                             22);
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_40 = 0x0000000cU;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_40)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                22);
                __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_40 
                    = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_40 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 0U;
            while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k)) {
                vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b 
                    = (((~ ((::IData)(1U) << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))) 
                        & (::IData)(vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b)) 
                       | (0x00ffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd) 
                                     << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))));
                __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_41 = 8U;
                while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_41)) {
                    Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                                   "@(posedge tb_fpga.clk)");
                    co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                23);
                    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_41 
                        = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_41 
                           - (::IData)(1U));
                }
                vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k 
                    = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k);
            }
            __Vtask_tb_fpga__DOT__recvb__b_39 = vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b;
            tb_fpga__DOT__b = __Vtask_tb_fpga__DOT__recvb__b_39;
            if (((::IData)(tb_fpga__DOT__b) != ((0x067fU 
                                                 >= 
                                                 (0x000007ffU 
                                                  & ((::IData)(0x0660U) 
                                                     + tb_fpga__DOT__i)))
                                                 ? vlSelfRef.tb_fpga__DOT__vec
                                                [(0x000007ffU 
                                                  & ((::IData)(0x0660U) 
                                                     + tb_fpga__DOT__i))]
                                                 : 0U))) {
                vlSelfRef.tb_fpga__DOT__errs = ((::IData)(1U) 
                                                + vlSelfRef.tb_fpga__DOT__errs);
            }
            tb_fpga__DOT__i = ((::IData)(1U) + tb_fpga__DOT__i);
        }
        VL_WRITEF_NX("mode %0d: decapsulation %0d cycles under trigger, errors so far %0d\n",3
                     , '~',32,tb_fpga__DOT__m, '#',64,vlSelfRef.tb_fpga__DOT__trig_cyc
                     , '~',32,vlSelfRef.tb_fpga__DOT__errs);
        VL_FFLUSH_MT();tb_fpga__DOT__m = ((::IData)(1U) 
                                          + tb_fpga__DOT__m);
    }
    __Vtask_tb_fpga__DOT__sendb__b_42 = 0x4dU;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_43 = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_44 = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_45 = 0U;
    tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_42;
    vlSelfRef.tb_fpga__DOT__host_tx = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_43 = 8U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_43)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         17);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_43 
            = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_43 
               - (::IData)(1U));
    }
    vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
    while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
        vlSelfRef.tb_fpga__DOT__host_tx = (1U & ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                 >> 
                                                 (7U 
                                                  & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_44 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_44)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             18);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_44 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_44 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 
            ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
    }
    vlSelfRef.tb_fpga__DOT__host_tx = 1U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_45 = 0x00000010U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_45)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         19);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_45 
            = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_45 
               - (::IData)(1U));
    }
    __Vtask_tb_fpga__DOT__sendb__b_46 = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_47 = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_48 = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_49 = 0U;
    tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_46;
    vlSelfRef.tb_fpga__DOT__host_tx = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_47 = 8U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_47)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         17);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_47 
            = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_47 
               - (::IData)(1U));
    }
    vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
    while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
        vlSelfRef.tb_fpga__DOT__host_tx = (1U & ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                 >> 
                                                 (7U 
                                                  & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_48 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_48)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             18);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_48 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_48 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 
            ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
    }
    vlSelfRef.tb_fpga__DOT__host_tx = 1U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_49 = 0x00000010U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_49)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         19);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_49 
            = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_49 
               - (::IData)(1U));
    }
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_51 = 0U;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_52 = 0U;
    Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(vlSelf, 
                                                   "@(negedge tb_fpga.dut.u_uart.txd)");
    co_await vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(negedge tb_fpga.dut.u_uart.txd)", 
                                                                     "tb_fpga.v", 
                                                                     22);
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_51 = 0x0000000cU;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_51)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         22);
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_51 
            = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_51 
               - (::IData)(1U));
    }
    vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 0U;
    while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k)) {
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b = 
            (((~ ((::IData)(1U) << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))) 
              & (::IData)(vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b)) 
             | (0x00ffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd) 
                           << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))));
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_52 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_52)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             23);
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_52 
                = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_52 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 
            ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k);
    }
    __Vtask_tb_fpga__DOT__recvb__b_50 = vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b;
    tb_fpga__DOT__b = __Vtask_tb_fpga__DOT__recvb__b_50;
    vlSelfRef.tb_fpga__DOT__trig_cyc = 0ULL;
    __Vtask_tb_fpga__DOT__sendb__b_53 = 0x42U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_54 = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_55 = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_56 = 0U;
    tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_53;
    vlSelfRef.tb_fpga__DOT__host_tx = 0U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_54 = 8U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_54)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         17);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_54 
            = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_54 
               - (::IData)(1U));
    }
    vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
    while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
        vlSelfRef.tb_fpga__DOT__host_tx = (1U & ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                 >> 
                                                 (7U 
                                                  & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_55 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_55)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             18);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_55 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_55 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 
            ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
    }
    vlSelfRef.tb_fpga__DOT__host_tx = 1U;
    __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_56 = 0x00000010U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_56)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         19);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_56 
            = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_56 
               - (::IData)(1U));
    }
    tb_fpga__DOT__i = 0U;
    while (VL_GTS_III(32, 8U, tb_fpga__DOT__i)) {
        __Vtask_tb_fpga__DOT__sendb__b_57 = (0x000000ffU 
                                             & VL_MULS_III(32, (::IData)(0x00000025U), tb_fpga__DOT__i));
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_58 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_59 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_60 = 0U;
        tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_57;
        vlSelfRef.tb_fpga__DOT__host_tx = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_58 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_58)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             17);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_58 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_58 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__host_tx = (1U & 
                                               ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                >> 
                                                (7U 
                                                 & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_59 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_59)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                18);
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_59 
                    = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_59 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
        }
        vlSelfRef.tb_fpga__DOT__host_tx = 1U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_60 = 0x00000010U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_60)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             19);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_60 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_60 
                   - (::IData)(1U));
        }
        tb_fpga__DOT__i = ((::IData)(1U) + tb_fpga__DOT__i);
    }
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_62 = 0U;
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_63 = 0U;
    Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(vlSelf, 
                                                   "@(negedge tb_fpga.dut.u_uart.txd)");
    co_await vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(negedge tb_fpga.dut.u_uart.txd)", 
                                                                     "tb_fpga.v", 
                                                                     22);
    __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_62 = 0x0000000cU;
    while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_62)) {
        Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                       "@(posedge tb_fpga.clk)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(posedge tb_fpga.clk)", 
                                                                         "tb_fpga.v", 
                                                                         22);
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_62 
            = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_62 
               - (::IData)(1U));
    }
    vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 0U;
    while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k)) {
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b = 
            (((~ ((::IData)(1U) << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))) 
              & (::IData)(vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b)) 
             | (0x00ffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd) 
                           << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))));
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_63 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_63)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             23);
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_63 
                = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_63 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 
            ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k);
    }
    __Vtask_tb_fpga__DOT__recvb__b_61 = vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b;
    tb_fpga__DOT__b = __Vtask_tb_fpga__DOT__recvb__b_61;
    VL_WRITEF_NX("basemul window: %0d cycles under trigger, reply %c\n",2
                 , '#',64,vlSelfRef.tb_fpga__DOT__trig_cyc
                 , '#',8,(::IData)(tb_fpga__DOT__b));
    tb_fpga__DOT__m = 0U;
    while (VL_GTS_III(32, 6U, tb_fpga__DOT__m)) {
        vlSelfRef.tb_fpga__DOT__trig_cyc = 0ULL;
        __Vtask_tb_fpga__DOT__sendb__b_64 = 0x54U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_65 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_66 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_67 = 0U;
        tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_64;
        vlSelfRef.tb_fpga__DOT__host_tx = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_65 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_65)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             17);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_65 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_65 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__host_tx = (1U & 
                                               ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                >> 
                                                (7U 
                                                 & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_66 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_66)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                18);
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_66 
                    = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_66 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
        }
        vlSelfRef.tb_fpga__DOT__host_tx = 1U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_67 = 0x00000010U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_67)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             19);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_67 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_67 
                   - (::IData)(1U));
        }
        __Vtask_tb_fpga__DOT__sendb__b_68 = (0x000000ffU 
                                             & tb_fpga__DOT__m);
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_69 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_70 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_71 = 0U;
        tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_68;
        vlSelfRef.tb_fpga__DOT__host_tx = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_69 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_69)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             17);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_69 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_69 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__host_tx = (1U & 
                                               ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                >> 
                                                (7U 
                                                 & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_70 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_70)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                18);
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_70 
                    = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_70 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
        }
        vlSelfRef.tb_fpga__DOT__host_tx = 1U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_71 = 0x00000010U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_71)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             19);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_71 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_71 
                   - (::IData)(1U));
        }
        __Vtask_tb_fpga__DOT__sendb__b_72 = 1U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_73 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_74 = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_75 = 0U;
        tb_fpga__DOT__sendb__Vstatic__b = __Vtask_tb_fpga__DOT__sendb__b_72;
        vlSelfRef.tb_fpga__DOT__host_tx = 0U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_73 = 8U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_73)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             17);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_73 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_1__DOT____Vrepeat0_73 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__host_tx = (1U & 
                                               ((::IData)(tb_fpga__DOT__sendb__Vstatic__b) 
                                                >> 
                                                (7U 
                                                 & vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k)));
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_74 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_74)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                18);
                __Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_74 
                    = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_2__DOT____Vrepeat1_74 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k);
        }
        vlSelfRef.tb_fpga__DOT__host_tx = 1U;
        __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_75 = 0x00000010U;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_75)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             19);
            __Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_75 
                = (__Vtask_tb_fpga__DOT__sendb__unnamedblk1_3__DOT____Vrepeat2_75 
                   - (::IData)(1U));
        }
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_77 = 0U;
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_78 = 0U;
        Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(vlSelf, 
                                                       "@(negedge tb_fpga.dut.u_uart.txd)");
        co_await vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.trigger(0U, 
                                                                         nullptr, 
                                                                         "@(negedge tb_fpga.dut.u_uart.txd)", 
                                                                         "tb_fpga.v", 
                                                                         22);
        __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_77 = 0x0000000cU;
        while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_77)) {
            Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                           "@(posedge tb_fpga.clk)");
            co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                             nullptr, 
                                                                             "@(posedge tb_fpga.clk)", 
                                                                             "tb_fpga.v", 
                                                                             22);
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_77 
                = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_4__DOT____Vrepeat3_77 
                   - (::IData)(1U));
        }
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = 0U;
        while (VL_GTS_III(32, 8U, vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k)) {
            vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b 
                = (((~ ((::IData)(1U) << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))) 
                    & (::IData)(vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b)) 
                   | (0x00ffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd) 
                                 << (7U & vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k))));
            __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_78 = 8U;
            while (VL_LTS_III(32, 0U, __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_78)) {
                Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(vlSelf, 
                                                               "@(posedge tb_fpga.clk)");
                co_await vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.trigger(0U, 
                                                                                nullptr, 
                                                                                "@(posedge tb_fpga.clk)", 
                                                                                "tb_fpga.v", 
                                                                                23);
                __Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_78 
                    = (__Vtask_tb_fpga__DOT__recvb__unnamedblk1_5__DOT____Vrepeat4_78 
                       - (::IData)(1U));
            }
            vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k 
                = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k);
        }
        __Vtask_tb_fpga__DOT__recvb__b_76 = vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b;
        tb_fpga__DOT__b = __Vtask_tb_fpga__DOT__recvb__b_76;
        VL_WRITEF_NX("TVLA target %0d: %0d cycles under trigger, reply %c\n",3
                     , '~',32,tb_fpga__DOT__m, '#',64,vlSelfRef.tb_fpga__DOT__trig_cyc
                     , '#',8,(::IData)(tb_fpga__DOT__b));
        tb_fpga__DOT__m = ((::IData)(1U) + tb_fpga__DOT__m);
    }
    VL_WRITEF_NX("RESULT %s errors=%0d\n",2, '#',32,
                 ((0U == vlSelfRef.tb_fpga__DOT__errs)
                   ? 0x50415353U : 0x4641494cU), '~',32,vlSelfRef.tb_fpga__DOT__errs);
    VL_FINISH_MT("tb_fpga.v", 57, "");
    co_return;
}

VlCoroutine Vtb_fpga___024root___eval_initial__TOP__Vtiming__1(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__Vnontrivs.__VdlySched.delay(0x0000000000004e20ULL, 
                                                         nullptr, 
                                                         "tb_fpga.v", 
                                                         6);
        vlSelfRef.tb_fpga__DOT__clk = (1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__clk)));
    }
    co_return;
}

bool Vtb_fpga___024root___trigger_anySet__ico(const ::VlUnpacked<::QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___trigger_anySet__ico\n"); );
    // Locals
    ::IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((::IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

bool Vtb_fpga___024root___trigger_anySet__act(const ::VlUnpacked<::QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___trigger_anySet__act\n"); );
    // Locals
    ::IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((::IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const ::VlWide<64>/*2047:0*/ Vtb_fpga__ConstPool__CONST_0;

void Vtb_fpga___024root___nba_sequent__TOP__0(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___nba_sequent__TOP__0\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT____Vcellinp__cpu__pcpi_ready;
    tb_fpga__DOT__dut__DOT____Vcellinp__cpu__pcpi_ready = 0;
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rinst;
    tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rinst = 0;
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rdata;
    tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rdata = 0;
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_wdata;
    tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_wdata = 0;
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__alu_eq;
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_eq = 0;
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__alu_ltu;
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_ltu = 0;
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__alu_lts;
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_lts = 0;
    ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__x5;
    tb_fpga__DOT__dut__DOT__ise__DOT__x5 = 0;
    ::IData/*23:0*/ tb_fpga__DOT__dut__DOT__ise__DOT____Vconcswap_1_ha31419c7__0;
    tb_fpga__DOT__dut__DOT__ise__DOT____Vconcswap_1_ha31419c7__0 = 0;
    ::CData/*2:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand;
    tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_0;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_0 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_1;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_1 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_2;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_2 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_3;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_3 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_4;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_4 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_5;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_5 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_6;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_6 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_7;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_7 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_8;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_8 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_9;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_9 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_10;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_10 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_11;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_11 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_12;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_12 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_13;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_13 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_14;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_14 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_15;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_15 = 0;
    ::IData/*23:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__Vfuncout_16;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__Vfuncout_16 = 0;
    ::CData/*2:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__s_17;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__s_17 = 0;
    ::IData/*23:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCond_2_18;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCond_2_18 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCall_1__msub_19;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCall_1__msub_19 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCall_0__msub_20;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCall_0__msub_20 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vfuncout_21;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vfuncout_21 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_22;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_22 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_23;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_23 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vfuncout_24;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vfuncout_24 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_25;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_25 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_26;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_26 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_27;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_27 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_28;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_28 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_29;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_29 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_30;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_30 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_31;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_31 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_32;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_32 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_33;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_33 = 0;
    ::SData/*11:0*/ __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_34;
    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_34 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1098;
    __Vdfg_Regularize_1098 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1099;
    __Vdfg_Regularize_1099 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1100;
    __Vdfg_Regularize_1100 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1101;
    __Vdfg_Regularize_1101 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1102;
    __Vdfg_Regularize_1102 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1130;
    __Vdfg_Regularize_1130 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1131;
    __Vdfg_Regularize_1131 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1132;
    __Vdfg_Regularize_1132 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1133;
    __Vdfg_Regularize_1133 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1134;
    __Vdfg_Regularize_1134 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1165;
    __Vdfg_Regularize_1165 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1166;
    __Vdfg_Regularize_1166 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1167;
    __Vdfg_Regularize_1167 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1168;
    __Vdfg_Regularize_1168 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1169;
    __Vdfg_Regularize_1169 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1170;
    __Vdfg_Regularize_1170 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1171;
    __Vdfg_Regularize_1171 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1172;
    __Vdfg_Regularize_1172 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1173;
    __Vdfg_Regularize_1173 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1174;
    __Vdfg_Regularize_1174 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1175;
    __Vdfg_Regularize_1175 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1176;
    __Vdfg_Regularize_1176 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1177;
    __Vdfg_Regularize_1177 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1178;
    __Vdfg_Regularize_1178 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1179;
    __Vdfg_Regularize_1179 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1180;
    __Vdfg_Regularize_1180 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1181;
    __Vdfg_Regularize_1181 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1182;
    __Vdfg_Regularize_1182 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1183;
    __Vdfg_Regularize_1183 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1184;
    __Vdfg_Regularize_1184 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1185;
    __Vdfg_Regularize_1185 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1186;
    __Vdfg_Regularize_1186 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1187;
    __Vdfg_Regularize_1187 = 0;
    ::QData/*63:0*/ __Vdfg_Regularize_1188;
    __Vdfg_Regularize_1188 = 0;
    ::QData/*63:0*/ __Vdly__tb_fpga__DOT__trig_cyc_1;
    __Vdly__tb_fpga__DOT__trig_cyc_1 = 0;
    ::QData/*63:0*/ __Vdly_Mask__tb_fpga__DOT__trig_cyc_2;
    __Vdly_Mask__tb_fpga__DOT__trig_cyc_2 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__mem_ready_4;
    __Vdly__tb_fpga__DOT__dut__DOT__mem_ready_4 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__tx_start_5;
    __Vdly__tb_fpga__DOT__dut__DOT__tx_start_5 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__rx_full_6;
    __Vdly__tb_fpga__DOT__dut__DOT__rx_full_6 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__ram_pend_8;
    __Vdly__tb_fpga__DOT__dut__DOT__ram_pend_8 = 0;
    ::CData/*1:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state_14;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state_14 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal_19;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal_19 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lbu_lhu_lw_23;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lbu_lhu_lw_23 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal_27;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal_27 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr_28;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr_28 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq_29;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq_29 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu_30;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu_30 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu_31;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu_31 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw_32;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw_32 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb_47;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb_47 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh_48;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh_48 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle_74;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle_74 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr_76;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr_76 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai_81;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai_81 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi_82;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi_82 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_83;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_83 = 0;
    ::CData/*4:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh_85;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh_85 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata_88;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata_88 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata_89;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata_89 = 0;
    ::CData/*3:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter_91;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter_91 = 0;
    ::QData/*63:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle_93;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle_93 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger_94;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger_94 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc_98;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc_98 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc_99;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc_99 = 0;
    ::QData/*63:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr_108;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr_108 = 0;
    ::CData/*7:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running_124;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running_124 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend_125;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend_125 = 0;
    ::QData/*62:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor_126;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor_126 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_128;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_128 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk_129;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk_129 = 0;
    ::CData/*3:0*/ __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active_133;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active_133 = 0;
    ::CData/*1:0*/ __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__state_135;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__state_135 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready_136;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready_136 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__breg_139;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__breg_139 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__lfsr_145;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__lfsr_145 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__xs1_147;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__xs1_147 = 0;
    ::IData/*31:0*/ __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt_150;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt_150 = 0;
    ::CData/*2:0*/ __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy_154;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy_154 = 0;
    ::CData/*3:0*/ __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__ndummy_156;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__ndummy_156 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy_174;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy_174 = 0;
    ::SData/*15:0*/ __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt_176;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt_176 = 0;
    ::CData/*3:0*/ __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit_177;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit_177 = 0;
    ::SData/*9:0*/ __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh_178;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh_178 = 0;
    ::CData/*1:0*/ __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__sync_179;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__sync_179 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy_181;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy_181 = 0;
    ::SData/*15:0*/ __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt_182;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt_182 = 0;
    ::CData/*3:0*/ __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit_183;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit_183 = 0;
    ::CData/*7:0*/ __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh_184;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh_184 = 0;
    ::VlWide<50>/*1599:0*/ __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186;
    VL_ZERO_W(1600, __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186);
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready_188;
    __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready_188 = 0;
    ::CData/*4:0*/ __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__rnd_189;
    __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__rnd_189 = 0;
    ::CData/*0:0*/ __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__busy_190;
    __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__busy_190 = 0;
    ::CData/*7:0*/ __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_193;
    __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_193 = 0;
    ::SData/*14:0*/ __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_194;
    __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_194 = 0;
    ::CData/*0:0*/ __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_195;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_195 = 0;
    ::CData/*7:0*/ __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_196;
    __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_196 = 0;
    ::SData/*14:0*/ __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_197;
    __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_197 = 0;
    ::CData/*0:0*/ __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_198;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_198 = 0;
    ::CData/*7:0*/ __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_199;
    __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_199 = 0;
    ::SData/*14:0*/ __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_200;
    __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_200 = 0;
    ::CData/*0:0*/ __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_201;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_201 = 0;
    ::CData/*7:0*/ __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_202;
    __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_202 = 0;
    ::SData/*14:0*/ __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_203;
    __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_203 = 0;
    ::CData/*0:0*/ __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_204;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_204 = 0;
    ::IData/*31:0*/ __Vdly_Val__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_205;
    __Vdly_Val__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_205 = 0;
    ::CData/*4:0*/ __Vdly_Dim0__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_206;
    __Vdly_Dim0__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_206 = 0;
    ::CData/*0:0*/ __Vdly_Set__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_207;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_207 = 0;
    ::SData/*11:0*/ __Vdly_Val__tb_fpga__DOT__dut__DOT__ise__DOT__slot_208;
    __Vdly_Val__tb_fpga__DOT__dut__DOT__ise__DOT__slot_208 = 0;
    ::CData/*2:0*/ __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ise__DOT__slot_209;
    __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ise__DOT__slot_209 = 0;
    ::CData/*0:0*/ __Vdly_Set__tb_fpga__DOT__dut__DOT__ise__DOT__slot_210;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__ise__DOT__slot_210 = 0;
    ::IData/*31:0*/ __Vilp1;
    ::IData/*31:0*/ __Vilp2;
    ::IData/*31:0*/ __Vilp3;
    // Body
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle_93 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__sync_179 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__sync;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt_182 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt_176 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy_174 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit_177 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running_124 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk_129 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy_181 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit_183 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt_150 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt;
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh_184 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_128 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active_133 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr_108 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh_85 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata_89 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata_88 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu_31 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw_32 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq_29 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal_27 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr_28 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu_30 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy_154 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger_94 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__ise__DOT__slot_210 = 0U;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state_14 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal_19 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc_98 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc_99 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_207 = 0U;
    __Vdly__tb_fpga__DOT__dut__DOT__tx_start_5 = vlSelfRef.tb_fpga__DOT__dut__DOT__tx_start;
    __Vdly__tb_fpga__DOT__dut__DOT__rx_full_6 = vlSelfRef.tb_fpga__DOT__dut__DOT__rx_full;
    if (VL_UNLIKELY(((0ULL == VL_MODDIV_QQQ(64, vlSelfRef.tb_fpga__DOT__cyc, 0x00000000001e8480ULL))))) {
        VL_WRITEF_NX("progress cyc=%0d pc=%08x led=%b\n",3
                     , '#',64,vlSelfRef.tb_fpga__DOT__cyc
                     , '#',32,vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc
                     , '#',4,(::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__led));
        VL_FFLUSH_MT();}
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh_178 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh;
    __Vdly__tb_fpga__DOT__dut__DOT__ram_pend_8 = vlSelfRef.tb_fpga__DOT__dut__DOT__ram_pend;
    __Vdly__tb_fpga__DOT__dut__DOT__mem_ready_4 = vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_195 = 0U;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_198 = 0U;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_201 = 0U;
    __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_204 = 0U;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle_74 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr_76 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb_47 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh_48 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh;
    __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__rnd_189 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__rnd;
    __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__busy_190 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__busy;
    __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready_188 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready_136 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__lfsr_145 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__xs1_147 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs1;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai_81 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi_82 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi;
    __Vilp1 = 0U;
    while ((__Vilp1 <= 0x00000031U)) {
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[__Vilp1] 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st
            [__Vilp1];
        __Vilp1 = ((::IData)(1U) + __Vilp1);
    }
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_83 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__ndummy_156 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__ndummy;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lbu_lhu_lw_23 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lbu_lhu_lw;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__state_135 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state;
    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__breg_139 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__breg;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend_125 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor_126 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state;
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter_91 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter;
    if (vlSelfRef.tb_fpga__DOT__dut__DOT__trigger) {
        __Vdly__tb_fpga__DOT__trig_cyc_1 = (1ULL + vlSelfRef.tb_fpga__DOT__trig_cyc);
        __Vdly_Mask__tb_fpga__DOT__trig_cyc_2 = 0xffffffffffffffffULL;
    }
    vlSelfRef.tb_fpga__DOT__cyc = (1ULL + vlSelfRef.tb_fpga__DOT__cyc);
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle_93 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__resetn)
            ? (1ULL + vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle)
            : 0ULL);
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle_93 
        = (0x00000000ffffffffULL & __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle_93);
    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__sync_179 
        = ((2U & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__sync) 
                  << 1U)) | (::IData)(vlSelfRef.tb_fpga__DOT__host_tx));
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active_133 
        = ((0x0eU & (::IData)(__Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active_133)) 
           | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mul) 
              & (~ (0U != (3U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active))))));
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active_133 
        = ((1U & (::IData)(__Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active_133)) 
           | (0x0000000eU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active) 
                             << 1U)));
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh_85 = 0U;
    tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_wdata = 0U;
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy) {
            if ((7U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt))) {
                __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt_182 = 0U;
                if ((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit))) {
                    if ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__sync))) {
                        __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy_181 = 0U;
                    }
                } else if ((8U < (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit))) {
                    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy_181 = 0U;
                }
                __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit_183 
                    = (0x0000000fU & ((::IData)(1U) 
                                      + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit)));
                if ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit))) {
                    if ((8U >= (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit))) {
                        __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh_184 
                            = ((0x00000080U & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__sync) 
                                               << 6U)) 
                               | (0x0000007fU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh) 
                                                 >> 1U)));
                    }
                }
            } else {
                __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt_182 
                    = (0x0000ffffU & ((::IData)(1U) 
                                      + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt)));
            }
        } else if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__sync) 
                             >> 1U)))) {
            __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt_182 = 4U;
            __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy_181 = 1U;
            __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit_183 = 0U;
        }
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy) {
            if ((7U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt))) {
                __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt_176 = 0U;
                if ((9U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit))) {
                    __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy_174 = 0U;
                }
                __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit_177 
                    = (0x0000000fU & ((::IData)(1U) 
                                      + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit)));
            } else {
                __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt_176 
                    = (0x0000ffffU & ((::IData)(1U) 
                                      + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt)));
            }
        } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__tx_start) {
            __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt_176 = 0U;
            __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy_174 = 1U;
            __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit_177 = 0U;
        }
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__start) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running_124 = 1U;
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk_129 = 0x80000000U;
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_128 = 0U;
        } else {
            if (((~ (0U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk)) 
                 & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running))) {
                __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running_124 = 0U;
            }
            if ((1U & (~ ((~ (0U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk)) 
                          & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running))))) {
                __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk_129 
                    = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk 
                       >> 1U);
                if ((vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor 
                     <= (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend)))) {
                    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_128 
                        = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient 
                           | vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk);
                }
            }
        }
        if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state) 
                      >> 1U)))) {
            if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
                __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt_150 
                    = ((::IData)(1U) + vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt);
            }
        }
        if (((((((((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
                   | (0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                  | (0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                 | (0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                | (8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
               | (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
              | (2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
             | (1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))) {
            if ((0x80U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                if ((0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger) {
                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr_108 
                            = (1ULL + vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr);
                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr_108 
                            = (0x00000000ffffffffULL 
                               & __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr_108);
                    }
                }
                if ((0x40U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) 
                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)) 
                             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal))) {
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                                __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh_85 
                                    = (0x0000001fU 
                                       & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs2);
                            }
                        } else if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu) 
                                             & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap)))))) {
                            if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi) 
                                          || (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai))))) {
                                __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh_85 
                                    = (0x0000001fU 
                                       & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs2);
                            }
                        }
                    } else if ((0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh_85 
                            = (0x0000001fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs2);
                    } else if ((8U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                            if ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh))) {
                                __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh_85 
                                    = (0x0000001fU 
                                       & ((4U <= (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh))
                                           ? ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh) 
                                              - (::IData)(4U))
                                           : ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh) 
                                              - (::IData)(1U))));
                            }
                        }
                    }
                    if ((0x20U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((0x10U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                            if ((8U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                if ((4U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                    if ((2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                        if ((1U & (
                                                   (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                                   | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                                            if ((1U 
                                                 & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata)))) {
                                                tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_wdata = 1U;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt_182 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt_176 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy_174 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit_177 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running_124 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy_181 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit_183 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt_150 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr_108 = 0ULL;
    }
    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)) 
               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata_89 = 0U;
    }
    if (tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_wdata) {
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata_89 = 1U;
    }
    tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rdata = 0U;
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        if (((((((((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
                   | (0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                  | (0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                 | (0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                | (8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
               | (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
              | (2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
             | (1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))) {
            if ((0x80U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                if ((0x40U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0x20U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((0x10U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                            if ((8U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                if ((4U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                    if ((2U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                        if ((1U & (
                                                   (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                                   | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                                            if ((1U 
                                                 & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata)))) {
                                                tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rdata = 1U;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)) 
               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata_88 = 0U;
    }
    if (tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rdata) {
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata_88 = 1U;
    }
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger_94 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst) 
           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done));
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal_19 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lui) 
           | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_auipc) 
              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal)));
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy_154 
            = (7U & (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy) 
                      + ((1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))
                          ? 1U : 0U)) - (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_valid) 
                                          & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_tag) 
                                             >> 3U))
                                          ? 1U : 0U)));
        if (((((((((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
                   | (0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                  | (0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                 | (0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                | (8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
               | (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
              | (2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
             | (1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))) {
            if ((0x80U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                if ((0x40U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0x20U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((0x10U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                            if ((8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) {
                                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0) {
                                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger_94 = 0U;
                                    }
                                }
                            } else if ((4U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                                    if (((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                         & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done))) {
                                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger_94 = 1U;
                                    }
                                }
                            }
                        }
                    }
                }
                if ((0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__current_pc 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc;
                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__current_pc 
                            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store)
                                ? (0xfffffffeU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_stalu)
                                                   ? vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_q
                                                   : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out))
                                : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc);
                    }
                    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc_98 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__current_pc;
                    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc_99 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__current_pc;
                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger) {
                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc_99 
                            = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__current_pc 
                               + ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__compressed_instr)
                                   ? 2U : 4U));
                        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal) {
                            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc_99 
                                = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__current_pc 
                                   + vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j);
                        }
                    }
                }
            }
        }
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_valid) {
            if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_tag) 
                          >> 3U)))) {
                if ((4U >= (7U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_tag)))) {
                    __Vdly_Val__tb_fpga__DOT__dut__DOT__ise__DOT__slot_208 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_r;
                    __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ise__DOT__slot_209 
                        = (7U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_tag));
                    __Vdly_Set__tb_fpga__DOT__dut__DOT__ise__DOT__slot_210 = 1U;
                }
            }
        }
    } else {
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy_154 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc_98 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc_99 = 0U;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__current_pc = 0U;
    if ((((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
          & ((0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
             & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch) 
                | (::IData)(vlSelfRef.__Vdfg_Regularize_1137)))) 
         & (0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_rd)))) {
        __Vdly_Val__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_205 
            = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch)
                 ? (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc 
                    + ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_compr)
                        ? 2U : 4U)) : (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_stalu)
                                         ? vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_q
                                         : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out) 
                                       & (- (::IData)((::IData)(vlSelfRef.__Vdfg_Regularize_1137))))) 
               & (- (::IData)((0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))));
        __Vdly_Dim0__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_206 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_rd;
        __Vdly_Set__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_207 = 1U;
    }
    __Vdly__tb_fpga__DOT__dut__DOT__tx_start_5 = 0U;
    __Vdly__tb_fpga__DOT__dut__DOT__mem_ready_4 = 0U;
    if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid) 
          & (0x00020000U > vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) 
         & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready)))) {
        if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb))) {
            __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_193 
                = (0x000000ffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wdata);
            __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_194 
                = (0x00007fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr 
                                  >> 2U));
            __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_195 = 1U;
        }
        if ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb))) {
            __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_196 
                = (0x000000ffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wdata 
                                  >> 8U));
            __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_197 
                = (0x00007fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr 
                                  >> 2U));
            __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_198 = 1U;
        }
        if ((4U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb))) {
            __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_199 
                = (0x000000ffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wdata 
                                  >> 0x10U));
            __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_200 
                = (0x00007fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr 
                                  >> 2U));
            __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_201 = 1U;
        }
        if ((8U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb))) {
            __Vdly_Val__tb_fpga__DOT__dut__DOT__ram_202 
                = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wdata 
                   >> 0x18U);
            __Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_203 
                = (0x00007fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr 
                                  >> 2U));
            __Vdly_Set__tb_fpga__DOT__dut__DOT__ram_204 = 1U;
        }
    }
    if (vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__busy) {
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[0U] 
            = (::IData)(((((::QData)((::IData)(Vtb_fpga__ConstPool__CONST_0
                                               [(((::IData)(0x0000003fU) 
                                                  + 
                                                  ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__rnd) 
                                                   << 6U)) 
                                                 >> 5U)])) 
                           << 0x00000020U) | (::QData)((::IData)(Vtb_fpga__ConstPool__CONST_0
                                                                 [
                                                                 (0x07fffffeU 
                                                                  & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__rnd) 
                                                                     << 1U))]))) 
                         ^ (((~ vlSelfRef.__Vdfg_Regularize_1111) 
                             & vlSelfRef.__Vdfg_Regularize_1117) 
                            ^ vlSelfRef.__Vdfg_Regularize_1105)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[1U] 
            = (::IData)((((((::QData)((::IData)(Vtb_fpga__ConstPool__CONST_0
                                                [(((::IData)(0x0000003fU) 
                                                   + 
                                                   ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__rnd) 
                                                    << 6U)) 
                                                  >> 5U)])) 
                            << 0x00000020U) | (::QData)((::IData)(Vtb_fpga__ConstPool__CONST_0
                                                                  [
                                                                  (0x07fffffeU 
                                                                   & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__rnd) 
                                                                      << 1U))]))) 
                          ^ (((~ vlSelfRef.__Vdfg_Regularize_1111) 
                              & vlSelfRef.__Vdfg_Regularize_1117) 
                             ^ vlSelfRef.__Vdfg_Regularize_1105)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[2U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1111 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1117) 
                            & vlSelfRef.__Vdfg_Regularize_1123)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[3U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1111 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1117) 
                             & vlSelfRef.__Vdfg_Regularize_1123)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[4U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1117 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1123) 
                            & vlSelfRef.__Vdfg_Regularize_1129)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[5U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1117 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1123) 
                             & vlSelfRef.__Vdfg_Regularize_1129)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[6U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1123 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1129) 
                            & vlSelfRef.__Vdfg_Regularize_1105)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[7U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1123 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1129) 
                             & vlSelfRef.__Vdfg_Regularize_1105)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[8U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1129 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1105) 
                            & vlSelfRef.__Vdfg_Regularize_1111)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[9U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1129 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1105) 
                             & vlSelfRef.__Vdfg_Regularize_1111)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[10U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1120 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1126) 
                            & vlSelfRef.__Vdfg_Regularize_1107)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[11U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1120 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1126) 
                             & vlSelfRef.__Vdfg_Regularize_1107)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[12U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1126 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1107) 
                            & vlSelfRef.__Vdfg_Regularize_1113)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[13U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1126 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1107) 
                             & vlSelfRef.__Vdfg_Regularize_1113)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[14U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1107 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1113) 
                            & vlSelfRef.__Vdfg_Regularize_1119)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[15U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1107 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1113) 
                             & vlSelfRef.__Vdfg_Regularize_1119)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[16U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1113 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1119) 
                            & vlSelfRef.__Vdfg_Regularize_1120)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[17U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1113 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1119) 
                             & vlSelfRef.__Vdfg_Regularize_1120)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[18U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1119 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1120) 
                            & vlSelfRef.__Vdfg_Regularize_1126)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[19U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1119 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1120) 
                             & vlSelfRef.__Vdfg_Regularize_1126)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[20U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1110 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1116) 
                            & vlSelfRef.__Vdfg_Regularize_1122)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[21U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1110 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1116) 
                             & vlSelfRef.__Vdfg_Regularize_1122)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[22U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1116 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1122) 
                            & vlSelfRef.__Vdfg_Regularize_1128)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[23U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1116 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1122) 
                             & vlSelfRef.__Vdfg_Regularize_1128)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[24U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1122 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1128) 
                            & vlSelfRef.__Vdfg_Regularize_1109)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[25U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1122 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1128) 
                             & vlSelfRef.__Vdfg_Regularize_1109)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[26U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1128 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1109) 
                            & vlSelfRef.__Vdfg_Regularize_1110)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[27U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1128 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1109) 
                             & vlSelfRef.__Vdfg_Regularize_1110)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[28U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1109 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1110) 
                            & vlSelfRef.__Vdfg_Regularize_1116)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[29U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1109 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1110) 
                             & vlSelfRef.__Vdfg_Regularize_1116)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[30U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1125 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1106) 
                            & vlSelfRef.__Vdfg_Regularize_1112)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[31U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1125 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1106) 
                             & vlSelfRef.__Vdfg_Regularize_1112)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[32U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1106 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1112) 
                            & vlSelfRef.__Vdfg_Regularize_1118)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[33U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1106 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1112) 
                             & vlSelfRef.__Vdfg_Regularize_1118)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[34U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1112 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1118) 
                            & vlSelfRef.__Vdfg_Regularize_1124)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[35U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1112 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1118) 
                             & vlSelfRef.__Vdfg_Regularize_1124)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[36U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1118 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1124) 
                            & vlSelfRef.__Vdfg_Regularize_1125)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[37U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1118 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1124) 
                             & vlSelfRef.__Vdfg_Regularize_1125)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[38U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1124 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1125) 
                            & vlSelfRef.__Vdfg_Regularize_1106)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[39U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1124 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1125) 
                             & vlSelfRef.__Vdfg_Regularize_1106)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[40U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1115 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1121) 
                            & vlSelfRef.__Vdfg_Regularize_1127)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[41U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1115 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1121) 
                             & vlSelfRef.__Vdfg_Regularize_1127)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[42U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1121 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1127) 
                            & vlSelfRef.__Vdfg_Regularize_1108)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[43U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1121 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1127) 
                             & vlSelfRef.__Vdfg_Regularize_1108)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[44U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1127 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1108) 
                            & vlSelfRef.__Vdfg_Regularize_1114)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[45U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1127 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1108) 
                             & vlSelfRef.__Vdfg_Regularize_1114)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[46U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1108 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1114) 
                            & vlSelfRef.__Vdfg_Regularize_1115)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[47U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1108 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1114) 
                             & vlSelfRef.__Vdfg_Regularize_1115)) 
                         >> 0x00000020U));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[48U] 
            = (::IData)((vlSelfRef.__Vdfg_Regularize_1114 
                         ^ ((~ vlSelfRef.__Vdfg_Regularize_1115) 
                            & vlSelfRef.__Vdfg_Regularize_1121)));
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[49U] 
            = (::IData)(((vlSelfRef.__Vdfg_Regularize_1114 
                          ^ ((~ vlSelfRef.__Vdfg_Regularize_1115) 
                             & vlSelfRef.__Vdfg_Regularize_1121)) 
                         >> 0x00000020U));
    } else if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__is_kk) 
                 & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready))) 
                & (0U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)))) {
        __Vilp2 = 0U;
        while ((__Vilp2 <= 0x00000030U)) {
            __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[__Vilp2] 
                = vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st
                [(__Vilp2 + (::IData)(1U))];
            __Vilp2 = ((::IData)(1U) + __Vilp2);
        }
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186[49U] 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1;
    }
    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lbu_lhu_lw_23 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lbu) 
           | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lhu) 
              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lw)));
    if (vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_valid) {
        __Vdly__tb_fpga__DOT__dut__DOT__rx_full_6 = 1U;
    }
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid) 
             & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready)))) {
            if ((0x00020000U <= vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                if ((0x10000000U == vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy)) 
                               & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__tx_start))))) {
                        __Vdly__tb_fpga__DOT__dut__DOT__tx_start_5 = 1U;
                    }
                }
                if ((0x10000000U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                    if ((0x10000004U == vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                        if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__rx_full) 
                             & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_valid)))) {
                            __Vdly__tb_fpga__DOT__dut__DOT__rx_full_6 = 0U;
                        }
                    }
                }
            }
            if ((0x00020000U > vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                if ((1U & (~ (0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb))))) {
                    __Vdly__tb_fpga__DOT__dut__DOT__ram_pend_8 
                        = (1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ram_pend)));
                }
                if ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb))) {
                    __Vdly__tb_fpga__DOT__dut__DOT__mem_ready_4 = 1U;
                } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__ram_pend) {
                    __Vdly__tb_fpga__DOT__dut__DOT__mem_ready_4 = 1U;
                }
            } else if ((0x10000000U == vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy)) 
                           & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__tx_start))))) {
                    __Vdly__tb_fpga__DOT__dut__DOT__mem_ready_4 = 1U;
                }
            } else {
                __Vdly__tb_fpga__DOT__dut__DOT__mem_ready_4 = 1U;
            }
        }
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy) {
            if ((7U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt))) {
                __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh_178 
                    = (0x00000200U | (0x000001ffU & 
                                      ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh) 
                                       >> 1U)));
            }
        } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__tx_start) {
            __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh_178 
                = (0x00000200U | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__tx_data) 
                                  << 1U));
        }
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready_188 = 0U;
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__busy) {
            __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__rnd_189 
                = (0x0000001fU & ((::IData)(1U) + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__rnd)));
            if ((0x17U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__rnd))) {
                __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__busy_190 = 0U;
                __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready_188 = 1U;
            }
        } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__is_kk) 
                    & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready)))) {
            if ((0U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                              >> 0x0000000cU)))) {
                if ((2U == (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                  >> 0x0000000cU)))) {
                    __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__rnd_189 = 0U;
                    __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__busy_190 = 1U;
                }
            }
            if ((0U == (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                              >> 0x0000000cU)))) {
                __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready_188 = 1U;
            } else if ((2U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                     >> 0x0000000cU)))) {
                __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready_188 = 1U;
            }
        }
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready_136 = 0U;
        if ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
            if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
                __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready_136 = 1U;
                __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__state_135 = 0U;
            } else if (((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy)) 
                        & (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__done) 
                            & (3U | (- (::IData)((4U 
                                                  == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op)))))) 
                           == (0x0000001fU & (3U | 
                                              (- (::IData)(
                                                           (4U 
                                                            == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))))))))) {
                __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__state_135 = 3U;
            }
        } else {
            if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state)))) {
                if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                     & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
                    if ((0x00004000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                        if ((0x00002000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                            __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready_136 = 1U;
                        }
                    } else if ((0x00001000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready_136 = 1U;
                    }
                }
            }
            if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
                if ((1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__ndummy))) {
                    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__state_135 = 2U;
                }
            } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                        & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
                if ((0x00004000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                    if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                  >> 0x0000000dU)))) {
                        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__state_135 
                            = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                                & ((0x0000000fU & vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr) 
                                   < (0x0000000fU & 
                                      ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                                       >> 4U)))) ? 1U
                                : 2U);
                    }
                } else if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                     >> 0x0000000cU)))) {
                    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__state_135 
                        = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                            & ((0x0000000fU & vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr) 
                               < (0x0000000fU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                                                 >> 4U))))
                            ? 1U : 2U);
                }
            }
        }
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs0 
            = (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs0 
               ^ vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xa3);
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__lfsr_145 
            = ((1U & vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr)
                ? (0x80200003U ^ vlSelfRef.__Vdfg_Regularize_1139)
                : vlSelfRef.__Vdfg_Regularize_1139);
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__xs1_147 
            = (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs1 
               ^ vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xa2);
        if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state) 
                      >> 1U)))) {
            if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state)))) {
                if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                     & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
                    if ((0x00004000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                        if ((0x00002000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                            if ((0x00001000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                                if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                              >> 0x0000001bU)))) {
                                    if ((0x04000000U 
                                         & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                    >> 0x00000019U)))) {
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs0 
                                                = (0x9e3779b9U 
                                                   ^ vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1);
                                            __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__lfsr_145 
                                                = (
                                                   (0U 
                                                    == vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1)
                                                    ? 1U
                                                    : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1);
                                            __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__xs1_147 
                                                = (~ vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
                __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__ndummy_156 
                    = (0x0000000fU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__ndummy) 
                                      - (::IData)(1U)));
            } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                        & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
                if ((0x00004000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                    if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                  >> 0x0000000dU)))) {
                        if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                             & ((0x0000000fU & vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr) 
                                < (0x0000000fU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                                                  >> 4U))))) {
                            __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__ndummy_156 
                                = (0x0000000fU & ((::IData)(1U) 
                                                  + 
                                                  (7U 
                                                   & ((vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
                                                       >> 4U) 
                                                      & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                                                         >> 8U)))));
                        }
                    }
                } else if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                     >> 0x0000000cU)))) {
                    if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                         & ((0x0000000fU & vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr) 
                            < (0x0000000fU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                                              >> 4U))))) {
                        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__ndummy_156 
                            = (0x0000000fU & ((::IData)(1U) 
                                              + (7U 
                                                 & ((vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
                                                     >> 4U) 
                                                    & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                                                       >> 8U)))));
                    }
                }
            }
        }
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__start) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend_125 
                = ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_div) 
                     | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_rem)) 
                    & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                       >> 0x1fU)) ? (- vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1)
                    : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1);
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor_126 
                = (0x7fffffffffffffffULL & (((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_div) 
                                               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_rem)) 
                                              & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                                                 >> 0x1fU))
                                              ? (- (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2)))
                                              : (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2))) 
                                            << 0x0000001fU));
        } else if ((1U & (~ ((~ (0U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk)) 
                             & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running))))) {
            if ((vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor 
                 <= (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend)))) {
                __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend_125 
                    = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend 
                       - (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor));
            }
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor_126 
                = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor 
                   >> 1U);
        }
        if (((((((((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
                   | (0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                  | (0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                 | (0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                | (8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
               | (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
              | (2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
             | (1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))) {
            if ((0x80U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                if ((0x40U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 = 0U;
                        if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) 
                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)) 
                             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal))) {
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                                __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                    = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs1;
                            } else if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)))) {
                                if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal) {
                                    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lui)
                                            ? 0U : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc);
                                }
                            }
                        } else {
                            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs1;
                        }
                    } else if ((0x10U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((8U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                            if ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                if ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh))) {
                                    if ((4U <= (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh))) {
                                        if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slli) 
                                             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sll))) {
                                            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                                = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                                   << 4U);
                                        } else if (
                                                   ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srli) 
                                                    | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srl))) {
                                            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                                = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                                   >> 4U);
                                        } else if (
                                                   ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srai) 
                                                    | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sra))) {
                                            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                                = VL_SHIFTRS_III(32,32,32, vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1, 4U);
                                        }
                                    } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slli) 
                                                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sll))) {
                                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                            = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                               << 1U);
                                    } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srli) 
                                                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srl))) {
                                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                            = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                               >> 1U);
                                    } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srai) 
                                                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sra))) {
                                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                            = VL_SHIFTRS_III(32,32,32, vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1, 1U);
                                    }
                                }
                            } else if ((2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                                    if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata)))) {
                                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                            = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                               + vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm);
                                    }
                                }
                            } else if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                                if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata)))) {
                                    __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111 
                                        = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                           + vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm);
                                }
                            }
                        }
                    }
                }
                if ((0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger) {
                        if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal)))) {
                            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x20U;
                        }
                    }
                } else if ((0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) 
                          | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)) 
                         | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal))) {
                        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready) {
                                __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x40U;
                            } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout) 
                                        | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ecall_ebreak))) {
                                __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x80U;
                            }
                        } else {
                            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 
                                = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)
                                    ? 0x40U : ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal)
                                                ? 8U
                                                : 0x40U));
                        }
                    } else {
                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 
                            = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu) 
                                & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap)))
                                ? 1U : (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi) 
                                         || (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai))
                                         ? 8U : ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw)
                                                  ? 2U
                                                  : 8U)));
                    }
                } else if ((0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready) {
                            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x40U;
                        } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout) 
                                    | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ecall_ebreak))) {
                            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x80U;
                        }
                    } else {
                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 
                            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw)
                                ? 2U : 8U);
                    }
                } else if ((8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) {
                        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done) {
                            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x40U;
                        }
                    } else {
                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x40U;
                    }
                } else if ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh))) {
                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x40U;
                    }
                } else if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                  | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                    if (((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                         & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done))) {
                        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x40U;
                    }
                }
            }
        }
    } else {
        __Vdly__tb_fpga__DOT__dut__DOT__rx_full_6 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__ram_pend_8 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__rnd_189 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__busy_190 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready_188 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready_136 = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs0 = 0x9e3779b9U;
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__lfsr_145 = 0xace12468U;
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__xs1_147 = 0x243f6a88U;
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__state_135 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x40U;
    }
    if (((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
         & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata) 
            | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata)))) {
        if (((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize)) 
             & (0U != (3U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1)))) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x80U;
        }
        if (((1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize)) 
             & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1)) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x80U;
        }
    }
    if ((((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
          & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst)) 
         & (0U != (3U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc)))) {
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110 = 0x80U;
    }
    if ((((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
          & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid)) 
         & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait) 
               | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wait) 
                  | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wait)))))) {
        if ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter))) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter_91 
                = (0x0000000fU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter) 
                                  - (::IData)(1U)));
        }
    } else {
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter_91 = 0x0fU;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__shift_out 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wr = 0U;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rd 
        = VL_MULS_QQQ(64, VL_EXTENDS_QQ(64,33, vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rs1), 
                      VL_EXTENDS_QQ(64,33, vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rs2));
    vlSelfRef.tb_fpga__DOT__trig_cyc = ((__Vdly__tb_fpga__DOT__trig_cyc_1 
                                         & __Vdly_Mask__tb_fpga__DOT__trig_cyc_2) 
                                        | (vlSelfRef.tb_fpga__DOT__trig_cyc 
                                           & (~ __Vdly_Mask__tb_fpga__DOT__trig_cyc_2)));
    __Vdly_Mask__tb_fpga__DOT__trig_cyc_2 = 0ULL;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_slti_blt_slt 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slti) 
           | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_blt) 
              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slt)));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sltiu_bltu_sltu 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltiu) 
           | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bltu) 
              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltu)));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal_jalr_addi_add_sub 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lui) 
           | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_auipc) 
              | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal) 
                 | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr) 
                    | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_addi) 
                       | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_add) 
                          | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sub)))))));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_compare 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
           | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slti) 
              | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slt) 
                 | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltiu) 
                    | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltu)))));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait_q 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait) 
           & (::IData)(vlSelfRef.tb_fpga__DOT__resetn));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_rd = 0U;
    if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger) 
         & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_pseudo_trigger)))) {
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle_74 
            = ((::IData)((0xc0002073U == (0xfffff07fU 
                                          & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q))) 
               | (::IData)((0xc0102073U == (0xfffff07fU 
                                            & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q))));
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr_76 
            = (::IData)((0xc0202073U == (0xfffff07fU 
                                         & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb_47 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh_48 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0x00001000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai_81 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
               & ((::IData)((0x00001000U == (0xfe007000U 
                                             & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q))) 
                  | ((::IData)((0x00005000U == (0xfe007000U 
                                                & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q))) 
                     | (::IData)((0x40005000U == (0xfe007000U 
                                                  & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q))))));
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi_82 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr) 
               | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
                  & ((0U == (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                   >> 0x0cU))) | ((2U 
                                                   == 
                                                   (7U 
                                                    & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                       >> 0x0cU))) 
                                                  | ((3U 
                                                      == 
                                                      (7U 
                                                       & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                          >> 0x0cU))) 
                                                     | ((4U 
                                                         == 
                                                         (7U 
                                                          & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                             >> 0x0cU))) 
                                                        | ((6U 
                                                            == 
                                                            (7U 
                                                             & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                                >> 0x0cU))) 
                                                           | (7U 
                                                              == 
                                                              (7U 
                                                               & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                                  >> 0x0cU))))))))));
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_83 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal)
                ? vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j
                : (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lui) 
                    | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_auipc))
                    ? (0xfffff000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)
                    : (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr) 
                        | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu) 
                           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm)))
                        ? VL_EXTENDS_II(32,12, (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                >> 0x14U))
                        : ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu)
                            ? VL_EXTENDS_II(32,13, 
                                            ((((2U 
                                                & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                   >> 0x0000001eU)) 
                                               | (1U 
                                                  & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                     >> 7U))) 
                                              << 0x0000000bU) 
                                             | ((0x000007e0U 
                                                 & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                    >> 0x00000014U)) 
                                                | (0x0000001eU 
                                                   & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                      >> 7U)))))
                            : ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw)
                                ? VL_EXTENDS_II(32,12, 
                                                ((0x00000fe0U 
                                                  & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                     >> 0x00000014U)) 
                                                 | (0x0000001fU 
                                                    & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                       >> 7U))))
                                : 0U)))));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_getq = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycleh = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstrh = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_fence 
            = ((0x0fU == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)) 
               & (~ (0U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                  >> 0x0cU)))));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_beq 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bne 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0x00001000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bge 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0x00005000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bgeu 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0x00007000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xor 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg) 
               & (0x00004000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_or 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg) 
               & (0x00006000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_and 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg) 
               & (0x00007000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xori 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
               & (0x00004000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ori 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
               & (0x00006000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_andi 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
               & (0x00007000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal_jalr_addi_add_sub = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_compare = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slli 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
               & (0x00001000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srli 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
               & (0x00005000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srai 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
               & (0x40005000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sll 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg) 
               & (0x00001000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srl 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg) 
               & (0x00005000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sra 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg) 
               & (0x40005000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_blt 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0x00004000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bltu 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0x00006000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_add 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg) 
               & (0U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_addi 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
               & (0U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sub 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg) 
               & (0x40000000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slt 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg) 
               & (0x00002000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltu 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg) 
               & (0x00003000U == (0xfe007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slti 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
               & (0x00002000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltiu 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm) 
               & (0x00003000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
    }
    if (__Vdly_Set__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_207) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs[__Vdly_Dim0__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_206] 
            = __Vdly_Val__tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_205;
    }
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd 
                = (1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh));
            if ((7U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt))) {
                if ((9U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd = 1U;
                }
            }
        }
        if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__start)))) {
            if (((~ (0U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk)) 
                 & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running))) {
                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wr = 1U;
                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_rd 
                    = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_div) 
                        | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_divu))
                        ? ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__outsign)
                            ? (- vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient)
                            : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient)
                        : ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__outsign)
                            ? (- vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend)
                            : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend));
            }
        }
        vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wr = 0U;
        if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__busy)))) {
            if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__is_kk) 
                 & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready)))) {
                if ((0U == (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                  >> 0x0000000cU)))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wr = 1U;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_rd 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[0U];
                }
            }
        }
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wr = 0U;
        if ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
            if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state)))) {
                if (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok) {
                    if ((4U >= (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick))) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__issued 
                            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__issued) 
                               | (0x1fU & ((::IData)(1U) 
                                           << (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick))));
                    }
                }
            }
            if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
                vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wr = 1U;
            }
        } else if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state)))) {
            if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                 & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
                vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__issued = 0U;
                if ((0x00004000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                    if ((0x00002000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wr 
                            = ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                         >> 0x0000000cU))) 
                               || ((1U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                          >> 0x0000001bU)) 
                                   || ((1U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                              >> 0x0000001aU)) 
                                       && (1U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                 >> 0x00000019U)))));
                    }
                } else if ((0x00001000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wr = 1U;
                }
            }
        }
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs3 
            = ((vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xa3 
                << 0x0000000bU) | (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xa3 
                                   >> 0x00000015U));
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs2 
            = ((vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs1 
                << 9U) ^ vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xa2);
        if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state) 
                      >> 1U)))) {
            if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state)))) {
                if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                     & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
                    if ((0x00004000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                        if ((0x00002000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                            if ((0x00001000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                                if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                              >> 0x0000001bU)))) {
                                    if ((0x04000000U 
                                         & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                    >> 0x00000019U)))) {
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs3 = 0x8aed2a6bU;
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs2 = 0xb7e15162U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__rot 
                        = ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg))
                            ? (3U & (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
                                     >> 8U)) : 0U);
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__swp 
                        = (1U & (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg) 
                                  >> 1U) & (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
                                            >> 0x0aU)));
                }
            }
        }
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_p 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_p;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_t 
            = (0x00001fffU & (::IData)((0x0000000000001fffULL 
                                        & ((0x00000000000013afULL 
                                            * (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_p))) 
                                           >> 0x18U))));
        if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid) 
             & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready)))) {
            if ((0x00020000U <= vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                if ((0x10000000U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                    if ((0x10000004U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                        if ((0x20000000U == vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__led 
                                = (4U | ((0U == (7U 
                                                 & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wdata)) 
                                         << 3U));
                        }
                    }
                }
            }
        }
    } else {
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd = 1U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__issued = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wr = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wr = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs3 = 0x8aed2a6bU;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs2 = 0xb7e15162U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_rd = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__led = 1U;
    }
    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__trap) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__led = (2U 
                                                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__led));
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy 
        = __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy_154;
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__ndummy 
        = __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__ndummy_156;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor_126;
    vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh 
        = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh_178;
    vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit 
        = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit_177;
    vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt 
        = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt_176;
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs1 
        = __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__xs1_147;
    __Vilp3 = 0U;
    while ((__Vilp3 <= 0x00000031U)) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[__Vilp3] 
            = __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__st_186
            [__Vilp3];
        __Vilp3 = ((::IData)(1U) + __Vilp3);
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_128;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend_125;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_q 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out;
    if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mul) 
         & (~ (0U != (3U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active)))))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rs1 
            = (0x00000001ffffffffULL & (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu) 
                                         | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh))
                                         ? VL_EXTENDS_QI(33,32, vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1)
                                         : (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1))));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rs2 
            = (0x00000001ffffffffULL & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh)
                                         ? VL_EXTENDS_QI(33,32, vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2)
                                         : (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2))));
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xa2 
        = (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs0 
           ^ vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs2);
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xa3 
        = (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs1 
           ^ vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs3);
    tb_fpga__DOT__dut__DOT__ise__DOT__x5 = (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs1 
                                            + (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs1 
                                               << 2U));
    __Vdfg_Regularize_1130 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[9U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[8U]))) 
                              ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[19U])) 
                                   << 0x00000020U) 
                                  | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[18U]))) 
                                 ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[29U])) 
                                      << 0x00000020U) 
                                     | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[28U]))) 
                                    ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[39U])) 
                                         << 0x00000020U) 
                                        | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[38U]))) 
                                       ^ (((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[49U])) 
                                           << 0x00000020U) 
                                          | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[48U])))))));
    __Vdfg_Regularize_1133 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[3U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[2U]))) 
                              ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[13U])) 
                                   << 0x00000020U) 
                                  | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[12U]))) 
                                 ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[23U])) 
                                      << 0x00000020U) 
                                     | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[22U]))) 
                                    ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[33U])) 
                                         << 0x00000020U) 
                                        | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[32U]))) 
                                       ^ (((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[43U])) 
                                           << 0x00000020U) 
                                          | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[42U])))))));
    __Vdfg_Regularize_1131 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[7U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[6U]))) 
                              ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[17U])) 
                                   << 0x00000020U) 
                                  | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[16U]))) 
                                 ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[27U])) 
                                      << 0x00000020U) 
                                     | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[26U]))) 
                                    ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[37U])) 
                                         << 0x00000020U) 
                                        | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[36U]))) 
                                       ^ (((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[47U])) 
                                           << 0x00000020U) 
                                          | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[46U])))))));
    __Vdfg_Regularize_1132 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[5U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[4U]))) 
                              ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[15U])) 
                                   << 0x00000020U) 
                                  | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[14U]))) 
                                 ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[25U])) 
                                      << 0x00000020U) 
                                     | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[24U]))) 
                                    ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[35U])) 
                                         << 0x00000020U) 
                                        | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[34U]))) 
                                       ^ (((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[45U])) 
                                           << 0x00000020U) 
                                          | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[44U])))))));
    __Vdfg_Regularize_1134 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[1U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[0U]))) 
                              ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[11U])) 
                                   << 0x00000020U) 
                                  | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[10U]))) 
                                 ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[21U])) 
                                      << 0x00000020U) 
                                     | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[20U]))) 
                                    ^ ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[31U])) 
                                         << 0x00000020U) 
                                        | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[30U]))) 
                                       ^ (((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[41U])) 
                                           << 0x00000020U) 
                                          | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[40U])))))));
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_div) 
               | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_divu) 
                  | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_rem) 
                     | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_remu))));
        if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid) 
             & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready)))) {
            if ((0x00020000U <= vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                if ((0x10000000U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                    if ((0x10000004U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                        if ((0x20000000U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                            if ((0x30000000U == vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__trigger 
                                    = (1U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wdata);
                            }
                        }
                    }
                }
            }
        }
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_r 
            = (0x00000fffU & ((0x00002000U & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_r0) 
                                              - (::IData)(0x0d01U)))
                               ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_r0)
                               : ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_r0) 
                                  - (::IData)(0x0d01U))));
    } else {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__trigger = 0U;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_r0 
        = (0x00003fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_p 
                          - ((0x00003800U & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_t) 
                                             << 0x0000000bU)) 
                             + ((0x00003c00U & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_t) 
                                                << 0x0000000aU)) 
                                + ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_t) 
                                   + (0x00003f00U & 
                                      ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_t) 
                                       << 8U)))))));
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        if (((((((((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
                   | (0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                  | (0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                 | (0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                | (8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
               | (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
              | (2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
             | (1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))) {
            if ((0x80U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                if ((0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_stalu = 0U;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_compr 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__compressed_instr;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_rd 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rd;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize = 0U;
                } else if ((0x20U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0x10U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                            if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu)))) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_stalu = 1U;
                            }
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_rd = 0U;
                            }
                        }
                        if ((8U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                            if ((4U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                if ((2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                                        if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata)))) {
                                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sb) {
                                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize = 2U;
                                            } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sh) {
                                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize = 1U;
                                            } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sw) {
                                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize = 0U;
                                            }
                                        }
                                    }
                                } else if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                                  | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                                    if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata)))) {
                                        if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb) 
                                             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lbu))) {
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize = 2U;
                                        } else if (
                                                   ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh) 
                                                    | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lhu))) {
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize = 1U;
                                        } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lw) {
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize = 0U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid) 
             & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready)))) {
            if ((0x00020000U <= vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                if ((0x10000000U == vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy)) 
                               & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__tx_start))))) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__tx_data 
                            = (0x000000ffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wdata);
                    }
                }
            }
        }
        vlSelfRef.tb_fpga__DOT__dut__DOT__tx_start 
            = __Vdly__tb_fpga__DOT__dut__DOT__tx_start_5;
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy_174;
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_valid) {
            if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_tag) 
                          >> 3U)))) {
                if ((4U >= (7U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_tag)))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__done 
                        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__done) 
                           | (0x1fU & ((::IData)(1U) 
                                       << (7U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_tag)))));
                }
            }
        }
        if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state) 
                      >> 1U)))) {
            if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state)))) {
                if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                     & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__done = 0U;
                }
            }
        }
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__busy) {
            if ((0x17U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__rnd))) {
                vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wait = 0U;
            }
        } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__is_kk) 
                    & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready)))) {
            if ((0U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                              >> 0x0000000cU)))) {
                if ((2U == (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                  >> 0x0000000cU)))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wait = 1U;
                }
            }
        }
    } else {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_stalu = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_rd = 2U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__tx_start 
            = __Vdly__tb_fpga__DOT__dut__DOT__tx_start_5;
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy_174;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__done = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wait = 0U;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__rnd 
        = __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__rnd_189;
    vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__busy 
        = __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__busy_190;
    vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready 
        = __Vdly__tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready_188;
    if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)))) {
        __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__sync_179 = 3U;
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active_133 = 0U;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active_133;
    __Vdfg_Regularize_1102 = (((__Vdfg_Regularize_1133 
                                << 1U) | (__Vdfg_Regularize_1133 
                                          >> 0x0000003fU)) 
                              ^ __Vdfg_Regularize_1130);
    __Vdfg_Regularize_1100 = (((__Vdfg_Regularize_1131 
                                << 1U) | (__Vdfg_Regularize_1131 
                                          >> 0x0000003fU)) 
                              ^ __Vdfg_Regularize_1133);
    __Vdfg_Regularize_1099 = (((__Vdfg_Regularize_1130 
                                << 1U) | (__Vdfg_Regularize_1130 
                                          >> 0x0000003fU)) 
                              ^ __Vdfg_Regularize_1132);
    __Vdfg_Regularize_1098 = (((__Vdfg_Regularize_1134 
                                << 1U) | (__Vdfg_Regularize_1134 
                                          >> 0x0000003fU)) 
                              ^ __Vdfg_Regularize_1131);
    __Vdfg_Regularize_1101 = (((__Vdfg_Regularize_1132 
                                << 1U) | (__Vdfg_Regularize_1132 
                                          >> 0x0000003fU)) 
                              ^ __Vdfg_Regularize_1134);
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_valid 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
           && (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_v));
    vlSelfRef.__Vdfg_Regularize_1105 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[1U])) 
                                          << 0x00000020U) 
                                         | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[0U]))) 
                                        ^ __Vdfg_Regularize_1102);
    __Vdfg_Regularize_1165 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[11U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[10U]))) 
                              ^ __Vdfg_Regularize_1102);
    __Vdfg_Regularize_1166 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[21U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[20U]))) 
                              ^ __Vdfg_Regularize_1102);
    __Vdfg_Regularize_1167 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[31U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[30U]))) 
                              ^ __Vdfg_Regularize_1102);
    __Vdfg_Regularize_1168 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[41U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[40U]))) 
                              ^ __Vdfg_Regularize_1102);
    __Vdfg_Regularize_1174 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[5U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[4U]))) 
                              ^ __Vdfg_Regularize_1100);
    __Vdfg_Regularize_1175 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[15U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[14U]))) 
                              ^ __Vdfg_Regularize_1100);
    __Vdfg_Regularize_1176 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[25U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[24U]))) 
                              ^ __Vdfg_Regularize_1100);
    __Vdfg_Regularize_1177 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[35U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[34U]))) 
                              ^ __Vdfg_Regularize_1100);
    __Vdfg_Regularize_1178 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[45U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[44U]))) 
                              ^ __Vdfg_Regularize_1100);
    __Vdfg_Regularize_1179 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[7U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[6U]))) 
                              ^ __Vdfg_Regularize_1099);
    __Vdfg_Regularize_1180 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[17U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[16U]))) 
                              ^ __Vdfg_Regularize_1099);
    __Vdfg_Regularize_1181 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[27U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[26U]))) 
                              ^ __Vdfg_Regularize_1099);
    __Vdfg_Regularize_1182 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[37U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[36U]))) 
                              ^ __Vdfg_Regularize_1099);
    __Vdfg_Regularize_1183 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[47U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[46U]))) 
                              ^ __Vdfg_Regularize_1099);
    __Vdfg_Regularize_1184 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[9U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[8U]))) 
                              ^ __Vdfg_Regularize_1098);
    __Vdfg_Regularize_1185 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[19U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[18U]))) 
                              ^ __Vdfg_Regularize_1098);
    __Vdfg_Regularize_1186 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[29U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[28U]))) 
                              ^ __Vdfg_Regularize_1098);
    __Vdfg_Regularize_1187 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[39U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[38U]))) 
                              ^ __Vdfg_Regularize_1098);
    __Vdfg_Regularize_1188 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[49U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[48U]))) 
                              ^ __Vdfg_Regularize_1098);
    __Vdfg_Regularize_1169 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[3U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[2U]))) 
                              ^ __Vdfg_Regularize_1101);
    __Vdfg_Regularize_1170 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[13U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[12U]))) 
                              ^ __Vdfg_Regularize_1101);
    __Vdfg_Regularize_1171 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[23U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[22U]))) 
                              ^ __Vdfg_Regularize_1101);
    __Vdfg_Regularize_1172 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[33U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[32U]))) 
                              ^ __Vdfg_Regularize_1101);
    __Vdfg_Regularize_1173 = ((((::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[43U])) 
                                << 0x00000020U) | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__st[42U]))) 
                              ^ __Vdfg_Regularize_1101);
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_remu = 0U;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_divu = 0U;
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        if ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
            if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
                vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wait = 0U;
            }
        } else if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state)))) {
            if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                 & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
                if ((0x00004000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                    if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                  >> 0x0000000dU)))) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wait = 1U;
                    }
                } else if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                     >> 0x0000000cU)))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wait = 1U;
                }
            }
        }
        if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state) 
                      >> 1U)))) {
            if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state)))) {
                if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                     & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
                    if ((0x00004000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                        if ((0x00002000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                            if ((0x00001000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                                if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                              >> 0x0000001bU)))) {
                                    if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                  >> 0x0000001aU)))) {
                                        if ((0x02000000U 
                                             & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg 
                                                = (0x000007ffU 
                                                   & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_p 
            = (0x00ffffffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_x) 
                              * (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_y)));
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__start) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__outsign 
                = ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_div) 
                     & ((vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                         >> 0x1fU) != (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                                       >> 0x1fU))) 
                    & (0U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2)) 
                   | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_rem) 
                      & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                         >> 0x1fU)));
        }
    } else {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wait = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__cfg = 0U;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_rem = 0U;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_div = 0U;
    if (((((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid)) 
          & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_ready))) 
         & (0x02000033U == (0xfe00007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)))) {
        if ((4U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                          >> 0x0cU)))) {
            if ((5U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                              >> 0x0cU)))) {
                if ((6U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                  >> 0x0cU)))) {
                    if ((7U == (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                      >> 0x0cU)))) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_remu = 1U;
                    }
                }
                if ((6U == (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                  >> 0x0cU)))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_rem = 1U;
                }
            }
            if ((5U == (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                              >> 0x0cU)))) {
                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_divu = 1U;
            }
        }
        if ((4U == (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                          >> 0x0cU)))) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_div = 1U;
        }
    }
    vlSelfRef.__Vdfg_Regularize_1106 = ((__Vdfg_Regularize_1165 
                                         << 0x24U) 
                                        | (__Vdfg_Regularize_1165 
                                           >> 0x0000001cU));
    vlSelfRef.__Vdfg_Regularize_1107 = ((__Vdfg_Regularize_1166 
                                         << 3U) | (__Vdfg_Regularize_1166 
                                                   >> 0x0000003dU));
    vlSelfRef.__Vdfg_Regularize_1108 = ((__Vdfg_Regularize_1167 
                                         << 0x29U) 
                                        | (__Vdfg_Regularize_1167 
                                           >> 0x00000017U));
    vlSelfRef.__Vdfg_Regularize_1109 = ((__Vdfg_Regularize_1168 
                                         << 0x12U) 
                                        | (__Vdfg_Regularize_1168 
                                           >> 0x0000002eU));
    vlSelfRef.__Vdfg_Regularize_1115 = ((__Vdfg_Regularize_1174 
                                         << 0x3eU) 
                                        | (__Vdfg_Regularize_1174 
                                           >> 2U));
    vlSelfRef.__Vdfg_Regularize_1116 = ((__Vdfg_Regularize_1175 
                                         << 6U) | (__Vdfg_Regularize_1175 
                                                   >> 0x0000003aU));
    vlSelfRef.__Vdfg_Regularize_1117 = ((__Vdfg_Regularize_1176 
                                         << 0x2bU) 
                                        | (__Vdfg_Regularize_1176 
                                           >> 0x00000015U));
    vlSelfRef.__Vdfg_Regularize_1118 = ((__Vdfg_Regularize_1177 
                                         << 0x0fU) 
                                        | (__Vdfg_Regularize_1177 
                                           >> 0x00000031U));
    vlSelfRef.__Vdfg_Regularize_1119 = ((__Vdfg_Regularize_1178 
                                         << 0x3dU) 
                                        | (__Vdfg_Regularize_1178 
                                           >> 3U));
    vlSelfRef.__Vdfg_Regularize_1120 = ((__Vdfg_Regularize_1179 
                                         << 0x1cU) 
                                        | (__Vdfg_Regularize_1179 
                                           >> 0x00000024U));
    vlSelfRef.__Vdfg_Regularize_1121 = ((__Vdfg_Regularize_1180 
                                         << 0x37U) 
                                        | (__Vdfg_Regularize_1180 
                                           >> 9U));
    vlSelfRef.__Vdfg_Regularize_1122 = ((__Vdfg_Regularize_1181 
                                         << 0x19U) 
                                        | (__Vdfg_Regularize_1181 
                                           >> 0x00000027U));
    vlSelfRef.__Vdfg_Regularize_1123 = ((__Vdfg_Regularize_1182 
                                         << 0x15U) 
                                        | (__Vdfg_Regularize_1182 
                                           >> 0x0000002bU));
    vlSelfRef.__Vdfg_Regularize_1124 = ((__Vdfg_Regularize_1183 
                                         << 0x38U) 
                                        | (__Vdfg_Regularize_1183 
                                           >> 8U));
    vlSelfRef.__Vdfg_Regularize_1125 = ((__Vdfg_Regularize_1184 
                                         << 0x1bU) 
                                        | (__Vdfg_Regularize_1184 
                                           >> 0x00000025U));
    vlSelfRef.__Vdfg_Regularize_1126 = ((__Vdfg_Regularize_1185 
                                         << 0x14U) 
                                        | (__Vdfg_Regularize_1185 
                                           >> 0x0000002cU));
    vlSelfRef.__Vdfg_Regularize_1127 = ((__Vdfg_Regularize_1186 
                                         << 0x27U) 
                                        | (__Vdfg_Regularize_1186 
                                           >> 0x00000019U));
    vlSelfRef.__Vdfg_Regularize_1128 = ((__Vdfg_Regularize_1187 
                                         << 8U) | (__Vdfg_Regularize_1187 
                                                   >> 0x00000038U));
    vlSelfRef.__Vdfg_Regularize_1129 = ((__Vdfg_Regularize_1188 
                                         << 0x0eU) 
                                        | (__Vdfg_Regularize_1188 
                                           >> 0x00000032U));
    vlSelfRef.__Vdfg_Regularize_1110 = ((__Vdfg_Regularize_1169 
                                         << 1U) | (__Vdfg_Regularize_1169 
                                                   >> 0x0000003fU));
    vlSelfRef.__Vdfg_Regularize_1111 = ((__Vdfg_Regularize_1170 
                                         << 0x2cU) 
                                        | (__Vdfg_Regularize_1170 
                                           >> 0x00000014U));
    vlSelfRef.__Vdfg_Regularize_1112 = ((__Vdfg_Regularize_1171 
                                         << 0x0aU) 
                                        | (__Vdfg_Regularize_1171 
                                           >> 0x00000036U));
    vlSelfRef.__Vdfg_Regularize_1113 = ((__Vdfg_Regularize_1172 
                                         << 0x2dU) 
                                        | (__Vdfg_Regularize_1172 
                                           >> 0x00000013U));
    vlSelfRef.__Vdfg_Regularize_1114 = ((__Vdfg_Regularize_1173 
                                         << 2U) | (__Vdfg_Regularize_1173 
                                                   >> 0x0000003eU));
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_tag 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_tag;
        if ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
            if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
                if ((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))) {
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_1 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[1U];
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_5 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[1U];
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_0 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a1;
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_4 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a1;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s 
                        = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_0) 
                                          + (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_1)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d 
                        = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_4) 
                                          - (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_5)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t 
                        = (0x00001fffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s) 
                                          - (::IData)(0x0d01U)));
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_7 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[0U];
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_3 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[0U];
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_6 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a0;
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_2 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a0;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_7__msub 
                        = (0x00000fffU & ((0x00001000U 
                                           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                           ? ((::IData)(0x0d01U) 
                                              + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                           : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d 
                        = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_6) 
                                          - (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_7)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_8__msub 
                        = (0x00000fffU & ((0x00001000U 
                                           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                           ? ((::IData)(0x0d01U) 
                                              + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                           : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_5__madd 
                        = (0x00000fffU & ((0x00001000U 
                                           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t))
                                           ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s)
                                           : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s 
                        = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_2) 
                                          + (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_3)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t 
                        = (0x00001fffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s) 
                                          - (::IData)(0x0d01U)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_6__madd 
                        = (0x00000fffU & ((0x00001000U 
                                           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t))
                                           ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s)
                                           : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t)));
                    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__breg_139 
                        = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_7__msub) 
                            << 0x00000010U) | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_8__msub));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd 
                        = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_5__madd) 
                            << 0x00000010U) | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_6__madd));
                } else if ((2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))) {
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_9 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b1;
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_8 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a1;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s 
                        = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_8) 
                                          + (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_9)));
                    __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__breg_139 
                        = ((vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[1U] 
                            << 0x00000010U) | vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[0U]);
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t 
                        = (0x00001fffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s) 
                                          - (::IData)(0x0d01U)));
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_11 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b0;
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_10 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a0;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_9__madd 
                        = (0x00000fffU & ((0x00001000U 
                                           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t))
                                           ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s)
                                           : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s 
                        = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_10) 
                                          + (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_11)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t 
                        = (0x00001fffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s) 
                                          - (::IData)(0x0d01U)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_10__madd 
                        = (0x00000fffU & ((0x00001000U 
                                           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t))
                                           ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s)
                                           : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd 
                        = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_9__madd) 
                            << 0x00000010U) | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_10__madd));
                } else if ((5U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd 
                        = ((vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[1U] 
                            << 0x00000010U) | vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[0U]);
                } else {
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_13 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[3U];
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_12 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[2U];
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s 
                        = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_12) 
                                          + (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_13)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t 
                        = (0x00001fffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s) 
                                          - (::IData)(0x0d01U)));
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_15 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[4U];
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_14 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[1U];
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_11__madd 
                        = (0x00000fffU & ((0x00001000U 
                                           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t))
                                           ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s)
                                           : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s 
                        = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_14) 
                                          + (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_15)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t 
                        = (0x00001fffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s) 
                                          - (::IData)(0x0d01U)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_12__madd 
                        = (0x00000fffU & ((0x00001000U 
                                           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t))
                                           ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s)
                                           : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t)));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd 
                        = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_11__madd) 
                            << 0x00000010U) | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_12__madd));
                }
            } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok) {
                __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__s_17 
                    = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick;
                if ((4U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))) {
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__Vfuncout_16 
                        = ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                            ? 0U : ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                                     ? ((0U == (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__s_17))
                                         ? (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__zreg) 
                                             << 0x0000000cU) 
                                            | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a0))
                                         : (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__zreg) 
                                             << 0x0000000cU) 
                                            | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a1)))
                                     : ((4U & (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__s_17))
                                         ? (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__zreg) 
                                             << 0x0000000cU) 
                                            | vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[0U])
                                         : ((2U & (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__s_17))
                                             ? ((1U 
                                                 & (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__s_17))
                                                 ? 
                                                (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a1) 
                                                  << 0x0000000cU) 
                                                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b0))
                                                 : 
                                                (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a0) 
                                                  << 0x0000000cU) 
                                                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b1)))
                                             : ((1U 
                                                 & (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__s_17))
                                                 ? 
                                                (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a0) 
                                                  << 0x0000000cU) 
                                                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b0))
                                                 : 
                                                (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a1) 
                                                  << 0x0000000cU) 
                                                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b1)))))));
                } else if ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))) {
                    if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))) {
                        __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__Vfuncout_16 = 0U;
                    } else {
                        if ((0U == (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__s_17))) {
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_23 
                                = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b0;
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_22 
                                = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a0;
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d 
                                = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_22) 
                                                  - (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_23)));
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vfuncout_21 
                                = (0x00000fffU & ((0x00001000U 
                                                   & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                                   ? 
                                                  ((::IData)(0x0d01U) 
                                                   + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                                   : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d)));
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCall_0__msub_20 
                                = __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vfuncout_21;
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCond_2_18 
                                = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__zreg) 
                                    << 0x0000000cU) 
                                   | (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCall_0__msub_20));
                        } else {
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_26 
                                = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b1;
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_25 
                                = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a1;
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d 
                                = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_25) 
                                                  - (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_26)));
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vfuncout_24 
                                = (0x00000fffU & ((0x00001000U 
                                                   & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                                   ? 
                                                  ((::IData)(0x0d01U) 
                                                   + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                                   : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d)));
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCall_1__msub_19 
                                = __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vfuncout_24;
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCond_2_18 
                                = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__zreg) 
                                    << 0x0000000cU) 
                                   | (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCall_1__msub_19));
                        }
                        __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__Vfuncout_16 
                            = __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops____VlefCond_2_18;
                    }
                } else {
                    __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__Vfuncout_16 
                        = ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                            ? 0U : ((0U == (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__s_17))
                                     ? (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__zreg) 
                                         << 0x0000000cU) 
                                        | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b0))
                                     : (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__zreg) 
                                         << 0x0000000cU) 
                                        | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b1))));
                }
                tb_fpga__DOT__dut__DOT__ise__DOT____Vconcswap_1_ha31419c7__0 
                    = __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__slot_ops__Vfuncout_16;
                vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_x 
                    = (0x00000fffU & (tb_fpga__DOT__dut__DOT__ise__DOT____Vconcswap_1_ha31419c7__0 
                                      >> 0x0000000cU));
                vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_y 
                    = (0x00000fffU & tb_fpga__DOT__dut__DOT__ise__DOT____Vconcswap_1_ha31419c7__0);
            }
        } else if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_x 
                = (0x00000fffU & ((0x0d01U <= (0x00000fffU 
                                               & vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr))
                                   ? (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
                                      - (::IData)(0x0d01U))
                                   : vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr));
            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_y 
                = (0x00000fffU & ((0x0d01U <= (0x00000fffU 
                                               & (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
                                                  >> 0x0cU)))
                                   ? ((vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
                                       >> 0x0cU) - (::IData)(0x0d01U))
                                   : (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
                                      >> 0x0cU)));
        } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                    & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
            if ((0x00004000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                if ((0x00002000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                    if ((0x00001000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                        if ((0x08000000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd 
                                = ((0x04000000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)
                                    ? vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt
                                    : ((0x02000000U 
                                        & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)
                                        ? ((vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xr7 
                                            << 3U) 
                                           + vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xr7)
                                        : vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt));
                        } else if ((0x04000000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                            if ((0x02000000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd 
                                    = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr;
                            }
                        }
                    } else {
                        if ((0x40000000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_28 
                                = (0x00000fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                                                  >> 0x10U));
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_27 
                                = (0x00000fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                                  >> 0x10U));
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d 
                                = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_27) 
                                                  - (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_28)));
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_30 
                                = (0x00000fffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_29 
                                = (0x00000fffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1);
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_0__msub 
                                = (0x00000fffU & ((0x00001000U 
                                                   & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                                   ? 
                                                  ((::IData)(0x0d01U) 
                                                   + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                                   : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d)));
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d 
                                = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__a_29) 
                                                  - (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__msub__b_30)));
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_1__msub 
                                = (0x00000fffU & ((0x00001000U 
                                                   & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                                   ? 
                                                  ((::IData)(0x0d01U) 
                                                   + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d))
                                                   : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d)));
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCond_4 
                                = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_0__msub) 
                                    << 0x00000010U) 
                                   | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_1__msub));
                        } else {
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_32 
                                = (0x00000fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                                                  >> 0x10U));
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_31 
                                = (0x00000fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                                  >> 0x10U));
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s 
                                = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_31) 
                                                  + (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_32)));
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t 
                                = (0x00001fffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s) 
                                                  - (::IData)(0x0d01U)));
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_34 
                                = (0x00000fffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
                            __Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_33 
                                = (0x00000fffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1);
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_2__madd 
                                = (0x00000fffU & ((0x00001000U 
                                                   & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t))
                                                   ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s)
                                                   : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t)));
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s 
                                = (0x00001fffU & ((::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__a_33) 
                                                  + (::IData)(__Vfunc_tb_fpga__DOT__dut__DOT__ise__DOT__madd__b_34)));
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t 
                                = (0x00001fffU & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s) 
                                                  - (::IData)(0x0d01U)));
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_3__madd 
                                = (0x00000fffU & ((0x00001000U 
                                                   & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t))
                                                   ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s)
                                                   : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t)));
                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCond_4 
                                = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_2__madd) 
                                    << 0x00000010U) 
                                   | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCall_3__madd));
                        }
                        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd 
                            = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT____VlemCond_4;
                    }
                }
            } else if ((0x00001000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd 
                    = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__breg;
            }
        }
    } else {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__breg_139 = 0U;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xr7 
        = ((tb_fpga__DOT__dut__DOT__ise__DOT__x5 << 7U) 
           | (tb_fpga__DOT__dut__DOT__ise__DOT__x5 
              >> 0x00000019U));
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__breg 
        = __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__breg_139;
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt 
        = __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt_150;
    if (__Vdly_Set__tb_fpga__DOT__dut__DOT__ise__DOT__slot_210) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__slot[__Vdly_Dim0__tb_fpga__DOT__dut__DOT__ise__DOT__slot_209] 
            = __Vdly_Val__tb_fpga__DOT__dut__DOT__ise__DOT__slot_208;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
        = __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__lfsr_145;
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_v 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
           && (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_v));
    vlSelfRef.__Vdfg_Regularize_1139 = (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
                                        >> 1U);
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_ready = 0U;
    if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger) 
         & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_pseudo_trigger)))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sb 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw) 
               & (0U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sh 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw) 
               & (0x00001000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sw 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw) 
               & (0x00002000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lbu 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0x00004000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lhu 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0x00005000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lw 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0x00002000U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)));
    }
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_tag 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_tag;
        if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state) 
                      >> 1U)))) {
            if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state)))) {
                if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise) 
                     & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a1 
                        = (0x00000fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                          >> 0x10U));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__a0 
                        = (0x00000fffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1);
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b1 
                        = (0x00000fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                                          >> 0x10U));
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__b0 
                        = (0x00000fffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op 
                        = (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                 >> 0x0000000cU));
                    if ((0x00004000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                        if ((0x00002000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                            if ((0x00001000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) {
                                if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                              >> 0x0000001bU)))) {
                                    if ((1U & (~ (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                  >> 0x0000001aU)))) {
                                        if ((1U & (~ 
                                                   (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                                    >> 0x00000019U)))) {
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__zreg 
                                                = (0x00000fffU 
                                                   & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__zreg = 0U;
    }
    if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger) 
         & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_pseudo_trigger)))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q;
    }
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__start)))) {
            if (((~ (0U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk)) 
                 & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running))) {
                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_ready = 1U;
            }
        }
        if (((((((((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
                   | (0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                  | (0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                 | (0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                | (8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
               | (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
              | (2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
             | (1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))) {
            if ((0x80U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                if ((0x40U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) 
                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)) 
                             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal))) {
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid = 1U;
                                if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid = 0U;
                                } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout) 
                                            | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ecall_ebreak))) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid = 0U;
                                }
                            }
                        }
                    } else if ((0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid = 1U;
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid = 0U;
                            } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout) 
                                        | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ecall_ebreak))) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid = 0U;
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid = 0U;
    }
    if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger) 
         & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_pseudo_trigger)))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ecall_ebreak 
            = (((0x73U == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q)) 
                & (~ (0U != (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                             >> 0x15U)))) & (~ (0U 
                                                != 
                                                (0x00001fffU 
                                                 & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
                                                    >> 7U)))));
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready 
        = __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready_136;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk_129;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running_124;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__start 
        = ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait_q)) 
           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait));
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_v 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
           && (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_v));
    if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst) 
         & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done))) {
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu_31 
            = (3U == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle));
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw_32 
            = (0x23U == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle));
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq_29 = 0U;
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal_27 
            = (0x6fU == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle));
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr_28 
            = (::IData)((0x00000067U == (0x0000707fU 
                                         & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle)));
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu_30 
            = (0x63U == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs1 
            = (0x0000001fU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle 
                              >> 0x0fU));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j 
            = ((0x000fffffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j) 
               | (0xfff00000U & VL_EXTENDS_II(32,21, 
                                              (0x001ffffeU 
                                               & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle 
                                                  >> 0x0000000bU)))));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j 
            = ((0xfffff801U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j) 
               | (0x000007feU & (VL_EXTENDS_II(32,21, 
                                               (0x001ffffeU 
                                                & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle 
                                                   >> 0x0000000bU))) 
                                 >> 9U)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j 
            = ((0xfffff7ffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j) 
               | (0x00000800U & (VL_EXTENDS_II(32,21, 
                                               (0x001ffffeU 
                                                & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle 
                                                   >> 0x0000000bU))) 
                                 << 2U)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j 
            = ((0xfff00fffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j) 
               | (0x000ff000U & (VL_EXTENDS_II(32,21, 
                                               (0x001ffffeU 
                                                & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle 
                                                   >> 0x0000000bU))) 
                                 << 0x0000000bU)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j 
            = ((0xfffffffeU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j) 
               | (1U & VL_EXTENDS_II(1,21, (0x001ffffeU 
                                            & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle 
                                               >> 0x0000000bU)))));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_auipc 
            = (0x17U == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lui 
            = (0x37U == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__compressed_instr = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rd 
            = (0x0000001fU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle 
                              >> 7U));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg 
            = (0x33U == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm 
            = (0x13U == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle));
    }
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_tag 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_tag;
        if (((((((((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
                   | (0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                  | (0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                 | (0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                | (8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
               | (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
              | (2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
             | (1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))) {
            if ((0x80U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                if ((0x40U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 = 0U;
                        if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) 
                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)) 
                             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal))) {
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                                    = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs2;
                            } else if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)))) {
                                if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                                        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm;
                                }
                            }
                        } else if ((1U & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu) 
                                             & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap)))))) {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                                = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi) 
                                    || (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai))
                                    ? ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai)
                                        ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs2)
                                        : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm)
                                    : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs2);
                        }
                    } else if ((0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                            = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs2;
                    }
                }
            }
        }
    }
    if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst) 
         & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs2 
            = (0x0000001fU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle 
                              >> 0x14U));
    }
    tb_fpga__DOT__dut__DOT____Vcellinp__cpu__pcpi_ready 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready) 
           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout 
        = (1U & (~ (0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter))));
    if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)))) {
        __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu_30 = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_fence = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_beq = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bne = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bge = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bgeu = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xor = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_or = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_and = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xori = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ori = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_andi = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_compare = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sll = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srl = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sra = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_blt = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bltu = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_add = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_addi = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sub = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slt = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltu = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slti = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltiu = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout = 0U;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter_91;
    if ((1U & (~ ((~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)) 
                  | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__trap))))) {
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_write) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wdata 
                = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wdata;
        }
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid) 
           & (0x0bU == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)));
    vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__is_kk 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid) 
           & (0x2bU == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_pseudo_trigger = 0U;
    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)) 
               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__trap)))) {
        if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)))) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state_14 = 0U;
        }
    } else if ((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) {
        if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch) 
              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst)) 
             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata))) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state_14 = 1U;
        }
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state_14 = 2U;
        }
    } else if ((1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) {
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state_14 
                = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst) 
                    | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata))
                    ? 0U : 3U);
        }
    } else if ((2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) {
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state_14 = 0U;
        }
    } else if ((3U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) {
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst) {
            __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state_14 = 0U;
        }
    }
    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata;
    }
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_v = 0U;
        if ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
            if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state)))) {
                if (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_v = 1U;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_tag 
                        = vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick;
                }
            }
        } else if ((1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state))) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_v = 1U;
            vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_tag = 8U;
        }
        if (((((((((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
                   | (0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                  | (0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                 | (0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                | (8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
               | (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
              | (2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
             | (1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))) {
            if ((0x80U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                if ((0x40U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0x20U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((0x10U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                            if ((8U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                if ((4U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                                        if (((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                             & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done))) {
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_pseudo_trigger = 1U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid) 
             & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready)))) {
            if ((0x00020000U > vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                if ((1U & (~ (0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb))))) {
                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__ram_pend) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata 
                            = vlSelfRef.tb_fpga__DOT__dut__DOT__ram_q;
                    }
                }
            } else if ((0x10000000U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                if ((0x10000004U == vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata 
                        = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__rx_full) 
                            << 8U) | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__rx_byte));
                } else if ((0x20000000U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                    if ((0x30000000U != vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr)) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata = 0U;
                    }
                }
            }
        }
    } else {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__mm_v = 0U;
    }
    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)) 
               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__trap)))) {
        if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)) 
                   | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready)))) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid = 0U;
        }
    } else if ((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) {
        if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch) 
              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst)) 
             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata))) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid = 1U;
        }
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid = 1U;
        }
    } else if ((1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) {
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid = 0U;
        }
    } else if ((2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) {
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid = 0U;
        }
    }
    if (vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_valid) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__rx_byte = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_data;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick = 0U;
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok = 0U;
    tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand 
        = ((4U == ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                    ? 4U : 2U)) ? (3U & ((::IData)(3U) 
                                         + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__rot)))
            : (1U & (1U ^ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__swp))));
    if (((3U < ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                 ? 4U : 2U)) & (~ ((4U >= (::IData)(tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand)) 
                                   && (1U & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__issued) 
                                             >> (::IData)(tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand))))))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick 
            = tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok = 1U;
    }
    tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand 
        = ((4U == ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                    ? 4U : 2U)) ? (3U & ((::IData)(2U) 
                                         + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__rot)))
            : (1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__swp)));
    if (((2U < ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                 ? 4U : 2U)) & (~ ((4U >= (::IData)(tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand)) 
                                   && (1U & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__issued) 
                                             >> (::IData)(tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand))))))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick 
            = tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok = 1U;
    }
    tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand 
        = ((4U == ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                    ? 4U : 2U)) ? (3U & ((::IData)(1U) 
                                         + (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__rot)))
            : (1U & (1U ^ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__swp))));
    if (((1U < ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                 ? 4U : 2U)) & (~ ((4U >= (::IData)(tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand)) 
                                   && (1U & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__issued) 
                                             >> (::IData)(tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand))))))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick 
            = tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok = 1U;
    }
    tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand 
        = ((4U == ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                    ? 4U : 2U)) ? (3U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__rot))
            : (1U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__swp)));
    if (((0U < ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))
                 ? 4U : 2U)) & (~ ((4U >= (::IData)(tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand)) 
                                   && (1U & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__issued) 
                                             >> (::IData)(tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand))))))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick 
            = tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok = 1U;
    }
    if (((((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok)) 
           & (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__op))) 
          & (~ ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__issued) 
                >> 4U))) & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__done))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick = 4U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok = 1U;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__state 
        = __Vdly__tb_fpga__DOT__dut__DOT__ise__DOT__state_135;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs2 
        = ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs2))
            ? vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs
           [vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs2]
            : 0U);
    vlSelfRef.tb_fpga__DOT__dut__DOT__rx_full = __Vdly__tb_fpga__DOT__dut__DOT__rx_full_6;
    vlSelfRef.tb_fpga__DOT__dut__DOT__ram_pend = __Vdly__tb_fpga__DOT__dut__DOT__ram_pend_8;
    vlSelfRef.tb_fpga__DOT__dut__DOT__ram_q = vlSelfRef.tb_fpga__DOT__dut__DOT__ram
        [(0x00007fffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr 
                         >> 2U))];
    if ((1U & (~ ((~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)) 
                  | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__trap))))) {
        if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_read) 
             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_write))) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb 
                = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wstrb) 
                   & (- (::IData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_write))));
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr 
                = ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch) 
                     | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst))
                     ? ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch) 
                          & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store))
                          ? (0xfffffffeU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out)
                          : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc) 
                        >> 2U) : (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                  >> 2U)) << 2U);
        }
        if ((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) {
            if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch) 
                  | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst)) 
                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata))) {
                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb = 0U;
            }
        }
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata_89;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state_14;
    vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready = __Vdly__tb_fpga__DOT__dut__DOT__mem_ready_4;
    if (__Vdly_Set__tb_fpga__DOT__dut__DOT__ram_195) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ram[__Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_194] 
            = ((0xffffff00U & vlSelfRef.tb_fpga__DOT__dut__DOT__ram
                [__Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_194]) 
               | (::IData)(__Vdly_Val__tb_fpga__DOT__dut__DOT__ram_193));
    }
    if (__Vdly_Set__tb_fpga__DOT__dut__DOT__ram_198) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ram[__Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_197] 
            = ((0xffff00ffU & vlSelfRef.tb_fpga__DOT__dut__DOT__ram
                [__Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_197]) 
               | ((::IData)(__Vdly_Val__tb_fpga__DOT__dut__DOT__ram_196) 
                  << 8U));
    }
    if (__Vdly_Set__tb_fpga__DOT__dut__DOT__ram_201) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ram[__Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_200] 
            = ((0xff00ffffU & vlSelfRef.tb_fpga__DOT__dut__DOT__ram
                [__Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_200]) 
               | ((::IData)(__Vdly_Val__tb_fpga__DOT__dut__DOT__ram_199) 
                  << 0x00000010U));
    }
    if (__Vdly_Set__tb_fpga__DOT__dut__DOT__ram_204) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__ram[__Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_203] 
            = ((0x00ffffffU & vlSelfRef.tb_fpga__DOT__dut__DOT__ram
                [__Vdly_Dim0__tb_fpga__DOT__dut__DOT__ram_203]) 
               | ((::IData)(__Vdly_Val__tb_fpga__DOT__dut__DOT__ram_202) 
                  << 0x00000018U));
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_valid = 0U;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid) 
           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer)
            ? vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata
            : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q);
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        if (vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy) {
            if ((7U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt))) {
                if ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit))) {
                    if ((8U < (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit))) {
                        if ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__sync))) {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_valid = 1U;
                            vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_data 
                                = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh;
                        }
                    }
                }
            }
        }
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh_184;
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit_183;
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy_181;
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt_182;
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__sync 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__sync_179;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc 
            = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc_99;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__trap = 0U;
        tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rinst = 0U;
        if (((((((((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
                   | (0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                  | (0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                 | (0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                | (8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
               | (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
              | (2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
             | (1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))) {
            if ((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__trap = 1U;
            }
            if ((0x80U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                if ((0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store = 0U;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch = 0U;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst 
                        = (1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger)) 
                                 & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__do_waitirq))));
                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger) {
                        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal) {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch = 1U;
                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst = 1U;
                        } else {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst = 0U;
                        }
                    }
                } else {
                    if ((0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) 
                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)) 
                             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal))) {
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                                if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store 
                                        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_wr;
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst = 1U;
                                }
                            } else {
                                if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store = 1U;
                                } else if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal)))) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store = 1U;
                                }
                                if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)))) {
                                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal) {
                                        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst 
                                            = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch;
                                    }
                                }
                            }
                        } else {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst 
                                = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu) 
                                    & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap))) 
                                   || (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi) 
                                        || (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai))
                                        ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)
                                        : ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw) 
                                           || (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch))));
                        }
                    } else if ((0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store 
                                    = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_wr;
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst = 1U;
                            }
                        } else {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst 
                                = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw) 
                                   || (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch));
                        }
                    } else if ((8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store 
                            = ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu))) 
                               || (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0));
                        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) {
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0) {
                                tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rinst = 1U;
                            }
                        }
                    } else if ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store = 1U;
                        if ((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh))) {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst 
                                = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch;
                        }
                    } else if ((2U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store = 1U;
                    }
                    if ((0x20U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((0x10U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                            if ((8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch 
                                    = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu)
                                        ? (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0)
                                        : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr));
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh_184;
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit_183;
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy_181;
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt_182;
        vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__sync 
            = __Vdly__tb_fpga__DOT__dut__DOT__u_uart__DOT__sync_179;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc 
            = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc_99;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__trap = 0U;
        tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rinst = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store = 1U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch = 0U;
    }
    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)) 
               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst = 0U;
    }
    if (tb_fpga__DOT__dut__DOT__cpu__DOT__set_mem_do_rinst) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst = 1U;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out = 0U;
    if (vlSelfRef.tb_fpga__DOT__resetn) {
        if (((((((((0x80U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)) 
                   | (0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                  | (0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                 | (0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
                | (8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
               | (4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
              | (2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) 
             | (1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state)))) {
            if ((0x80U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                if ((0x40U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0x20U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) 
                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)) 
                             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal))) {
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                                if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out 
                                        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_rd;
                                }
                            } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh) {
                                if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out 
                                        = (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle);
                                } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out 
                                        = (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr);
                                }
                            } else if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal)))) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out 
                                    = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__timer;
                            }
                            if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap)))) {
                                if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)))) {
                                    if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal)))) {
                                        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__timer 
                                            = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs1;
                                    }
                                }
                            }
                        }
                    } else if ((0x10U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap) {
                            if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready) {
                                vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out 
                                    = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_rd;
                            }
                        }
                    } else if ((8U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out 
                            = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc 
                               + vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm);
                    } else if ((4U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh))) {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out 
                                = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1;
                        }
                    } else if ((2U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                   | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                            if (((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                 & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done))) {
                                if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lu) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out 
                                        = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_word;
                                } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lh) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out 
                                        = VL_EXTENDS_II(32,16, 
                                                        (0x0000ffffU 
                                                         & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_word));
                                } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lb) {
                                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out 
                                        = VL_EXTENDS_II(32,8, 
                                                        (0x000000ffU 
                                                         & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_word));
                                }
                            }
                        }
                    }
                }
                if ((0x40U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lu = 0U;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lh = 0U;
                    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lb = 0U;
                    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger) {
                        if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal)))) {
                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch 
                                = (1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr)) 
                                         & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq))));
                        }
                    }
                } else if ((0x20U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                    if ((0x10U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                        if ((8U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                            if ((4U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                if ((2U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state))) {
                                    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch)) 
                                               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
                                        if ((1U & (~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata)))) {
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lu 
                                                = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lbu_lhu_lw;
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lh 
                                                = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh;
                                            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lb 
                                                = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out = 0x00020000U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__timer = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lu = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lh = 0U;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lb = 0U;
    }
    if ((1U & ((~ (::IData)(vlSelfRef.tb_fpga__DOT__resetn)) 
               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done)))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch = 0U;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_wr 
        = (1U & ((::IData)(tb_fpga__DOT__dut__DOT____Vcellinp__cpu__pcpi_ready)
                  ? ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wr) 
                     | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wr))
                  : (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active) 
                      >> 1U) | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_ready) 
                                & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wr)))));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi_82;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai_81;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw_32;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu_31;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu_30;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle_93;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr_108;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_83;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc_98;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh_85;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready 
        = (1U & ((::IData)(tb_fpga__DOT__dut__DOT____Vcellinp__cpu__pcpi_ready) 
                 | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_ready) 
                    | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active) 
                       >> 1U))));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_rd 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready)
            ? vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_rd
            : ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready)
                ? vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd
                : ((2U & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active))
                    ? ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__shift_out)
                        ? (::IData)((vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rd 
                                     >> 0x00000020U))
                        : (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rd))
                    : (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_rd 
                       & (- (::IData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_ready)))))));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle_74;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr_76;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1_111;
    if ((0U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wdata 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wstrb = 0x0fU;
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_word 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata;
    } else if ((1U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wdata 
            = ((vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                << 0x00000010U) | (0x0000ffffU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2));
        if ((2U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1)) {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wstrb = 0x0cU;
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_word 
                = (vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata 
                   >> 0x10U);
        } else {
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wstrb = 3U;
            vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_word 
                = (0x0000ffffU & vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata);
        }
    } else if ((2U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wdata 
            = ((vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                << 0x00000018U) | ((0x00ff0000U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                                                   << 0x00000010U)) 
                                   | ((0x0000ff00U 
                                       & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 
                                          << 8U)) | 
                                      (0x000000ffU 
                                       & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2))));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wstrb 
            = (0x0000000fU & ((::IData)(1U) << (3U 
                                                & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1)));
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_word 
            = ((2U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1)
                ? ((1U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1)
                    ? (vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata 
                       >> 0x18U) : (0x000000ffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata 
                                                   >> 0x10U)))
                : ((1U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1)
                    ? (0x000000ffU & (vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata 
                                      >> 8U)) : (0x000000ffU 
                                                 & vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata)));
    }
    vlSelfRef.__Vdfg_Regularize_1137 = ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch)) 
                                        & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__do_waitirq = 0U;
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_eq = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                                == vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_lts = VL_LTS_III(32, vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1, vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_ltu = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                                 < vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0 = 0U;
    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_beq) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0 
            = tb_fpga__DOT__dut__DOT__cpu__DOT__alu_eq;
    } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bne) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0 
            = (1U & (~ (::IData)(tb_fpga__DOT__dut__DOT__cpu__DOT__alu_eq)));
    } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bge) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0 
            = (1U & (~ (::IData)(tb_fpga__DOT__dut__DOT__cpu__DOT__alu_lts)));
    } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bgeu) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0 
            = (1U & (~ (::IData)(tb_fpga__DOT__dut__DOT__cpu__DOT__alu_ltu)));
    } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_slti_blt_slt) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0 
            = tb_fpga__DOT__dut__DOT__cpu__DOT__alu_lts;
    } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_sltiu_bltu_sltu) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0 
            = tb_fpga__DOT__dut__DOT__cpu__DOT__alu_ltu;
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out = 0U;
    if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal_jalr_addi_add_sub) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out 
            = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sub)
                ? (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                   - vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2)
                : (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                   + vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2));
    } else if (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_compare) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out 
            = vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0;
    } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xori) 
                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xor))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out 
            = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
               ^ vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
    } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ori) 
                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_or))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out 
            = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
               | vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
    } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_andi) 
                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_and))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out 
            = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
               & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
    } else if (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sll) 
                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slli))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out 
            = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
               << (0x0000001fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2));
    } else if (((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srl) 
                  | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srli)) 
                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sra)) 
                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srai))) {
        vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out 
            = (::IData)((0x00000001ffffffffULL & VL_SHIFTRS_QQI(33,33,5, 
                                                                (((::QData)((::IData)(
                                                                                ((vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                                                                >> 0x0000001fU) 
                                                                                & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srai) 
                                                                                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sra))))) 
                                                                  << 0x00000020U) 
                                                                 | (::QData)((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1))), 
                                                                (0x0000001fU 
                                                                 & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2))));
    }
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs1 
        = ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs1))
            ? vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs
           [vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs1]
            : 0U);
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal_19;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle) 
           | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycleh) 
              | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr) 
                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstrh))));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_lbu_lhu_lw 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__is_lbu_lhu_lw_23;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh_48;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata_88;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb_47;
    vlSelfRef.__Vdfg_Regularize_1135 = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst) 
                                        | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state_110;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq_29;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr_28;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal_27;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger 
        = __Vdly__tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger_94;
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap 
        = (1U & (~ ((((((((((((((((((((((((((((((((
                                                   (((((((((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lui) 
                                                           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_auipc)) 
                                                          | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal)) 
                                                         | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr)) 
                                                        | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_beq)) 
                                                       | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bne)) 
                                                      | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_blt)) 
                                                     | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bge)) 
                                                    | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bltu)) 
                                                   | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bgeu)) 
                                                  | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb)) 
                                                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh)) 
                                                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lw)) 
                                               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lbu)) 
                                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lhu)) 
                                             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sb)) 
                                            | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sh)) 
                                           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sw)) 
                                          | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_addi)) 
                                         | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slti)) 
                                        | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltiu)) 
                                       | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xori)) 
                                      | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ori)) 
                                     | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_andi)) 
                                    | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slli)) 
                                   | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srli)) 
                                  | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srai)) 
                                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_add)) 
                                | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sub)) 
                               | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sll)) 
                              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slt)) 
                             | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltu)) 
                            | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xor)) 
                           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srl)) 
                          | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sra)) 
                         | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_or)) 
                        | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_and)) 
                       | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh)) 
                      | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_fence)) 
                     | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_getq)) 
                    | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq))));
}

void Vtb_fpga___024root___timing_ready(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___timing_ready\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((((1ULL & vlSelfRef.__VactTriggered[0U])) != 0ULL)) {
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(
                                                              "@(posedge tb_fpga.clk)");
    }
    if ((((2ULL & vlSelfRef.__VactTriggered[0U])) != 0ULL)) {
        vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.ready(
                                                              "@(negedge tb_fpga.dut.u_uart.txd)");
    }
}

void Vtb_fpga___024root___timing_resume(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___timing_resume\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.moveToResumeQueue(
                                                                      "@(posedge tb_fpga.clk)");
    vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.moveToResumeQueue(
                                                                      "@(negedge tb_fpga.dut.u_uart.txd)");
    vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.resume(
                                                           "@(posedge tb_fpga.clk)");
    vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.resume(
                                                           "@(negedge tb_fpga.dut.u_uart.txd)");
    if ((((4ULL & vlSelfRef.__VactTriggered[0U])) != 0ULL)) {
        vlSelfRef.__Vnontrivs.__VdlySched.resume();
    }
}

void Vtb_fpga___024root___trigger_orInto__act_vec_vec(::VlUnpacked<::QData/*63:0*/, 1> &out, const ::VlUnpacked<::QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    ::IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((::IData)(1U) + n);
    } while ((0U >= n));
}

void Vtb_fpga___024root___trigger_clear__act(::VlUnpacked<::QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___trigger_clear__act\n"); );
    // Locals
    ::IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((::IData)(1U) + n);
    } while ((1U > n));
}

void Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0(Vtb_fpga___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root____VbeforeTrig_h6ba11e6d__0\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::VlUnpacked<::QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (::QData)((::IData)(((::IData)(vlSelfRef.tb_fpga__DOT__clk) 
                                      & (~ (::IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_fpga__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_fpga__DOT__clk__0 
        = vlSelfRef.tb_fpga__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_h6ba11e6d__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0(Vtb_fpga___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root____VbeforeTrig_hbf79de5d__0\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::VlUnpacked<::QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (::QData)((::IData)((((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd)) 
                                       & (::IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_fpga__DOT__dut__DOT__u_uart__DOT__txd__0)) 
                                      << 1U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_fpga__DOT__dut__DOT__u_uart__DOT__txd__0 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd;
    if ((2ULL & __VTmp[0U])) {
        vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.ready(__VeventDescription);
        vlSelfRef.__Vnontrivs.__VtrigSched_hbf79de5d__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_fpga___024root___eval_debug_assertions(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_debug_assertions\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
