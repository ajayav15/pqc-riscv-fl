// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_fpga__pch.h"

//============================================================
// Constructors

Vtb_fpga::Vtb_fpga(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_fpga__Syms(contextp(), _vcname__, this)}
    , m_evalLoop{*this, /*convergeLimit:*/ 10000}
    , rootp{&(vlSymsp->vlInst.TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_fpga::Vtb_fpga(const char* _vcname__)
    : Vtb_fpga(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_fpga::~Vtb_fpga() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_fpga___024root___eval_debug_assertions(Vtb_fpga___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vtb_fpga___024root___eval_static(Vtb_fpga___024root* vlSelf);
void Vtb_fpga___024root___eval_initial(Vtb_fpga___024root* vlSelf);
VL_ATTR_COLD bool Vtb_fpga___024root___eval_stl(Vtb_fpga___024root* vlSelf, ::CData/*0:0*/ firstIteration);
void Vtb_fpga___024root___eval_sample(Vtb_fpga___024root* vlSelf);
bool Vtb_fpga___024root___eval_ico(Vtb_fpga___024root* vlSelf, ::CData/*0:0*/ firstIteration);
bool Vtb_fpga___024root___eval_act(Vtb_fpga___024root* vlSelf);
bool Vtb_fpga___024root___eval_inact(Vtb_fpga___024root* vlSelf);
bool Vtb_fpga___024root___eval_nba(Vtb_fpga___024root* vlSelf);
bool Vtb_fpga___024root___eval_obs(Vtb_fpga___024root* vlSelf);
bool Vtb_fpga___024root___eval_react(Vtb_fpga___024root* vlSelf);
void Vtb_fpga___024root___eval_postponed(Vtb_fpga___024root* vlSelf);
VL_ATTR_COLD void Vtb_fpga___024root___eval_final(Vtb_fpga___024root* vlSelf);
VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__stl(Vtb_fpga___024root* vlSelf);
VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__ico(Vtb_fpga___024root* vlSelf);
VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__act(Vtb_fpga___024root* vlSelf);
VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__nba(Vtb_fpga___024root* vlSelf);
VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__obs(Vtb_fpga___024root* vlSelf);
VL_ATTR_COLD void Vtb_fpga___024root___eval_dump_triggers__react(Vtb_fpga___024root* vlSelf);

void Vtb_fpga::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_fpga::eval_step\n"); );
    m_evalLoop.eval();
}

void Vtb_fpga::evalBegin() {
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_fpga___024root___eval_debug_assertions(&(vlSymsp->vlInst.TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
}

void Vtb_fpga::evalEnd() {
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
    vlSymsp->vlInst.TOP.__Vnontrivs.__VdlySched.cleanupForevered();
}

void Vtb_fpga::evalStatic() {
    Vtb_fpga___024root___eval_static(&(vlSymsp->vlInst.TOP));
}

void Vtb_fpga::evalInitial() {
    Vtb_fpga___024root___eval_initial(&(vlSymsp->vlInst.TOP));
}

bool Vtb_fpga::evalStl(bool firstIteration) {
    return Vtb_fpga___024root___eval_stl(&(vlSymsp->vlInst.TOP), firstIteration);
}

void Vtb_fpga::evalSample() {
    Vtb_fpga___024root___eval_sample(&(vlSymsp->vlInst.TOP));
}

bool Vtb_fpga::evalIco(bool firstIteration) {
    return Vtb_fpga___024root___eval_ico(&(vlSymsp->vlInst.TOP), firstIteration);
}

bool Vtb_fpga::evalAct() {
    return Vtb_fpga___024root___eval_act(&(vlSymsp->vlInst.TOP));
}

bool Vtb_fpga::evalInact() {
    return Vtb_fpga___024root___eval_inact(&(vlSymsp->vlInst.TOP));
}

bool Vtb_fpga::evalNba() {
    return Vtb_fpga___024root___eval_nba(&(vlSymsp->vlInst.TOP));
}

bool Vtb_fpga::evalObs() {
    return Vtb_fpga___024root___eval_obs(&(vlSymsp->vlInst.TOP));
}

bool Vtb_fpga::evalReact() {
    return Vtb_fpga___024root___eval_react(&(vlSymsp->vlInst.TOP));
}

void Vtb_fpga::evalPostponed() {
    Vtb_fpga___024root___eval_postponed(&(vlSymsp->vlInst.TOP));
}

void Vtb_fpga::evalFinal() {
    Vtb_fpga___024root___eval_final(&(vlSymsp->vlInst.TOP));
}

VL_ATTR_COLD void Vtb_fpga::dumpTriggersStl() {
    Vtb_fpga___024root___eval_dump_triggers__stl(&(vlSymsp->vlInst.TOP));
}

VL_ATTR_COLD void Vtb_fpga::dumpTriggersIco() {
    Vtb_fpga___024root___eval_dump_triggers__ico(&(vlSymsp->vlInst.TOP));
}

VL_ATTR_COLD void Vtb_fpga::dumpTriggersAct() {
    Vtb_fpga___024root___eval_dump_triggers__act(&(vlSymsp->vlInst.TOP));
}

VL_ATTR_COLD void Vtb_fpga::dumpTriggersNba() {
    Vtb_fpga___024root___eval_dump_triggers__nba(&(vlSymsp->vlInst.TOP));
}

VL_ATTR_COLD void Vtb_fpga::dumpTriggersObs() {
    Vtb_fpga___024root___eval_dump_triggers__obs(&(vlSymsp->vlInst.TOP));
}

VL_ATTR_COLD void Vtb_fpga::dumpTriggersReact() {
    Vtb_fpga___024root___eval_dump_triggers__react(&(vlSymsp->vlInst.TOP));
}

//============================================================
// Events and timing
bool Vtb_fpga::eventsPending() { return !vlSymsp->vlInst.TOP.__Vnontrivs.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_fpga::nextTimeSlot() { return vlSymsp->vlInst.TOP.__Vnontrivs.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_fpga::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void Vtb_fpga::final() {
    contextp()->executingFinal(true);
    evalFinal();
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_fpga::hierName() const { return vlSymsp->name(); }
const char* Vtb_fpga::modelName() const { return "Vtb_fpga"; }
unsigned Vtb_fpga::threads() const { return 1; }
void Vtb_fpga::prepareClone() const { contextp()->prepareClone(); }
void Vtb_fpga::atClone() const {
    contextp()->threadPoolpOnClone();
}
