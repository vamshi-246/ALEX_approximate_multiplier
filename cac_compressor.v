`default_nettype none
module cac_compressor (
    input  wire X1, X2, X3, X4,
    output wire Sum,
    output wire Carry
);
    assign Sum   = ((X1 & X2) & (X3 | X4)) | (X3 & X4);
    assign Carry = 1'b1;  // Always VDD — hardwired, not computed
endmodule
