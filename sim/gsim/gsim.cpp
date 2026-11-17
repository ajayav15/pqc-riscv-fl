// gsim.cpp : timing-annotated, glitch-aware gate-level power simulator for the
// flattened PicoRV32 + kyber_ise NanGate45 netlist written by export.py.
//
// Each clock cycle is simulated event by event: flops update with their
// clock-to-Q delays, the testbench SRAM drives its outputs after T_SRAM, and
// every gate output changes after the NLDM delay of the input arc that caused
// it (rise/fall). Gates use the inertial delay model (a pulse shorter than the
// gate delay is filtered, as in Verilog gate primitives); every surviving
// output change, functional or glitch, costs the net's switching energy plus
// the driver's internal energy and is accumulated in time bins of the cycle.
// The testbench (single-cycle SRAM, MMIO console/exit/mark) is identical to
// tb/tb_soc.v, so cycle counts must match the RTL simulation exactly.
//
//   gsim <netlist.gnl> <firmware.hex> [-o leak.bin] [-period ps] [-maxcyc N] [-v]
// leak.bin: for every MARK 0x4C01 .. 0x4C00 window: uint32 ncycles, then per
// cycle NB uint16 values in units of 0.01 pJ: bins [0,1) [1,2) [2,4) [4,T) ns of
// the glitch-aware energy, then the zero-delay (settled-toggle) energy.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

struct Gate { uint64_t tt; int out; int in[6]; uint8_t nin; };
struct GateDel { int rise[6], fall[6]; };
struct FF { int d, q, qn, rq, fq, rqn, fqn; };
struct Ev { int t; uint32_t seq; int net; uint8_t val; int gate; };
struct EvCmp { bool operator()(const Ev &a, const Ev &b) const { return a.t != b.t ? a.t > b.t : a.seq > b.seq; } };

static int nnets;
static std::vector<double> E;
static std::vector<Gate> G;
static std::vector<GateDel> GD;
static std::vector<FF> F;
struct Fo { int gate; uint16_t rise, fall; uint8_t pin; };
static std::vector<int> fo_start;                        // CSR fan-out: net -> [fo_start, fo_start+1)
static std::vector<Fo> fo;
static std::vector<uint8_t> val;
static std::vector<uint32_t> pend;                       // per gate: seq of pending event (0 none)
static std::vector<uint8_t> pendv;
static double e_ck, e_leak_ns, e_clknet = 0;
static std::vector<int> port_clk, port_resetn, port_ready, port_rdata, port_irq, port_valid, port_instr,
    port_addr, port_wdata, port_wstrb, port_trap;

static const int NB = 4;
static const int BIN_EDGE[NB] = {1000, 2000, 4000, 1 << 30};
static double bins[NB + 1];
static uint32_t seqc = 1;
static const int TMAX = 1 << 16;                       // ps horizon of one cycle's events
static std::vector<std::vector<Ev>> bucket(TMAX);
static int t_hi = 0;
static uint64_t bmap[TMAX / 64];
static inline void qpush(const Ev &e) {
    int t = e.t < TMAX ? e.t : TMAX - 1;
    bucket[t].push_back(e); bmap[t >> 6] |= 1ull << (t & 63);
    if (t > t_hi) t_hi = t;
}
// zero-delay mode (outside measurement windows): levelized, event-driven
static std::vector<int> level;
static std::vector<std::vector<int>> lvq;
static std::vector<uint8_t> dirty;
static bool zd_mode = false;
static std::vector<int> touched;
static std::vector<int> ffd_start, ffd;                 // net -> flops with that D input (CSR)
static std::vector<int> dirty_ff; static std::vector<uint8_t> ff_dirty;
static std::vector<uint8_t> start_val, is_touched;
static long long n_events = 0, n_glitch_toggles = 0, n_toggles = 0;
static int max_settle = 0;

static inline int bin_of(int t) { return t < 1000 ? 0 : t < 2000 ? 1 : t < 4000 ? 2 : 3; }

static inline uint8_t eval(const Gate &g) {
    unsigned idx = 0;
    for (int k = 0; k < g.nin; k++) idx |= (unsigned)val[g.in[k]] << k;
    return (g.tt >> idx) & 1;
}

