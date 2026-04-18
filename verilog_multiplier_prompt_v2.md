# Verilog Implementation Prompt — Energy-Efficient Approximate 8×8 Multiplier
## Based on: Sadeghi et al., "Energy Efficient Compact Approximate Multiplier for Error-Resilient Applications", IEEE TCSII 2024

---

## SECTION 0 — READ THIS FIRST

This prompt is complete and self-contained. Every signal name, Boolean equation, port connection, pipeline register, and output assignment is specified exactly. You must implement **exactly** what is written here — do not reinterpret, simplify, merge, or reorder anything unless the prompt explicitly permits it. Where the prompt says a carry is always 1'b1, wire it as a constant. Where a signal is described as floating, declare it as a named wire with a comment and do not connect it to any logic input.

**The design implements an 8×8 unsigned approximate pipelined multiplier** producing a 16-bit result, using the ACMLC-based compressor and CAC architecture from the paper. The pipeline has 3 stages separated by 2 sets of pipeline registers, giving a latency of 3 clock cycles and a throughput of 1 result per cycle.

---

## SECTION 1 — TOP-LEVEL INTERFACE

```verilog
module approx_multiplier_8x8 (
    input  wire        clk,
    input  wire        rst,       // synchronous, active-high
    input  wire        valid_in,
    input  wire [7:0]  A,
    input  wire [7:0]  B,
    output reg  [15:0] P,
    output reg         valid_out
);
```

**Output bit assignment:**

| Bits    | Region              | Source                          |
|---------|---------------------|---------------------------------|
| P[3:0]  | Constant Truncated  | Hardwired 4'b0110 (LSB to MSB: 0,1,1,0) |
| P[4]    | Approximate         | sum_CAC_1 (Stage 2, direct)     |
| P[5]    | Approximate         | 1'b0 (MHA result, always 0)     |
| P[6]    | Approximate         | sum_MFA_0 (Stage 3)             |
| P[7]    | Approximate         | sum_MFA_1 (Stage 3)             |
| P[8]    | Approximate         | sum_MFA_2 (Stage 3)             |
| P[9]    | Approximate         | sum_FA_6  (Stage 3)             |
| P[10]   | Exact               | sum_MFA_3 (Stage 3)             |
| P[11]   | Exact               | sum_FA_7  (Stage 3)             |
| P[12]   | Exact               | sum_FA_8  (Stage 3)             |
| P[13]   | Exact               | sum_FA_9  (Stage 3)             |
| P[14]   | Exact               | sum_FA_10 (Stage 3)             |
| P[15]   | Exact (overflow)    | carry_FA_10 (Stage 3)           |

---

## SECTION 2 — PARTIAL PRODUCT NOTATION AND GENERATION RULES

`p[i][j]` denotes the partial product `A[i] & B[j]` where `i` is the index into operand A and `j` is the index into operand B (both 0-indexed from LSB). The column position of `p[i][j]` in the output is `i + j`.

**Naming convention in Verilog:** `wire p_I_J = A[I] & B[J];`
Example: `wire p_7_3 = A[7] & B[3];`

### 2.1 — Partial Products That Must NEVER Be Generated

The following AND gates must not appear anywhere in your code. Any port that would have received them receives `1'b0` or is handled as described per cell.

| Signal   | Column | Reason                                  |
|----------|--------|-----------------------------------------|
| p[0][0]–p[3][x], p[x][0]–p[x][3] where i+j < 4 | 0–3 | Entire columns 0–3 truncated; replaced by constant 4'b0110 |
| p[2][3]  | 5      | Discarded X4 input of ACMLC_0           |
| p[3][3]  | 6      | Discarded X4 input of ACMLC_1           |
| p[4][3]  | 7      | Discarded X4 input of ACMLC_2           |
| p[0][7]  | 7      | Discarded X4 input of ACMLC_3           |
| p[4][4]  | 8      | Discarded X4 input of ACMLC_4           |
| p[0][6]  | 6      | Discarded X4 input of MACMLC_1 (Stage 2)|

Total AND gates eliminated: 10 (truncation) + 6 (approximation discards) = **16 eliminated**, 48 generated.

### 2.2 — Complete Table of All Partial Products to Generate

Generate exactly these, and no others:

```
// Column 4
wire p_4_0 = A[4] & B[0];
wire p_3_1 = A[3] & B[1];

// Column 5
wire p_5_0 = A[5] & B[0];
wire p_4_1 = A[4] & B[1];
wire p_3_2 = A[3] & B[2];

// Column 6
wire p_6_0 = A[6] & B[0];
wire p_5_1 = A[5] & B[1];
wire p_4_2 = A[4] & B[2];

// Column 7
wire p_7_0 = A[7] & B[0];
wire p_6_1 = A[6] & B[1];
wire p_5_2 = A[5] & B[2];
wire p_3_4 = A[3] & B[4];
wire p_2_5 = A[2] & B[5];
wire p_1_6 = A[1] & B[6];

// Column 8
wire p_7_1 = A[7] & B[1];
wire p_6_2 = A[6] & B[2];
wire p_5_3 = A[5] & B[3];
wire p_3_5 = A[3] & B[5];
wire p_2_6 = A[2] & B[6];
wire p_1_7 = A[1] & B[7];

// Column 9
wire p_7_2 = A[7] & B[2];
wire p_6_3 = A[6] & B[3];
wire p_5_4 = A[5] & B[4];
wire p_4_5 = A[4] & B[5];
wire p_3_6 = A[3] & B[6];
wire p_2_7 = A[2] & B[7];

// Column 10 (Exact component starts)
wire p_7_3 = A[7] & B[3];
wire p_6_4 = A[6] & B[4];
wire p_5_5 = A[5] & B[5];
wire p_4_6 = A[4] & B[6];

// Column 11
wire p_7_4 = A[7] & B[4];
wire p_6_5 = A[6] & B[5];
wire p_5_6 = A[5] & B[6];

// Column 12
wire p_7_5 = A[7] & B[5];
wire p_6_6 = A[6] & B[6];
wire p_5_7 = A[5] & B[7];

// Column 13
wire p_7_6 = A[7] & B[6];
wire p_6_7 = A[6] & B[7];

// Column 14
wire p_7_7 = A[7] & B[7];

// For Stage 2 only — intermediate column sums
wire p_2_2 = A[2] & B[2];   // Stage 2 col 4, CAC_1 input
wire p_1_3 = A[1] & B[3];   // Stage 2 col 4, CAC_1 input
wire p_0_4 = A[0] & B[4];   // Stage 2 col 4, CAC_1 input
wire p_1_4 = A[1] & B[4];   // Stage 2 col 5, MACMLC_0 input
wire p_0_5 = A[0] & B[5];   // Stage 2 col 5, MACMLC_0 input
wire p_2_4 = A[2] & B[4];   // Stage 2 col 6, MACMLC_1 input
wire p_1_5 = A[1] & B[5];   // Stage 2 col 6, MACMLC_1 input
wire p_3_7 = A[3] & B[7];   // Stage 2 col 10, FA_3 input
wire p_4_7 = A[4] & B[7];   // Stage 2 col 11, FA_4 input
```

