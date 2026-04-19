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
