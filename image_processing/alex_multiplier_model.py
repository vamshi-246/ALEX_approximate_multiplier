"""
Bit-accurate Python model of the ALEX 8x8 Approximate Multiplier.

This module translates the Verilog RTL (approx_multiplier_8x8.v and all sub-modules)
into pure-Python bitwise logic, producing cycle-accurate results matching hardware.

The multiplier takes two unsigned 8-bit operands and produces a 16-bit product.
Lower 4 bits P[3:0] are hardwired to 0b0110 (=6 decimal).
Columns 4-9 use approximate compressors (ACMLC, CAC, MACMLC).
Columns 10-14 use exact compressors.

Author: Auto-generated from Verilog RTL
"""

import numpy as np


# ─── Sub-module functions (matching Verilog gate-level) ───────────────────────

def exact_half_adder(x1: int, x2: int):
    """Returns (sum, carry)"""
    s = x1 ^ x2
    c = x1 & x2
    return s, c


def exact_full_adder(x1: int, x2: int, cin: int):
    """Returns (sum, carry)"""
    s = x1 ^ x2 ^ cin
    c = (x1 & x2) | (cin & (x1 | x2))
    return s, c


def exact_compressor(x1: int, x2: int, x3: int, x4: int, cin: int):
    """Returns (sum, carry, cout)"""
    xor4 = x1 ^ x2 ^ x3 ^ x4
    s = xor4 ^ cin
    carry = (xor4 & cin) | (x4 & (xor4 ^ 1))  # ~xor4 for single bit
    cout = ((x1 ^ x2) & x3) | (x1 & x2)
    return s, carry, cout


def acmlc_compressor(x1: int, x2: int, x3: int, x4: int):
    """ACMLC: Sum=1 always, Carry=(X1&X3)|X2. X4 is discarded."""
    s = 1  # hardwired VDD
    c = (x1 & x3) | x2
    return s, c


def cac_compressor(x1: int, x2: int, x3: int, x4: int):
    """CAC: Sum=((X1&X2)&(X3|X4))|(X3&X4), Carry=1 always."""
    s = ((x1 & x2) & (x3 | x4)) | (x3 & x4)
    c = 1  # hardwired VDD
    return s, c


def macmlc_compressor(x2: int, x3: int, x4: int):
    """MACMLC: Sum=1 always, Carry=X2|X3. X4 is discarded."""
    s = 1  # hardwired VDD
    c = x2 | x3
    return s, c


def mha_two_ones():
    """MHA: Both inputs are 1. Sum=0, Carry=1."""
    return 0, 1


def mfa_one_input_one(x2: int, cin: int):
    """MFA: X1=1 absorbed. Sum=XNOR(X2,Cin), Carry=X2|Cin."""
    s = (x2 ^ cin) ^ 1  # XNOR
    c = x2 | cin
    return s, c


# ─── Main multiplier (combinational, ignoring pipeline registers) ────────────

