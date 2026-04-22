// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vapprox_multiplier_8x8.h for the primary calling header

#ifndef VERILATED_VAPPROX_MULTIPLIER_8X8___024ROOT_H_
#define VERILATED_VAPPROX_MULTIPLIER_8X8___024ROOT_H_  // guard

#include "verilated.h"


class Vapprox_multiplier_8x8__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vapprox_multiplier_8x8___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst,0,0);
        VL_IN8(valid_in,0,0);
        VL_IN8(A,7,0);
        VL_IN8(B,7,0);
        VL_OUT8(valid_out,0,0);
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_4_0;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_3_1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_3_5;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_2_6;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_1_7;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_5_4;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_4_5;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_3_6;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_2_7;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_7_3;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_6_4;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_5_5;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_4_6;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_7_4;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_6_5;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_5_6;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_7_5;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_6_6;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_5_7;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_7_6;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_6_7;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_HA_0_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_ACMLC_2_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_ACMLC_4_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_FA_0_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_FA_0_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_CAC_0_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_HA_1_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_HA_1_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_EX_COMP_0_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_EX_COMP_0_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__cout_EX_COMP_0_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_FA_1_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_FA_1_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_FA_2_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_FA_2_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_HA_2_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_HA_2_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_2_2_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_1_3_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_0_4_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_1_4_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_0_5_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_2_4_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_1_5_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_3_7_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_4_7_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__p_7_7_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__valid_r1;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_CAC_1_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_MACMLC_0_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_MACMLC_1_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_MACMLC_2_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_MACMLC_3_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_CAC_2_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_FA_3_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_FA_3_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_FA_4_r2;
    };
    struct {
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_FA_4_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_FA_5_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_FA_5_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_HA_3_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_HA_3_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__sum_HA_4_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_HA_4_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__valid_r2;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_FA_6;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_MFA_3;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_FA_7;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_FA_8;
        CData/*0:0*/ approx_multiplier_8x8__DOT__carry_FA_9;
        CData/*0:0*/ approx_multiplier_8x8__DOT__EX_COMP_0__DOT__xor4;
        CData/*0:0*/ approx_multiplier_8x8__DOT__EX_COMP_0__DOT____VdfgRegularize_he8a0cc24_0_0;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __VicoPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        VL_OUT16(P,15,0);
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };

    // INTERNAL VARIABLES
    Vapprox_multiplier_8x8__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vapprox_multiplier_8x8___024root(Vapprox_multiplier_8x8__Syms* symsp, const char* namep);
    ~Vapprox_multiplier_8x8___024root();
    VL_UNCOPYABLE(Vapprox_multiplier_8x8___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
