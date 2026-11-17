// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_fpga.h for the primary calling header

#include "Vtb_fpga__pch.h"

void Vtb_fpga___024root___timing_ready(Vtb_fpga___024root* vlSelf);

VL_ATTR_COLD void Vtb_fpga___024root___eval_static(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_static\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_static__TOP
        ::CData/*2:0*/ __Vinline_0__eval_static__TOP_tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand;
        __Vinline_0__eval_static__TOP_tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand = 0;
        vlSelfRef.tb_fpga__DOT__clk = 0U;
        vlSelfRef.tb_fpga__DOT__resetn = 0U;
        vlSelfRef.tb_fpga__DOT__host_tx = 1U;
        const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
        vlSelfRef.tb_fpga__DOT__sendb__Vstatic__k = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2955074067240172733ull);
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__b = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8929735292989235617ull);
        vlSelfRef.tb_fpga__DOT__recvb__Vstatic__k = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15364095338831668950ull);
        vlSelfRef.tb_fpga__DOT__errs = 0U;
        vlSelfRef.tb_fpga__DOT__cyc = 0ULL;
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__s = VL_SCOPED_RAND_RESET_I(13, __VscopeHash, 17353273216633357745ull);
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__madd__Vstatic__t = VL_SCOPED_RAND_RESET_I(13, __VscopeHash, 4433527992633816601ull);
        vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__msub__Vstatic__d = VL_SCOPED_RAND_RESET_I(13, __VscopeHash, 1192661810653830338ull);
        __Vinline_0__eval_static__TOP_tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand = 0;
    }
    vlSelfRef.__Vtrigprevexpr___TOP__tb_fpga__DOT__clk__0 = 0U;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_fpga__DOT__dut__DOT__u_uart__DOT__txd__0 
        = vlSelfRef.tb_fpga__DOT__dut__DOT__u_uart__DOT__txd;
    Vtb_fpga___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((::IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_fpga___024root___dump_triggers__stl(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_fpga___024root___trigger_anySet__stl(const ::VlUnpacked<::QData/*63:0*/, 1> &in);
VL_ATTR_COLD void Vtb_fpga___024root___stl_comb__TOP__0(Vtb_fpga___024root* vlSelf);

VL_ATTR_COLD bool Vtb_fpga___024root___eval_stl(Vtb_fpga___024root* vlSelf, ::CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_stl\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::CData/*0:0*/ __VstlExecute;
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (::IData)((::IData)(firstIteration)));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_fpga___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_fpga___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        {
            // Inlined CFunc: _eval_body__stl
            if ((((1ULL & vlSelfRef.__VstlTriggered[0U])) != 0ULL)) {
                Vtb_fpga___024root___stl_comb__TOP__0(vlSelf);
            }
        }
    }
    return (__VstlExecute);
}

VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__stl(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_dump_triggers__stl\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vtb_fpga___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_fpga___024root___dump_triggers__ico(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__ico(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_dump_triggers__ico\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vtb_fpga___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_fpga___024root___dump_triggers__act(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__act(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_dump_triggers__act\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vtb_fpga___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
}

VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__nba(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_dump_triggers__nba\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    Vtb_fpga___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
}

VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__obs(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_dump_triggers__obs\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__react(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_dump_triggers__react\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtb_fpga___024root___eval_final(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___eval_final\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_fpga___024root___dump_triggers__stl(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (::IData)(Vtb_fpga___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (::IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_fpga___024root___trigger_anySet__stl(const ::VlUnpacked<::QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_fpga___024root___stl_comb__TOP__0(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___stl_comb__TOP__0\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT____Vcellinp__cpu__pcpi_ready;
    tb_fpga__DOT__dut__DOT____Vcellinp__cpu__pcpi_ready = 0;
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__alu_eq;
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_eq = 0;
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__alu_ltu;
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_ltu = 0;
    ::CData/*0:0*/ tb_fpga__DOT__dut__DOT__cpu__DOT__alu_lts;
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_lts = 0;
    ::IData/*31:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__x5;
    tb_fpga__DOT__dut__DOT__ise__DOT__x5 = 0;
    ::CData/*2:0*/ tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand;
    tb_fpga__DOT__dut__DOT__ise__DOT__walk__DOT__cand = 0;
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
    ::CData/*0:0*/ __Vdfg_Regularize_1103;
    __Vdfg_Regularize_1103 = 0;
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
    ::CData/*0:0*/ __Vdfg_Regularize_1138;
    __Vdfg_Regularize_1138 = 0;
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
    // Body
    vlSelfRef.__Vdfg_Regularize_1139 = (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__lfsr 
                                        >> 1U);
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
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs2 
        = ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs2))
            ? vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs
           [vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs2]
            : 0U);
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs1 
        = ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs1))
            ? vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs
           [vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs1]
            : 0U);
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__is_ise 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid) 
           & (0x0bU == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)));
    vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__is_kk 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid) 
           & (0x2bU == (0x0000007fU & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__start 
        = ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait_q)) 
           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait));
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xa2 
        = (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs0 
           ^ vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs2);
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xa3 
        = (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs1 
           ^ vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs3);
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
    vlSelfRef.__Vdfg_Regularize_1137 = ((~ (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch)) 
                                        & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store));
    tb_fpga__DOT__dut__DOT__ise__DOT__x5 = (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs1 
                                            + (vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xs1 
                                               << 2U));
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
    __Vdfg_Regularize_1138 = ((~ (0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) 
                              & (::IData)(vlSelfRef.tb_fpga__DOT__resetn));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid) 
           & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__mem_ready));
    tb_fpga__DOT__dut__DOT____Vcellinp__cpu__pcpi_ready 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready) 
           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready));
    vlSelfRef.__Vdfg_Regularize_1135 = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst) 
                                        | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata));
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_eq = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                                == vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_lts = VL_LTS_III(32, vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1, vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
    tb_fpga__DOT__dut__DOT__cpu__DOT__alu_ltu = (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 
                                                 < vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2);
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle) 
           | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycleh) 
              | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr) 
                 | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstrh))));
    __Vdfg_Regularize_1103 = (((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
                               & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid)) 
                              & (0x02000033U == (0xfe00007fU 
                                                 & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)));
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
    vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__xr7 
        = ((tb_fpga__DOT__dut__DOT__ise__DOT__x5 << 7U) 
           | (tb_fpga__DOT__dut__DOT__ise__DOT__x5 
              >> 0x00000019U));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_write 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata) 
           & (::IData)(__Vdfg_Regularize_1138));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer)
            ? vlSelfRef.tb_fpga__DOT__dut__DOT__mem_rdata
            : vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q);
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready 
        = (1U & ((::IData)(tb_fpga__DOT__dut__DOT____Vcellinp__cpu__pcpi_ready) 
                 | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_ready) 
                    | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active) 
                       >> 1U))));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_wr 
        = (1U & ((::IData)(tb_fpga__DOT__dut__DOT____Vcellinp__cpu__pcpi_ready)
                  ? ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wr) 
                     | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wr))
                  : (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active) 
                      >> 1U) | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_ready) 
                                & (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wr)))));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_read 
        = (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch) 
            | (::IData)(vlSelfRef.__Vdfg_Regularize_1135)) 
           & (::IData)(__Vdfg_Regularize_1138));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__resetn) 
           & (((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst) 
               & (3U == (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state))) 
              | ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer) 
                 & ((0U != (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state)) 
                    & ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata) 
                       | (::IData)(vlSelfRef.__Vdfg_Regularize_1135))))));
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
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh 
        = (::IData)((((0x00001000U == (0x00007000U 
                                       & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                      & (::IData)(__Vdfg_Regularize_1103)) 
                     & (0U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                     >> 0x0000000cU)))));
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu 
        = (::IData)((((0x00002000U == (0x00007000U 
                                       & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                      & (::IData)(__Vdfg_Regularize_1103)) 
                     & ((0U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                      >> 0x0000000cU))) 
                        & (1U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                        >> 0x0000000cU))))));
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
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh 
        = ((::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh) 
           | ((::IData)((((0x00003000U == (0x00007000U 
                                           & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                          & (::IData)(__Vdfg_Regularize_1103)) 
                         & (((0U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                           >> 0x0000000cU))) 
                             & (1U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                             >> 0x0000000cU)))) 
                            & (2U != (7U & (vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn 
                                            >> 0x0000000cU)))))) 
              | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu)));
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
    vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mul 
        = ((::IData)(((0U == (0x00007000U & vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn)) 
                      & (::IData)(__Vdfg_Regularize_1103))) 
           | (::IData)(vlSelfRef.tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh));
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
}

