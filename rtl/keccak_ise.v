// -----------------------------------------------------------------------------
// keccak_ise.v
// Keccak-f[1600] coprocessor for PicoRV32 (PCPI), custom-1 opcode (0101011).
// The 1600-bit state lives in the unit; one round per clock (24 cycles per
// permutation). To keep the unit small there is no word addressing: the state
// is a 50 x 32-bit shift chain. Word 2i is the low half of lane i, word 2i+1
// the high half (lane i = x + 5y, FIPS 202 order).
//
//   funct3  mnemonic  semantics
//   000     kk.swap   rd <= S[31:0];  S <= {rs1, S[1599:32]}
//   010     kk.perm   S <= Keccak-f[1600](S)   (multi-cycle, 24 rounds)
// 50 swaps load a state (word 0 first) and, after kk.perm, 50 swaps read it
// back in the same order. The state has no reset: software always loads it.
// -----------------------------------------------------------------------------
module keccak_ise (
    input  wire        clk,
    input  wire        resetn,
    input  wire        pcpi_valid,
    input  wire [31:0] pcpi_insn,
    input  wire [31:0] pcpi_rs1,
    input  wire [31:0] pcpi_rs2,
    output reg         pcpi_wr,
    output reg  [31:0] pcpi_rd,
    output reg         pcpi_wait,
    output reg         pcpi_ready
);
    wire is_kk = pcpi_valid && (pcpi_insn[6:0] == 7'b0101011);
    wire [2:0] f3 = pcpi_insn[14:12];

    reg  [1599:0] st;
    reg  [4:0]    rnd;
    reg           busy;

    function [63:0] rc;
        input [4:0] r;
        case (r)
            5'd0:  rc = 64'h0000000000000001; 5'd1:  rc = 64'h0000000000008082;
            5'd2:  rc = 64'h800000000000808A; 5'd3:  rc = 64'h8000000080008000;
            5'd4:  rc = 64'h000000000000808B; 5'd5:  rc = 64'h0000000080000001;
            5'd6:  rc = 64'h8000000080008081; 5'd7:  rc = 64'h8000000000008009;
            5'd8:  rc = 64'h000000000000008A; 5'd9:  rc = 64'h0000000000000088;
            5'd10: rc = 64'h0000000080008009; 5'd11: rc = 64'h000000008000000A;
            5'd12: rc = 64'h000000008000808B; 5'd13: rc = 64'h800000000000008B;
            5'd14: rc = 64'h8000000000008089; 5'd15: rc = 64'h8000000000008003;
            5'd16: rc = 64'h8000000000008002; 5'd17: rc = 64'h8000000000000080;
            5'd18: rc = 64'h000000000000800A; 5'd19: rc = 64'h800000008000000A;
            5'd20: rc = 64'h8000000080008081; 5'd21: rc = 64'h8000000000008080;
            5'd22: rc = 64'h0000000080000001; default: rc = 64'h8000000080008008;
        endcase
    endfunction

    // rotation offsets r[x][y], indexed by lane = x + 5y
    function [5:0] rho;
        input integer l;
        case (l)
            0: rho = 0;  1: rho = 1;  2: rho = 62; 3: rho = 28; 4: rho = 27;
            5: rho = 36; 6: rho = 44; 7: rho = 6;  8: rho = 55; 9: rho = 20;
            10: rho = 3; 11: rho = 10; 12: rho = 43; 13: rho = 25; 14: rho = 39;
            15: rho = 41; 16: rho = 45; 17: rho = 15; 18: rho = 21; 19: rho = 8;
            20: rho = 18; 21: rho = 2; 22: rho = 61; 23: rho = 56; default: rho = 14;
        endcase
    endfunction

    function [63:0] rotl;
        input [63:0] v;
        input [5:0]  n;
        rotl = (n == 0) ? v : ((v << n) | (v >> (64 - n)));
    endfunction

    // ---------------- one round (combinational) ----------------
    reg [63:0] A [0:24];
    reg [63:0] B [0:24];
    reg [63:0] C [0:4];
    reg [63:0] D [0:4];
    reg [1599:0] nxt;
    integer x, y;
    always @* begin
        for (x = 0; x < 25; x = x + 1) A[x] = st[64 * x +: 64];
        for (x = 0; x < 5; x = x + 1) C[x] = A[x] ^ A[x + 5] ^ A[x + 10] ^ A[x + 15] ^ A[x + 20];
        for (x = 0; x < 5; x = x + 1) D[x] = C[(x + 4) % 5] ^ rotl(C[(x + 1) % 5], 6'd1);
        // theta + rho + pi: B[y, 2x+3y] = rot(A[x,y] ^ D[x], r[x,y])
        for (x = 0; x < 5; x = x + 1)
            for (y = 0; y < 5; y = y + 1)
                B[y + 5 * ((2 * x + 3 * y) % 5)] = rotl(A[x + 5 * y] ^ D[x], rho(x + 5 * y));
        // chi + iota
        for (x = 0; x < 5; x = x + 1)
            for (y = 0; y < 5; y = y + 1)
                nxt[64 * (x + 5 * y) +: 64] = B[x + 5 * y] ^ (~B[(x + 1) % 5 + 5 * y] & B[(x + 2) % 5 + 5 * y]);
        nxt[63:0] = nxt[63:0] ^ rc(rnd);
    end

    // ---------------- state register ----------------
    wire st_en = busy | (is_kk && !pcpi_ready && f3 == 3'd0);
`ifdef KECCAK_CG
    // clock-gated state: the 1600 state flops are clocked only while the unit
    // permutes or shifts (integrated clock gate, latch + AND); no feedback muxes
    wire gclk;
    kk_icg icg (.CK(clk), .E(st_en), .GCK(gclk));
    always @(posedge gclk) st <= busy ? nxt : {pcpi_rs1, st[1599:32]};
`else
    always @(posedge clk) begin
        if (busy) st <= nxt;
        else if (st_en) st <= {pcpi_rs1, st[1599:32]};
    end
`endif
    always @(posedge clk) begin
        if (!resetn) begin
            rnd <= 5'd0; busy <= 1'b0;
            pcpi_wr <= 1'b0; pcpi_ready <= 1'b0; pcpi_wait <= 1'b0; pcpi_rd <= 32'd0;
        end else begin
            pcpi_wr <= 1'b0;
            pcpi_ready <= 1'b0;
            if (busy) begin
                rnd <= rnd + 5'd1;
                if (rnd == 5'd23) begin
                    busy <= 1'b0; pcpi_wait <= 1'b0; pcpi_ready <= 1'b1;
                end
            end else if (is_kk && !pcpi_ready) begin
                case (f3)
                3'd0: begin pcpi_rd <= st[31:0]; pcpi_wr <= 1'b1; pcpi_ready <= 1'b1; end
                3'd2: begin busy <= 1'b1; rnd <= 5'd0; pcpi_wait <= 1'b1; end
                default: pcpi_ready <= 1'b1;
                endcase
            end
        end
    end
endmodule

`ifdef KECCAK_CG
// clock gate: latch (transparent while CK is low) + AND, synthesized to DLL_X1 + AND2_X1;
// -DKK_ICG_CELL instantiates the NanGate45 CLKGATE_X1 integrated cell instead
module kk_icg (input wire CK, input wire E, output wire GCK);
`ifdef KK_ICG_CELL
    (* keep *) CLKGATE_X1 cg (.CK(CK), .E(E), .GCK(GCK));
`else
    reg en_l;
    always @(CK or E) if (!CK) en_l = E;
    assign GCK = CK & en_l;
`endif
endmodule
`endif
