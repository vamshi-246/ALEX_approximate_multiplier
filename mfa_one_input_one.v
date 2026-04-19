`default_nettype none
module mfa_one_input_one (
    input  wire X2, Cin,
    output wire Sum,
    output wire Carry
);
    assign Sum   = ~(X2 ^ Cin);   // X2 XNOR Cin
    assign Carry = X2 | Cin;
endmodule
