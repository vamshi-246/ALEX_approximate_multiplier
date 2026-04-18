`default_nettype none
module approx_multiplier_8x8 (
    input  wire        clk,
    input  wire        rst,       // synchronous, active-high
    input  wire        valid_in,
    input  wire [7:0]  A,
    input  wire [7:0]  B,
    output reg  [15:0] P,
    output reg         valid_out
);

    // =========================================================================
    // PARTIAL PRODUCT GENERATION (Section 2.2)
    // =========================================================================

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

    // =========================================================================
    // STAGE 1 — COMBINATIONAL LOGIC (Section 4)
    // =========================================================================

    // --- Stage 1 — Approximate Component (Columns 4–9) ---

    // Stage 1 | Column 4 | HA_0: X1=p_4_0, X2=p_3_1 → sum_HA_0, carry_HA_0
    wire sum_HA_0, carry_HA_0;
    exact_half_adder HA_0 (
        .X1    (p_4_0),
        .X2    (p_3_1),
        .Sum   (sum_HA_0),
        .Carry (carry_HA_0)
    );

    // Stage 1 | Column 5 | ACMLC_0: X1=p_5_0, X2=p_4_1, X3=p_3_2, X4=0 → sum_ACMLC_0(=1), carry_ACMLC_0
    wire sum_ACMLC_0, carry_ACMLC_0;
    acmlc_compressor ACMLC_0 (
        .X1    (p_5_0),
        .X2    (p_4_1),
        .X3    (p_3_2),
        .X4    (1'b0),      // p[2][3] was never generated; tie to 0 for discarded port
        .Sum   (sum_ACMLC_0),   // = 1'b1 constant by definition
        .Carry (carry_ACMLC_0)
    );

    // Stage 1 | Column 6 | ACMLC_1: X1=p_6_0, X2=p_5_1, X3=p_4_2, X4=0 → sum_ACMLC_1(=1), carry_ACMLC_1
    wire sum_ACMLC_1, carry_ACMLC_1;
    acmlc_compressor ACMLC_1 (
        .X1    (p_6_0),
        .X2    (p_5_1),
        .X3    (p_4_2),
        .X4    (1'b0),      // p[3][3] was never generated
        .Sum   (sum_ACMLC_1),   // = 1'b1 constant by definition
        .Carry (carry_ACMLC_1)
    );

    // Stage 1 | Column 7 | ACMLC_2: X1=p_7_0, X2=p_6_1, X3=p_5_2, X4=0 → sum_ACMLC_2(=1), carry_ACMLC_2
    wire sum_ACMLC_2, carry_ACMLC_2;
    acmlc_compressor ACMLC_2 (
        .X1    (p_7_0),
        .X2    (p_6_1),
        .X3    (p_5_2),
        .X4    (1'b0),      // p[4][3] never generated
        .Sum   (sum_ACMLC_2),   // = 1'b1 constant by definition
        .Carry (carry_ACMLC_2)
    );

    // Stage 1 | Column 7 | ACMLC_3: X1=p_3_4, X2=p_2_5, X3=p_1_6, X4=0 → sum_ACMLC_3(=1), carry_ACMLC_3
    wire sum_ACMLC_3, carry_ACMLC_3;
    acmlc_compressor ACMLC_3 (
        .X1    (p_3_4),
        .X2    (p_2_5),
        .X3    (p_1_6),
        .X4    (1'b0),      // p[0][7] never generated
        .Sum   (sum_ACMLC_3),   // = 1'b1 constant by definition
        .Carry (carry_ACMLC_3)
    );

    // Stage 1 | Column 8 | ACMLC_4: X1=p_7_1, X2=p_6_2, X3=p_5_3, X4=0 → sum_ACMLC_4(=1), carry_ACMLC_4
    wire sum_ACMLC_4, carry_ACMLC_4;
    acmlc_compressor ACMLC_4 (
        .X1    (p_7_1),
        .X2    (p_6_2),
        .X3    (p_5_3),
        .X4    (1'b0),      // p[4][4] never generated
        .Sum   (sum_ACMLC_4),   // = 1'b1 constant by definition
        .Carry (carry_ACMLC_4)
    );

    // Stage 1 | Column 8 | FA_0: X1=p_3_5, X2=p_2_6, Cin=p_1_7 → sum_FA_0, carry_FA_0
    wire sum_FA_0, carry_FA_0;
    exact_full_adder FA_0 (
        .X1    (p_3_5),
        .X2    (p_2_6),
        .Cin   (p_1_7),     // p[1][7] acts as carry-in per architecture
        .Sum   (sum_FA_0),
        .Carry (carry_FA_0)
    );

    // Stage 1 | Column 9 | CAC_0: X1=p_7_2, X2=p_6_3, X3=p_5_4, X4=p_4_5 → sum_CAC_0, carry_CAC_0(=1)
    wire sum_CAC_0;
    wire carry_CAC_0_unused; // CAC carry output — always 1'b1 by definition
    cac_compressor CAC_0 (
        .X1    (p_7_2),
        .X2    (p_6_3),
        .X3    (p_5_4),
        .X4    (p_4_5),
        .Sum   (sum_CAC_0),
        .Carry (carry_CAC_0_unused) // Always 1'b1 — we wire the constant directly below
    );
    wire carry_CAC_0 = 1'b1; // Hardwired constant from CAC_0 — feeds EX_COMP_0 Cin directly

    // Stage 1 | Column 9 | HA_1: X1=p_3_6, X2=p_2_7 → sum_HA_1, carry_HA_1
    wire sum_HA_1, carry_HA_1;
    exact_half_adder HA_1 (
        .X1    (p_3_6),
        .X2    (p_2_7),
        .Sum   (sum_HA_1),
        .Carry (carry_HA_1)
    );

    // --- Stage 1 — Exact Component (Columns 10–14) ---

    // Stage 1 | Column 10 | EX_COMP_0: X1=p_7_3, X2=p_6_4, X3=p_5_5, X4=p_4_6, Cin=carry_CAC_0(=1) → sum, carry, cout
    wire sum_EX_COMP_0, carry_EX_COMP_0, cout_EX_COMP_0;
    exact_compressor EX_COMP_0 (
        .X1    (p_7_3),
        .X2    (p_6_4),
        .X3    (p_5_5),
        .X4    (p_4_6),
        .Cin   (carry_CAC_0),    // = 1'b1 hardwired constant
        .Sum   (sum_EX_COMP_0),
        .Carry (carry_EX_COMP_0),
        .Cout  (cout_EX_COMP_0)
    );

    // Stage 1 | Column 11 | FA_1: X1=p_7_4, X2=p_6_5, Cin=p_5_6 → sum_FA_1, carry_FA_1
    wire sum_FA_1, carry_FA_1;
    exact_full_adder FA_1 (
        .X1    (p_7_4),
        .X2    (p_6_5),
        .Cin   (p_5_6),
        .Sum   (sum_FA_1),
        .Carry (carry_FA_1)
    );

    // Stage 1 | Column 12 | FA_2: X1=p_7_5, X2=p_6_6, Cin=p_5_7 → sum_FA_2, carry_FA_2
    wire sum_FA_2, carry_FA_2;
    exact_full_adder FA_2 (
        .X1    (p_7_5),
        .X2    (p_6_6),
        .Cin   (p_5_7),
        .Sum   (sum_FA_2),
        .Carry (carry_FA_2)
    );

    // Stage 1 | Column 13 | HA_2: X1=p_7_6, X2=p_6_7 → sum_HA_2, carry_HA_2
    wire sum_HA_2, carry_HA_2;
    exact_half_adder HA_2 (
        .X1    (p_7_6),
        .X2    (p_6_7),
        .Sum   (sum_HA_2),
        .Carry (carry_HA_2)
    );

    // Column 14 — p_7_7 passes directly to Stage 2 pipeline register. No logic in Stage 1.

    // =========================================================================
    // PIPELINE REGISTER 1 (Stage 1 → Stage 2) — Section 5
    // =========================================================================
    // Do NOT register sum_ACMLC_0/1/2/3/4 — they are 1'b1 constants
    // Do NOT register carry_CAC_0 — it is 1'b1 constant used within Stage 1

    reg sum_HA_0_r1;
    reg carry_HA_0_r1;
    reg carry_ACMLC_0_r1;
    reg carry_ACMLC_1_r1;
    reg carry_ACMLC_2_r1;
    reg carry_ACMLC_3_r1;
    reg carry_ACMLC_4_r1;
    reg sum_FA_0_r1;
    reg carry_FA_0_r1;
    reg sum_CAC_0_r1;
    reg sum_HA_1_r1;
    reg carry_HA_1_r1;
    reg sum_EX_COMP_0_r1;
    reg carry_EX_COMP_0_r1;
    reg cout_EX_COMP_0_r1;
    reg sum_FA_1_r1;
    reg carry_FA_1_r1;
    reg sum_FA_2_r1;
    reg carry_FA_2_r1;
    reg sum_HA_2_r1;
    reg carry_HA_2_r1;
    reg p_2_2_r1;
    reg p_1_3_r1;
    reg p_0_4_r1;
    reg p_1_4_r1;
    reg p_0_5_r1;
    reg p_2_4_r1;
    reg p_1_5_r1;
    reg p_3_7_r1;
    reg p_4_7_r1;
    reg p_7_7_r1;
    reg valid_r1;

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

    // =========================================================================
    // STAGE 2 — COMBINATIONAL LOGIC (Section 6, operates on _r1 signals)
    // =========================================================================

    // --- Stage 2 — Approximate Component (Columns 4–9) ---

    // Stage 2 | Column 4 | CAC_1: X1=sum_HA_0_r1, X2=p_2_2_r1, X3=p_1_3_r1, X4=p_0_4_r1 → sum_CAC_1, carry_CAC_1(=1)
    wire sum_CAC_1;
    wire carry_CAC_1_unused; // Always 1'b1 by CAC definition
    cac_compressor CAC_1 (
        .X1    (sum_HA_0_r1),
        .X2    (p_2_2_r1),
        .X3    (p_1_3_r1),
        .X4    (p_0_4_r1),
        .Sum   (sum_CAC_1),
        .Carry (carry_CAC_1_unused) // = 1'b1 constant by CAC definition
    );

    // Stage 2 | Column 5 | MACMLC_0: X2=p_1_4_r1, X3=p_0_5_r1, X4=carry_HA_0_r1(discarded) → sum_MACMLC_0(=1), carry_MACMLC_0
    wire sum_MACMLC_0; // = 1'b1 constant — intentionally unused downstream
    wire carry_MACMLC_0;
    wire unused_carry_HA_0_in_col5 = carry_HA_0_r1; // intentionally not consumed in logic — discarded X4
    macmlc_compressor MACMLC_0 (
        .X2    (p_1_4_r1),
        .X3    (p_0_5_r1),
        .X4    (1'b0),      // carry_HA_0_r1 is discarded; tie port to 0
        .Sum   (sum_MACMLC_0),   // = 1'b1 constant — do NOT pipeline
        .Carry (carry_MACMLC_0)
    );

    // Stage 2 | Column 6 | MACMLC_1: X2=p_2_4_r1, X3=p_1_5_r1, X4=0(p[0][6] never generated) → sum_MACMLC_1(=1), carry_MACMLC_1
    wire sum_MACMLC_1; // = 1'b1 constant — intentionally unused downstream
    wire carry_MACMLC_1;
    macmlc_compressor MACMLC_1 (
        .X2    (p_2_4_r1),
        .X3    (p_1_5_r1),
        .X4    (1'b0),      // p[0][6] was never generated; tie discarded port to 0
        .Sum   (sum_MACMLC_1),   // = 1'b1 constant — do NOT pipeline
        .Carry (carry_MACMLC_1)
    );

    // Stage 2 | Column 7 | MACMLC_2: X2=sum_ACMLC_3_r1(=1), X3=carry_ACMLC_1_r1, X4=carry_ACMLC_0_r1(discarded) → sum_MACMLC_2(floating), carry_MACMLC_2
    // Note: sum_ACMLC_3 = 1'b1 always. We use 1'b1 directly since we don't register ACMLC sums.
    wire unused_sum_MACMLC_2; // floating per architecture — intentionally unused
    wire carry_MACMLC_2;
    wire unused_carry_ACMLC_0_col7 = carry_ACMLC_0_r1; // intentionally not consumed in logic — discarded X4
    macmlc_compressor MACMLC_2 (
        .X2    (1'b1),              // sum_ACMLC_3 = 1'b1 always (not registered, constant)
        .X3    (carry_ACMLC_1_r1),
        .X4    (1'b0),              // carry_ACMLC_0_r1 is discarded; tie port to 0
        .Sum   (unused_sum_MACMLC_2),   // floating per architecture
        .Carry (carry_MACMLC_2)         // = 1'b1 | carry_ACMLC_1_r1 = 1'b1 always
    );

    // Stage 2 | Column 8 | MACMLC_3: X2=sum_FA_0_r1, X3=carry_ACMLC_2_r1, X4=carry_ACMLC_3_r1(discarded) → sum_MACMLC_3(floating), carry_MACMLC_3
    wire unused_sum_MACMLC_3; // floating per architecture — intentionally unused
    wire carry_MACMLC_3;
    wire unused_carry_ACMLC_3_col8 = carry_ACMLC_3_r1; // intentionally not consumed in logic — discarded X4
    macmlc_compressor MACMLC_3 (
        .X2    (sum_FA_0_r1),
        .X3    (carry_ACMLC_2_r1),
        .X4    (1'b0),              // carry_ACMLC_3_r1 is discarded; tie port to 0
        .Sum   (unused_sum_MACMLC_3),   // floating per architecture
        .Carry (carry_MACMLC_3)
    );

    // Stage 2 | Column 9 | CAC_2: X1=sum_CAC_0_r1, X2=sum_HA_1_r1, X3=carry_ACMLC_4_r1, X4=carry_FA_0_r1 → sum_CAC_2, carry_CAC_2(=1)
    wire sum_CAC_2;
    wire carry_CAC_2_from_module; // Always 1'b1 by CAC definition
    cac_compressor CAC_2 (
        .X1    (sum_CAC_0_r1),
        .X2    (sum_HA_1_r1),
        .X3    (carry_ACMLC_4_r1),
        .X4    (carry_FA_0_r1),
        .Sum   (sum_CAC_2),
        .Carry (carry_CAC_2_from_module) // = 1'b1 constant by CAC definition — wire as constant, do NOT pipeline
    );

    // --- Stage 2 — Exact Component (Columns 10–14) ---

    // Stage 2 | Column 10 | FA_3: X1=sum_EX_COMP_0_r1, X2=p_3_7_r1, Cin=carry_HA_1_r1 → sum_FA_3, carry_FA_3
    wire sum_FA_3, carry_FA_3;
    exact_full_adder FA_3 (
        .X1    (sum_EX_COMP_0_r1),
        .X2    (p_3_7_r1),
        .Cin   (carry_HA_1_r1),
        .Sum   (sum_FA_3),
        .Carry (carry_FA_3)
    );

    // Stage 2 | Column 11 | FA_4: X1=sum_FA_1_r1, X2=p_4_7_r1, Cin=carry_EX_COMP_0_r1 → sum_FA_4, carry_FA_4
    wire sum_FA_4, carry_FA_4;
    exact_full_adder FA_4 (
        .X1    (sum_FA_1_r1),
        .X2    (p_4_7_r1),
        .Cin   (carry_EX_COMP_0_r1),   // This is the CARRY output of exact_compressor, NOT Cout
        .Sum   (sum_FA_4),
        .Carry (carry_FA_4)
    );

    // Stage 2 | Column 12 | FA_5: X1=sum_FA_2_r1, X2=carry_FA_1_r1, Cin=cout_EX_COMP_0_r1 → sum_FA_5, carry_FA_5
    wire sum_FA_5, carry_FA_5;
    exact_full_adder FA_5 (
        .X1    (sum_FA_2_r1),
        .X2    (carry_FA_1_r1),
        .Cin   (cout_EX_COMP_0_r1),    // This is the COUT (cascade) output of exact_compressor, NOT Carry
        .Sum   (sum_FA_5),
        .Carry (carry_FA_5)
    );

    // Stage 2 | Column 13 | HA_3: X1=sum_HA_2_r1, X2=carry_FA_2_r1 → sum_HA_3, carry_HA_3
    wire sum_HA_3, carry_HA_3;
    exact_half_adder HA_3 (
        .X1    (sum_HA_2_r1),
        .X2    (carry_FA_2_r1),
        .Sum   (sum_HA_3),
        .Carry (carry_HA_3)
    );

    // Stage 2 | Column 14 | HA_4: X1=p_7_7_r1, X2=carry_HA_2_r1 → sum_HA_4, carry_HA_4
    wire sum_HA_4, carry_HA_4;
    exact_half_adder HA_4 (
        .X1    (p_7_7_r1),
        .X2    (carry_HA_2_r1),
        .Sum   (sum_HA_4),
        .Carry (carry_HA_4)
    );

    // carry_HA_4 from Stage 2 is not consumed anywhere in Stage 3 — column 15 overflow, architecturally not used
    wire unused_carry_HA_4 = carry_HA_4; // column 15 overflow, architecturally not used

    // =========================================================================
    // PIPELINE REGISTER 2 (Stage 2 → Stage 3) — Section 7
    // =========================================================================
    // Do NOT register carry_CAC_1, carry_CAC_2 (1'b1 constants from CAC modules)
    // Do NOT register sum_MACMLC_2, sum_MACMLC_3 (floating, architecturally disconnected)

    reg sum_CAC_1_r2;
    reg carry_MACMLC_0_r2;
    reg carry_MACMLC_1_r2;
    reg carry_MACMLC_2_r2;     // = 1'b1 always, but register for timing
    reg carry_MACMLC_3_r2;
    reg sum_CAC_2_r2;
    reg sum_FA_3_r2;
    reg carry_FA_3_r2;
    reg sum_FA_4_r2;
    reg carry_FA_4_r2;
    reg sum_FA_5_r2;
    reg carry_FA_5_r2;
    reg sum_HA_3_r2;
    reg carry_HA_3_r2;
    reg sum_HA_4_r2;
    reg carry_HA_4_r2;
    reg valid_r2;

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

    // =========================================================================
    // STAGE 3 — COMBINATIONAL LOGIC AND OUTPUT (Section 8)
    // =========================================================================

    // --- Stage 3 Constant Carry Chain ---
    wire carry_MHA_0 = 1'b1;    // from mha_two_ones module definition
    wire carry_MFA_0 = 1'b1;    // carry_MACMLC_0_r2 | carry_MHA_0 = X | 1 = 1
    wire carry_MFA_1 = 1'b1;    // carry_MACMLC_1_r2 | carry_MFA_0 = X | 1 = 1
    wire carry_MFA_2 = 1'b1;    // carry_MACMLC_2_r2 | carry_MFA_1 = X | 1 = 1
    wire carry_CAC_2 = 1'b1;    // from cac_compressor definition (already in Stage 2)

    // --- Stage 3 — Approximate Component (Columns 4–9) ---

    // Column 4 — Direct result: P[4] = sum_CAC_1_r2 (no logic cell)

    // Stage 3 | Column 5 | MHA_0: no inputs → sum_MHA_0(=0), carry_MHA_0(=1)
    wire sum_MHA_0;
    wire carry_MHA_0_from_module; // will be 1'b1
    mha_two_ones MHA_0 (
        .Sum   (sum_MHA_0),          // = 1'b0 → P[5] = 1'b0
        .Carry (carry_MHA_0_from_module)  // = 1'b1
    );

    // Stage 3 | Column 6 | MFA_0: X2=carry_MACMLC_0_r2, Cin=carry_MHA_0(=1) → sum_MFA_0, carry_MFA_0(=1)
    wire sum_MFA_0;
    wire carry_MFA_0_from_module; // will be 1'b1
    mfa_one_input_one MFA_0 (
        .X2    (carry_MACMLC_0_r2),
        .Cin   (carry_MHA_0),       // = 1'b1
        .Sum   (sum_MFA_0),         // = carry_MACMLC_0_r2 (XNOR with 1 = identity)
        .Carry (carry_MFA_0_from_module)  // = carry_MACMLC_0_r2 | 1 = 1'b1
    );

    // Stage 3 | Column 7 | MFA_1: X2=carry_MACMLC_1_r2, Cin=carry_MFA_0(=1) → sum_MFA_1, carry_MFA_1(=1)
    wire sum_MFA_1;
    wire carry_MFA_1_from_module; // will be 1'b1
    mfa_one_input_one MFA_1 (
        .X2    (carry_MACMLC_1_r2),
        .Cin   (carry_MFA_0),       // = 1'b1
        .Sum   (sum_MFA_1),         // = carry_MACMLC_1_r2
        .Carry (carry_MFA_1_from_module)  // = 1'b1
    );

    // Stage 3 | Column 8 | MFA_2: X2=carry_MACMLC_2_r2, Cin=carry_MFA_1(=1) → sum_MFA_2, carry_MFA_2(=1)
    wire sum_MFA_2;
    wire carry_MFA_2_from_module; // will be 1'b1
    mfa_one_input_one MFA_2 (
        .X2    (carry_MACMLC_2_r2),
        .Cin   (carry_MFA_1),       // = 1'b1
        .Sum   (sum_MFA_2),         // = carry_MACMLC_2_r2
        .Carry (carry_MFA_2_from_module)  // = 1'b1
    );

    // Stage 3 | Column 9 | FA_6: X1=sum_CAC_2_r2, X2=carry_MACMLC_3_r2, Cin=carry_MFA_2(=1) → sum_FA_6, carry_FA_6
    wire sum_FA_6, carry_FA_6;
    exact_full_adder FA_6 (
        .X1    (sum_CAC_2_r2),
        .X2    (carry_MACMLC_3_r2),
        .Cin   (carry_MFA_2),       // = 1'b1
        .Sum   (sum_FA_6),          // = ~(sum_CAC_2_r2 ^ carry_MACMLC_3_r2)
        .Carry (carry_FA_6)         // = sum_CAC_2_r2 | carry_MACMLC_3_r2
    );

    // --- Stage 3 — Exact Component (Columns 10–14) ---

    // Stage 3 | Column 10 | MFA_3: X2=sum_FA_3_r2, Cin=carry_FA_6 → sum_MFA_3, carry_MFA_3
    wire sum_MFA_3, carry_MFA_3;
    mfa_one_input_one MFA_3 (
        .X2    (sum_FA_3_r2),
        .Cin   (carry_FA_6),
        .Sum   (sum_MFA_3),         // = ~(sum_FA_3_r2 ^ carry_FA_6), i.e. XNOR
        .Carry (carry_MFA_3)        // = sum_FA_3_r2 | carry_FA_6
    );

    // Stage 3 | Column 11 | FA_7: X1=sum_FA_4_r2, X2=carry_FA_3_r2, Cin=carry_MFA_3 → sum_FA_7, carry_FA_7
    wire sum_FA_7, carry_FA_7;
    exact_full_adder FA_7 (
        .X1    (sum_FA_4_r2),
        .X2    (carry_FA_3_r2),
        .Cin   (carry_MFA_3),
        .Sum   (sum_FA_7),
        .Carry (carry_FA_7)
    );

    // Stage 3 | Column 12 | FA_8: X1=sum_FA_5_r2, X2=carry_FA_4_r2, Cin=carry_FA_7 → sum_FA_8, carry_FA_8
    wire sum_FA_8, carry_FA_8;
    exact_full_adder FA_8 (
        .X1    (sum_FA_5_r2),
        .X2    (carry_FA_4_r2),
        .Cin   (carry_FA_7),
        .Sum   (sum_FA_8),
        .Carry (carry_FA_8)
    );

    // Stage 3 | Column 13 | FA_9: X1=sum_HA_3_r2, X2=carry_FA_5_r2, Cin=carry_FA_8 → sum_FA_9, carry_FA_9
    wire sum_FA_9, carry_FA_9;
    exact_full_adder FA_9 (
        .X1    (sum_HA_3_r2),
        .X2    (carry_FA_5_r2),
        .Cin   (carry_FA_8),
        .Sum   (sum_FA_9),
        .Carry (carry_FA_9)
    );

    // Stage 3 | Column 14 | FA_10: X1=sum_HA_4_r2, X2=carry_HA_3_r2, Cin=carry_FA_9 → sum_FA_10, carry_FA_10
    wire sum_FA_10, carry_FA_10;
    exact_full_adder FA_10 (
        .X1    (sum_HA_4_r2),
        .X2    (carry_HA_3_r2),
        .Cin   (carry_FA_9),
        .Sum   (sum_FA_10),
        .Carry (carry_FA_10)
    );
wire p_15;
assign p_15 = carry_FA_10 ^ carry_HA_4_r2;
    // =========================================================================
    // OUTPUT REGISTER AND FINAL ASSEMBLY (Section 9)
    // =========================================================================

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
            P[15]   <= p_15;      // Overflow carry from col 14
            valid_out <= valid_r2;
        end
    end

endmodule