static inline void mark_ff(int net) {
    for (int k = ffd_start[net], ke = ffd_start[net + 1]; k < ke; k++) {
        int f = ffd[k];
        if (!ff_dirty[f]) { ff_dirty[f] = 1; dirty_ff.push_back(f); }
    }
}
static void set_net(int net, uint8_t v, int t) {
    if (val[net] == v) return;
    mark_ff(net);
    if (zd_mode) {
        val[net] = v;
        if (!is_touched[net]) { is_touched[net] = 1; start_val[net] = 1 - v; touched.push_back(net); }
        for (int k = fo_start[net], ke = fo_start[net + 1]; k < ke; k++) { int gi = fo[k].gate; if (!dirty[gi]) { dirty[gi] = 1; lvq[level[gi]].push_back(gi); } }
        return;
    }
    if (!is_touched[net]) { is_touched[net] = 1; start_val[net] = val[net]; touched.push_back(net); }
    val[net] = v;
    bins[bin_of(t)] += E[net];
    n_toggles++;
    if (t > max_settle) max_settle = t;
    for (int k = fo_start[net], ke = fo_start[net + 1]; k < ke; k++) {
        const Fo &fp = fo[k];
        int gi = fp.gate;
        const Gate &g = G[gi];
        uint8_t nv = eval(g);
        if (pend[gi]) pend[gi] = 0;                       // inertial: replace pending change
        uint8_t cur = val[g.out];
        if (nv != cur) {
            int d = nv ? fp.rise : fp.fall;
            uint32_t s = seqc++;
            pend[gi] = s; pendv[gi] = nv;
            qpush(Ev{t + d, s, g.out, nv, gi});
        }
    }
}

static void run_events() {
    if (zd_mode) {                                        // sources first, then levels in order
        for (int t = 0; t <= t_hi; t++) { for (auto &e : bucket[t]) set_net(e.net, e.val, 0); bucket[t].clear(); }
        for (int w = 0; w <= (t_hi >> 6); w++) bmap[w] = 0;
        t_hi = 0;
        for (size_t L = 0; L < lvq.size(); L++)
            for (size_t k = 0; k < lvq[L].size(); k++) {
                int gi = lvq[L][k]; dirty[gi] = 0;
                uint8_t nv = eval(G[gi]);
                if (nv != val[G[gi].out]) set_net(G[gi].out, nv, 0);
            }
        for (auto &v : lvq) v.clear();
        return;
    }
    for (int w = 0; w <= (t_hi >> 6); w++) {
      while (bmap[w]) {
        int t = (w << 6) + __builtin_ctzll(bmap[w]);
        for (size_t k = 0; k < bucket[t].size(); k++) {
            Ev e = bucket[t][k];
            n_events++;
            if (e.gate >= 0) {
                if (pend[e.gate] != e.seq) continue;      // cancelled
                pend[e.gate] = 0;
            }
            set_net(e.net, e.val, e.t);
        }
        bucket[t].clear();
        bmap[w] &= ~(1ull << (t & 63));
      }
    }
    t_hi = 0;
}

static void src(int net, uint8_t v, int t) {                // a source change (flop / input)
    if (net < 2) return;
    uint32_t s = seqc++;
    qpush(Ev{t, s, net, v, -1});
}

static std::vector<int> readbits(std::istringstream &ss, int n) {
    std::vector<int> b(n);
    for (int i = 0; i < n; i++) ss >> b[i];
    return b;
}