def alex_approx_multiply(a: int, b: int) -> int:
    """
    Compute the 16-bit approximate product of two unsigned 8-bit values.

    This is a bit-accurate translation of the 3-stage pipelined Verilog design.
    Pipeline registers are ignored since they don't affect the combinational result.

    Parameters
    ----------
    a : int  (0..255)
    b : int  (0..255)

    Returns
    -------
    int : 16-bit unsigned product (approximate)
    """
    a = int(a) & 0xFF
    b = int(b) & 0xFF

    # ── Partial product generation ──
    def pp(i, j):
        return ((a >> i) & 1) & ((b >> j) & 1)

    # ══════════════ STAGE 1 ══════════════

    # --- Approximate columns 4-9 ---

    # Col 4: HA_0
    sum_HA_0, carry_HA_0 = exact_half_adder(pp(4, 0), pp(3, 1))

    # Col 5: ACMLC_0
    _, carry_ACMLC_0 = acmlc_compressor(pp(5, 0), pp(4, 1), pp(3, 2), 0)

    # Col 6: ACMLC_1
    _, carry_ACMLC_1 = acmlc_compressor(pp(6, 0), pp(5, 1), pp(4, 2), 0)

    # Col 7: ACMLC_2
    _, carry_ACMLC_2 = acmlc_compressor(pp(7, 0), pp(6, 1), pp(5, 2), 0)

    # Col 7: ACMLC_3
    _, carry_ACMLC_3 = acmlc_compressor(pp(3, 4), pp(2, 5), pp(1, 6), 0)

    # Col 8: ACMLC_4
    _, carry_ACMLC_4 = acmlc_compressor(pp(7, 1), pp(6, 2), pp(5, 3), 0)

    # Col 8: FA_0
    sum_FA_0, carry_FA_0 = exact_full_adder(pp(3, 5), pp(2, 6), pp(1, 7))

    # Col 9: CAC_0
    sum_CAC_0, _ = cac_compressor(pp(7, 2), pp(6, 3), pp(5, 4), pp(4, 5))
    carry_CAC_0 = 1  # hardwired

    # Col 9: HA_1
    sum_HA_1, carry_HA_1 = exact_half_adder(pp(3, 6), pp(2, 7))

    # --- Exact columns 10-14 ---

    # Col 10: EX_COMP_0
    sum_EX_COMP_0, carry_EX_COMP_0, cout_EX_COMP_0 = exact_compressor(
        pp(7, 3), pp(6, 4), pp(5, 5), pp(4, 6), carry_CAC_0
    )

    # Col 11: FA_1
    sum_FA_1, carry_FA_1 = exact_full_adder(pp(7, 4), pp(6, 5), pp(5, 6))

    # Col 12: FA_2
    sum_FA_2, carry_FA_2 = exact_full_adder(pp(7, 5), pp(6, 6), pp(5, 7))

    # Col 13: HA_2
    sum_HA_2, carry_HA_2 = exact_half_adder(pp(7, 6), pp(6, 7))

    # p_7_7 passes through

    # ══════════════ STAGE 2 ══════════════
    # (operates on _r1 registered values, but combinationally identical)

    # Col 4: CAC_1
    sum_CAC_1, _ = cac_compressor(sum_HA_0, pp(2, 2), pp(1, 3), pp(0, 4))

    # Col 5: MACMLC_0 (carry_HA_0 discarded)
    _, carry_MACMLC_0 = macmlc_compressor(pp(1, 4), pp(0, 5), 0)

    # Col 6: MACMLC_1 (p[0][6] never generated)
    _, carry_MACMLC_1 = macmlc_compressor(pp(2, 4), pp(1, 5), 0)

    # Col 7: MACMLC_2 (carry_ACMLC_0 discarded, sum_ACMLC_3=1)
    _, carry_MACMLC_2 = macmlc_compressor(1, carry_ACMLC_1, 0)

    # Col 8: MACMLC_3 (carry_ACMLC_3 discarded)
    _, carry_MACMLC_3 = macmlc_compressor(sum_FA_0, carry_ACMLC_2, 0)

    # Col 9: CAC_2
    sum_CAC_2, _ = cac_compressor(sum_CAC_0, sum_HA_1, carry_ACMLC_4, carry_FA_0)

    # Col 10: FA_3
    sum_FA_3, carry_FA_3 = exact_full_adder(sum_EX_COMP_0, pp(3, 7), carry_HA_1)

    # Col 11: FA_4
    sum_FA_4, carry_FA_4 = exact_full_adder(sum_FA_1, pp(4, 7), carry_EX_COMP_0)

    # Col 12: FA_5
    sum_FA_5, carry_FA_5 = exact_full_adder(sum_FA_2, carry_FA_1, cout_EX_COMP_0)

    # Col 13: HA_3
    sum_HA_3, carry_HA_3 = exact_half_adder(sum_HA_2, carry_FA_2)

    # Col 14: HA_4
    sum_HA_4, carry_HA_4 = exact_half_adder(pp(7, 7), carry_HA_2)

    # ══════════════ STAGE 3 ══════════════

    # Constant carry chain
    carry_MHA_0 = 1
    carry_MFA_0 = 1
    carry_MFA_1 = 1
    carry_MFA_2 = 1

    # Col 4: P[4] = sum_CAC_1 (direct)
    p4 = sum_CAC_1

    # Col 5: MHA_0
    sum_MHA_0, _ = mha_two_ones()
    p5 = sum_MHA_0  # always 0

    # Col 6: MFA_0
    sum_MFA_0, _ = mfa_one_input_one(carry_MACMLC_0, carry_MHA_0)
    p6 = sum_MFA_0

    # Col 7: MFA_1
    sum_MFA_1, _ = mfa_one_input_one(carry_MACMLC_1, carry_MFA_0)
    p7 = sum_MFA_1

    # Col 8: MFA_2
    sum_MFA_2, _ = mfa_one_input_one(carry_MACMLC_2, carry_MFA_1)
    p8 = sum_MFA_2

    # Col 9: FA_6
    sum_FA_6, carry_FA_6 = exact_full_adder(sum_CAC_2, carry_MACMLC_3, carry_MFA_2)
    p9 = sum_FA_6

    # Col 10: MFA_3
    sum_MFA_3, carry_MFA_3 = mfa_one_input_one(sum_FA_3, carry_FA_6)
    p10 = sum_MFA_3

    # Col 11: FA_7
    sum_FA_7, carry_FA_7 = exact_full_adder(sum_FA_4, carry_FA_3, carry_MFA_3)
    p11 = sum_FA_7

    # Col 12: FA_8
    sum_FA_8, carry_FA_8 = exact_full_adder(sum_FA_5, carry_FA_4, carry_FA_7)
    p12 = sum_FA_8

    # Col 13: FA_9
    sum_FA_9, carry_FA_9 = exact_full_adder(sum_HA_3, carry_FA_5, carry_FA_8)
    p13 = sum_FA_9

    # Col 14: FA_10
    sum_FA_10, carry_FA_10 = exact_full_adder(sum_HA_4, carry_HA_3, carry_FA_9)
    p14 = sum_FA_10

    # Col 15
    p15 = carry_FA_10 ^ carry_HA_4

    # ── Assemble output ──
    # P[3:0] = 4'b0110 = 6
    product = (
        0b0110        |  # bits 3:0
        (p4  << 4)    |
        (p5  << 5)    |
        (p6  << 6)    |
        (p7  << 7)    |
        (p8  << 8)    |
        (p9  << 9)    |
        (p10 << 10)   |
        (p11 << 11)   |
        (p12 << 12)   |
        (p13 << 13)   |
        (p14 << 14)   |
        (p15 << 15)
    )

    return product & 0xFFFF