---

## SECTION 3 — SUB-MODULE SPECIFICATIONS

Implement each sub-module in its own file. Use `\`default_nettype none` at the top of every file. All equations are given in Verilog-ready form. Do not alter them.

---

### MODULE 1: `cac_compressor.v`
**Compensator Approximate Compressor (CAC) — 14 transistors**

```verilog
`default_nettype none
module cac_compressor (
    input  wire X1, X2, X3, X4,
    output wire Sum,
    output wire Carry
);
    assign Sum   = ((X1 & X2) & (X3 | X4)) | (X3 & X4);
    assign Carry = 1'b1;  // Always VDD — hardwired, not computed
endmodule
```

*Carry is always logic 1 by design. This is not a simplification — it is the defined behavior of the CAC architecture. Every instantiation of this module produces Carry = VDD.*

---

### MODULE 2: `acmlc_compressor.v`
**Approximate Condition-based Majority Logic Compressor (ACMLC) — 8 transistors**

```verilog
`default_nettype none
module acmlc_compressor (
    input  wire X1, X2, X3,
    input  wire X4,          // Declared but architecturally discarded — do not use in logic
    output wire Sum,
    output wire Carry
);
    // X4 is intentionally unused — discarded per ACMLC architecture (eliminates one AND gate)
    wire unused_X4;
    assign unused_X4 = X4;   // Prevents unconnected port warning; synthesis will optimize away

    assign Sum   = 1'b1;            // Always VDD — hardwired, not computed
    assign Carry = (X1 & X3) | X2;
endmodule
```

*Sum is always logic 1 by design. X4 is received only to satisfy the 4-input compressor interface but is never consumed in any logic expression.*

---

### MODULE 3: `macmlc_compressor.v`
**Modified ACMLC — X1 is architecturally always 1, absorbed into equations**

This module is used in Stage 2. Because all ACMLC Sum outputs are always 1'b1, Stage 2 uses them as fixed-1 inputs to compressors. Substituting X1=1 into the ACMLC equations eliminates one AND gate. The result is this module: X4 is still discarded.

```verilog
`default_nettype none
module macmlc_compressor (
    input  wire X2, X3,
    input  wire X4,          // Declared but architecturally discarded — do not use in logic
    output wire Sum,
    output wire Carry
);
    // X1 = 1'b1 is absorbed: original ACMLC Carry = (X1&X3)|X2 becomes X3|X2
    // X4 is intentionally unused — discarded per MACMLC architecture
    wire unused_X4;
    assign unused_X4 = X4;

    assign Sum   = 1'b1;       // Always VDD — inherited from ACMLC
    assign Carry = X2 | X3;   // Simplified from (1&X3)|X2 = X3|X2
endmodule
```

---

### MODULE 4: `exact_compressor.v`
**Exact 4:2 Compressor with Cin**

This module is instantiated exactly ONCE in the entire design (as EX_COMP_0 in Stage 1, column 10). It has three distinct outputs: Sum, Carry, and Cout. **All three are used downstream.**

```verilog
`default_nettype none
module exact_compressor (
    input  wire X1, X2, X3, X4,
    input  wire Cin,
    output wire Sum,
    output wire Carry,
    output wire Cout
);
    wire xor4;
    assign xor4  = X1 ^ X2 ^ X3 ^ X4;
    assign Sum   = xor4 ^ Cin;
    assign Carry = (xor4 & Cin) | (X4 & ~xor4);
    assign Cout  = ((X1 ^ X2) & X3) | (X1 & X2);
    // Note: Cout = majority(X1, X2, X3) — proven by Boolean simplification of
    // ((X1^X2)&X3) | (X1 & ~(X1^X2)) = ((X1^X2)&X3) | (X1&X2)
endmodule
```