static void load_gnl(const char *path) {
    std::ifstream f(path);
    if (!f) { fprintf(stderr, "cannot open %s\n", path); exit(1); }
    std::string line;
    while (std::getline(f, line)) {
        std::istringstream ss(line);
        std::string k; ss >> k;
        if (k == "nets") ss >> nnets;
        else if (k == "e_ck") ss >> e_ck;
        else if (k == "e_leak_per_ns") ss >> e_leak_ns;
        else if (k == "P") {
            std::string name, dir; int n; ss >> name >> dir >> n;
            auto b = readbits(ss, n);
            if (name == "clk") port_clk = b; else if (name == "resetn") port_resetn = b;
            else if (name == "mem_ready") port_ready = b; else if (name == "mem_rdata") port_rdata = b;
            else if (name == "irq") port_irq = b; else if (name == "mem_valid") port_valid = b;
            else if (name == "mem_instr") port_instr = b; else if (name == "mem_addr") port_addr = b;
            else if (name == "mem_wdata") port_wdata = b; else if (name == "mem_wstrb") port_wstrb = b;
            else if (name == "trap") port_trap = b;
        } else if (k == "E") {
            E.resize(nnets);
            for (int i = 0; i < nnets; i++) ss >> E[i];
        } else if (k == "G") {
            Gate g; GateDel gd; std::string tt; int nin;
            ss >> g.out >> nin >> tt;
            g.nin = (uint8_t)nin;
            g.tt = std::stoull(tt, nullptr, 16);
            for (int i = 0; i < nin; i++) ss >> g.in[i] >> gd.rise[i] >> gd.fall[i];
            G.push_back(g); GD.push_back(gd);
        } else if (k == "F") {
            FF x; ss >> x.d >> x.q >> x.qn >> x.rq >> x.fq >> x.rqn >> x.fqn;
            F.push_back(x);
        }
    }
    fo_start.assign(nnets + 1, 0);
    for (auto &g : G) for (int k = 0; k < g.nin; k++) fo_start[g.in[k] + 1]++;
    for (int n = 0; n < nnets; n++) fo_start[n + 1] += fo_start[n];
    fo.resize(fo_start[nnets]);
    {
        std::vector<int> fill(fo_start.begin(), fo_start.end() - 1);
        for (size_t i = 0; i < G.size(); i++)
            for (int k = 0; k < G[i].nin; k++)
                fo[fill[G[i].in[k]]++] = Fo{(int)i, (uint16_t)GD[i].rise[k], (uint16_t)GD[i].fall[k], (uint8_t)k};
    }
    val.assign(nnets, 0);
    val[1] = 1;
    pend.assign(G.size(), 0); pendv.assign(G.size(), 0);
    start_val.assign(nnets, 0); is_touched.assign(nnets, 0);
    ffd_start.assign(nnets + 1, 0);
    for (auto &x : F) ffd_start[x.d + 1]++;
    for (int n = 0; n < nnets; n++) ffd_start[n + 1] += ffd_start[n];
    ffd.resize(F.size());
    {
        std::vector<int> fill(ffd_start.begin(), ffd_start.end() - 1);
        for (size_t i = 0; i < F.size(); i++) ffd[fill[F[i].d]++] = (int)i;
    }
    ff_dirty.assign(F.size(), 0);
    {   // gate levels (gates are written in topological order)
        std::vector<int> nlev(nnets, 0);
        level.assign(G.size(), 0);
        int mx = 0;
        for (size_t i = 0; i < G.size(); i++) {
            int l = 0;
            for (int k = 0; k < G[i].nin; k++) l = std::max(l, nlev[G[i].in[k]]);
            level[i] = l; nlev[G[i].out] = l + 1; mx = std::max(mx, l);
        }
        lvq.assign(mx + 1, {});
        dirty.assign(G.size(), 0);
    }
    E[0] = E[1] = 0;
    // ideal clock: the clock net is not simulated; its switching energy (CK pin and
    // wire capacitance, two transitions per cycle) and the flops' clock-pin internal
    // energy (e_ck) are added as a constant per cycle, as in analysis/gate_energy.py
    if (!port_clk.empty()) { e_clknet = 2.0 * E[port_clk[0]]; E[port_clk[0]] = 0; }
}

static uint32_t getw(const std::vector<int> &b) { uint32_t v = 0; for (size_t i = 0; i < b.size(); i++) v |= (uint32_t)val[b[i]] << i; return v; }
static void putw_src(const std::vector<int> &b, uint32_t v, int t) {
    for (size_t i = 0; i < b.size(); i++) { uint8_t x = (v >> i) & 1; if (val[b[i]] != x) src(b[i], x, t); }
}

