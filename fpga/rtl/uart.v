// -----------------------------------------------------------------------------
// uart.v : minimal 8N1 UART (TX + RX) for the FPGA side-channel target.
// CLKS_PER_BIT = f_clk / baud (e.g. 25 MHz / 115200 = 217).
// -----------------------------------------------------------------------------
module uart #(
    parameter CLKS_PER_BIT = 217
) (
    input  wire       clk,
    input  wire       rst,
    // transmitter
    input  wire       tx_start,
    input  wire [7:0] tx_data,
    output reg        tx_busy,
    output reg        txd,
    // receiver
    input  wire       rxd,
    output reg        rx_valid,     // one-cycle pulse
    output reg  [7:0] rx_data
);
    // ---------------- TX ----------------
    reg [15:0] tcnt;
    reg [3:0]  tbit;
    reg [9:0]  tsh;
    always @(posedge clk) begin
        if (rst) begin
            tx_busy <= 1'b0; txd <= 1'b1; tcnt <= 0; tbit <= 0;
        end else if (!tx_busy) begin
            if (tx_start) begin
                tsh <= {1'b1, tx_data, 1'b0};
                tx_busy <= 1'b1; tcnt <= 0; tbit <= 0;
            end
        end else begin
            txd <= tsh[0];
            if (tcnt == CLKS_PER_BIT - 1) begin
                tcnt <= 0;
                tsh  <= {1'b1, tsh[9:1]};
                tbit <= tbit + 1;
                if (tbit == 4'd9) begin tx_busy <= 1'b0; txd <= 1'b1; end
            end else tcnt <= tcnt + 1;
        end
    end
    // ---------------- RX ----------------
    reg [1:0]  sync;
    reg [15:0] rcnt;
    reg [3:0]  rbit;
    reg        rbusy;
    reg [7:0]  rsh;
    always @(posedge clk) begin
        sync <= {sync[0], rxd};
        rx_valid <= 1'b0;
        if (rst) begin
            rbusy <= 1'b0; rcnt <= 0; rbit <= 0; sync <= 2'b11;
        end else if (!rbusy) begin
            if (!sync[1]) begin rbusy <= 1'b1; rcnt <= CLKS_PER_BIT / 2; rbit <= 0; end
        end else if (rcnt == CLKS_PER_BIT - 1) begin
            rcnt <= 0;
            rbit <= rbit + 1;
            if (rbit == 4'd0) begin
                if (sync[1]) rbusy <= 1'b0;          // false start bit
            end else if (rbit <= 4'd8) rsh <= {sync[1], rsh[7:1]};
            else begin
                rbusy <= 1'b0;
                if (sync[1]) begin rx_valid <= 1'b1; rx_data <= rsh; end
            end
        end else rcnt <= rcnt + 1;
    end
endmodule