**CRITICAL NAMING:** In this design, `Carry` is the internal carry (goes to the same column's next stage), `Cout` is the cascade carry (goes to column 11 in Stage 2). These are **different signals**. Never confuse them.

| Output | Used by              |
|--------|----------------------|
| Sum    | FA_3 (Stage 2, col 10) as X1 |
| Carry  | FA_4 (Stage 2, col 11) as Cin |
| Cout   | FA_5 (Stage 2, col 12) as Cin |

---

### MODULE 5: `exact_full_adder.v`

```verilog
`default_nettype none
module exact_full_adder (
    input  wire X1, X2, Cin,
    output wire Sum,
    output wire Carry
);
    assign Sum   = X1 ^ X2 ^ Cin;
    assign Carry = (X1 & X2) | (Cin & (X1 | X2));
endmodule
```

---

### MODULE 6: `exact_half_adder.v`

```verilog
`default_nettype none
module exact_half_adder (
    input  wire X1, X2,
    output wire Sum,
    output wire Carry
);
    assign Sum   = X1 ^ X2;
    assign Carry = X1 & X2;
endmodule
```

---

### MODULE 7: `mha_two_ones.v`
**Modified Half Adder — both inputs are architecturally 1**

This module is instantiated once in Stage 3, column 5. Since both inputs are always logic 1 (1+1=10 in binary), the sum is always 0 and carry is always 1. There are no input ports.

```verilog
`default_nettype none
module mha_two_ones (
    output wire Sum,
    output wire Carry
);
    assign Sum   = 1'b0;  // 1 + 1 = 10 in binary; sum bit = 0
    assign Carry = 1'b1;  // carry out = 1
endmodule
```

---

### MODULE 8: `mfa_one_input_one.v`
**Modified Full Adder — X1 is architecturally always 1, absorbed into equations**

Substituting X1=1 into the standard full adder:
- Sum  = 1 XOR X2 XOR Cin = ~(X2 XOR Cin) = X2 XNOR Cin
- Carry = (1 & X2) | (Cin & (1 | X2)) = X2 | Cin

```verilog
`default_nettype none
module mfa_one_input_one (
    input  wire X2, Cin,
    output wire Sum,
    output wire Carry
);
    assign Sum   = ~(X2 ^ Cin);   // X2 XNOR Cin
    assign Carry = X2 | Cin;
endmodule
```

---

## SECTION 4 — STAGE 1 LOGIC (COMBINATIONAL)

Stage 1 is purely combinational, operating directly on the partial product wires. All outputs are latched into Pipeline Register 1 at the end.

### Stage 1 — Approximate Component (Columns 4–9)

---

**Column 4 — HA_0** (`exact_half_adder`)
```
X1 = p_4_0
X2 = p_3_1
→ sum_HA_0, carry_HA_0
```

---

**Column 5 — ACMLC_0** (`acmlc_compressor`)
```
X1 = p_5_0
X2 = p_4_1
X3 = p_3_2
X4 = 1'b0    ← p[2][3] was never generated; tie to 0 for the discarded port
→ sum_ACMLC_0 = 1'b1 (constant by definition — do NOT pipeline this)
→ carry_ACMLC_0
```

---

**Column 6 — ACMLC_1** (`acmlc_compressor`)
```
X1 = p_6_0
X2 = p_5_1
X3 = p_4_2
X4 = 1'b0    ← p[3][3] was never generated
→ sum_ACMLC_1 = 1'b1 (constant — do NOT pipeline)
→ carry_ACMLC_1
```

---

**Column 7 — ACMLC_2 and ACMLC_3** (two `acmlc_compressor` instances)
```
ACMLC_2:
  X1 = p_7_0,  X2 = p_6_1,  X3 = p_5_2,  X4 = 1'b0 (p[4][3] never generated)
  → sum_ACMLC_2 = 1'b1 (constant — do NOT pipeline)
  → carry_ACMLC_2

ACMLC_3:
  X1 = p_3_4,  X2 = p_2_5,  X3 = p_1_6,  X4 = 1'b0 (p[0][7] never generated)
  → sum_ACMLC_3 = 1'b1 (constant — do NOT pipeline)
  → carry_ACMLC_3
```

---

**Column 8 — ACMLC_4 and FA_0**
```
ACMLC_4: (acmlc_compressor)
  X1 = p_7_1,  X2 = p_6_2,  X3 = p_5_3,  X4 = 1'b0 (p[4][4] never generated)
  → sum_ACMLC_4 = 1'b1 (constant — do NOT pipeline)
  → carry_ACMLC_4

FA_0: (exact_full_adder)
  X1  = p_3_5
  X2  = p_2_6
  Cin = p_1_7   ← p[1][7] acts as carry-in per architecture
  → sum_FA_0, carry_FA_0
```

---

**Column 9 — CAC_0 and HA_1**
```
CAC_0: (cac_compressor)
  X1 = p_7_2,  X2 = p_6_3,  X3 = p_5_4,  X4 = p_4_5
  → sum_CAC_0
  → carry_CAC_0 = 1'b1  ← ALWAYS 1 by CAC definition. Wire this constant directly.
    Use: wire carry_CAC_0 = 1'b1;
    This constant feeds EX_COMP_0's Cin port — it must be wired, not registered.

HA_1: (exact_half_adder)
  X1 = p_3_6,  X2 = p_2_7
  → sum_HA_1, carry_HA_1
```

---

### Stage 1 — Exact Component (Columns 10–14)

---

**Column 10 — EX_COMP_0** (`exact_compressor`)

```
X1  = p_7_3
X2  = p_6_4
X3  = p_5_5
X4  = p_4_6
Cin = carry_CAC_0 = 1'b1   ← hardwired constant from CAC_0

→ sum_EX_COMP_0       (used by Stage 2 FA_3 as X1)
→ carry_EX_COMP_0     (used by Stage 2 FA_4 as Cin)
→ cout_EX_COMP_0      (used by Stage 2 FA_5 as Cin)
```
**ALL THREE outputs are used. Carry and Cout are different signals — do not mix them up.**

---

**Column 11 — FA_1** (`exact_full_adder`)
```
X1  = p_7_4
X2  = p_6_5
Cin = p_5_6
→ sum_FA_1, carry_FA_1
```

---

**Column 12 — FA_2** (`exact_full_adder`)
```
X1  = p_7_5
X2  = p_6_6
Cin = p_5_7
→ sum_FA_2, carry_FA_2
```

---

**Column 13 — HA_2** (`exact_half_adder`)
```
X1 = p_7_6,  X2 = p_6_7
→ sum_HA_2, carry_HA_2
```

---

**Column 14 — No logic in Stage 1**
```
p_7_7 passes directly to Stage 2 pipeline register.
```

---

## SECTION 5 — PIPELINE REGISTER 1 (Stage 1 → Stage 2)

**Important rules before listing signals:**

1. **Do NOT register `sum_ACMLC_X` signals.** They are architecturally always 1'b1. Stage 2 MACMLC modules have X1=1 absorbed into their equations — they do not consume these signals at all.
2. **Do NOT register `carry_CAC_0`.** It is `wire carry_CAC_0 = 1'b1;` and connects directly to EX_COMP_0's Cin within Stage 1. It does not cross into Stage 2.
3. Register every signal that is produced in Stage 1 and consumed in Stage 2. Suffix all registered signals with `_r1`.
4. Also register partial products that were generated combinationally from A/B but are consumed in Stage 2 (because A and B are first-stage inputs only — they are not held across stages).
5. All registers: positive-edge clocked, synchronous reset to 1'b0.

**Signals to register in Pipeline Register 1:**

```verilog
always @(posedge clk) begin
    if (rst) begin
        // Stage 1 Approximate outputs
        sum_HA_0_r1          <= 1'b0;
        carry_HA_0_r1        <= 1'b0;
        carry_ACMLC_0_r1     <= 1'b0;
        carry_ACMLC_1_r1     <= 1'b0;
        carry_ACMLC_2_r1     <= 1'b0;
        carry_ACMLC_3_r1     <= 1'b0;
        carry_ACMLC_4_r1     <= 1'b0;
        sum_FA_0_r1          <= 1'b0;
        carry_FA_0_r1        <= 1'b0;
        sum_CAC_0_r1         <= 1'b0;
        // carry_CAC_0 is 1'b1 constant — NOT registered
        sum_HA_1_r1          <= 1'b0;
        carry_HA_1_r1        <= 1'b0;
        // Stage 1 Exact outputs
        sum_EX_COMP_0_r1     <= 1'b0;
        carry_EX_COMP_0_r1   <= 1'b0;
        cout_EX_COMP_0_r1    <= 1'b0;
        sum_FA_1_r1          <= 1'b0;
        carry_FA_1_r1        <= 1'b0;
        sum_FA_2_r1          <= 1'b0;
        carry_FA_2_r1        <= 1'b0;
        sum_HA_2_r1          <= 1'b0;
        carry_HA_2_r1        <= 1'b0;
        // Partial products needed by Stage 2
        p_2_2_r1             <= 1'b0;
        p_1_3_r1             <= 1'b0;
        p_0_4_r1             <= 1'b0;
        p_1_4_r1             <= 1'b0;
        p_0_5_r1             <= 1'b0;
        p_2_4_r1             <= 1'b0;
        p_1_5_r1             <= 1'b0;
        p_3_7_r1             <= 1'b0;
        p_4_7_r1             <= 1'b0;
        p_7_7_r1             <= 1'b0;
        // Valid
        valid_r1             <= 1'b0;
    end else begin
        sum_HA_0_r1          <= sum_HA_0;
        carry_HA_0_r1        <= carry_HA_0;
        carry_ACMLC_0_r1     <= carry_ACMLC_0;
        carry_ACMLC_1_r1     <= carry_ACMLC_1;
        carry_ACMLC_2_r1     <= carry_ACMLC_2;
        carry_ACMLC_3_r1     <= carry_ACMLC_3;
        carry_ACMLC_4_r1     <= carry_ACMLC_4;
        sum_FA_0_r1          <= sum_FA_0;
        carry_FA_0_r1        <= carry_FA_0;
        sum_CAC_0_r1         <= sum_CAC_0;
        sum_HA_1_r1          <= sum_HA_1;
        carry_HA_1_r1        <= carry_HA_1;
        sum_EX_COMP_0_r1     <= sum_EX_COMP_0;
        carry_EX_COMP_0_r1   <= carry_EX_COMP_0;
        cout_EX_COMP_0_r1    <= cout_EX_COMP_0;
        sum_FA_1_r1          <= sum_FA_1;
        carry_FA_1_r1        <= carry_FA_1;
        sum_FA_2_r1          <= sum_FA_2;
        carry_FA_2_r1        <= carry_FA_2;
        sum_HA_2_r1          <= sum_HA_2;
        carry_HA_2_r1        <= carry_HA_2;
        p_2_2_r1             <= p_2_2;
        p_1_3_r1             <= p_1_3;
        p_0_4_r1             <= p_0_4;
        p_1_4_r1             <= p_1_4;
        p_0_5_r1             <= p_0_5;
        p_2_4_r1             <= p_2_4;
        p_1_5_r1             <= p_1_5;
        p_3_7_r1             <= p_3_7;
        p_4_7_r1             <= p_4_7;
        p_7_7_r1             <= p_7_7;
        valid_r1             <= valid_in;
    end
end
```

---

## SECTION 6 — STAGE 2 LOGIC (COMBINATIONAL, operates on _r1 signals)

### Stage 2 — Approximate Component (Columns 4–9)

---

**Column 4 — CAC_1** (`cac_compressor`)
```
X1 = sum_HA_0_r1
X2 = p_2_2_r1
X3 = p_1_3_r1
X4 = p_0_4_r1
→ sum_CAC_1   ← this becomes P[4] directly in Stage 3 (res_4 = sum_CAC_1_r2)
→ carry_CAC_1 = 1'b1 (constant by CAC definition)
```

---

**Column 5 — MACMLC_0** (`macmlc_compressor`)

The sum output of ACMLC_0 from Stage 1 is always 1'b1. Stage 2 uses this as the fixed-X1=1 input of MACMLC. The X4 input to MACMLC_0 would be `carry_HA_0_r1` — but since MACMLC discards X4, this signal is floating. Handle it as shown.

```
X2 = p_1_4_r1
X3 = p_0_5_r1
X4 = carry_HA_0_r1   ← DISCARDED. Declare below and tie module port to 1'b0.
     wire unused_carry_HA_0_in_col5 = carry_HA_0_r1; // intentionally not consumed in logic

→ sum_MACMLC_0 = 1'b1 (constant — do NOT pipeline)
→ carry_MACMLC_0 = p_1_4_r1 | p_0_5_r1
```

---

**Column 6 — MACMLC_1** (`macmlc_compressor`)

X4 would be p[0][6], which was never generated.

```
X2 = p_2_4_r1
X3 = p_1_5_r1
X4 = 1'b0   ← p[0][6] was never generated; tie discarded port to 0

→ sum_MACMLC_1 = 1'b1 (constant — do NOT pipeline)
→ carry_MACMLC_1 = p_2_4_r1 | p_1_5_r1
```

---

**Column 7 — MACMLC_2** (`macmlc_compressor`)

The X1 input (discarded in MACMLC) would be sum_ACMLC_2 = 1'b1 — already absorbed.
The X4 input would be carry_ACMLC_0_r1 — discarded by MACMLC architecture.

```
X2 = sum_ACMLC_3_r1   ← Note: sum_ACMLC_3 = 1'b1 always; but it IS registered and used here
                         as a real signal because MACMLC does use X2 in its carry equation.
                         carry_MACMLC_2 = X2 | X3 = sum_ACMLC_3_r1 | carry_ACMLC_1_r1
                         Since sum_ACMLC_3_r1 = 1'b1 always, carry_MACMLC_2 = 1'b1 always.
                         Implement it through the module anyway; synthesis will constant-fold.
X3 = carry_ACMLC_1_r1
X4 = carry_ACMLC_0_r1  ← DISCARDED. Declare:
     wire unused_carry_ACMLC_0_col7 = carry_ACMLC_0_r1; // intentionally not consumed in logic

→ sum_MACMLC_2 = 1'b1 — FLOATING OUTPUT. This is not connected to anything.
     Declare: wire unused_sum_MACMLC_2; // floating per architecture
→ carry_MACMLC_2 = sum_ACMLC_3_r1 | carry_ACMLC_1_r1
     Note: Since sum_ACMLC_3_r1 = 1'b1, carry_MACMLC_2 = 1'b1 always.
     Still implement through module for structural correctness.
```

---

**Column 8 — MACMLC_3** (`macmlc_compressor`)

```
X2 = sum_FA_0_r1
X3 = carry_ACMLC_2_r1
X4 = carry_ACMLC_3_r1  ← DISCARDED. Declare:
     wire unused_carry_ACMLC_3_col8 = carry_ACMLC_3_r1; // intentionally not consumed in logic

→ sum_MACMLC_3 = 1'b1 — FLOATING OUTPUT. Not connected to anything.
     Declare: wire unused_sum_MACMLC_3; // floating per architecture
→ carry_MACMLC_3 = sum_FA_0_r1 | carry_ACMLC_2_r1
```

---

**Column 9 — CAC_2** (`cac_compressor`)
```
X1 = sum_CAC_0_r1
X2 = sum_HA_1_r1
X3 = carry_ACMLC_4_r1
X4 = carry_FA_0_r1

→ sum_CAC_2
→ carry_CAC_2 = 1'b1 (constant by CAC definition — wire as constant, do NOT pipeline)
```

---

### Stage 2 — Exact Component (Columns 10–14)

---

**Column 10 — FA_3** (`exact_full_adder`)
```
X1  = sum_EX_COMP_0_r1
X2  = p_3_7_r1
Cin = carry_HA_1_r1
→ sum_FA_3, carry_FA_3
```

---

**Column 11 — FA_4** (`exact_full_adder`)
```
X1  = sum_FA_1_r1
X2  = p_4_7_r1
Cin = carry_EX_COMP_0_r1   ← This is the CARRY output of exact_compressor, NOT Cout
→ sum_FA_4, carry_FA_4
```

---

**Column 12 — FA_5** (`exact_full_adder`)
```
X1  = sum_FA_2_r1
X2  = carry_FA_1_r1
Cin = cout_EX_COMP_0_r1    ← This is the COUT (cascade) output of exact_compressor, NOT Carry
→ sum_FA_5, carry_FA_5
```

---

**Column 13 — HA_3** (`exact_half_adder`)
```
X1 = sum_HA_2_r1
X2 = carry_FA_2_r1
→ sum_HA_3, carry_HA_3
```

---

**Column 14 — HA_4** (`exact_half_adder`)
```
X1 = p_7_7_r1
X2 = carry_HA_2_r1
→ sum_HA_4, carry_HA_4
```

---

## SECTION 7 — PIPELINE REGISTER 2 (Stage 2 → Stage 3)

**Important rules:**
1. Do NOT register `carry_CAC_1`, `carry_CAC_2`, `carry_MACMLC_2`, `carry_MACMLC_3` as separate signals — they are either 1'b1 constants or can be wired directly. However, if you choose to use them through modules, their outputs may be registered for timing closure.
2. Do NOT register floating signals (`sum_MACMLC_2`, `sum_MACMLC_3`) — they are architecturally disconnected.
3. Register all Stage 2 outputs that are consumed by Stage 3. Suffix with `_r2`.

```verilog
always @(posedge clk) begin
    if (rst) begin
        sum_CAC_1_r2        <= 1'b0;
        carry_MACMLC_0_r2   <= 1'b0;
        carry_MACMLC_1_r2   <= 1'b0;
        carry_MACMLC_2_r2   <= 1'b0;   // = 1'b1 always, but register for timing
        carry_MACMLC_3_r2   <= 1'b0;
        sum_CAC_2_r2        <= 1'b0;
        // carry_CAC_2 = 1'b1 constant — wire directly, do NOT register
        sum_FA_3_r2         <= 1'b0;
        carry_FA_3_r2       <= 1'b0;
        sum_FA_4_r2         <= 1'b0;
        carry_FA_4_r2       <= 1'b0;
        sum_FA_5_r2         <= 1'b0;
        carry_FA_5_r2       <= 1'b0;
        sum_HA_3_r2         <= 1'b0;
        carry_HA_3_r2       <= 1'b0;
        sum_HA_4_r2         <= 1'b0;
        carry_HA_4_r2       <= 1'b0;
        valid_r2            <= 1'b0;
    end else begin
        sum_CAC_1_r2        <= sum_CAC_1;
        carry_MACMLC_0_r2   <= carry_MACMLC_0;
        carry_MACMLC_1_r2   <= carry_MACMLC_1;
        carry_MACMLC_2_r2   <= carry_MACMLC_2;
        carry_MACMLC_3_r2   <= carry_MACMLC_3;
        sum_CAC_2_r2        <= sum_CAC_2;
        sum_FA_3_r2         <= sum_FA_3;
        carry_FA_3_r2       <= carry_FA_3;
        sum_FA_4_r2         <= sum_FA_4;
        carry_FA_4_r2       <= carry_FA_4;
        sum_FA_5_r2         <= sum_FA_5;
        carry_FA_5_r2       <= carry_FA_5;
        sum_HA_3_r2         <= sum_HA_3;
        carry_HA_3_r2       <= carry_HA_3;
        sum_HA_4_r2         <= sum_HA_4;
        carry_HA_4_r2       <= carry_HA_4;
        valid_r2            <= valid_r1;
    end
end
```

---

## SECTION 8 — STAGE 3 LOGIC AND CONSTANT PROPAGATION ANALYSIS

Before specifying Stage 3, the following constant carry chain analysis must be understood and explicitly implemented. These are NOT approximations — they follow deterministically from the sub-module equations.

### Stage 3 Constant Carry Chain

```
carry_MHA_0  = 1'b1                    ← from mha_two_ones module definition
carry_MFA_0  = carry_MACMLC_0_r2 | carry_MHA_0
             = carry_MACMLC_0_r2 | 1'b1
             = 1'b1                    ← constant
carry_MFA_1  = carry_MACMLC_1_r2 | carry_MFA_0
             = carry_MACMLC_1_r2 | 1'b1
             = 1'b1                    ← constant
carry_MFA_2  = carry_MACMLC_2_r2 | carry_MFA_1
             = carry_MACMLC_2_r2 | 1'b1
             = 1'b1                    ← constant
carry_CAC_2  = 1'b1                    ← from cac_compressor definition (already in Stage 2)
```

**Implementation requirement:** Declare these as:
```verilog
wire carry_MHA_0 = 1'b1;
wire carry_MFA_0 = 1'b1;
wire carry_MFA_1 = 1'b1;
wire carry_MFA_2 = 1'b1;
wire carry_CAC_2 = 1'b1;   // already established in Stage 2, but used again in Stage 3 col 10
```

These constants then simplify several MFA operations as noted below. You must still instantiate the modules — but be aware of what the outputs will evaluate to.

---

### Stage 3 — Approximate Component (Columns 4–9)

---

**Column 4 — Direct result**
```
res_4 = sum_CAC_1_r2
→ P[4] = sum_CAC_1_r2
No logic cell. Direct wire assignment.
```

---

**Column 5 — MHA_0** (`mha_two_ones`)
```
No inputs. This cell encodes the fact that sum_MACMLC_0 = 1'b1 (from Stage 2)
and carry_CAC_1 = 1'b1 (from Stage 2 CAC_1). Two 1's entering this bit position.
→ Sum  = 1'b0 → P[5] = 1'b0
→ Carry = carry_MHA_0 = 1'b1
```

---

**Column 6 — MFA_0** (`mfa_one_input_one`)

X1=1 absorbed. X2 and Cin are:
```
X2  = carry_MACMLC_0_r2
Cin = carry_MHA_0 = 1'b1

Sum   = ~(carry_MACMLC_0_r2 ^ 1'b1) = carry_MACMLC_0_r2   (XNOR with 1 = identity)
Carry = carry_MACMLC_0_r2 | 1'b1 = 1'b1 = carry_MFA_0

→ sum_MFA_0 = carry_MACMLC_0_r2
→ P[6] = sum_MFA_0
```

---

**Column 7 — MFA_1** (`mfa_one_input_one`)
```
X2  = carry_MACMLC_1_r2
Cin = carry_MFA_0 = 1'b1

Sum   = ~(carry_MACMLC_1_r2 ^ 1'b1) = carry_MACMLC_1_r2
Carry = carry_MACMLC_1_r2 | 1'b1 = 1'b1 = carry_MFA_1

→ sum_MFA_1 = carry_MACMLC_1_r2
→ P[7] = sum_MFA_1
```

---

**Column 8 — MFA_2** (`mfa_one_input_one`)
```
X2  = carry_MACMLC_2_r2
Cin = carry_MFA_1 = 1'b1

Sum   = ~(carry_MACMLC_2_r2 ^ 1'b1) = carry_MACMLC_2_r2
Carry = carry_MACMLC_2_r2 | 1'b1 = 1'b1 = carry_MFA_2

→ sum_MFA_2 = carry_MACMLC_2_r2
→ P[8] = sum_MFA_2
```

---

**Column 9 — FA_6** (`exact_full_adder`)

Cin = carry_MFA_2 = 1'b1 (constant proven above).
With Cin=1: Sum = X1 ^ X2 ^ 1 = ~(X1 ^ X2); Carry = X1|X2

```
X1  = sum_CAC_2_r2
X2  = carry_MACMLC_3_r2
Cin = carry_MFA_2 = 1'b1

sum_FA_6   = ~(sum_CAC_2_r2 ^ carry_MACMLC_3_r2)
carry_FA_6 = sum_CAC_2_r2 | carry_MACMLC_3_r2

→ P[9] = sum_FA_6
```

---

### Stage 3 — Exact Component (Columns 10–14)

---

**Column 10 — MFA_3** (`mfa_one_input_one`)

**This is the corrected version.** After the confirmed X1/X2 swap:
- X1 (fixed=1, absorbed) = carry_CAC_2 = 1'b1
- X2 = sum_FA_3_r2
- Cin = carry_FA_6

```
X2  = sum_FA_3_r2
Cin = carry_FA_6

sum_MFA_3   = ~(sum_FA_3_r2 ^ carry_FA_6)   (i.e., sum_FA_3_r2 XNOR carry_FA_6)
carry_MFA_3 = sum_FA_3_r2 | carry_FA_6

→ P[10] = sum_MFA_3
```

**P[10] is NOT sum_FA_3_r2 directly. It is the output of MFA_3.**

---

**Column 11 — FA_7** (`exact_full_adder`)
```
X1  = sum_FA_4_r2
X2  = carry_FA_3_r2
Cin = carry_MFA_3

→ sum_FA_7, carry_FA_7
→ P[11] = sum_FA_7
```

---

**Column 12 — FA_8** (`exact_full_adder`)
```
X1  = sum_FA_5_r2
X2  = carry_FA_4_r2
Cin = carry_FA_7

→ sum_FA_8, carry_FA_8
→ P[12] = sum_FA_8
```

---

**Column 13 — FA_9** (`exact_full_adder`)
```
X1  = sum_HA_3_r2
X2  = carry_FA_5_r2
Cin = carry_FA_8

→ sum_FA_9, carry_FA_9
→ P[13] = sum_FA_9
```

---

**Column 14 — FA_10** (`exact_full_adder`)
```
X1  = sum_HA_4_r2
X2  = carry_HA_3_r2
Cin = carry_FA_9

→ sum_FA_10  → P[14] = sum_FA_10
→ carry_FA_10 → P[15] = carry_FA_10  (16th bit: overflow from column 14)
```

---

## SECTION 9 — OUTPUT REGISTER AND FINAL ASSEMBLY

```verilog
always @(posedge clk) begin
    if (rst) begin
        P         <= 16'b0;
        valid_out <= 1'b0;
    end else begin
        P[3:0]  <= 4'b0110;          // Constant truncated: LSB=0, then 1,1,0
        P[4]    <= sum_CAC_1_r2;     // Stage 3 col 4: direct
        P[5]    <= 1'b0;             // Stage 3 col 5: MHA sum always 0
        P[6]    <= sum_MFA_0;        // Stage 3 col 6
        P[7]    <= sum_MFA_1;        // Stage 3 col 7
        P[8]    <= sum_MFA_2;        // Stage 3 col 8
        P[9]    <= sum_FA_6;         // Stage 3 col 9
        P[10]   <= sum_MFA_3;        // Stage 3 col 10 — OUTPUT OF MFA_3, not sum_FA_3_r2
        P[11]   <= sum_FA_7;         // Stage 3 col 11
        P[12]   <= sum_FA_8;         // Stage 3 col 12
        P[13]   <= sum_FA_9;         // Stage 3 col 13
        P[14]   <= sum_FA_10;        // Stage 3 col 14
        P[15]   <= carry_FA_10;      // Overflow carry from col 14
        valid_out <= valid_r2;
    end
end
```

---

## SECTION 10 — PIPELINE VALID AND FSM CONTROL

### Valid Signal Propagation

```verilog
// Pipeline valid through registers
always @(posedge clk) begin
    if (rst) valid_r1 <= 1'b0;
    else     valid_r1 <= valid_in;
end

always @(posedge clk) begin
    if (rst) valid_r2 <= 1'b0;
    else     valid_r2 <= valid_r1;
end
// valid_out registered in Section 9 output register
```

**Latency = 3 clock cycles.** The result at P[15:0] corresponds to the inputs A, B presented 3 cycles earlier. Throughput = 1 result per cycle (fully pipelined).

### FSM Consideration

For this design, a simple 3-stage shift-register valid chain is sufficient — no explicit FSM is required because:
- The pipeline has no stall conditions (purely combinational stages, no memory access, no variable-latency operations)
- There is no backpressure mechanism

However, if this module is integrated into a system requiring flow control, a handshake FSM (ready/valid protocol) should be wrapped around this module externally. The internal pipeline should remain free-running.

If an FSM is required by the integrating system, implement a 3-state FSM:
- **IDLE**: Output valid_out=0, wait for valid_in.
- **RUNNING**: Pipeline is filling. Assert internal pipeline enables.
- **OUTPUTTING**: valid_out asserted when result is available.

For standalone operation as described, the valid shift-register approach is both correct and sufficient.

---

## SECTION 11 — TESTBENCH SPECIFICATION

File: `tb_approx_multiplier_8x8.v`

```verilog
`timescale 1ns/1ps
`default_nettype none
module tb_approx_multiplier_8x8;
    // ... (implement per spec below)
endmodule
```

### 11.1 — Required Test Cases

**Directed corner cases (check these explicitly):**

| A   | B   | Exact Product | Notes                     |
|-----|-----|---------------|---------------------------|
| 0   | 0   | 0             | All-zero input             |
| 255 | 255 | 65025         | All-ones input             |
| 1   | 1   | 1             | Minimum nonzero            |
| 128 | 128 | 16384         | MSB-only inputs            |
| 255 | 0   | 0             | One zero operand           |
| 0   | 255 | 0             | Other zero operand         |
| 128 | 1   | 128           | Powers of 2                |
| 170 | 85  | 14450         | Alternating bit patterns   |
| 15  | 15  | 225           | Lower nibble only          |
| 240 | 240 | 57600         | Upper nibble only          |

**For directed cases:** Display `EXACT_MATCH` if `P == exact_product`, otherwise display `APPROX_DIFF: delta = %0d` and check that `|P - exact_product| <= 256` (the error budget from truncating 4 LSBs and approximating with ACMLC/CAC). A result outside ±256 is a **FAIL**.

### 11.2 — Random Stimulus (1000 cases)

Generate 1000 random 8-bit input pairs using `$random`. For each:
1. Compute `exact = A_tb * B_tb` as a 16-bit reference (using the `*` operator in the testbench only).
2. Compute the expected error budget: the truncation of the 4 LSBs alone contributes up to 15×255 ≈ 3825 to the error. However, for this architecture the maximum absolute error has been empirically bounded. Use a tolerance of **±4096** (2^12) for random cases to account for all approximate sources.
3. Check: `|DUT_P - exact| <= 4096`. Fail if exceeded.
4. For all cases: check that `P[3:0] == 4'b0110` always. This is a hard check — any deviation is an immediate **FAIL**.

### 11.3 — Pipeline Sequencing Test

1. Apply 5 back-to-back valid inputs without gaps.
2. Verify that `valid_out` goes high exactly on the 4th clock edge after the first `valid_in` (i.e., 3 cycle latency).
3. Verify that `valid_out` remains high for all 5 subsequent cycles (one per pipelined result).
4. Verify output P changes each cycle, corresponding to different input pairs.

### 11.4 — Reset Test

1. Apply `rst=1` for 3 cycles while providing valid inputs. Verify P=0 and valid_out=0 during reset.
2. Deassert rst. Verify normal operation resumes.

### 11.5 — Timing and Infrastructure

```verilog
parameter CLK_PERIOD = 10; // 10 ns = 100 MHz
initial clk = 0;
always #(CLK_PERIOD/2) clk = ~clk;

initial begin
    $dumpfile("tb_approx_multiplier_8x8.vcd");
    $dumpvars(0, tb_approx_multiplier_8x8);
end
```

### 11.6 — Reporting

At the end of all tests:
```
$display("===== TESTBENCH SUMMARY =====");
$display("Directed:  PASS=%0d  FAIL=%0d", dir_pass, dir_fail);
$display("Random:    PASS=%0d  FAIL=%0d", rnd_pass, rnd_fail);
$display("Pipeline:  %s", pipe_ok ? "PASS" : "FAIL");
$display("P[3:0] hardwire: %s", hw_ok ? "PASS" : "FAIL");
$display("==============================");
```

---

## SECTION 12 — CODE QUALITY AND SYNTHESIS REQUIREMENTS

### File Structure (10 files, no exceptions)

| File | Module | Description |
|------|--------|-------------|
| `approx_multiplier_8x8.v` | `approx_multiplier_8x8` | Top-level pipelined design |
| `cac_compressor.v` | `cac_compressor` | CAC 14T approximate compressor |
| `acmlc_compressor.v` | `acmlc_compressor` | ACMLC 8T approximate compressor |
| `macmlc_compressor.v` | `macmlc_compressor` | Modified ACMLC (X1=1 absorbed) |
| `exact_compressor.v` | `exact_compressor` | Exact 4:2 compressor with Cin |
| `exact_full_adder.v` | `exact_full_adder` | Exact FA |
| `exact_half_adder.v` | `exact_half_adder` | Exact HA |
| `mha_two_ones.v` | `mha_two_ones` | Modified HA, both inputs=1 |
| `mfa_one_input_one.v` | `mfa_one_input_one` | Modified FA, X1=1 absorbed |
| `tb_approx_multiplier_8x8.v` | `tb_approx_multiplier_8x8` | Self-checking testbench |

### Mandatory Rules (violations are defects)

1. `` `default_nettype none `` at the top of **every** `.v` file.
2. No `*` (multiply) operator in any synthesizable file. Testbench only.
3. No `#delay` in synthesizable files.
4. No `initial` blocks in synthesizable files.
5. All module instantiations use **named port connections** (`.portname(signal)` style). No positional connections.
6. Every floating/discarded signal must be declared as a named `wire` with a comment: `// intentionally unused — [architectural reason]`.
7. No undeclared signals. `\`default_nettype none` enforces this.
8. No inferred latches. Combinational `always` blocks must use sensitivity list `(*)` and cover all branches with an `else` clause or default assignments.
9. No `1'bz` (high-impedance) in synthesizable code. Discarded ports receive `1'b0`.
10. Every module instantiation must have a comment above it in the format:
    ```verilog
    // Stage X | Column Y | CellType_N: input1=sigA, input2=sigB → output1, output2
    ```
11. No behavioral `always @(*)` blocks for sequential logic — only `always @(posedge clk)`.
12. The exact_compressor's Sum, Carry, and Cout outputs must have **distinct names** at every point they are used. Never alias Carry to Cout or vice versa.

---

## SECTION 13 — COMPLETE SIGNAL CROSS-REFERENCE

This table is the authoritative reference. Every signal produced in one stage must appear as a consumer in the correct downstream stage. Use this to verify your implementation before submission.

| Signal | Produced In | Consumed In | Notes |
|--------|------------|-------------|-------|
| sum_HA_0 | Stage 1 col 4 | Stage 2 col 4 (as X1 of CAC_1) via _r1 | |
| carry_HA_0 | Stage 1 col 4 | Stage 2 col 5 (discarded X4 of MACMLC_0) via _r1 | Floating in Stage 2 |
| carry_ACMLC_0 | Stage 1 col 5 | Stage 2 col 7 (discarded X4 of MACMLC_2) via _r1 | Floating in Stage 2 |
| carry_ACMLC_1 | Stage 1 col 6 | Stage 2 col 7 (X3 of MACMLC_2) via _r1 | |
| carry_ACMLC_2 | Stage 1 col 7 | Stage 2 col 8 (X3 of MACMLC_3) via _r1 | |
| carry_ACMLC_3 | Stage 1 col 7 | Stage 2 col 8 (discarded X4 of MACMLC_3) via _r1 | Floating |
| carry_ACMLC_4 | Stage 1 col 8 | Stage 2 col 9 (X3 of CAC_2) via _r1 | |
| sum_FA_0 | Stage 1 col 8 | Stage 2 col 8 (X2 of MACMLC_3) via _r1 | |
| carry_FA_0 | Stage 1 col 8 | Stage 2 col 9 (X4 of CAC_2) via _r1 | |
| sum_CAC_0 | Stage 1 col 9 | Stage 2 col 9 (X1 of CAC_2) via _r1 | |
| carry_CAC_0 | Stage 1 col 9 | Stage 1 col 10 (Cin of EX_COMP_0) | Wire=1'b1, NOT registered |
| sum_HA_1 | Stage 1 col 9 | Stage 2 col 9 (X2 of CAC_2) via _r1 | |
| carry_HA_1 | Stage 1 col 9 | Stage 2 col 10 (Cin of FA_3) via _r1 | |
| sum_EX_COMP_0 | Stage 1 col 10 | Stage 2 col 10 (X1 of FA_3) via _r1 | |
| carry_EX_COMP_0 | Stage 1 col 10 | Stage 2 col 11 (Cin of FA_4) via _r1 | NOT Cout |
| cout_EX_COMP_0 | Stage 1 col 10 | Stage 2 col 12 (Cin of FA_5) via _r1 | NOT Carry |
| sum_FA_1 | Stage 1 col 11 | Stage 2 col 11 (X1 of FA_4) via _r1 | |
| carry_FA_1 | Stage 1 col 11 | Stage 2 col 12 (X2 of FA_5) via _r1 | |
| sum_FA_2 | Stage 1 col 12 | Stage 2 col 12 (X1 of FA_5) via _r1 | |
| carry_FA_2 | Stage 1 col 12 | Stage 2 col 13 (X2 of HA_3) via _r1 | |
| sum_HA_2 | Stage 1 col 13 | Stage 2 col 13 (X1 of HA_3) via _r1 | |
| carry_HA_2 | Stage 1 col 13 | Stage 2 col 14 (X2 of HA_4) via _r1 | |
| sum_CAC_1 | Stage 2 col 4 | Stage 3 col 4 (direct P[4]) via _r2 | |
| carry_MACMLC_0 | Stage 2 col 5 | Stage 3 col 6 (X2 of MFA_0) via _r2 | |
| carry_MACMLC_1 | Stage 2 col 6 | Stage 3 col 7 (X2 of MFA_1) via _r2 | |
| carry_MACMLC_2 | Stage 2 col 7 | Stage 3 col 8 (X2 of MFA_2) via _r2 | =1'b1 always |
| carry_MACMLC_3 | Stage 2 col 8 | Stage 3 col 9 (X2 of FA_6) via _r2 | |
| sum_CAC_2 | Stage 2 col 9 | Stage 3 col 9 (X1 of FA_6) via _r2 | |
| sum_FA_3 | Stage 2 col 10 | Stage 3 col 10 (X2 of MFA_3) via _r2 | |
| carry_FA_3 | Stage 2 col 10 | Stage 3 col 11 (X2 of FA_7) via _r2 | |
| sum_FA_4 | Stage 2 col 11 | Stage 3 col 11 (X1 of FA_7) via _r2 | |
| carry_FA_4 | Stage 2 col 11 | Stage 3 col 12 (X2 of FA_8) via _r2 | |
| sum_FA_5 | Stage 2 col 12 | Stage 3 col 12 (X1 of FA_8) via _r2 | |
| carry_FA_5 | Stage 2 col 12 | Stage 3 col 13 (X2 of FA_9) via _r2 | |
| sum_HA_3 | Stage 2 col 13 | Stage 3 col 13 (X1 of FA_9) via _r2 | |
| carry_HA_3 | Stage 2 col 13 | Stage 3 col 14 (X2 of FA_10) via _r2 | |
| sum_HA_4 | Stage 2 col 14 | Stage 3 col 14 (X1 of FA_10) via _r2 | |
| carry_HA_4 | Stage 2 col 14 | Unused — HA_4 carry not used in Stage 3 | Declare as named unused wire |

**Note on carry_HA_4:** The carry output of HA_4 in Stage 2 is not consumed anywhere in Stage 3. This is architecturally correct — column 15 does not exist in a 16-bit result from 8×8. Declare `wire unused_carry_HA_4 = carry_HA_4; // column 15 overflow, architecturally not used`.

---

## SECTION 14 — FINAL VERIFICATION CHECKLIST

Before submitting any code, verify every item:

**Sub-modules:**
- [ ] `cac_compressor`: `Carry = 1'b1` is a constant wire, not logic
- [ ] `acmlc_compressor`: `Sum = 1'b1` is a constant wire; X4 declared but never in any expression
- [ ] `macmlc_compressor`: `Carry = X2 | X3` (NOT X1|X3); X1=1 absorbed; X4 discarded
- [ ] `exact_compressor`: Has THREE outputs (Sum, Carry, Cout); all three are distinct and used
- [ ] `exact_compressor`: `Cout = ((X1^X2)&X3) | (X1&X2)` (majority of X1,X2,X3)
- [ ] `mha_two_ones`: No input ports; Sum=1'b0, Carry=1'b1
- [ ] `mfa_one_input_one`: Sum = ~(X2^Cin); Carry = X2|Cin

**Partial products:**
- [ ] p[2][3], p[3][3], p[4][3], p[0][7], p[4][4], p[0][6] are never generated (no AND gate)
- [ ] All 48 partial products from Section 2.2 are present
- [ ] carry_CAC_0 is declared as `wire carry_CAC_0 = 1'b1;` (not as module output registered)

**Pipeline registers:**
- [ ] sum_ACMLC_0/1/2/3/4 are NOT in Pipeline Register 1 (they are 1'b1 constants, not piped)
- [ ] sum_MACMLC_2 and sum_MACMLC_3 are NOT in Pipeline Register 2 (floating, not piped)
- [ ] carry_HA_4 from Stage 2 is declared as unused wire, not an error

**Stage 3:**
- [ ] carry_MHA_0, carry_MFA_0, carry_MFA_1, carry_MFA_2 are all wired as `1'b1`
- [ ] MFA_3 takes `X2 = sum_FA_3_r2`, `Cin = carry_FA_6` → outputs `sum_MFA_3`, `carry_MFA_3`
- [ ] P[10] = `sum_MFA_3` (NOT `sum_FA_3_r2` — this is a critical distinction)
- [ ] FA_6 Cin = 1'b1; therefore sum_FA_6 = ~(sum_CAC_2_r2 ^ carry_MACMLC_3_r2)

**Output assembly:**
- [ ] P[3:0] = 4'b0110 (NOT 4'b0110 reversed — LSB=P[0]=0, P[1]=1, P[2]=1, P[3]=0)
- [ ] P[5] = 1'b0 (hardwired; MHA output)
- [ ] P[10] = sum_MFA_3 (confirmed correct)
- [ ] P[15] = carry_FA_10 (overflow from column 14)
- [ ] valid_out is asserted exactly 3 clock cycles after valid_in

**Code quality:**
- [ ] `` `default_nettype none `` in all 10 files
- [ ] All module instantiations use named port connections
- [ ] No `*` operator in synthesizable code
- [ ] All floating signals are named wires with `// intentionally unused` comment
- [ ] Every cell instantiation has a Stage/Column/CellName comment above it

---

*End of prompt. Generate all 10 files in full. No placeholders, no TODOs, no omitted sections. Every signal listed in Section 13 must trace cleanly from its source to its consumer.*
