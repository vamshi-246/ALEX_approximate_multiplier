`default_nettype none
module exact_full_adder (
    input  wire X1, X2, Cin,
    output wire Sum,
    output wire Carry
);
    assign Sum   = X1 ^ X2 ^ Cin;
    assign Carry = (X1 & X2) | (Cin & (X1 | X2));
endmodule
