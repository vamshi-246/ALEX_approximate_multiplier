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
