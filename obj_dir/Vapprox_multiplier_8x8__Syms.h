// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VAPPROX_MULTIPLIER_8X8__SYMS_H_
#define VERILATED_VAPPROX_MULTIPLIER_8X8__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vapprox_multiplier_8x8.h"

// INCLUDE MODULE CLASSES
#include "Vapprox_multiplier_8x8___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vapprox_multiplier_8x8__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vapprox_multiplier_8x8* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vapprox_multiplier_8x8___024root TOP;

    // CONSTRUCTORS
    Vapprox_multiplier_8x8__Syms(VerilatedContext* contextp, const char* namep, Vapprox_multiplier_8x8* modelp);
    ~Vapprox_multiplier_8x8__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
