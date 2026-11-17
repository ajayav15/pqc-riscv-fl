// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_fpga.h for the primary calling header

#include "Vtb_fpga__pch.h"

void Vtb_fpga___024root___ctor_var_reset(Vtb_fpga___024root* vlSelf);

void Vtb_fpga___024root__ctor(Vtb_fpga___024root* vlSelf, Vtb_fpga__Syms* symsp, const char* namep) {
    vlSelf->vlSymsp = symsp;
    vlSelf->vlNamep = strdup(namep);
    // Construct members
    VL_INPLACE_CONSTRUCT(vlSelf->__Vnontrivs.__VdlySched, *vlSelf->vlSymsp->_vm_contextp__);
    VL_INPLACE_CONSTRUCT(vlSelf->__Vnontrivs.__VtrigSched_h6ba11e6d__0);
    VL_INPLACE_CONSTRUCT(vlSelf->__Vnontrivs.__VtrigSched_hbf79de5d__0);
    // Reset structure values
    Vtb_fpga___024root___ctor_var_reset(vlSelf);
}

Vtb_fpga___024root::Vtb_fpga___024root(Vtb_fpga__Syms* symsp, const char* namep) {
    Vtb_fpga___024root__ctor(this, symsp, namep);
}

void Vtb_fpga___024root__dtor(Vtb_fpga___024root* vlSelf) {
    // Destroy members
    VL_INPLACE_DESTRUCT(vlSelf->__Vnontrivs.__VtrigSched_hbf79de5d__0);
    VL_INPLACE_DESTRUCT(vlSelf->__Vnontrivs.__VtrigSched_h6ba11e6d__0);
    VL_INPLACE_DESTRUCT(vlSelf->__Vnontrivs.__VdlySched);
    VL_DO_DANGLING(std::free(const_cast<char*>(vlSelf->vlNamep)), vlSelf->vlNamep);
}

Vtb_fpga___024root::~Vtb_fpga___024root() {
    Vtb_fpga___024root__dtor(this);
}
