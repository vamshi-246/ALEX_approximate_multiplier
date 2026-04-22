// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vapprox_multiplier_8x8__pch.h"

//============================================================
// Constructors

Vapprox_multiplier_8x8::Vapprox_multiplier_8x8(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vapprox_multiplier_8x8__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , valid_in{vlSymsp->TOP.valid_in}
    , A{vlSymsp->TOP.A}
    , B{vlSymsp->TOP.B}
    , valid_out{vlSymsp->TOP.valid_out}
    , P{vlSymsp->TOP.P}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vapprox_multiplier_8x8::Vapprox_multiplier_8x8(const char* _vcname__)
    : Vapprox_multiplier_8x8(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vapprox_multiplier_8x8::~Vapprox_multiplier_8x8() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vapprox_multiplier_8x8___024root___eval_debug_assertions(Vapprox_multiplier_8x8___024root* vlSelf);
#endif  // VL_DEBUG
void Vapprox_multiplier_8x8___024root___eval_static(Vapprox_multiplier_8x8___024root* vlSelf);
void Vapprox_multiplier_8x8___024root___eval_initial(Vapprox_multiplier_8x8___024root* vlSelf);
void Vapprox_multiplier_8x8___024root___eval_settle(Vapprox_multiplier_8x8___024root* vlSelf);
void Vapprox_multiplier_8x8___024root___eval(Vapprox_multiplier_8x8___024root* vlSelf);

void Vapprox_multiplier_8x8::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vapprox_multiplier_8x8::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vapprox_multiplier_8x8___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vapprox_multiplier_8x8___024root___eval_static(&(vlSymsp->TOP));
        Vapprox_multiplier_8x8___024root___eval_initial(&(vlSymsp->TOP));
        Vapprox_multiplier_8x8___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vapprox_multiplier_8x8___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vapprox_multiplier_8x8::eventsPending() { return false; }

uint64_t Vapprox_multiplier_8x8::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vapprox_multiplier_8x8::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vapprox_multiplier_8x8___024root___eval_final(Vapprox_multiplier_8x8___024root* vlSelf);

VL_ATTR_COLD void Vapprox_multiplier_8x8::final() {
    Vapprox_multiplier_8x8___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vapprox_multiplier_8x8::hierName() const { return vlSymsp->name(); }
const char* Vapprox_multiplier_8x8::modelName() const { return "Vapprox_multiplier_8x8"; }
unsigned Vapprox_multiplier_8x8::threads() const { return 1; }
void Vapprox_multiplier_8x8::prepareClone() const { contextp()->prepareClone(); }
void Vapprox_multiplier_8x8::atClone() const {
    contextp()->threadPoolpOnClone();
}
