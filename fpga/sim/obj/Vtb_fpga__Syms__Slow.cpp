// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtb_fpga__pch.h"


void Vtb_fpga__Syms__ctor(Vtb_fpga__Syms* vlSymsp, const char* namep) {
    // Setup top module instance
    VL_INPLACE_CONSTRUCT(vlSymsp->vlInst.TOP, vlSymsp, namep);
    // Check resources
    Verilated::stackCheck(732);
    // Setup sub module instances
    // Configure time unit / time precision
    vlSymsp->_vm_contextp__->timeunit(-9);
    vlSymsp->_vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
}

Vtb_fpga__Syms::Vtb_fpga__Syms(VerilatedContext* contextp, const char* namep, Vtb_fpga* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    , __Vm_didInit{modelp->m_didInit}
{
    Vtb_fpga__Syms__ctor(this, namep);
}

void Vtb_fpga__Syms__dtor(Vtb_fpga__Syms* vlSymsp) {
    // Tear down scopes
    // Tear down sub module instances
    // Tear down top module instance
    VL_INPLACE_DESTRUCT(vlSymsp->vlInst.TOP);
}

Vtb_fpga__Syms::~Vtb_fpga__Syms() {
    Vtb_fpga__Syms__dtor(this);
}
