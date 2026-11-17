// -----------------------------------------------------------------------------
// kyber_modmul.v
// 3-stage pipelined modular multiplier for ML-KEM (q = 3329).
//   r = (x * y) mod q,  x, y in [0, q)
// Barrett reduction with k = 24, m = floor(2^24 / q) = 5039.
// For p = x*y < q^2 < 2^24 the quotient estimate is off by at most one,
// so a single conditional subtraction gives the canonical result in [0, q).
// The tag travels with the data so the sequencer can match results to slots.
// -----------------------------------------------------------------------------
module kyber_modmul #(
    parameter TAGW = 4
) (
    input  wire            clk,
    input  wire            rst,
    input  wire            in_valid,
    input  wire [11:0]     in_x,
    input  wire [11:0]     in_y,
    input  wire [TAGW-1:0] in_tag,
    output reg             out_valid,
    output reg  [11:0]     out_r,
    output reg  [TAGW-1:0] out_tag
);
    localparam [11:0] Q = 12'd3329;
    localparam [12:0] M = 13'd5039;

    // ---------------- stage 1: integer product ----------------
    reg            s1_v;
    reg [23:0]     s1_p;
    reg [TAGW-1:0] s1_tag;
    always @(posedge clk) begin
        if (rst) begin
            s1_v <= 1'b0;
        end else begin
            s1_v   <= in_valid;
            s1_p   <= in_x * in_y;
            s1_tag <= in_tag;
        end
    end

    // ---------------- stage 2: Barrett quotient estimate --------
    wire [36:0] s1_pm = s1_p * M;          // < 2^37
    reg            s2_v;
    reg [23:0]     s2_p;
    reg [12:0]     s2_t;                   // floor(p*m / 2^24) <= 3328
    reg [TAGW-1:0] s2_tag;
    always @(posedge clk) begin
        if (rst) begin
            s2_v <= 1'b0;
        end else begin
            s2_v   <= s1_v;
            s2_p   <= s1_p;
            s2_t   <= s1_pm[36:24];
            s2_tag <= s1_tag;
        end
    end

    // ---------------- stage 3: remainder and correction ---------
    // q = 2^11 + 2^10 + 2^8 + 1, so t*q is three shifts and adds
    wire [24:0] s2_tq  = {s2_t, 11'b0} + {s2_t, 10'b0} + {s2_t, 8'b0} + s2_t;
    wire [13:0] s2_r0  = s2_p[13:0] - s2_tq[13:0];   // true value < 2q < 2^13
    wire [13:0] s2_r1  = s2_r0 - {2'b00, Q};
    wire [11:0] s2_r   = s2_r1[13] ? s2_r0[11:0] : s2_r1[11:0];
    always @(posedge clk) begin
        if (rst) begin
            out_valid <= 1'b0;
        end else begin
            out_valid <= s2_v;
            out_r     <= s2_r;
            out_tag   <= s2_tag;
        end
    end
endmodule
