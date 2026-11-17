// tb_fpga.v : protocol-level test of fpga/rtl/soc_top.v with a UART host model.
`timescale 1ns/1ps
module tb_fpga;
    localparam CPB = 8;                      // fast UART for simulation
    reg clk = 0, resetn = 0;
    always #20 clk = ~clk;                   // 25 MHz
    reg  host_tx = 1'b1;
    wire host_rx, trig;
    wire [3:0] led;
    soc_top #(.MEM_WORDS(32768), .FIRMWARE("../../sw/build/sca_app.hex"), .CLKS_PER_BIT(CPB)) dut (
        .clk(clk), .resetn(resetn), .uart_rxd(host_tx), .uart_txd(host_rx), .trigger(trig), .led(led));

    reg [7:0] vec [0:64+800+768+32-1];
    initial $readmemh("vec.hex", vec);

    task sendb(input [7:0] b); integer k; begin
        host_tx = 0; repeat (CPB) @(posedge clk);
        for (k = 0; k < 8; k = k + 1) begin host_tx = b[k]; repeat (CPB) @(posedge clk); end
        host_tx = 1; repeat (2 * CPB) @(posedge clk);
    end endtask
    task recvb(output [7:0] b); integer k; begin
        @(negedge host_rx); repeat (CPB + CPB / 2) @(posedge clk);
        for (k = 0; k < 8; k = k + 1) begin b[k] = host_rx; repeat (CPB) @(posedge clk); end
    end endtask

    integer i, errs = 0, m;
    reg [7:0] b;
    reg [63:0] t0, trig_cyc;
    reg [63:0] cyc = 0;
    always @(posedge clk) begin cyc <= cyc + 1; if (trig) trig_cyc <= trig_cyc + 1; end
    always @(posedge clk) if (cyc % 64'd2000000 == 0) begin $display("progress cyc=%0d pc=%08x led=%b", cyc, dut.cpu.reg_pc, led); $fflush; end
    initial begin
        trig_cyc = 0;
        repeat (20) @(posedge clk); resetn = 1;
        recvb(b); if (b != "R") errs = errs + 1;          // wait for the ready banner
        // keygen
        sendb("K"); for (i = 0; i < 64; i = i + 1) sendb(vec[i]);
        recvb(b); if (b != "k") errs = errs + 1;
        for (i = 0; i < 800; i = i + 1) begin recvb(b); if (b != vec[64 + i]) errs = errs + 1; end
        $display("keygen done, pk mismatches so far: %0d", errs); $fflush;
        for (m = 0; m < 3; m = m + 1) begin
            sendb("M"); sendb(m); recvb(b);
            trig_cyc = 0;
            sendb("D"); for (i = 0; i < 768; i = i + 1) sendb(vec[864 + i]);
            recvb(b); if (b != "d") errs = errs + 1;
            for (i = 0; i < 32; i = i + 1) begin recvb(b); if (b != vec[1632 + i]) errs = errs + 1; end
            $display("mode %0d: decapsulation %0d cycles under trigger, errors so far %0d", m, trig_cyc, errs); $fflush;
        end
        sendb("M"); sendb(0); recvb(b);
        trig_cyc = 0; sendb("B"); for (i = 0; i < 8; i = i + 1) sendb(i * 37); recvb(b);
        $display("basemul window: %0d cycles under trigger, reply %c", trig_cyc, b);
        for (m = 0; m < 6; m = m + 1) begin
            trig_cyc = 0; sendb("T"); sendb(m); sendb(1); recvb(b);
            $display("TVLA target %0d: %0d cycles under trigger, reply %c", m, trig_cyc, b);
        end
        $display("RESULT %s errors=%0d", errs == 0 ? "PASS" : "FAIL", errs);
        $finish;
    end
endmodule
