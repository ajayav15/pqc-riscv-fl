// -----------------------------------------------------------------------------
// top_arty.v : Digilent Arty A7-35T / A7-100T top level for the side-channel target.
// 100 MHz board clock -> MMCM -> 25 MHz core clock (a low, stable clock makes
// power/EM traces cleaner; change CLKOUT0_DIVIDE_F for other rates and set
// CLKS_PER_BIT = f_core / 115200 accordingly).
// Trigger on Pmod JA pin 1 for the oscilloscope / ChipWhisperer.
// -----------------------------------------------------------------------------
module top_arty (
    input  wire       CLK100MHZ,
    input  wire       ck_rst,          // active-low reset button
    input  wire       uart_txd_in,     // from the USB-UART bridge (FPGA RX)
    output wire       uart_rxd_out,    // to the USB-UART bridge (FPGA TX)
    output wire       ja1,             // scope trigger
    output wire [3:0] led
);
    wire clk_fb, clk25_unbuf, clk25, locked;
    MMCME2_BASE #(
        .CLKIN1_PERIOD(10.0), .CLKFBOUT_MULT_F(10.0), .DIVCLK_DIVIDE(1),
        .CLKOUT0_DIVIDE_F(40.0)                       // 1000 MHz VCO / 40 = 25 MHz
    ) mmcm (
        .CLKIN1(CLK100MHZ), .CLKFBIN(clk_fb), .CLKFBOUT(clk_fb),
        .CLKOUT0(clk25_unbuf), .LOCKED(locked), .PWRDWN(1'b0), .RST(1'b0),
        .CLKOUT0B(), .CLKOUT1(), .CLKOUT1B(), .CLKOUT2(), .CLKOUT2B(), .CLKOUT3(),
        .CLKOUT3B(), .CLKOUT4(), .CLKOUT5(), .CLKOUT6(), .CLKFBOUTB()
    );
    BUFG bufg (.I(clk25_unbuf), .O(clk25));

    reg [3:0] rst_sync = 4'h0;
    always @(posedge clk25) rst_sync <= {rst_sync[2:0], locked & ck_rst};

    soc_top #(
        .MEM_WORDS(32768), .FIRMWARE("firmware.hex"), .CLKS_PER_BIT(217)
    ) soc (
        .clk(clk25), .resetn(rst_sync[3]),
        .uart_rxd(uart_txd_in), .uart_txd(uart_rxd_out),
        .trigger(ja1), .led(led)
    );
endmodule
