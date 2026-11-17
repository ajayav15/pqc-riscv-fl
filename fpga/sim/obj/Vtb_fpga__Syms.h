// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_FPGA__SYMS_H_
#define VERILATED_VTB_FPGA__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_fpga.h"

// INCLUDE MODULE CLASSES
#include "Vtb_fpga___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_fpga__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_fpga* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool& __Vm_didInit;

    // MODULE INSTANCE STATE
    union {
        struct {
            Vtb_fpga___024root             TOP;
        } vlInst;
    };

    // CONSTRUCTORS
    Vtb_fpga__Syms(VerilatedContext* contextp, const char* namep, Vtb_fpga* modelp);
    ~Vtb_fpga__Syms();

    // METHODS
    const char* name() const { return vlInst.TOP.vlNamep; }
};

#endif  // guard
