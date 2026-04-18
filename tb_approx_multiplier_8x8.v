`timescale 1ns/1ps
`default_nettype none
module tb_approx_multiplier_8x8;

    // =========================================================================
    // CLOCK AND SIGNAL DECLARATIONS
    // =========================================================================
    parameter CLK_PERIOD = 10; // 10 ns = 100 MHz

    reg         clk;
    reg         rst;
    reg         valid_in;
    reg  [7:0]  A_tb, B_tb;
    wire [15:0] P_tb;
    wire        valid_out_tb;

    initial clk = 0;
    always #(CLK_PERIOD/2) clk = ~clk;

    // =========================================================================
    // DUT INSTANTIATION
    // =========================================================================
    approx_multiplier_8x8 DUT (
        .clk       (clk),
        .rst       (rst),
        .valid_in  (valid_in),
        .A         (A_tb),
        .B         (B_tb),
        .P         (P_tb),
        .valid_out (valid_out_tb)
    );

    // =========================================================================
    // VCD DUMP
    // =========================================================================
    initial begin
        $dumpfile("tb_approx_multiplier_8x8.vcd");
        $dumpvars(0, tb_approx_multiplier_8x8);
    end

    // =========================================================================
    // TEST INFRASTRUCTURE
    // =========================================================================
    integer dir_pass, dir_fail;
    integer rnd_pass, rnd_fail;
    integer pipe_ok_int;
    integer hw_ok_int;
    integer i;
    integer delta;
    integer abs_delta;
    reg [15:0] exact_product;
    reg [7:0]  saved_A, saved_B;

    reg [7:0]  dir_A [0:9];
    reg [7:0]  dir_B [0:9];
    reg [15:0] dir_exact [0:9];

    // Pipeline sequencing storage
    reg [7:0]  pipe_A [0:4];
    reg [7:0]  pipe_B [0:4];

    reg [31:0] rand_val;

    // =========================================================================
    // TASK: Apply single input and wait for result (3 cycle latency)
    // =========================================================================
    task apply_and_wait;
        input [7:0] a_val;
        input [7:0] b_val;
        begin
            @(negedge clk);
            A_tb     = a_val;
            B_tb     = b_val;
            valid_in = 1'b1;
            @(negedge clk);
            valid_in = 1'b0;
            A_tb     = 8'b0;
            B_tb     = 8'b0;
            // Wait 2 more cycles for pipeline to complete (total 3 posedge transitions)
            @(negedge clk);
            @(negedge clk);
        end
    endtask

    // =========================================================================
    // MAIN TEST SEQUENCE
    // =========================================================================
    initial begin
        // Initialize
        dir_pass    = 0;
        dir_fail    = 0;
        rnd_pass    = 0;
        rnd_fail    = 0;
        pipe_ok_int = 1;
        hw_ok_int   = 1;
        rst         = 1;
        valid_in    = 0;
        A_tb        = 8'b0;
        B_tb        = 8'b0;

        // -----------------------------------------------------------------
        // Directed test case table
        // -----------------------------------------------------------------
        dir_A[0] = 8'd0;   dir_B[0] = 8'd0;   dir_exact[0] = 16'd0;
        dir_A[1] = 8'd255; dir_B[1] = 8'd255; dir_exact[1] = 16'd65025;
        dir_A[2] = 8'd1;   dir_B[2] = 8'd1;   dir_exact[2] = 16'd1;
        dir_A[3] = 8'd128; dir_B[3] = 8'd128; dir_exact[3] = 16'd16384;
        dir_A[4] = 8'd255; dir_B[4] = 8'd0;   dir_exact[4] = 16'd0;
        dir_A[5] = 8'd0;   dir_B[5] = 8'd255; dir_exact[5] = 16'd0;
        dir_A[6] = 8'd128; dir_B[6] = 8'd1;   dir_exact[6] = 16'd128;
        dir_A[7] = 8'd170; dir_B[7] = 8'd85;  dir_exact[7] = 16'd14450;
        dir_A[8] = 8'd15;  dir_B[8] = 8'd15;  dir_exact[8] = 16'd225;
        dir_A[9] = 8'd240; dir_B[9] = 8'd240; dir_exact[9] = 16'd57600;

        // -----------------------------------------------------------------
        // RESET TEST (Section 11.4)
        // -----------------------------------------------------------------
        $display("\n===== RESET TEST =====");
        rst      = 1'b1;
        valid_in = 1'b1;
        A_tb     = 8'd170;
        B_tb     = 8'd85;
        repeat (3) @(posedge clk);
        #1;
        if (P_tb !== 16'b0) begin
            $display("FAIL: P != 0 during reset. P = %0d", P_tb);
        end else begin
            $display("PASS: P = 0 during reset");
        end
        if (valid_out_tb !== 1'b0) begin
            $display("FAIL: valid_out != 0 during reset");
        end else begin
            $display("PASS: valid_out = 0 during reset");
        end

        // Deassert reset
        @(negedge clk);
        rst      = 1'b0;
        valid_in = 1'b0;
        A_tb     = 8'b0;
        B_tb     = 8'b0;
        // Wait for pipeline to flush
        repeat (5) @(posedge clk);

        // -----------------------------------------------------------------
        // DIRECTED TEST CASES (Section 11.1)
        // -----------------------------------------------------------------
        $display("\n===== DIRECTED TEST CASES =====");
        for (i = 0; i < 10; i = i + 1) begin
            saved_A = dir_A[i];
            saved_B = dir_B[i];
            apply_and_wait(saved_A, saved_B);
            #1;

            // Check P[3:0] hardwire
            if (P_tb[3:0] !== 4'b0110) begin
                $display("FAIL: P[3:0] != 4'b0110 for A=%0d, B=%0d. Got P[3:0]=%b", saved_A, saved_B, P_tb[3:0]);
                hw_ok_int = 0;
            end

            delta = $signed({1'b0, P_tb}) - $signed({1'b0, dir_exact[i]});
            abs_delta = (delta < 0) ? -delta : delta;

            if (P_tb == dir_exact[i]) begin
                $display("Directed[%0d]: A=%3d, B=%3d | P=%5d | Exact=%5d | EXACT_MATCH", i, saved_A, saved_B, P_tb, dir_exact[i]);
                dir_pass = dir_pass + 1;
            end else if (abs_delta <= 256) begin
                $display("Directed[%0d]: A=%3d, B=%3d | P=%5d | Exact=%5d | APPROX_DIFF: delta = %0d", i, saved_A, saved_B, P_tb, dir_exact[i], delta);
                dir_pass = dir_pass + 1;
            end else begin
                $display("Directed[%0d]: A=%3d, B=%3d | P=%5d | Exact=%5d | FAIL: |delta|=%0d > 256", i, saved_A, saved_B, P_tb, dir_exact[i], abs_delta);
                dir_fail = dir_fail + 1;
            end
        end

        // -----------------------------------------------------------------
        // RANDOM STIMULUS (Section 11.2) — 1000 cases
        // -----------------------------------------------------------------
        $display("\n===== RANDOM STIMULUS (1000 cases) =====");
        for (i = 0; i < 1000; i = i + 1) begin
            rand_val = $random;
            saved_A  = rand_val[7:0];
            saved_B  = rand_val[15:8];

            apply_and_wait(saved_A, saved_B);
            #1;

            // Check P[3:0] hardwire
            if (P_tb[3:0] !== 4'b0110) begin
                $display("FAIL: Random[%0d] P[3:0] != 4'b0110. A=%0d, B=%0d, P[3:0]=%b", i, saved_A, saved_B, P_tb[3:0]);
                hw_ok_int = 0;
                rnd_fail  = rnd_fail + 1;
            end else begin
                // Compute exact product using 16-bit width to avoid truncation
                exact_product = {8'b0, saved_A} * {8'b0, saved_B};
                delta = $signed({1'b0, P_tb}) - $signed({1'b0, exact_product});
                abs_delta = (delta < 0) ? -delta : delta;

                if (abs_delta <= 4096) begin
                    rnd_pass = rnd_pass + 1;
                end else begin
                    $display("FAIL: Random[%0d] A=%3d, B=%3d | P=%5d | Exact=%5d | |delta|=%0d > 4096",
                             i, saved_A, saved_B, P_tb, exact_product, abs_delta);
                    rnd_fail = rnd_fail + 1;
                end
            end
        end
        if (rnd_fail == 0)
            $display("All 1000 random tests PASSED (within +/-4096 tolerance).");

        // -----------------------------------------------------------------
        // PIPELINE SEQUENCING TEST (Section 11.3)
        // -----------------------------------------------------------------
        $display("\n===== PIPELINE SEQUENCING TEST =====");

        pipe_A[0] = 8'd10;  pipe_B[0] = 8'd20;
        pipe_A[1] = 8'd30;  pipe_B[1] = 8'd40;
        pipe_A[2] = 8'd50;  pipe_B[2] = 8'd60;
        pipe_A[3] = 8'd70;  pipe_B[3] = 8'd80;
        pipe_A[4] = 8'd90;  pipe_B[4] = 8'd100;

        // Flush pipeline with reset
        @(negedge clk);
        rst = 1'b1;
        repeat (4) @(posedge clk);
        @(negedge clk);
        rst = 1'b0;
        valid_in = 1'b0;
        A_tb     = 8'b0;
        B_tb     = 8'b0;
        repeat (4) @(posedge clk);

        begin : pipe_test_block
            integer cycle_count;
            integer first_valid_cycle;
            integer valid_count;
            integer outputs_differ;
            reg [15:0] prev_P;

            first_valid_cycle = -1;
            valid_count = 0;
            outputs_differ = 0;
            prev_P = 16'hFFFF;

            // Apply 5 back-to-back valid inputs without gaps starting NOW.
            // We will simultaneously apply inputs and monitor outputs.
            // Cycle counting starts from the first input application.
            // First input at negedge of cycle 0.
            // valid_out should go high at posedge of cycle 3 (3-cycle latency).
            // We keep valid_in=1 for cycles 0..4 (5 inputs), then deassert.
            // valid_out should be high at posedge of cycles 3..7 (5 outputs).
            // Monitor for cycles 0..9.

            // Apply first input
            @(negedge clk);
            A_tb     = pipe_A[0];
            B_tb     = pipe_B[0];
            valid_in = 1'b1;

            // Now monitor posedge and apply next inputs at negedge
            for (cycle_count = 0; cycle_count < 12; cycle_count = cycle_count + 1) begin
                @(posedge clk);
                #1;
                // Check valid_out
                if (valid_out_tb) begin
                    valid_count = valid_count + 1;
                    if (first_valid_cycle == -1) first_valid_cycle = cycle_count;
                    if (P_tb != prev_P) outputs_differ = outputs_differ + 1;
                    prev_P = P_tb;
                    $display("  Pipeline cycle %0d: valid_out=1, P=%0d", cycle_count, P_tb);
                end

                // Apply next input at negedge or deassert
                @(negedge clk);
                if (cycle_count < 4) begin
                    // Apply next input (indices 1..4)
                    A_tb     = pipe_A[cycle_count + 1];
                    B_tb     = pipe_B[cycle_count + 1];
                    valid_in = 1'b1;
                end else begin
                    valid_in = 1'b0;
                    A_tb     = 8'b0;
                    B_tb     = 8'b0;
                end
            end

            $display("  First valid_out at cycle: %0d (expected: 3)", first_valid_cycle);
            $display("  Total valid_out assertions: %0d (expected 5)", valid_count);

            if (first_valid_cycle == 3) begin
                $display("  Pipeline: latency PASS (3 cycles)");
            end else begin
                $display("  Pipeline: latency FAIL (first output at cycle %0d, expected 3)", first_valid_cycle);
                pipe_ok_int = 0;
            end

            if (valid_count == 5) begin
                $display("  Pipeline: valid_out count PASS (5 results received)");
            end else begin
                $display("  Pipeline: valid_out count FAIL (got %0d, expected 5)", valid_count);
                pipe_ok_int = 0;
            end

            // Verify outputs change each cycle (different input pairs)
            if (outputs_differ >= 4) begin
                $display("  Pipeline: output variation PASS (%0d distinct transitions)", outputs_differ);
            end else begin
                $display("  Pipeline: output variation NOTE (%0d distinct transitions)", outputs_differ);
            end
        end

        // -----------------------------------------------------------------
        // FINAL SUMMARY (Section 11.6)
        // -----------------------------------------------------------------
        $display("\n===== TESTBENCH SUMMARY =====");
        $display("Directed:  PASS=%0d  FAIL=%0d", dir_pass, dir_fail);
        $display("Random:    PASS=%0d  FAIL=%0d", rnd_pass, rnd_fail);
        $display("Pipeline:  %s", pipe_ok_int ? "PASS" : "FAIL");
        $display("P[3:0] hardwire: %s", hw_ok_int ? "PASS" : "FAIL");
        $display("==============================\n");

        #100;
        $finish;
    end

    // =========================================================================
    // TIMEOUT WATCHDOG
    // =========================================================================
    initial begin
        #1000000; // 1ms timeout
        $display("ERROR: Simulation timed out!");
        $finish;
    end

endmodule
