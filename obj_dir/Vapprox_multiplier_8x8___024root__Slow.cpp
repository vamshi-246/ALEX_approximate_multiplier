// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vapprox_multiplier_8x8.h for the primary calling header

#include "Vapprox_multiplier_8x8__pch.h"

void Vapprox_multiplier_8x8___024root___ctor_var_reset(Vapprox_multiplier_8x8___024root* vlSelf);

Vapprox_multiplier_8x8___024root::Vapprox_multiplier_8x8___024root(Vapprox_multiplier_8x8__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vapprox_multiplier_8x8___024root___ctor_var_reset(this);
}

void Vapprox_multiplier_8x8___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vapprox_multiplier_8x8___024root::~Vapprox_multiplier_8x8___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
