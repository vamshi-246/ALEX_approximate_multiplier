`default_nettype none
module exact_half_adder (
    input  wire X1, X2,
    output wire Sum,
    output wire Carry
);
    assign Sum   = X1 ^ X2;
    assign Carry = X1 & X2;
endmodule