int main(int argc, char **argv) {
    if (argc < 3) { fprintf(stderr, "usage: gsim net.gnl fw.hex [-o leak.bin] [-period ps] [-maxcyc N]\n"); return 1; }
    const char *outp = "leak.bin";
    int period = 10000, t_sram = 150;
    long long maxcyc = 200000000LL;
    bool verbose = false, full_timing = false, timed_windows = false;
    int dump_win = -1; const char *dump_path = nullptr;
    double pvar = 0; uint64_t pseed = 1;
    for (int i = 3; i < argc; i++) {
        if (!strcmp(argv[i], "-o")) outp = argv[++i];
        else if (!strcmp(argv[i], "-period")) period = atoi(argv[++i]);
        else if (!strcmp(argv[i], "-maxcyc")) maxcyc = atoll(argv[++i]);
        else if (!strcmp(argv[i], "-v")) verbose = true;
        else if (!strcmp(argv[i], "-full")) full_timing = true;
        else if (!strcmp(argv[i], "-tw")) timed_windows = true;
        else if (!strcmp(argv[i], "-pvar")) { pvar = atof(argv[++i]); pseed = (uint64_t)atoll(argv[++i]); }  // per-cell delay variation
        else if (!strcmp(argv[i], "-dumptog")) { dump_win = atoi(argv[++i]); dump_path = argv[++i]; }   // timing-simulate the 0x1xx energy windows
    }
    load_gnl(argv[1]);
    if (pvar > 0) {
        // local process variation: every gate and flip-flop instance gets one delay
        // factor N(1, pvar) (clipped to [0.5, 1.5]) applied to all its timing arcs
        uint64_t st = pseed * 0x9E3779B97F4A7C15ull + 1;
        auto u01 = [&]() { st ^= st << 13; st ^= st >> 7; st ^= st << 17; return ((st >> 11) + 0.5) * (1.0 / 9007199254740992.0); };
        auto gauss = [&]() { double a = u01(), b = u01(); return sqrt(-2 * log(a)) * cos(6.283185307179586 * b); };
        auto fac = [&]() { double f = 1 + pvar * gauss(); return f < 0.5 ? 0.5 : f > 1.5 ? 1.5 : f; };
        std::vector<double> gf(G.size());
        for (auto &x : gf) x = fac();
        for (auto &p : fo) { double f = gf[p.gate]; p.rise = (uint16_t)std::max(1.0, p.rise * f + 0.5); p.fall = (uint16_t)std::max(1.0, p.fall * f + 0.5); }
        for (auto &x : F) { double f = fac(); x.rq = (int)(x.rq * f + 0.5); x.fq = (int)(x.fq * f + 0.5); x.rqn = (int)(x.rqn * f + 0.5); x.fqn = (int)(x.fqn * f + 0.5); }
        fprintf(stderr, "gsim: delay variation sigma=%.3f seed=%llu\n", pvar, (unsigned long long)pseed);
    }
    // memory
    const int WORDS = 65536;
    std::vector<uint32_t> mem(WORDS, 0);
    {
        std::ifstream f(argv[2]); std::string s; int a = 0;
        while (f >> s && a < WORDS) { if (s[0] == '@') { a = std::stoul(s.substr(1), nullptr, 16); continue; } mem[a++] = std::stoul(s, nullptr, 16); }
    }
    // initial settled state (gates are in topological order)
    for (auto &x : F) { val[x.q >= 0 ? x.q : 0] = 0; if (x.qn >= 0) val[x.qn] = 1; }
    val[0] = 0; val[1] = 1;
    for (auto &g : G) val[g.out] = eval(g);
    for (size_t i = 0; i < F.size(); i++) { ff_dirty[i] = 1; dirty_ff.push_back((int)i); }
    FILE *lf = fopen(outp, "wb");
    std::vector<uint16_t> win;
    bool leak_on = false;
    uint8_t mem_ready = 0, resetn = 0;
    uint32_t mem_rdata = 0;
    long long cycles = 0, win_cycles = 0;
    double e_total = 0, e_zd_total = 0;
    long long t_viol = 0;
    std::vector<uint8_t> nq(F.size());
    // energy windows opened / closed by MARK 0x1xx / 0x2xx (as bench_energy.c)
    bool ewin = false; int ewin_id = -1;
    long long ew_cyc = 0, ew_acc = 0;
    double ew_zd = 0, ew_gl = 0;
    bool ew_timed = false;
    std::vector<uint32_t> togc;              // -dumptog: settled toggles per net in one window
    for (long long cyc = 0; cyc < maxcyc; cyc++) {
        // ---------------- posedge: sample settled values ----------------
        uint8_t valid = val[port_valid[0]];
        uint32_t addr = getw(port_addr), wdata = getw(port_wdata), wstrb = getw(port_wstrb);
        bool sample_window = leak_on;                      // this cycle belongs to the window
        // flops whose D did not change since their last update keep their state
        std::vector<int> cur_dirty; cur_dirty.swap(dirty_ff);
        std::sort(cur_dirty.begin(), cur_dirty.end());   // same event order as a full scan
        for (int i : cur_dirty) { nq[i] = val[F[i].d]; ff_dirty[i] = 0; }
        // testbench (non-blocking semantics: decisions use pre-edge values)
        uint8_t n_ready = 0; uint32_t n_rdata = mem_rdata;
        bool do_exit = false; int exit_code = 0;
        if (resetn && valid && !mem_ready) {
            n_ready = 1;
            if (ewin && addr < 4u * WORDS) ew_acc++;
            if (addr < 4u * WORDS) {
                n_rdata = mem[addr >> 2];
                uint32_t m = 0;
                for (int b = 0; b < 4; b++) if (wstrb >> b & 1) m |= 0xFFu << (8 * b);
                mem[addr >> 2] = (mem[addr >> 2] & ~m) | (wdata & m);
            } else {
                n_rdata = 0;
                if (wstrb) {
                    if (addr == 0x10000000u) { putchar(wdata & 0xFF); }
                    else if (addr == 0x20000000u) { do_exit = true; exit_code = (int)wdata; }
                    else if (addr == 0x30000000u) {
                        if (wdata == 0x4C01u) { leak_on = true; win.clear(); win_cycles = 0; }
                        else if (wdata == 0x4C00u) {
                            leak_on = false;
                            uint32_t n = (uint32_t)win_cycles;
                            fwrite(&n, 4, 1, lf);
                            fwrite(win.data(), 2, win.size(), lf);
                        } else if ((wdata & 0x300u) == 0x100u) {
                            ewin = true; ewin_id = wdata & 0xFF; ew_cyc = ew_acc = 0; ew_zd = ew_gl = 0; ew_timed = true;
                        } else if ((wdata & 0x300u) == 0x200u && ewin) {
                            ewin = false;
                            if (ewin_id == dump_win && dump_path) {
                                FILE *tf = fopen(dump_path, "w");
                                for (int n = 0; n < nnets; n++) if (togc[n]) fprintf(tf, "%d %u\n", n, togc[n]);
                                fclose(tf);
                            }
                            double ec = ew_cyc * (e_ck + e_clknet + e_leak_ns * period * 1e-3);
                            printf("WINE %d cycles=%lld sram_accesses=%lld logic_zd_uJ=%.4f logic_glitch_uJ=%.4f%s\n",
                                   ewin_id, ew_cyc, ew_acc, (ew_zd + ec) * 1e-6, (ew_gl + ec) * 1e-6,
                                   ew_timed ? "" : " (glitch value invalid: window not timing-simulated)");
                        } else if (verbose) printf("MARK %u @%lld\n", wdata, cycles);
                    }
                }
            }
        }
        if (do_exit) {
            fflush(stdout);
            printf("\nEXIT code=%d cycles=%lld\n", exit_code, cyc);
            break;
        }
        uint8_t n_resetn = cyc >= 9 ? 1 : 0;               // tb: resetn <= 1 at the 10th posedge
        // ---------------- schedule this cycle's source events ----------------
        for (int b = 0; b <= NB; b++) bins[b] = 0;
        max_settle = 0;
        for (int i : cur_dirty) {
            const FF &x = F[i];
            uint8_t v = nq[i];
            if (x.q >= 0 && val[x.q] != v) src(x.q, v, v ? x.rq : x.fq);
            if (x.qn >= 0 && val[x.qn] != (uint8_t)(1 - v)) src(x.qn, 1 - v, v ? x.fqn : x.rqn);
        }
        if (n_ready != mem_ready) src(port_ready[0], n_ready, t_sram);
        putw_src(port_rdata, n_rdata, t_sram);
        if (n_resetn != resetn) src(port_resetn[0], n_resetn, t_sram);
        mem_ready = n_ready; mem_rdata = n_rdata; resetn = n_resetn;
        if (resetn) cycles++;
        // ---------------- events ----------------
        zd_mode = !(full_timing || leak_on || sample_window || (timed_windows && ewin));
        if (ewin && zd_mode) ew_timed = false;
        run_events();
        if (max_settle >= period) t_viol++;
        double zd = 0;
        if (togc.empty()) togc.assign(nnets, 0);
        for (int n : touched) {
            if (val[n] != start_val[n]) { zd += E[n]; if (ewin && ewin_id == dump_win) togc[n]++; }
            is_touched[n] = 0;
        }
        touched.clear();
        double eg = 0;
        for (int b = 0; b < NB; b++) eg += bins[b];
        double e_const = e_ck + e_clknet + e_leak_ns * period * 1e-3;
        if (!zd_mode) { e_total += eg + e_const; e_zd_total += zd + e_const; }
        if (ewin) { ew_cyc++; ew_zd += zd; ew_gl += eg; }
        if (sample_window) {
            for (int b = 0; b < NB; b++) win.push_back((uint16_t)std::min(65535.0, bins[b] * 100.0 + 0.5));
            win.push_back((uint16_t)std::min(65535.0, zd * 100.0 + 0.5));
            win_cycles++;
        }
    }
    fclose(lf);
    fprintf(stderr, "gsim: cycles=%lld events=%lld toggles=%lld E_glitch=%.3f uJ E_zero_delay=%.3f uJ "
                    "glitch_overhead=%.2f%% timing_violations=%lld (energies: timing-simulated cycles only)\n",
            cycles, n_events, n_toggles, e_total * 1e-6, e_zd_total * 1e-6,
            100.0 * (e_total - e_zd_total) / e_zd_total, t_viol);
    return 0;
}
