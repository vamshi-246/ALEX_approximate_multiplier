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
