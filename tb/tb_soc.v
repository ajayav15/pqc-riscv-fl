// -----------------------------------------------------------------------------
// tb_soc.v : cycle-accurate RTL simulation of PicoRV32 (RV32IM) with the
// kyber_ise coprocessor on PCPI. Single-cycle SRAM, MMIO console/exit.
//   +fw=<hex>   firmware image (32-bit words)
//   define NO_ISE to build the baseline core without the extension
// -----------------------------------------------------------------------------
`timescale 1ns/1ps
module tb_soc;
    reg clk = 0, resetn = 0;
    always #5 clk = ~clk;

    wire        mem_valid, mem_instr;
    reg         mem_ready;
    wire [31:0] mem_addr, mem_wdata;
    wire [3:0]  mem_wstrb;
    reg  [31:0] mem_rdata;

    wire        pcpi_valid;
    wire [31:0] pcpi_insn, pcpi_rs1, pcpi_rs2;
    wire        pcpi_wr, pcpi_wait, pcpi_ready;
    wire [31:0] pcpi_rd;
    wire        dvfs_req, mitig_active;
    wire        trap;

`ifdef GATE
    picorv32 cpu (      // synthesized netlist: parameters are baked in (syn/run_syn.py)
`else
    picorv32 #(
        .ENABLE_COUNTERS(1), .ENABLE_COUNTERS64(0), .BARREL_SHIFTER(1),
        .ENABLE_PCPI(1), .ENABLE_MUL(0), .ENABLE_FAST_MUL(1), .ENABLE_DIV(1),
        .COMPRESSED_ISA(0), .ENABLE_IRQ(0), .CATCH_MISALIGN(1), .CATCH_ILLINSN(1),
        .PROGADDR_RESET(32'h0)
    ) cpu (
`endif
        .clk(clk), .resetn(resetn), .trap(trap),
        .mem_valid(mem_valid), .mem_instr(mem_instr), .mem_ready(mem_ready),
        .mem_addr(mem_addr), .mem_wdata(mem_wdata), .mem_wstrb(mem_wstrb), .mem_rdata(mem_rdata),
        .pcpi_valid(pcpi_valid), .pcpi_insn(pcpi_insn), .pcpi_rs1(pcpi_rs1), .pcpi_rs2(pcpi_rs2),
        .pcpi_wr(pcpi_wr), .pcpi_rd(pcpi_rd), .pcpi_wait(pcpi_wait), .pcpi_ready(pcpi_ready),
        .irq(32'b0)
    );
`ifndef NO_ISE
    // two coprocessors share the PCPI port: kyber_ise (custom-0) and keccak_ise (custom-1)
    wire        k_wr, k_wait, k_ready, h_wr, h_wait, h_ready;
    wire [31:0] k_rd, h_rd;
    kyber_ise ise (
        .clk(clk), .resetn(resetn),
        .pcpi_valid(pcpi_valid), .pcpi_insn(pcpi_insn), .pcpi_rs1(pcpi_rs1), .pcpi_rs2(pcpi_rs2),
        .pcpi_wr(k_wr), .pcpi_rd(k_rd), .pcpi_wait(k_wait), .pcpi_ready(k_ready),
        .dvfs_req(dvfs_req), .mitig_active(mitig_active)
    );
`ifndef NO_KECCAK
    keccak_ise kise (
        .clk(clk), .resetn(resetn),
        .pcpi_valid(pcpi_valid), .pcpi_insn(pcpi_insn), .pcpi_rs1(pcpi_rs1), .pcpi_rs2(pcpi_rs2),
        .pcpi_wr(h_wr), .pcpi_rd(h_rd), .pcpi_wait(h_wait), .pcpi_ready(h_ready)
    );
`else
    assign h_wr = 1'b0, h_rd = 32'd0, h_wait = 1'b0, h_ready = 1'b0;
`endif
    assign pcpi_wr    = k_wr | h_wr;
    assign pcpi_rd    = h_ready ? h_rd : k_rd;
    assign pcpi_wait  = k_wait | h_wait;
    assign pcpi_ready = k_ready | h_ready;
`else
    assign pcpi_wr = 1'b0, pcpi_rd = 32'd0, pcpi_wait = 1'b0, pcpi_ready = 1'b0;
    assign dvfs_req = 1'b0, mitig_active = 1'b0;
`endif

    // ---------------- memory ----------------
    localparam WORDS = 65536;      // 256 KiB
    reg [31:0] mem [0:WORDS-1];
    reg [1023:0] fw;
    integer i;
    initial begin
        for (i = 0; i < WORDS; i = i + 1) mem[i] = 32'd0;
        if (!$value$plusargs("fw=%s", fw)) fw = "bench.hex";
        $readmemh(fw, mem);
    end

`ifdef PROFILE
    // cycle-level PC profile: attribute every cycle to the instruction in flight
    reg [31:0] prof [0:WORDS-1];
    integer pi;
    initial for (pi = 0; pi < WORDS; pi = pi + 1) prof[pi] = 0;
    reg prof_on = 0;
    always @(posedge clk) if (resetn && prof_on) prof[cpu.reg_pc[17:2]] <= prof[cpu.reg_pc[17:2]] + 1;
    task dump_prof;
        integer f, j;
        begin
            f = $fopen("prof.txt", "w");
            for (j = 0; j < WORDS; j = j + 1) if (prof[j] != 0) $fwrite(f, "%08x %0d\n", j * 4, prof[j]);
            $fclose(f);
        end
    endtask
`endif
`ifdef LEAKTRACE
    // Simulated power side channel of the whole core (value + transition models).
    // Per cycle inside a MARK window: byte 0 = HW(register write) + HW(data-bus
    // read/write), byte 1 = HD(previous register write, this register write),
    // byte 2 = extended transition model: Hamming distance between the old and new
    // contents of every datapath state element that changes in this cycle (the
    // written register-file entry, reg_op1, reg_op2 (= PCPI rs1/rs2), reg_out,
    // alu_out_q, the store-data bus mem_wdata and the read-data bus mem_rdata).
    // Each window: 32-bit sample count, then the samples (3 bytes each), to leak.bin.
    integer lf = 0;
    reg leak_on = 0;
    reg [31:0] leak_n = 0, last_wr = 0;
    reg [7:0]  lv, ld, lx;
    reg [31:0] p_op1 = 0, p_op2 = 0, p_out = 0, p_aluq = 0, p_wd = 0, p_rd = 0;
    initial lf = $fopen("leak.bin", "wb");
    function [5:0] popc; input [31:0] v; integer b; begin popc = 0; for (b = 0; b < 32; b = b + 1) popc = popc + v[b]; end endfunction
    reg [23:0] samples [0:2097151];
    reg [31:0] spc [0:2097151];          // PC of every sample (first window only, for attribution)
    reg first_win = 1;
    always @(posedge clk) if (resetn && leak_on) begin
        lv = 0; ld = 0; lx = 0;
        if (cpu.cpuregs_write && cpu.latched_rd != 0) begin
            lv = popc(cpu.cpuregs_wrdata);
            ld = popc(cpu.cpuregs_wrdata ^ last_wr);
            last_wr <= cpu.cpuregs_wrdata;
            lx = popc(cpu.cpuregs_wrdata ^ cpu.cpuregs[cpu.latched_rd]);
        end
        if (mem_valid && mem_ready && !mem_instr) lv = lv + popc(|mem_wstrb ? mem_wdata : mem_rdata);
        lx = lx + popc(cpu.reg_op1 ^ p_op1) + popc(cpu.reg_op2 ^ p_op2) + popc(cpu.reg_out ^ p_out)
                + popc(cpu.alu_out_q ^ p_aluq) + popc(mem_wdata ^ p_wd) + popc(mem_rdata ^ p_rd);
        samples[leak_n] <= {lx, ld, lv};
        spc[leak_n] <= cpu.reg_pc;
        leak_n <= leak_n + 1;
    end
    always @(posedge clk) begin
        p_op1 <= cpu.reg_op1; p_op2 <= cpu.reg_op2; p_out <= cpu.reg_out;
        p_aluq <= cpu.alu_out_q; p_wd <= mem_wdata; p_rd <= mem_rdata;
    end
    task leak_flush;
        integer j;
        begin
            $fwrite(lf, "%c%c%c%c", leak_n[7:0], leak_n[15:8], leak_n[23:16], leak_n[31:24]);
            for (j = 0; j < leak_n; j = j + 1) $fwrite(lf, "%c%c%c", samples[j][7:0], samples[j][15:8], samples[j][23:16]);
            if (first_win) begin : pcdump
                integer pf;
                pf = $fopen("leakpc.txt", "w");
                for (j = 0; j < leak_n; j = j + 1) $fwrite(pf, "%08x\n", spc[j]);
                $fclose(pf);
                first_win = 0;
            end
        end
    endtask
`endif
    reg [63:0] cycles = 0;
    // per-window statistics (measurement windows opened/closed by MARK 0x1xx / 0x2xx)
    reg [63:0] win_start = 0;
    reg [63:0] w_ifetch = 0, w_load = 0, w_store = 0, w_ise = 0, w_isebusy = 0;   // free-running
    reg [63:0] s_ifetch = 0, s_load = 0, s_store = 0, s_ise = 0, s_isebusy = 0;   // snapshot at open
    reg [63:0] w_kken = 0, s_kken = 0;      // cycles in which the Keccak state register is enabled
`ifndef NO_ISE
`ifndef NO_KECCAK
`ifndef GATE
    always @(posedge clk) if (kise.st_en) w_kken <= w_kken + 1;
`endif
`endif
`endif
    always @(posedge clk) if (resetn && mem_valid && mem_ready && mem_addr < 4 * WORDS) begin
        if (mem_instr) w_ifetch <= w_ifetch + 1;
        else if (|mem_wstrb) w_store <= w_store + 1;
        else w_load <= w_load + 1;
    end
    always @(posedge clk) begin
        if (pcpi_ready) w_ise <= w_ise + 1;
        if (pcpi_wait) w_isebusy <= w_isebusy + 1;
    end
    reg [63:0] ise_busy = 0, ise_ops = 0;
    always @(posedge clk) begin
        cycles <= cycles + 1;
        if (pcpi_wait) ise_busy <= ise_busy + 1;
        if (pcpi_ready) ise_ops <= ise_ops + 1;
    end

    always @(posedge clk) begin
        mem_ready <= 1'b0;
        if (resetn && mem_valid && !mem_ready) begin
            mem_ready <= 1'b1;
            if (mem_addr < 4 * WORDS) begin
                mem_rdata <= mem[mem_addr >> 2];
                if (mem_wstrb[0]) mem[mem_addr >> 2][ 7: 0] <= mem_wdata[ 7: 0];
                if (mem_wstrb[1]) mem[mem_addr >> 2][15: 8] <= mem_wdata[15: 8];
                if (mem_wstrb[2]) mem[mem_addr >> 2][23:16] <= mem_wdata[23:16];
                if (mem_wstrb[3]) mem[mem_addr >> 2][31:24] <= mem_wdata[31:24];
            end else begin
                mem_rdata <= 32'd0;
                if (|mem_wstrb) begin
                    case (mem_addr)
                    32'h1000_0000: $write("%c", mem_wdata[7:0]);
                    32'h2000_0000: begin
                        $display("EXIT code=%0d cycles=%0d ise_ops=%0d ise_busy_cycles=%0d",
                                 mem_wdata, cycles, ise_ops, ise_busy);
`ifdef LEAKTRACE
                        $fclose(lf);
`endif
`ifdef PROFILE
                        dump_prof;
`endif
                        $finish;
                    end
                    32'h3000_0000: begin
`ifdef LEAKTRACE
                        if (mem_wdata == 32'h4C01) begin leak_on <= 1; leak_n <= 0; end
                        else if (mem_wdata == 32'h4C00) begin leak_on <= 0; leak_flush; end
                        else
`endif
                        $display("MARK %0d @%0d", mem_wdata, cycles);
                        // measurement windows: 0x100+id opens, 0x200+id closes.
                        // Gate level (-DCOVWIN): zero / dump the per-net toggle counters.
                        if (mem_wdata[9:8] == 2'b01) begin
`ifdef COVWIN
                            $c("Verilated::threadContextp()->coveragep()->zero();");
`endif
                            win_start = cycles;
                            s_ifetch = w_ifetch; s_load = w_load; s_store = w_store;
                            s_ise = w_ise; s_isebusy = w_isebusy; s_kken = w_kken;
                        end
                        if (mem_wdata[9:8] == 2'b10) begin
`ifdef COVWIN
                            $c("{ char b[64]; snprintf(b, sizeof b, \"cov_%d.dat\", (int)", mem_wdata[7:0],
                               "); Verilated::threadContextp()->coveragep()->write(b); }");
`endif
                            $display("WIN %0d cycles=%0d ifetch=%0d load=%0d store=%0d ise_ops=%0d ise_busy=%0d kk_en=%0d",
                                     mem_wdata[7:0], cycles - win_start, w_ifetch - s_ifetch, w_load - s_load,
                                     w_store - s_store, w_ise - s_ise, w_isebusy - s_isebusy, w_kken - s_kken);
                        end
`ifdef PROFILE
                        prof_on <= mem_wdata[0];
`endif
                    end
                    default: ;
                    endcase
                end
            end
        end
    end

    reg [63:0] maxcyc;
    initial begin
        if (!$value$plusargs("maxcyc=%d", maxcyc)) maxcyc = 64'd200_000_000;
        repeat (10) @(posedge clk);
        resetn <= 1'b1;
        wait (cycles >= maxcyc);
        $display("TIMEOUT after %0d cycles", cycles);
        $finish;
    end

    always @(posedge clk) if (resetn && trap) begin
`ifdef GATE
        $display("TRAP at cycle %0d", cycles);
`else
        $display("TRAP at cycle %0d pc=%08x", cycles, cpu.reg_pc);
`endif
        $finish;
    end
endmodule