bool Vtb_fpga___024root___trigger_anySet__ico(const ::VlUnpacked<::QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_fpga___024root___dump_triggers__ico(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (::IData)(Vtb_fpga___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (::IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vtb_fpga___024root___trigger_anySet__act(const ::VlUnpacked<::QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_fpga___024root___dump_triggers__act(const ::VlUnpacked<::QData/*63:0*/, 1> &triggers, const ::std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (::IData)(Vtb_fpga___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (::IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_fpga.clk)\n");
    }
    if ((1U & (::IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_fpga.dut.u_uart.txd)\n");
    }
    if ((1U & (::IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_fpga___024root___ctor_var_reset(Vtb_fpga___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_fpga___024root___ctor_var_reset\n"); );
    Vtb_fpga__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    for (int __Vi0 = 0; __Vi0 < 1664; ++__Vi0) {
        vlSelf->tb_fpga__DOT__vec[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4947978433831952162ull);
    }
    vlSelf->tb_fpga__DOT__trig_cyc = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 3631622057210581793ull);
    vlSelf->tb_fpga__DOT__dut__DOT__trigger = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16343703482288511327ull);
    vlSelf->tb_fpga__DOT__dut__DOT__led = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 652776299922859940ull);
    vlSelf->tb_fpga__DOT__dut__DOT__mem_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17501196574063266465ull);
    vlSelf->tb_fpga__DOT__dut__DOT__mem_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14914621673454263380ull);
    for (int __Vi0 = 0; __Vi0 < 32768; ++__Vi0) {
        vlSelf->tb_fpga__DOT__dut__DOT__ram[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9237445229130211526ull);
    }
    vlSelf->tb_fpga__DOT__dut__DOT__ram_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15190177494290006898ull);
    vlSelf->tb_fpga__DOT__dut__DOT__tx_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2423072485359084984ull);
    vlSelf->tb_fpga__DOT__dut__DOT__tx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16701335848113153369ull);
    vlSelf->tb_fpga__DOT__dut__DOT__rx_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5035561541447788778ull);
    vlSelf->tb_fpga__DOT__dut__DOT__rx_byte = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3830074232485995675ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ram_pend = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13241348057428509634ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__trap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14580756839598748012ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11742354578798504016ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12173917060024290302ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9889908161097290111ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12756578738158612497ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10688008257091206981ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5939339255586938586ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 533458357567058711ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_la_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 929430069106103539ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7088252482674533778ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_insn = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2032725255640547518ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__count_cycle = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7001917191327912945ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__count_instr = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 2384921212688756118ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__reg_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16576832726572119023ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__reg_next_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8322074098871300096ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16055708993891631927ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__reg_op2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2074093381395210438ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__reg_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14485982720685428445ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__reg_sh = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 17898203465683567996ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__timer = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3885123223005437532ull);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14704858296129734808ull);
    }
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_wr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 770521173801364903ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_rd = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4649931398873849591ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_int_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13155150825123178146ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16147236628672852589ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_wordsize = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15483911930861906188ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_word = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9224035934245926044ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2377449040375472688ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_prefetch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1008422753039102825ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rinst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3730968929115414055ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_rdata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 475200876604095077ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_do_wdata = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13371972312850409279ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_xfer = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7777804659994601303ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_rdata_latched_noshuffle = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5929166612353644637ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__mem_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11638250326510566551ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lui = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3611192488809273896ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_auipc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12995878704084799692ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9836211640633434908ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6031301592252683629ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_beq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10397425958642023876ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bne = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13804035941935218035ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_blt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16457084554330617749ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bge = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3579199538061581474ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bltu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17267561697867693596ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_bgeu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11763276381524070324ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14986850624063845098ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16778126046614919375ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9721743478530229737ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lbu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4429643646415010131ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_lhu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18127483594368732710ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9392063031432894031ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9416364847806731427ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10598113341666027446ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_addi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3072046928265790508ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slti = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8361494488758273240ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltiu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3853648871663922753ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xori = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16315447313164677272ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ori = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 785468473749788339ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_andi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11958506536370093797ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slli = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7941890267948929286ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srli = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5773666119290031390ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srai = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16297649688560939911ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_add = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18404811879528003900ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sub = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9264339542016442617ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sll = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3076656157031955724ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_slt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17816971453117762803ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sltu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7450887461083937437ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_xor = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11318418421706784660ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_srl = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5037041607746050795ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_sra = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12017879349358488660ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_or = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5053043432695341006ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_and = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12567267527085463727ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycle = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10354582135930900305ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdcycleh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6783492291581022983ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1361640016295084534ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_rdinstrh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 688224970883529131ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_ecall_ebreak = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9285542102668839516ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_fence = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14059216973875914233ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_getq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5967875033124639530ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_retirq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12828100891448991529ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__instr_trap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12594995378350206089ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3602734325456024903ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs1 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 442628611310163662ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_rs2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13761758863488253047ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5417715186551281014ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__decoded_imm_j = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 55948034067253854ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_trigger = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13811730789696754221ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__decoder_pseudo_trigger = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9804070616777787610ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__compressed_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3108545106585480082ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1924102196216587844ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_lb_lh_lw_lbu_lhu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7720909136671884260ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_slli_srli_srai = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16212860106626694367ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5340073794744292261ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_sb_sh_sw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12679426490656268524ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_lui_auipc_jal_jalr_addi_add_sub = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4535613839451395903ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_slti_blt_slt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1451458084015317700ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_sltiu_bltu_sltu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16229622094316477494ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14627750537221542832ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_lbu_lhu_lw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14700352017146827672ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_imm = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1476783360325244366ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_alu_reg_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6587739692153933803ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_compare = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2321634273126528390ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5510890860026154839ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__cpu_state = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9798474436020514158ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__latched_store = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13911793773747460391ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__latched_stalu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2596868747886652395ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__latched_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15683989761836734533ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__latched_compr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14937535346744258031ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17009914531008672734ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14169770087700686769ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__latched_is_lb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15981785404805929581ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__latched_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 14042527146585959727ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__current_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15009173553390565775ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout_counter = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1589358946560317607ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__pcpi_timeout = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12998691167138338198ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__do_waitirq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15871902275039444870ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10912797419705476122ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9529009002427886717ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__alu_out_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16282364432465332283ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5871886233756751688ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__cpuregs_rs2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18227236295528056407ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 29380363434058978ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_rd = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2514289991020985082ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15124729524874907738ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3409819874388912584ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_div = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13652008978021747715ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_divu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5510406750216560339ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_rem = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2349550675697554503ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__instr_remu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6945072707088622045ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16044329323944063847ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1891656078215688873ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__dividend = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2001867199705537743ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__divisor = VL_SCOPED_RAND_RESET_Q(63, __VscopeHash, 7594402230639449087ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13049040532291717984ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__quotient_msk = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6272317458539258717ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__running = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 575775417560064218ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk2__DOT__pcpi_div__DOT__outsign = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3315318784094894767ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2574777982520469667ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 578872515392509991ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mul = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1293020798785782466ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13127642588903258806ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__shift_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16028962834487660190ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__active = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 2325108696600920273ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rs1 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 15708273705641235998ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rs2 = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 13530705612372865341ull);
    vlSelf->tb_fpga__DOT__dut__DOT__cpu__DOT__genblk1__DOT__pcpi_mul__DOT__rd = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12777447478847749466ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1933897523191530420ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_rd = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1928584238355422794ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_wait = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12719784265144914935ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__pcpi_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10460232533832193151ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__is_ise = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7563243420080330179ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__zreg = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 13128314842552994931ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__cfg = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 17314139042279756524ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__lfsr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3565510664067584431ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__breg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9216317367255812281ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__dummy_cnt = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8370098713916008321ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__xs0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12039296537717177210ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__xs1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2317542790003029388ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__xs2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5964300715456960577ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__xs3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3482840683466400027ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__xr7 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8522471552401896250ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__xa2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6290539827150158416ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__xa3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13276542095716200106ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__op = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12466012754716419010ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__a0 = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 11638227326701384598ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__a1 = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 10303287010576232204ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__b0 = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 9273864175346283177ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__b1 = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 15739632022191125238ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__mm_v = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3754057815640919130ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__mm_x = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 16457560648361708519ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__mm_y = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 651793779837250258ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__mm_tag = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1320484680980783896ull);
    for (int __Vi0 = 0; __Vi0 < 5; ++__Vi0) {
        vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__slot[__Vi0] = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 4396176133177266860ull);
    }
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__done = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8726052734012218809ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__issued = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13141918512402002726ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__rot = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14824956918176370628ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__swp = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10465543241940989455ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__ndummy = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10190071528860499050ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__inflight_dummy = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10044876354104226850ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__pick = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 1107408103702893796ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__pick_ok = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18078169104327511595ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13009833279572702268ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10620618647530311154ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_r = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 10419238253013528443ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__out_tag = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 14863632289338439741ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_v = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12394915188018893474ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_p = VL_SCOPED_RAND_RESET_I(24, __VscopeHash, 2691380413319745358ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s1_tag = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12344692785819620397ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_v = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13195035578297102584ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_p = VL_SCOPED_RAND_RESET_I(24, __VscopeHash, 1563455120893918001ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_t = VL_SCOPED_RAND_RESET_I(13, __VscopeHash, 7944953840449720949ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_tag = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 489545752028942258ull);
    vlSelf->tb_fpga__DOT__dut__DOT__ise__DOT__u_mm__DOT__s2_r0 = VL_SCOPED_RAND_RESET_I(14, __VscopeHash, 4693890477885444316ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__tx_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8314644826528231801ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__txd = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1373547766896255749ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12462051227072280726ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__rx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6213486452574814740ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__tcnt = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7321903957528339796ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__tbit = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10677477318875677340ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__tsh = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 3974782588329822139ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__sync = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17824788402249240575ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__rcnt = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7078449076260263562ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__rbit = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17341064457840110559ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__rbusy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8567846913005343650ull);
    vlSelf->tb_fpga__DOT__dut__DOT__u_uart__DOT__rsh = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6676245546711734894ull);
    vlSelf->tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17451275069942161782ull);
    vlSelf->tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_rd = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11126922870270248020ull);
    vlSelf->tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_wait = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14064739098621249145ull);
    vlSelf->tb_fpga__DOT__dut__DOT__kise__DOT__pcpi_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5061592961293640824ull);
    vlSelf->tb_fpga__DOT__dut__DOT__kise__DOT__is_kk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10894712262175916006ull);
    VL_SCOPED_RAND_RESET_W(1600, vlSelf->tb_fpga__DOT__dut__DOT__kise__DOT__st, __VscopeHash, 8006165593408822220ull);
    vlSelf->tb_fpga__DOT__dut__DOT__kise__DOT__rnd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13443488459516063930ull);
    vlSelf->tb_fpga__DOT__dut__DOT__kise__DOT__busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17414368443474197686ull);
    vlSelf->__Vdfg_Regularize_1105 = 0;
    vlSelf->__Vdfg_Regularize_1106 = 0;
    vlSelf->__Vdfg_Regularize_1107 = 0;
    vlSelf->__Vdfg_Regularize_1108 = 0;
    vlSelf->__Vdfg_Regularize_1109 = 0;
    vlSelf->__Vdfg_Regularize_1110 = 0;
    vlSelf->__Vdfg_Regularize_1111 = 0;
    vlSelf->__Vdfg_Regularize_1112 = 0;
    vlSelf->__Vdfg_Regularize_1113 = 0;
    vlSelf->__Vdfg_Regularize_1114 = 0;
    vlSelf->__Vdfg_Regularize_1115 = 0;
    vlSelf->__Vdfg_Regularize_1116 = 0;
    vlSelf->__Vdfg_Regularize_1117 = 0;
    vlSelf->__Vdfg_Regularize_1118 = 0;
    vlSelf->__Vdfg_Regularize_1119 = 0;
    vlSelf->__Vdfg_Regularize_1120 = 0;
    vlSelf->__Vdfg_Regularize_1121 = 0;
    vlSelf->__Vdfg_Regularize_1122 = 0;
    vlSelf->__Vdfg_Regularize_1123 = 0;
    vlSelf->__Vdfg_Regularize_1124 = 0;
    vlSelf->__Vdfg_Regularize_1125 = 0;
    vlSelf->__Vdfg_Regularize_1126 = 0;
    vlSelf->__Vdfg_Regularize_1127 = 0;
    vlSelf->__Vdfg_Regularize_1128 = 0;
    vlSelf->__Vdfg_Regularize_1129 = 0;
    vlSelf->__Vdfg_Regularize_1135 = 0;
    vlSelf->__Vdfg_Regularize_1137 = 0;
    vlSelf->__Vdfg_Regularize_1139 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_fpga__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_fpga__DOT__dut__DOT__u_uart__DOT__txd__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
