// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vapprox_multiplier_8x8.h for the primary calling header

#include "Vapprox_multiplier_8x8__pch.h"

void Vapprox_multiplier_8x8___024root___eval_triggers_vec__ico(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_triggers_vec__ico\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vapprox_multiplier_8x8___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vapprox_multiplier_8x8___024root___ico_sequent__TOP__0(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___ico_sequent__TOP__0\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.approx_multiplier_8x8__DOT__p_4_0 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 4U) 
                                                      & (IData)(vlSelfRef.B)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_3_1 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 3U) 
                                                      & ((IData)(vlSelfRef.B) 
                                                         >> 1U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_3_5 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 3U) 
                                                      & ((IData)(vlSelfRef.B) 
                                                         >> 5U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_2_6 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 2U) 
                                                      & ((IData)(vlSelfRef.B) 
                                                         >> 6U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_1_7 = (IData)(
                                                          (((IData)(vlSelfRef.A) 
                                                            >> 1U) 
                                                           & ((IData)(vlSelfRef.B) 
                                                              >> 7U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_5_4 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 5U) 
                                                      & ((IData)(vlSelfRef.B) 
                                                         >> 4U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_4_5 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 4U) 
                                                      & ((IData)(vlSelfRef.B) 
                                                         >> 5U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_3_6 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 3U) 
                                                      & ((IData)(vlSelfRef.B) 
                                                         >> 6U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_2_7 = (IData)(
                                                          (((IData)(vlSelfRef.A) 
                                                            >> 2U) 
                                                           & ((IData)(vlSelfRef.B) 
                                                              >> 7U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_7_4 = (IData)(
                                                          (((IData)(vlSelfRef.A) 
                                                            >> 7U) 
                                                           & ((IData)(vlSelfRef.B) 
                                                              >> 4U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_6_5 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 6U) 
                                                      & ((IData)(vlSelfRef.B) 
                                                         >> 5U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_5_6 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 5U) 
                                                      & ((IData)(vlSelfRef.B) 
                                                         >> 6U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_7_5 = (IData)(
                                                          (((IData)(vlSelfRef.A) 
                                                            >> 7U) 
                                                           & ((IData)(vlSelfRef.B) 
                                                              >> 5U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_6_6 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       & (IData)(vlSelfRef.B)) 
                                                      >> 6U));
    vlSelfRef.approx_multiplier_8x8__DOT__p_5_7 = (IData)(
                                                          (((IData)(vlSelfRef.A) 
                                                            >> 5U) 
                                                           & ((IData)(vlSelfRef.B) 
                                                              >> 7U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_7_6 = (IData)(
                                                          (((IData)(vlSelfRef.A) 
                                                            >> 7U) 
                                                           & ((IData)(vlSelfRef.B) 
                                                              >> 6U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_6_7 = (IData)(
                                                          (((IData)(vlSelfRef.A) 
                                                            >> 6U) 
                                                           & ((IData)(vlSelfRef.B) 
                                                              >> 7U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_5_5 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       & (IData)(vlSelfRef.B)) 
                                                      >> 5U));
    vlSelfRef.approx_multiplier_8x8__DOT__p_4_6 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 4U) 
                                                      & ((IData)(vlSelfRef.B) 
                                                         >> 6U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_7_3 = (IData)(
                                                          (((IData)(vlSelfRef.A) 
                                                            >> 7U) 
                                                           & ((IData)(vlSelfRef.B) 
                                                              >> 3U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_6_4 = (1U 
                                                   & (((IData)(vlSelfRef.A) 
                                                       >> 6U) 
                                                      & ((IData)(vlSelfRef.B) 
                                                         >> 4U)));
    vlSelfRef.approx_multiplier_8x8__DOT__EX_COMP_0__DOT____VdfgRegularize_he8a0cc24_0_0 
        = ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_3) 
           ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_4));
    vlSelfRef.approx_multiplier_8x8__DOT__EX_COMP_0__DOT__xor4 
        = ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__EX_COMP_0__DOT____VdfgRegularize_he8a0cc24_0_0) 
           ^ ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_5_5) 
              ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_4_6)));
}

void Vapprox_multiplier_8x8___024root___eval_ico(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_ico\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vapprox_multiplier_8x8___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vapprox_multiplier_8x8___024root___eval_phase__ico(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_phase__ico\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vapprox_multiplier_8x8___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vapprox_multiplier_8x8___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vapprox_multiplier_8x8___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vapprox_multiplier_8x8___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vapprox_multiplier_8x8___024root___eval_triggers_vec__act(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_triggers_vec__act\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

bool Vapprox_multiplier_8x8___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vapprox_multiplier_8x8___024root___nba_sequent__TOP__0(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___nba_sequent__TOP__0\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.valid_out = ((1U & (~ (IData)(vlSelfRef.rst))) 
                           && (IData)(vlSelfRef.approx_multiplier_8x8__DOT__valid_r2));
    if (vlSelfRef.rst) {
        vlSelfRef.P = 0U;
    } else {
        vlSelfRef.P = ((0xff80U & (IData)(vlSelfRef.P)) 
                       | (6U | (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_0_r2) 
                                 << 6U) | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_CAC_1_r2) 
                                           << 4U))));
        vlSelfRef.P = ((0xf87fU & (IData)(vlSelfRef.P)) 
                       | ((((2U & ((~ ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_6) 
                                       ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_3_r2))) 
                                   << 1U)) | (1U ^ 
                                              ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_3_r2) 
                                               ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_CAC_2_r2)))) 
                           << 9U) | (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_2_r2) 
                                      << 8U) | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_1_r2) 
                                                << 7U))));
        vlSelfRef.P = ((0x87ffU & (IData)(vlSelfRef.P)) 
                       | ((((((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_4_r2) 
                              ^ ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_9) 
                                 ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_3_r2))) 
                             << 3U) | (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_3_r2) 
                                        ^ ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_8) 
                                           ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_5_r2))) 
                                       << 2U)) | ((
                                                   ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_5_r2) 
                                                    ^ 
                                                    ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_7) 
                                                     ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_4_r2))) 
                                                   << 1U) 
                                                  | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_4_r2) 
                                                     ^ 
                                                     ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_MFA_3) 
                                                      ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_3_r2))))) 
                          << 0x0000000bU));
        vlSelfRef.P = ((0x7fffU & (IData)(vlSelfRef.P)) 
                       | (((((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_3_r2) 
                             & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_4_r2)) 
                            | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_9) 
                               & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_3_r2) 
                                  | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_4_r2)))) 
                           ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_4_r2)) 
                          << 0x0000000fU));
    }
    vlSelfRef.approx_multiplier_8x8__DOT__valid_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (IData)(vlSelfRef.approx_multiplier_8x8__DOT__valid_r1));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_2_r2 
        = (1U & (~ (IData)(vlSelfRef.rst)));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_3_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_2_r1) 
                                                 & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_2_r1)));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_3_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_2_r1) 
                                                 ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_2_r1)));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_4_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_2_r1) 
                                                 ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_7_r1)));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_4_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_2_r1) 
                                                 & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_7_r1)));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_0_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_0_5_r1) 
                                                 | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_1_4_r1)));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_1_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_1_5_r1) 
                                                 | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_2_4_r1)));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_3_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_ACMLC_2_r1) 
                                                 | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_0_r1)));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_3_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_3_7_r1) 
                                                  & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_EX_COMP_0_r1)) 
                                                 | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_1_r1) 
                                                    & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_3_7_r1) 
                                                       | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_EX_COMP_0_r1)))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_5_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_1_r1) 
                                                  & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_2_r1)) 
                                                 | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__cout_EX_COMP_0_r1) 
                                                    & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_1_r1) 
                                                       | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_2_r1)))));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_3_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_EX_COMP_0_r1) 
                                                 ^ 
                                                 ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_1_r1) 
                                                  ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_3_7_r1))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_4_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_4_7_r1) 
                                                  & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_1_r1)) 
                                                 | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_EX_COMP_0_r1) 
                                                    & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_4_7_r1) 
                                                       | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_1_r1)))));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_5_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_2_r1) 
                                                 ^ 
                                                 ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_1_r1) 
                                                  ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__cout_EX_COMP_0_r1))));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_4_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_1_r1) 
                                                 ^ 
                                                 ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_EX_COMP_0_r1) 
                                                  ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_4_7_r1))));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_CAC_1_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_0_r1) 
                                                  & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_2_2_r1) 
                                                     & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_0_4_r1) 
                                                        | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_1_3_r1)))) 
                                                 | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_0_4_r1) 
                                                    & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_1_3_r1))));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_CAC_2_r2 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_CAC_0_r1) 
                                                  & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_1_r1) 
                                                     & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_ACMLC_4_r1) 
                                                        | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_0_r1)))) 
                                                 | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_ACMLC_4_r1) 
                                                    & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_0_r1))));
    vlSelfRef.approx_multiplier_8x8__DOT__valid_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (IData)(vlSelfRef.valid_in));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_2_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_6) 
                                                 ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_7)));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_2_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_5) 
                                                  & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_6)) 
                                                 | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_5_7) 
                                                    & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_5) 
                                                       | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_6)))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_2_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_6) 
                                                 & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_7)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_7_7_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & (((IData)(vlSelfRef.A) 
                                                     & (IData)(vlSelfRef.B)) 
                                                    >> 7U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_0_5_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & ((IData)(vlSelfRef.A) 
                                                    & ((IData)(vlSelfRef.B) 
                                                       >> 5U))));
    vlSelfRef.approx_multiplier_8x8__DOT__p_1_4_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & (((IData)(vlSelfRef.A) 
                                                     >> 1U) 
                                                    & ((IData)(vlSelfRef.B) 
                                                       >> 4U))));
    vlSelfRef.approx_multiplier_8x8__DOT__p_1_5_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & (((IData)(vlSelfRef.A) 
                                                     >> 1U) 
                                                    & ((IData)(vlSelfRef.B) 
                                                       >> 5U))));
    vlSelfRef.approx_multiplier_8x8__DOT__p_2_4_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & (((IData)(vlSelfRef.A) 
                                                     >> 2U) 
                                                    & ((IData)(vlSelfRef.B) 
                                                       >> 4U))));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_0_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_3_5) 
                                                 ^ 
                                                 ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_1_7) 
                                                  ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_2_6))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_ACMLC_2_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & ((IData)(
                                                            ((0xa0U 
                                                              == 
                                                              (0xa0U 
                                                               & (IData)(vlSelfRef.A))) 
                                                             & (5U 
                                                                == 
                                                                (5U 
                                                                 & (IData)(vlSelfRef.B))))) 
                                                    | (((IData)(vlSelfRef.A) 
                                                        >> 6U) 
                                                       & ((IData)(vlSelfRef.B) 
                                                          >> 1U)))));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_EX_COMP_0_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & (~ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__EX_COMP_0__DOT__xor4))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_HA_1_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_3_6) 
                                                 & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_2_7)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_3_7_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (IData)(
                                                        (((IData)(vlSelfRef.A) 
                                                          >> 3U) 
                                                         & ((IData)(vlSelfRef.B) 
                                                            >> 7U))));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_2_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_5) 
                                                 ^ 
                                                 ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_5_7) 
                                                  ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_6))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_1_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_4) 
                                                  & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_5)) 
                                                 | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_5_6) 
                                                    & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_4) 
                                                       | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_5)))));
    vlSelfRef.approx_multiplier_8x8__DOT__cout_EX_COMP_0_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__EX_COMP_0__DOT____VdfgRegularize_he8a0cc24_0_0) 
                                                  & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_5_5)) 
                                                 | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_3) 
                                                    & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_4))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_EX_COMP_0_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__EX_COMP_0__DOT__xor4) 
                                                 | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_4_6)));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_1_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_4) 
                                                 ^ 
                                                 ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_5_6) 
                                                  ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_5))));
    vlSelfRef.approx_multiplier_8x8__DOT__p_4_7_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (IData)(
                                                        (((IData)(vlSelfRef.A) 
                                                          >> 4U) 
                                                         & ((IData)(vlSelfRef.B) 
                                                            >> 7U))));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_0_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_4_0) 
                                                 ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_3_1)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_2_2_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & (((IData)(vlSelfRef.A) 
                                                     & (IData)(vlSelfRef.B)) 
                                                    >> 2U)));
    vlSelfRef.approx_multiplier_8x8__DOT__p_0_4_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & ((IData)(vlSelfRef.A) 
                                                    & ((IData)(vlSelfRef.B) 
                                                       >> 4U))));
    vlSelfRef.approx_multiplier_8x8__DOT__p_1_3_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & (((IData)(vlSelfRef.A) 
                                                     >> 1U) 
                                                    & ((IData)(vlSelfRef.B) 
                                                       >> 3U))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_6 
        = (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_3_r2) 
            & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_CAC_2_r2)) 
           | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_3_r2) 
              | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_CAC_2_r2)));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_1_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_3_6) 
                                                 ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_2_7)));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_0_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_3_5) 
                                                  & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_2_6)) 
                                                 | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_1_7) 
                                                    & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_3_5) 
                                                       | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_2_6)))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_ACMLC_4_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && (1U 
                                                 & ((IData)(
                                                            ((0xa0U 
                                                              == 
                                                              (0xa0U 
                                                               & (IData)(vlSelfRef.A))) 
                                                             & (0x0aU 
                                                                == 
                                                                (0x0aU 
                                                                 & (IData)(vlSelfRef.B))))) 
                                                    | (((IData)(vlSelfRef.A) 
                                                        >> 6U) 
                                                       & ((IData)(vlSelfRef.B) 
                                                          >> 2U)))));
    vlSelfRef.approx_multiplier_8x8__DOT__sum_CAC_0_r1 
        = ((1U & (~ (IData)(vlSelfRef.rst))) && ((IData)(
                                                         (((0xc0U 
                                                            == 
                                                            (0xc0U 
                                                             & (IData)(vlSelfRef.A))) 
                                                           & (0x0cU 
                                                              == 
                                                              (0x0cU 
                                                               & (IData)(vlSelfRef.B)))) 
                                                          & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_5_4) 
                                                             | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_4_5)))) 
                                                 | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_5_4) 
                                                    & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_4_5))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_MFA_3 
        = ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_6) 
           | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_3_r2));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_7 
        = (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_3_r2) 
            & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_4_r2)) 
           | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_MFA_3) 
              & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_3_r2) 
                 | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_4_r2))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_8 
        = (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_4_r2) 
            & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_5_r2)) 
           | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_7) 
              & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_4_r2) 
                 | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_5_r2))));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_9 
        = (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_5_r2) 
            & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_3_r2)) 
           | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_8) 
              & ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_5_r2) 
                 | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_HA_3_r2))));
}

void Vapprox_multiplier_8x8___024root___eval_nba(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_nba\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vapprox_multiplier_8x8___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vapprox_multiplier_8x8___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vapprox_multiplier_8x8___024root___eval_phase__act(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_phase__act\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vapprox_multiplier_8x8___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vapprox_multiplier_8x8___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vapprox_multiplier_8x8___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vapprox_multiplier_8x8___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vapprox_multiplier_8x8___024root___eval_phase__nba(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_phase__nba\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vapprox_multiplier_8x8___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vapprox_multiplier_8x8___024root___eval_nba(vlSelf);
        Vapprox_multiplier_8x8___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vapprox_multiplier_8x8___024root___eval(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vapprox_multiplier_8x8___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("approx_multiplier_8x8.v", 2, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vapprox_multiplier_8x8___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vapprox_multiplier_8x8___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("approx_multiplier_8x8.v", 2, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vapprox_multiplier_8x8___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("approx_multiplier_8x8.v", 2, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vapprox_multiplier_8x8___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vapprox_multiplier_8x8___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vapprox_multiplier_8x8___024root___eval_debug_assertions(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_debug_assertions\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.valid_in & 0xfeU)))) {
        Verilated::overWidthError("valid_in");
    }
}
#endif  // VL_DEBUG
