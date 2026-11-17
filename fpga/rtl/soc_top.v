// -----------------------------------------------------------------------------
// soc_top.v : FPGA side-channel target SoC
//   PicoRV32 (RV32IM, same configuration as the ASIC flow) + kyber_ise (custom-0)
//   + keccak_ise (custom-1), on-chip RAM initialised with the firmware image,
//   UART, a scope trigger and LEDs.
// Memory map
//   0x0000_0000  RAM (MEM_WORDS x 32 bit)
//   0x1000_0000  UART TX data      (write; the bus stalls while the UART is busy)
//   0x1000_0004  UART RX           (read: bit 8 = byte valid, bits 7:0 = byte; read clears)
//   0x2000_0000  exit / status LED (write)
//   0x3000_0000  trigger           (write bit 0: scope trigger output level)
// Same addresses as tb/tb_soc.v, so the firmware runs unchanged in simulation.
// -----------------------------------------------------------------------------
module soc_top #(
    parameter MEM_WORDS    = 32768,            // 128 KiB
    parameter FIRMWARE     = "firmware.hex",
    parameter CLKS_PER_BIT = 217
) (
    input  wire       clk,
    input  wire       resetn,
    input  wire       uart_rxd,
    output wire       uart_txd,
    output reg        trigger,
    output reg  [3:0] led
);
    wire        mem_valid, mem_instr;
    reg         mem_ready;
    wire [31:0] mem_addr, mem_wdata;
    wire [3:0]  mem_wstrb;
    reg  [31:0] mem_rdata;
    wire        pcpi_valid;
    wire [31:0] pcpi_insn, pcpi_rs1, pcpi_rs2;
    wire        k_wr, k_wait, k_ready, h_wr, h_wait, h_ready;
    wire [31:0] k_rd, h_rd;
    wire        dvfs_req, mitig_active, trap;

    picorv32 #(
        .ENABLE_COUNTERS(1), .ENABLE_COUNTERS64(0), .BARREL_SHIFTER(1),
        .ENABLE_PCPI(1), .ENABLE_MUL(0), .ENABLE_FAST_MUL(1), .ENABLE_DIV(1),
        .COMPRESSED_ISA(0), .ENABLE_IRQ(0), .CATCH_MISALIGN(1), .CATCH_ILLINSN(1),
        .PROGADDR_RESET(32'h0), .STACKADDR(4 * MEM_WORDS)
    ) cpu (
        .clk(clk), .resetn(resetn), .trap(trap),
        .mem_valid(mem_valid), .mem_instr(mem_instr), .mem_ready(mem_ready),
        .mem_addr(mem_addr), .mem_wdata(mem_wdata), .mem_wstrb(mem_wstrb), .mem_rdata(mem_rdata),
        .pcpi_valid(pcpi_valid), .pcpi_insn(pcpi_insn), .pcpi_rs1(pcpi_rs1), .pcpi_rs2(pcpi_rs2),
        .pcpi_wr(k_wr | h_wr), .pcpi_rd(h_ready ? h_rd : k_rd),
        .pcpi_wait(k_wait | h_wait), .pcpi_ready(k_ready | h_ready),
        .irq(32'b0)
    );
    kyber_ise ise (
        .clk(clk), .resetn(resetn),
        .pcpi_valid(pcpi_valid), .pcpi_insn(pcpi_insn), .pcpi_rs1(pcpi_rs1), .pcpi_rs2(pcpi_rs2),
        .pcpi_wr(k_wr), .pcpi_rd(k_rd), .pcpi_wait(k_wait), .pcpi_ready(k_ready),
        .dvfs_req(dvfs_req), .mitig_active(mitig_active)
    );
    keccak_ise kise (
        .clk(clk), .resetn(resetn),
        .pcpi_valid(pcpi_valid), .pcpi_insn(pcpi_insn), .pcpi_rs1(pcpi_rs1), .pcpi_rs2(pcpi_rs2),
        .pcpi_wr(h_wr), .pcpi_rd(h_rd), .pcpi_wait(h_wait), .pcpi_ready(h_ready)
    );

    // ---------------- RAM (inferred block RAM, byte enables) ----------------
    reg [31:0] ram [0:MEM_WORDS-1];
    initial $readmemh(FIRMWARE, ram);
    wire is_ram = mem_addr < 4 * MEM_WORDS;
    wire [$clog2(MEM_WORDS)-1:0] widx = mem_addr[$clog2(MEM_WORDS)+1:2];
    reg  [31:0] ram_q;
    always @(posedge clk) begin
        if (mem_valid && is_ram && !mem_ready) begin
            if (mem_wstrb[0]) ram[widx][ 7: 0] <= mem_wdata[ 7: 0];
            if (mem_wstrb[1]) ram[widx][15: 8] <= mem_wdata[15: 8];
            if (mem_wstrb[2]) ram[widx][23:16] <= mem_wdata[23:16];
            if (mem_wstrb[3]) ram[widx][31:24] <= mem_wdata[31:24];
        end
        ram_q <= ram[widx];
    end

    // ---------------- UART ----------------
    wire       tx_busy, rx_valid;
    wire [7:0] rx_data;
    reg        tx_start;
    reg  [7:0] tx_data;
    reg        rx_full;
    reg  [7:0] rx_byte;
    uart #(.CLKS_PER_BIT(CLKS_PER_BIT)) u_uart (
        .clk(clk), .rst(!resetn),
        .tx_start(tx_start), .tx_data(tx_data), .tx_busy(tx_busy), .txd(uart_txd),
        .rxd(uart_rxd), .rx_valid(rx_valid), .rx_data(rx_data)
    );

    // ---------------- bus ----------------
    // RAM reads take two cycles (registered block RAM output)
    reg ram_pend;
    always @(posedge clk) begin
        mem_ready <= 1'b0;
        tx_start  <= 1'b0;
        if (rx_valid) begin rx_full <= 1'b1; rx_byte <= rx_data; end
        if (!resetn) begin
            ram_pend <= 1'b0; trigger <= 1'b0; led <= 4'b0001; rx_full <= 1'b0;
        end else if (mem_valid && !mem_ready) begin
            if (is_ram) begin
                if (|mem_wstrb) mem_ready <= 1'b1;
                else if (!ram_pend) ram_pend <= 1'b1;
                else begin ram_pend <= 1'b0; mem_rdata <= ram_q; mem_ready <= 1'b1; end
            end else begin
                case (mem_addr)
                32'h1000_0000: if (!tx_busy && !tx_start) begin
                                   tx_start <= 1'b1; tx_data <= mem_wdata[7:0]; mem_ready <= 1'b1;
                               end
                32'h1000_0004: begin
                                   mem_rdata <= {23'd0, rx_full, rx_byte}; mem_ready <= 1'b1;
                                   if (rx_full && !rx_valid) rx_full <= 1'b0;
                               end
                32'h2000_0000: begin led <= {mem_wdata[2:0] == 3'd0, 3'b100}; mem_ready <= 1'b1; end
                32'h3000_0000: begin trigger <= mem_wdata[0]; mem_ready <= 1'b1; end
                default:       begin mem_rdata <= 32'd0; mem_ready <= 1'b1; end
                endcase
            end
        end
        if (trap) led[1] <= 1'b1;
    end
endmodule