# ─── Build lookup table for vectorized operation ─────────────────────────────

def build_approx_lut() -> np.ndarray:
    """Build a 256x256 lookup table: lut[a][b] = alex_approx_multiply(a, b)."""
    lut = np.zeros((256, 256), dtype=np.uint16)
    for a in range(256):
        for b in range(256):
            lut[a, b] = alex_approx_multiply(a, b)
    return lut


def build_exact_lut() -> np.ndarray:
    """Build a 256x256 exact multiplication lookup table."""
    a_vals = np.arange(256, dtype=np.uint32)
    b_vals = np.arange(256, dtype=np.uint32)
    lut = np.outer(a_vals, b_vals).astype(np.uint16)
    return lut


# ─── Quick self-test ─────────────────────────────────────────────────────────

if __name__ == "__main__":
    print("Running ALEX multiplier model self-test...")

    # Test a few known values
    test_cases = [
        (0, 0), (1, 1), (2, 3), (15, 15), (127, 127), (255, 255),
        (100, 200), (50, 50), (200, 100), (128, 128),
    ]

    max_err = 0
    total_err = 0
    count = 0

    for a, b in test_cases:
        exact = a * b
        approx = alex_approx_multiply(a, b)
        err = abs(exact - approx)
        max_err = max(max_err, err)
        total_err += err
        count += 1
        print(f"  {a:3d} x {b:3d} = {exact:5d} (exact) vs {approx:5d} (approx)  err={err}")

    print(f"\n  Max error: {max_err}")
    print(f"  Mean error: {total_err / count:.1f}")

    # Exhaustive statistics
    print("\nRunning exhaustive 256x256 error analysis...")
    errors = []
    for a in range(256):
        for b in range(256):
            exact = a * b
            approx = alex_approx_multiply(a, b)
            errors.append(abs(exact - approx))

    errors = np.array(errors)
    print(f"  Total combinations: {len(errors)}")
    print(f"  Max absolute error: {errors.max()}")
    print(f"  Mean absolute error: {errors.mean():.2f}")
    print(f"  Std of error: {errors.std():.2f}")
    print(f"  Exact matches: {np.sum(errors == 0)} ({100*np.sum(errors==0)/len(errors):.1f}%)")
    print(f"  Mean relative error: {np.mean(errors[errors > 0] / np.array([a*b for a in range(256) for b in range(256)])[errors > 0]) * 100:.3f}%")
    print("\nModel self-test complete.")
