// -----------------------------------------------------------------------------
// kyber_ise.v
// Lightweight RISC-V ISE unit for ML-KEM (FIPS 203, q = 3329) with
// on-demand side-channel mitigations. Attaches to PicoRV32 through PCPI.
//
// All instructions use the custom-0 major opcode (0001011), R-type.
// Coefficients are packed two per register: rs = {c[2i+1], c[2i]} in 16-bit
// lanes (12 bits used), canonical in [0, q).
//
//   funct3 funct7   mnemonic   semantics (zeta = internal Z register)
//   000    0000000  kct.a      CT butterfly x2: rd = {a1+z*b1, a0+z*b0}; B <= {a1-z*b1, a0-z*b0}
//   001    0000000  kct.b      rd = B   (second half of the last butterfly)
//   010    0000000  kgs.a      GS butterfly x2: rd = {a1+b1, a0+b0};     B <= {z*(a1-b1), z*(a0-b0)}
//   011    0000000  kgs.b      rd = B
//   100    0000000  kbmul      degree-1 base multiply: rd = {a0*b1 + a1*b0, a0*b0 + z*a1*b1}
//   101    0000000  kmulz      rd = {z*x1, z*x0}
//   110    0000000  kaddq      rd = {a1+b1, a0+b0} mod q
//   110    0100000  ksubq      rd = {a1-b1, a0-b0} mod q
//   111    0000000  kzeta      Z <= rs1[11:0]
//   111    0000001  kcfg       CFG <= rs1            (mitigation control, see below)
//   111    0000010  kseed      LFSR <= rs1 (nonzero) (seed from TRNG in a real SoC)
//   111    0000011  krnd       rd = LFSR             (for software shuffling)
//   111    0000100  kstat      rd = number of dummy micro-ops executed
//   111    0000101  krng       rd = fresh 32-bit word from the masking PRNG (xoshiro128**,
//                              one new output per cycle; kseed also seeds it; a TRNG
//                              would reseed it in a real SoC)
//
// CFG register:
//   [0]     dummy_en   insert random dummy multiplications before each op
//   [1]     shuffle_en randomise the issue order of the micro-ops of each op
//   [2]     dvfs_req   request a randomised DVFS operating point (to PMU)
//   [7:4]   dummy_th   insert dummies when LFSR[3:0] < dummy_th
//   [10:8]  dummy_mask dummies per op = (LFSR[6:4] & dummy_mask) + 1   (1..8)
// The federated detector writes CFG only when it flags an anomalous window,
// so the nominal (benign) path pays no mitigation cost.
// -----------------------------------------------------------------------------
module kyber_ise (
    input  wire        clk,
    input  wire        resetn,
    // PicoRV32 PCPI
    input  wire        pcpi_valid,
    input  wire [31:0] pcpi_insn,
    input  wire [31:0] pcpi_rs1,
    input  wire [31:0] pcpi_rs2,
    output reg         pcpi_wr,
    output reg  [31:0] pcpi_rd,
    output reg         pcpi_wait,
    output reg         pcpi_ready,
    // mitigation side band
    output wire        dvfs_req,
    output wire        mitig_active
);
    localparam [11:0] Q = 12'd3329;
    wire rst = ~resetn;

    // ---------------- decode ----------------
    wire       is_ise = pcpi_valid && (pcpi_insn[6:0] == 7'b0001011);
    wire [2:0] f3     = pcpi_insn[14:12];
    wire [6:0] f7     = pcpi_insn[31:25];

    localparam OP_CT = 3'd0, OP_CTB = 3'd1, OP_GS = 3'd2, OP_GSB = 3'd3,
               OP_BM = 3'd4, OP_MZ  = 3'd5, OP_ADD = 3'd6, OP_SYS = 3'd7;

    // ---------------- architectural state ----------------
    reg [11:0] zreg;
    reg [10:0] cfg;
    reg [31:0] lfsr;
    reg [31:0] breg;
    reg [31:0] dummy_cnt;

    assign dvfs_req     = cfg[2];
    assign mitig_active = cfg[0] | cfg[1] | cfg[2];

    // 32-bit maximal-length Galois LFSR, taps 32,22,2,1 (0x80200003)
    wire [31:0] lfsr_nx = lfsr[0] ? ((lfsr >> 1) ^ 32'h80200003) : (lfsr >> 1);

    // masking PRNG: xoshiro128** (output = rotl(s1 * 5, 7) * 9), advanced every cycle
    reg  [31:0] xs0, xs1, xs2, xs3;
    wire [31:0] x5   = (xs1 << 2) + xs1;
    wire [31:0] xr7  = {x5[24:0], x5[31:25]};
    wire [31:0] xout = (xr7 << 3) + xr7;
    wire [31:0] xa2  = xs2 ^ xs0;
    wire [31:0] xa3  = xs3 ^ xs1;
    wire [31:0] xn1  = xs1 ^ xa2;
    wire [31:0] xn0  = xs0 ^ xa3;
    wire [31:0] xn2  = xa2 ^ (xs1 << 9);
    wire [31:0] xn3  = {xa3[20:0], xa3[31:21]};

    // ---------------- modular add / sub helpers ----------------
    function [11:0] madd;
        input [11:0] a, b;
        reg   [12:0] s, t;
        begin
            s = a + b;
            t = s - Q;
            madd = t[12] ? s[11:0] : t[11:0];
        end
    endfunction
    function [11:0] msub;
        input [11:0] a, b;
        reg   [12:0] d;
        begin
            d = {1'b0, a} - {1'b0, b};
            msub = d[12] ? (d[11:0] + Q) : d[11:0];
        end
    endfunction

    // ---------------- latched operands ----------------
    reg [2:0]  op;
    reg [11:0] a0, a1, b0, b1;

    // ---------------- multiplier ----------------
    reg         mm_v;
    reg  [11:0] mm_x, mm_y;
    reg  [3:0]  mm_tag;              // {dummy, slot[2:0]}
    wire        mr_v;
    wire [11:0] mr_r;
    wire [3:0]  mr_tag;

    kyber_modmul #(.TAGW(4)) u_mm (
        .clk(clk), .rst(rst),
        .in_valid(mm_v), .in_x(mm_x), .in_y(mm_y), .in_tag(mm_tag),
        .out_valid(mr_v), .out_r(mr_r), .out_tag(mr_tag)
    );

    // result slots
    reg [11:0] slot [0:4];
    reg [4:0]  done;
    reg [4:0]  issued;
    reg [2:0]  nslots;               // number of slots for current op
    reg [1:0]  rot;                  // issue-order rotation (shuffle)
    reg        swp;
    reg [3:0]  ndummy;
    reg [2:0]  inflight_dummy;

    // operands of each slot
    function [23:0] slot_ops;        // {x, y}
        input [2:0] s;
        begin
            case (op)
                OP_CT: slot_ops = (s == 3'd0) ? {zreg, b0} : {zreg, b1};
                OP_GS: slot_ops = (s == 3'd0) ? {zreg, msub(a0, b0)} : {zreg, msub(a1, b1)};
                OP_MZ: slot_ops = (s == 3'd0) ? {zreg, a0} : {zreg, a1};
                OP_BM: case (s)
                           3'd0: slot_ops = {a1, b1};
                           3'd1: slot_ops = {a0, b0};
                           3'd2: slot_ops = {a0, b1};
                           3'd3: slot_ops = {a1, b0};
                           default: slot_ops = {zreg, slot[0]};
                       endcase
                default: slot_ops = 24'd0;
            endcase
        end
    endfunction

    // next slot to issue for the independent slots (0..nslots_indep-1)
    wire [2:0] nindep = (op == OP_BM) ? 3'd4 : 3'd2;
    reg  [2:0] pick;
    reg        pick_ok;
    integer k;
    always @* begin
        pick    = 3'd0;
        pick_ok = 1'b0;
        // walk the (possibly rotated / swapped) issue order
        for (k = 3; k >= 0; k = k - 1) begin : walk
            reg [2:0] cand;
            if (nindep == 3'd4) cand = (k[1:0] + rot) & 3'd3;
            else                cand = (k[0] ^ swp) & 3'd1;
            if (k < nindep && !issued[cand]) begin
                pick    = cand;
                pick_ok = 1'b1;
            end
        end
        // dependent slot of kbmul: z * (a1*b1)
        if (!pick_ok && op == OP_BM && !issued[4] && done[0]) begin
            pick    = 3'd4;
            pick_ok = 1'b1;
        end
    end

    // ---------------- control FSM ----------------
    localparam S_IDLE = 2'd0, S_DUMMY = 2'd1, S_RUN = 2'd2, S_DONE = 2'd3;
    reg [1:0] state;

    wire [4:0] need = (op == OP_BM) ? 5'b11111 : 5'b00011;
    wire       all_done = ((done & need) == need) && (inflight_dummy == 3'd0);

    always @(posedge clk) begin
        if (rst) begin
            state      <= S_IDLE;
            pcpi_ready <= 1'b0;
            pcpi_wr    <= 1'b0;
            pcpi_wait  <= 1'b0;
            pcpi_rd    <= 32'd0;
            zreg       <= 12'd0;
            cfg        <= 11'd0;
            lfsr       <= 32'hACE1_2468;
            xs0 <= 32'h9E3779B9; xs1 <= 32'h243F6A88; xs2 <= 32'hB7E15162; xs3 <= 32'h8AED2A6B;
            breg       <= 32'd0;
            dummy_cnt  <= 32'd0;
            mm_v       <= 1'b0;
            done       <= 5'd0;
            issued     <= 5'd0;
            inflight_dummy <= 3'd0;
        end else begin
            pcpi_ready <= 1'b0;
            pcpi_wr    <= 1'b0;
            mm_v       <= 1'b0;
            lfsr       <= lfsr_nx;
            xs0 <= xn0; xs1 <= xn1; xs2 <= xn2; xs3 <= xn3;

            // dummy multiplications in flight (issued in S_DUMMY, retired at output)
            inflight_dummy <= inflight_dummy + ((state == S_DUMMY) ? 3'd1 : 3'd0)
                                             - ((mr_v && mr_tag[3]) ? 3'd1 : 3'd0);

            // collect multiplier results
            if (mr_v) begin
                if (!mr_tag[3]) begin
                    slot[mr_tag[2:0]] <= mr_r;
                    done[mr_tag[2:0]] <= 1'b1;
                end
            end

            case (state)
            S_IDLE: begin
                if (is_ise && !pcpi_ready) begin
                    op <= f3;
                    a0 <= pcpi_rs1[11:0];  a1 <= pcpi_rs1[27:16];
                    b0 <= pcpi_rs2[11:0];  b1 <= pcpi_rs2[27:16];
                    done   <= 5'd0;
                    issued <= 5'd0;
                    rot    <= cfg[1] ? lfsr[9:8] : 2'd0;
                    swp    <= cfg[1] ? lfsr[10]  : 1'b0;
                    case (f3)
                    OP_CTB, OP_GSB: begin
                        pcpi_rd <= breg; pcpi_wr <= 1'b1; pcpi_ready <= 1'b1;
                    end
                    OP_ADD: begin
                        pcpi_rd <= f7[5] ?
                            {4'd0, msub(pcpi_rs1[27:16], pcpi_rs2[27:16]), 4'd0, msub(pcpi_rs1[11:0], pcpi_rs2[11:0])} :
                            {4'd0, madd(pcpi_rs1[27:16], pcpi_rs2[27:16]), 4'd0, madd(pcpi_rs1[11:0], pcpi_rs2[11:0])};
                        pcpi_wr <= 1'b1; pcpi_ready <= 1'b1;
                    end
                    OP_SYS: begin
                        case (f7[2:0])
                        3'd0: begin zreg <= pcpi_rs1[11:0]; pcpi_wr <= 1'b0; end
                        3'd1: begin cfg  <= pcpi_rs1[10:0]; pcpi_wr <= 1'b0; end
                        3'd2: begin lfsr <= (pcpi_rs1 == 32'd0) ? 32'h1 : pcpi_rs1; pcpi_wr <= 1'b0;
                                    xs0 <= pcpi_rs1 ^ 32'h9E3779B9; xs1 <= ~pcpi_rs1; xs2 <= 32'hB7E15162; xs3 <= 32'h8AED2A6B; end
                        3'd3: begin pcpi_rd <= lfsr; pcpi_wr <= 1'b1; end
                        3'd5: begin pcpi_rd <= xout; pcpi_wr <= 1'b1; end
                        default: begin pcpi_rd <= dummy_cnt; pcpi_wr <= 1'b1; end
                        endcase
                        pcpi_ready <= 1'b1;
                    end
                    default: begin   // multiplier ops
                        pcpi_wait <= 1'b1;
                        if (cfg[0] && (lfsr[3:0] < cfg[7:4])) begin
                            ndummy <= {1'b0, (lfsr[6:4] & cfg[10:8])} + 4'd1;
                            state  <= S_DUMMY;
                        end else begin
                            state  <= S_RUN;
                        end
                    end
                    endcase
                end
            end

            S_DUMMY: begin
                // random-operand multiplications: same datapath, same power signature
                mm_v   <= 1'b1;
                mm_x   <= (lfsr[11:0]  >= Q) ? (lfsr[11:0]  - Q) : lfsr[11:0];
                mm_y   <= (lfsr[23:12] >= Q) ? (lfsr[23:12] - Q) : lfsr[23:12];
                mm_tag <= 4'b1000;
                dummy_cnt <= dummy_cnt + 32'd1;
                ndummy <= ndummy - 4'd1;
                if (ndummy == 4'd1) state <= S_RUN;
            end

            S_RUN: begin
                if (pick_ok) begin
                    mm_v   <= 1'b1;
                    {mm_x, mm_y} <= slot_ops(pick);
                    mm_tag <= {1'b0, pick};
                    issued[pick] <= 1'b1;
                end
                if (all_done) state <= S_DONE;
            end

            S_DONE: begin
                case (op)
                OP_CT: begin
                    pcpi_rd <= {4'd0, madd(a1, slot[1]), 4'd0, madd(a0, slot[0])};
                    breg    <= {4'd0, msub(a1, slot[1]), 4'd0, msub(a0, slot[0])};
                end
                OP_GS: begin
                    pcpi_rd <= {4'd0, madd(a1, b1), 4'd0, madd(a0, b0)};
                    breg    <= {4'd0, slot[1], 4'd0, slot[0]};
                end
                OP_MZ:  pcpi_rd <= {4'd0, slot[1], 4'd0, slot[0]};
                default: // OP_BM
                    pcpi_rd <= {4'd0, madd(slot[2], slot[3]), 4'd0, madd(slot[1], slot[4])};
                endcase
                pcpi_wr    <= 1'b1;
                pcpi_ready <= 1'b1;
                pcpi_wait  <= 1'b0;
                state      <= S_IDLE;
            end
            endcase
        end
    end
endmodule
