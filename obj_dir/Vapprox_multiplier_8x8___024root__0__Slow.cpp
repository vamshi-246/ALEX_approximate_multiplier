// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vapprox_multiplier_8x8.h for the primary calling header

#include "Vapprox_multiplier_8x8__pch.h"

VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___eval_static(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_static\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___eval_initial(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_initial\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___eval_final(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_final\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vapprox_multiplier_8x8___024root___eval_phase__stl(Vapprox_multiplier_8x8___024root* vlSelf);

VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___eval_settle(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_settle\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vapprox_multiplier_8x8___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("approx_multiplier_8x8.v", 2, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vapprox_multiplier_8x8___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___eval_triggers_vec__stl(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_triggers_vec__stl\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vapprox_multiplier_8x8___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vapprox_multiplier_8x8___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vapprox_multiplier_8x8___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___stl_sequent__TOP__0(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___stl_sequent__TOP__0\n"); );
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
    vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_6 
        = (((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_3_r2) 
            & (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_CAC_2_r2)) 
           | ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_MACMLC_3_r2) 
              | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_CAC_2_r2)));
    vlSelfRef.approx_multiplier_8x8__DOT__EX_COMP_0__DOT____VdfgRegularize_he8a0cc24_0_0 
        = ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_7_3) 
           ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_6_4));
    vlSelfRef.approx_multiplier_8x8__DOT__carry_MFA_3 
        = ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__carry_FA_6) 
           | (IData)(vlSelfRef.approx_multiplier_8x8__DOT__sum_FA_3_r2));
    vlSelfRef.approx_multiplier_8x8__DOT__EX_COMP_0__DOT__xor4 
        = ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__EX_COMP_0__DOT____VdfgRegularize_he8a0cc24_0_0) 
           ^ ((IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_5_5) 
              ^ (IData)(vlSelfRef.approx_multiplier_8x8__DOT__p_4_6)));
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

VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___eval_stl(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_stl\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vapprox_multiplier_8x8___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vapprox_multiplier_8x8___024root___eval_phase__stl(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___eval_phase__stl\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vapprox_multiplier_8x8___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vapprox_multiplier_8x8___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vapprox_multiplier_8x8___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vapprox_multiplier_8x8___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vapprox_multiplier_8x8___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vapprox_multiplier_8x8___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vapprox_multiplier_8x8___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vapprox_multiplier_8x8___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vapprox_multiplier_8x8___024root___ctor_var_reset(Vapprox_multiplier_8x8___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vapprox_multiplier_8x8___024root___ctor_var_reset\n"); );
    Vapprox_multiplier_8x8__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->valid_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16540271516330450727ull);
    vlSelf->A = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3969090544990846983ull);
    vlSelf->B = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 149303876845869574ull);
    vlSelf->P = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 8235454673289795724ull);
    vlSelf->valid_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8744939437868816662ull);
    vlSelf->approx_multiplier_8x8__DOT__p_4_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2258446591076006722ull);
    vlSelf->approx_multiplier_8x8__DOT__p_3_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11293953187080687754ull);
    vlSelf->approx_multiplier_8x8__DOT__p_3_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18342978245617977573ull);
    vlSelf->approx_multiplier_8x8__DOT__p_2_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2070324357385912634ull);
    vlSelf->approx_multiplier_8x8__DOT__p_1_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4182832877734685192ull);
    vlSelf->approx_multiplier_8x8__DOT__p_5_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10988041080512280866ull);
    vlSelf->approx_multiplier_8x8__DOT__p_4_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16647375810647940912ull);
    vlSelf->approx_multiplier_8x8__DOT__p_3_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3696435499806528231ull);
    vlSelf->approx_multiplier_8x8__DOT__p_2_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 975493900900672188ull);
    vlSelf->approx_multiplier_8x8__DOT__p_7_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9840310966595334857ull);
    vlSelf->approx_multiplier_8x8__DOT__p_6_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1746122387998745857ull);
    vlSelf->approx_multiplier_8x8__DOT__p_5_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9762171483912034961ull);
    vlSelf->approx_multiplier_8x8__DOT__p_4_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15273515734262711550ull);
    vlSelf->approx_multiplier_8x8__DOT__p_7_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7288667288680613752ull);
    vlSelf->approx_multiplier_8x8__DOT__p_6_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11719635203322973075ull);
    vlSelf->approx_multiplier_8x8__DOT__p_5_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11897456692666087593ull);
    vlSelf->approx_multiplier_8x8__DOT__p_7_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2970446849672394508ull);
    vlSelf->approx_multiplier_8x8__DOT__p_6_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15307870176170468030ull);
    vlSelf->approx_multiplier_8x8__DOT__p_5_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6538592789389267912ull);
    vlSelf->approx_multiplier_8x8__DOT__p_7_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15014726328682012644ull);
    vlSelf->approx_multiplier_8x8__DOT__p_6_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7498845496332487886ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_HA_0_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6811932808767915164ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_ACMLC_2_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14432381085936258565ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_ACMLC_4_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7675391436585939073ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_FA_0_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2185296525220163363ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_FA_0_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3148308861014808420ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_CAC_0_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12826230873506098553ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_HA_1_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7942990140403502750ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_HA_1_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11875500777218900635ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_EX_COMP_0_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 536684729530032757ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_EX_COMP_0_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16603843736850025334ull);
    vlSelf->approx_multiplier_8x8__DOT__cout_EX_COMP_0_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17252011354780081567ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_FA_1_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10383783196219560549ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_FA_1_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12812879976609136368ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_FA_2_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3742864590170788933ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_FA_2_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17067879503541826448ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_HA_2_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13300780901188746235ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_HA_2_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8440007507358548660ull);
    vlSelf->approx_multiplier_8x8__DOT__p_2_2_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6175543443227133378ull);
    vlSelf->approx_multiplier_8x8__DOT__p_1_3_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16538413101527204636ull);
    vlSelf->approx_multiplier_8x8__DOT__p_0_4_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 792255192204264619ull);
    vlSelf->approx_multiplier_8x8__DOT__p_1_4_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15906483052954472095ull);
    vlSelf->approx_multiplier_8x8__DOT__p_0_5_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11399358488507968364ull);
    vlSelf->approx_multiplier_8x8__DOT__p_2_4_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1151627396996964393ull);
    vlSelf->approx_multiplier_8x8__DOT__p_1_5_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14757995210768666482ull);
    vlSelf->approx_multiplier_8x8__DOT__p_3_7_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11233610922910933942ull);
    vlSelf->approx_multiplier_8x8__DOT__p_4_7_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9014996869494937163ull);
    vlSelf->approx_multiplier_8x8__DOT__p_7_7_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9020940763480625426ull);
    vlSelf->approx_multiplier_8x8__DOT__valid_r1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12255984201523925331ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_CAC_1_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3650117438183247415ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_MACMLC_0_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7491794034623895746ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_MACMLC_1_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4905734480404144227ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_MACMLC_2_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4034950232078110355ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_MACMLC_3_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3964288318004240514ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_CAC_2_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16665133350502238594ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_FA_3_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5121047167463730205ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_FA_3_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4941675870807588456ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_FA_4_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10105023477658486048ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_FA_4_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16581758963453453871ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_FA_5_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1132510410857094587ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_FA_5_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4794935501880286073ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_HA_3_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 785844726593226260ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_HA_3_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9561813742426880366ull);
    vlSelf->approx_multiplier_8x8__DOT__sum_HA_4_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9709934569566507799ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_HA_4_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12554812695613470384ull);
    vlSelf->approx_multiplier_8x8__DOT__valid_r2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 705983350936912869ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_FA_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3076681412964745241ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_MFA_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13540654655219693630ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_FA_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 358339893765971881ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_FA_8 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2619868148089215610ull);
    vlSelf->approx_multiplier_8x8__DOT__carry_FA_9 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15991139040654717956ull);
    vlSelf->approx_multiplier_8x8__DOT__EX_COMP_0__DOT__xor4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14281116618994802271ull);
    vlSelf->approx_multiplier_8x8__DOT__EX_COMP_0__DOT____VdfgRegularize_he8a0cc24_0_0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
