`default_nettype none
module mha_two_ones (
    output wire Sum,
    output wire Carry
);
    assign Sum   = 1'b0;  // 1 + 1 = 10 in binary; sum bit = 0
    assign Carry = 1'b1;  // carry out = 1
endmodule
