"""
ise_trace.py : gate-level power traces of the synthesized kyber_ise netlist
(NanGate 45nm) running the secret-dependent step of ML-KEM decapsulation,
  r_i = sum_k s_hat[k][i] o u_hat[k][i]   (basemul + modular add, K=2)
for two consecutive coefficient-pair words.

Each simulated instance is one decapsulation window; instances are vectorised
over the netlist bit-vectors. The PCPI handshake matches PicoRV32: pcpi_valid
is held with the operands until pcpi_ready, then the bus idles for a few
cycles. Every pcpi_rd produced by the netlist is checked against golden.py.
"""
import os
import sys
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', 'syn'))
sys.path.insert(0, os.path.join(HERE, '..', 'sw'))
import netlist as NL          # noqa: E402
import golden as G            # noqa: E402

Q = G.Q
LIB = os.environ.get('NANGATE_LIB', '/home/claude/tools/pdk/orfs/flow/platforms/nangate45/lib/'
                     'NangateOpenCellLibrary_typical.lib')
NET = os.path.join(HERE, '..', 'syn', 'out', 'kyber_ise.json')


def insn(f3, f7=0, rd=10, rs1=11, rs2=12):
    return (f7 << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | 0x0B


I_ZETA, I_CFG, I_SEED = insn(7, 0), insn(7, 1), insn(7, 2)
I_BMUL, I_ADD = insn(4), insn(6)

_cache = {}


def load_netlist():
    if 'nl' not in _cache:
        cells, wl = NL.load_liberty(LIB)
        _cache['nl'] = NL.Netlist(NET, 'kyber_ise', cells, wl)
    return _cache['nl']


def build_program(s, u, zetas):
    """s,u: (n,K=2,2) packed words. One identical-structure op list per instance."""
    n = s.shape[0]
    progs = []
    for t in range(n):
        ops = []
        for w in range(2):
            iz = G.ISE(); iz.kzeta(int(zetas[w]))
            ops.append((I_ZETA, int(zetas[w]), 0, None))
            r0 = iz.kbmul(int(s[t, 0, w]), int(u[t, 0, w]))
            r1 = iz.kbmul(int(s[t, 1, w]), int(u[t, 1, w]))
            ops.append((I_BMUL, int(s[t, 0, w]), int(u[t, 0, w]), r0))
            ops.append((I_BMUL, int(s[t, 1, w]), int(u[t, 1, w]), r1))
            ops.append((I_ADD, r0, r1, G.ISE.kaddq(r0, r1)))
        progs.append(ops)
    return progs


def simulate(s, u, zetas, cfg=0, seeds=None, gap=8, tclk_ns=5.0, check=True, maxcyc=400):
    """Returns (traces (n, L) pJ/cycle, mismatches). L is the common window length."""
    nl = load_netlist()
    n = s.shape[0]
    progs = build_program(s, u, zetas)
    if seeds is None:
        seeds = np.random.default_rng().integers(1, 2 ** 32, n, dtype=np.uint64)

    v = nl.new_state(n)
    nl.set_port(v, 'resetn', 0); nl.set_port(v, 'pcpi_valid', 0)
    nl.set_port(v, 'pcpi_insn', 0); nl.set_port(v, 'pcpi_rs1', 0); nl.set_port(v, 'pcpi_rs2', 0)
    for _ in range(3):
        nl.eval_comb(v); nl.clock(v)
    nl.set_port(v, 'resetn', 1)

    pre = [(I_SEED, None, 0, None), (I_CFG, cfg, 0, None)]
    ops = [[(i, (int(sd) & 0x7FFFFFFF) if a is None else a, b, e) for (i, a, b, e) in pre] + p
           for p, sd in zip(progs, seeds)]
    nops = len(ops[0])
    INS = np.array([[o[0] for o in p] for p in ops], dtype=np.int64)
    RS1 = np.array([[o[1] for o in p] for p in ops], dtype=np.int64)
    RS2 = np.array([[o[2] for o in p] for p in ops], dtype=np.int64)
    EXP = np.array([[(-1 if o[3] is None else o[3]) for o in p] for p in ops], dtype=np.int64)

    ptr = np.zeros(n, dtype=int)
    gapc = np.zeros(n, dtype=int)
    done = np.zeros(n, dtype=bool)
    mism = 0
    traces = [[] for _ in range(n)]

    v_prev = v.copy()
    cyc = 0
    while not done.all() and cyc < maxcyc:
        active = (~done) & (gapc == 0)
        nl.set_port(v, 'pcpi_valid', active.astype(int))
        cur = np.clip(ptr, 0, nops - 1)
        nl.set_port(v, 'pcpi_insn', np.where(active, INS[np.arange(n), cur], 0))
        nl.set_port(v, 'pcpi_rs1', np.where(active, RS1[np.arange(n), cur], 0))
        nl.set_port(v, 'pcpi_rs2', np.where(active, RS2[np.arange(n), cur], 0))

        nl.eval_comb(v)
        ready = (nl.get_port(v, 'pcpi_ready') == 1) & active
        wr = (nl.get_port(v, 'pcpi_wr') == 1)
        rd = nl.get_port(v, 'pcpi_rd')

        if check and ready.any():
            idx = np.where(ready & wr)[0]
            for t in idx:
                e = EXP[t, ptr[t]]
                if e >= 0 and rd[t] != e:
                    mism += 1

        # record energy only inside the measured window (the arithmetic ops, not seed/cfg)
        e_cyc = nl.cycle_energy(v_prev, v, tclk_ns)
        for t in range(n):
            if not done[t] and ptr[t] >= len(pre):
                traces[t].append(e_cyc[t])

        # advance handshake
        for t in range(n):
            if done[t]:
                continue
            if gapc[t] > 0:
                gapc[t] -= 1
                continue
            if ready[t]:
                ptr[t] += 1
                gapc[t] = gap
                if ptr[t] >= nops:
                    done[t] = True
        v_prev = v.copy()
        nl.clock(v)
        cyc += 1

    # windows differ in length when dummy operations are inserted: pad every
    # trace to the longest one with its own final (idle) value
    L = max(len(t) for t in traces)
    T = np.array([t + [t[-1]] * (L - len(t)) for t in traces], dtype=float)
    return T, mism


if __name__ == '__main__':
    rng = np.random.default_rng(0)
    n = 8
    s = rng.integers(0, Q, (n, 2, 2)); u = rng.integers(0, Q, (n, 2, 2))
    z = [G.ZETAS[64], (Q - G.ZETAS[64]) % Q]
    T, mism = simulate(s, u, z, cfg=0, maxcyc=300)
    print('window length', T.shape, 'mismatches', mism,
          'mean pJ/cyc', round(float(T.mean()), 4))
