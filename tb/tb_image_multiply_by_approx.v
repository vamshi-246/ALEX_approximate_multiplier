`timescale 1ns/1ps

module tb_approx_multiplier;

    // =============================
    // PARAMETERS
    // =============================
    parameter N = 256*256;

    // =============================
    // DUT SIGNALS
    // =============================
    reg clk;
    reg rst;
    reg valid_in;
    reg [7:0] A;
    reg [7:0] B;

    wire [15:0] P;
    wire valid_out;

    // =============================
    // MEMORY
    // =============================
    reg [7:0] memA [0:N-1];
    reg [7:0] memB [0:N-1];

    integer i;
    integer out_file;

    // =============================
    // DUT INSTANCE
    // =============================
    approx_multiplier_8x8 dut (
        .clk(clk),
        .rst(rst),
        .valid_in(valid_in),
        .A(A),
        .B(B),
        .P(P),
        .valid_out(valid_out)
    );

    // =============================
    // CLOCK
    // =============================
    always #5 clk = ~clk;

    // =============================
    // INIT
    // =============================
    initial begin
        clk = 0;
        rst = 1;
        valid_in = 0;
        A = 0;
        B = 0;

        // Load files (decimal format)
        $readmemh("cameraman.txt", memA);  // or $readmemh if hex
        $readmemh("circle.txt", memB);

        out_file = $fopen("cameramanxcircle.txt", "w");

        #20;
        rst = 0;

        // =============================
        // FEED INPUT STREAM
        // =============================
        for (i = 0; i < N; i = i + 1) begin
            @(posedge clk);
            A <= memA[i];
            B <= memB[i];
            valid_in <= 1;
        end

        // stop input
        @(posedge clk);
        valid_in <= 0;
        A <= 0;
        B <= 0;

        // wait for pipeline flush
        repeat(10) @(posedge clk);

        $fclose(out_file);
        $finish;
    end

    // =============================
    // OUTPUT CAPTURE
    // =============================
    always @(posedge clk) begin
        if (valid_out) begin
            $fwrite(out_file, "%0d\n", P);
        end
    end

endmodule