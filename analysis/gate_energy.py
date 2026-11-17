"""
gate_energy.py : gate-level energy of the full SoC logic (PicoRV32 core + ISE)
for every measurement window, from Verilator toggle counts on the synthesized
NanGate45 netlists (tb_soc.v -DGATE -DCOVWIN, firmware sw/fw/bench_energy.c).

  E_window = sum_nets toggles(n) * [ 1/2 C(n) Vdd^2 + E_int(driver(n)) ]
           + cycles * ( E_clk-pins + P_leak * T_clk )

C(n): fan-out pin capacitance + 5K_hvratio wire-load model; E_int: liberty
internal-power tables (cell output and flop Q pins); clock pins of every flop
switch every cycle. Zero-delay toggles (no glitches) and no clock tree: a lower
bound on dynamic energy, applied identically to all variants.
SRAM energy is reported separately from the RTL access counts with an assumed
per-access energy (E_SRAM_PJ, see README) because no memory macro is synthesized.

Output: results/energy.csv
"""
import csv
import os
import re
import sys
from collections import defaultdict
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
sys.path.insert(0, os.path.join(ROOT, 'syn'))
import netlist as NL  # noqa: E402

LIB = os.environ.get('NANGATE_LIB', '/home/claude/tools/pdk/orfs/flow/platforms/nangate45/lib/'
                     'NangateOpenCellLibrary_typical.lib')
F_MHZ = 100.0                    # IoT operating point for leakage and power figures
E_SRAM_PJ = float(os.environ.get('E_SRAM_PJ', '10.0'))   # assumed energy per 32-bit SRAM access
OPS = ['NTT', 'INTT', 'BaseMulAcc', 'KeyGen', 'Encaps', 'Decaps', 'MaskedDecaps']
# netlists the gate-level runs were made with (snapshot; syn/out may be re-synthesized later)
NETDIR = os.path.join(ROOT, 'syn', 'out_energy_netlists')
VARIANTS = ('ref', 'ise', 'ise_mitig', 'isek', 'isek_mitig', 'isek_masked')


NETDIR_OF = {'isek_masked': os.path.join(ROOT, 'syn', 'out_energy_masked')}   # run with the PRNG-equipped ISE


class Unit:
    def __init__(self, name, cells, wl, netdir=None):
        NETDIR_ = netdir or NETDIR
        self.nl = NL.Netlist(os.path.join(NETDIR_, '%s.json' % name), name, cells, wl)
        nl = self.nl
        e_tog = 0.5 * NL.VDD ** 2 * nl.cap * 1e-3                 # pJ per toggle (switching)
        for i, c in enumerate(nl.comb):
            e_tog[c[3]] += nl.e_int[i]
        for i, f in enumerate(nl.ffs):
            q = f[3] if f[3] is not None else f[4]
            if q is not None:
                e_tog[q] += nl.e_ffq[i]
        self.e_tog = e_tog
        m = __import__('json').load(open(os.path.join(NETDIR_, '%s.json' % name)))['modules'][name]
        self.bit = {}
        for nn, n in m['netnames'].items():
            for i, b in enumerate(n['bits']):
                if isinstance(b, int):
                    self.bit[(nn, i)] = b
                    if len(n['bits']) == 1:
                        self.bit[(nn, None)] = b


_sig = re.compile(r'^(.*?)(?:\[(\d+)\])?:(0->1|1->0)$')


def read_cov(path):
    """{hier: {(signal, bit): toggles}}"""
    out = defaultdict(lambda: defaultdict(int))
    for ln in open(path):
        if not ln.startswith('C '):
            continue
        k = ln[3:ln.rindex("'")]
        d = dict(x.split('\x02', 1) for x in k.split('\x01') if '\x02' in x)
        if d.get('t') != 'toggle':
            continue
        m = _sig.match(d['o'])
        if not m:
            continue
        name = re.sub(r'__0([0-9a-f]{2})', lambda e: chr(int(e.group(1), 16)), m.group(1))
        idx = m.group(2)
        out[d['h']][(name, int(idx) if idx is not None else None)] += int(ln.rsplit(' ', 1)[1])
    return out


def window_energy(unit, counts, cycles):
    """dynamic + clock + leakage energy (pJ) of one unit over one window"""
    tog = np.zeros(unit.nl.nnets)
    seen = 0
    for key, c in counts.items():
        b = unit.bit.get(key)
        if b is None and key[1] is None:
            b = unit.bit.get((key[0], 0))
        if b is None or b < 2 or b >= unit.nl.nnets:     # constants / dangling nets
            continue
        tog[b] = max(tog[b], c)          # aliases of the same net carry the same count
        seen += 1
    e_dyn = float((tog * unit.e_tog).sum())
    e_clk = unit.nl.e_ck * cycles
    e_leak = unit.nl.leak_nw * 1e-9 * cycles / (F_MHZ * 1e6) * 1e12
    cov = (tog > 0).sum()
    return e_dyn, e_clk, e_leak, seen


def winlog(path):
    w = {}
    for ln in open(path):
        if ln.startswith('WIN'):
            p = dict(x.split('=') for x in ln.split()[2:])
            w[int(ln.split()[1])] = {k: int(v) for k, v in p.items()}
    return w


def main():
    cells, wl = NL.load_liberty(LIB)
    cache = {}

    def units_for(var):
        nd = NETDIR_OF.get(var, NETDIR)
        if nd not in cache:
            cache[nd] = {'cpu': Unit('picorv32', cells, wl, nd), 'ise': Unit('kyber_ise', cells, wl, nd),
                         'kise': Unit('keccak_ise', cells, wl, nd)}
        return cache[nd]
    rows = []
    for var in VARIANTS:
        if not os.path.exists(os.path.join(ROOT, 'sim/rtlwin/%s.log' % var)):
            continue
        stats = winlog(os.path.join(ROOT, 'sim/rtlwin/%s.log' % var))
        units = units_for(var)
        for wid, op in enumerate(OPS):
            path = os.path.join(ROOT, 'sim/gate/%s/cov_%d.dat' % (var, wid))
            if not os.path.exists(path):
                continue
            cov = read_cov(path)
            cyc = stats[wid]['cycles']
            row = dict(variant=var, op=op, cycles=cyc)
            tot = 0.0
            if wid not in stats:
                continue
            for h, key in (('tb_soc.cpu', 'cpu'), ('tb_soc.ise', 'ise'), ('tb_soc.kise', 'kise')):
                if h not in cov:
                    continue
                d, c, l, seen = window_energy(units[key], cov[h], cyc)
                row[key + '_dyn_nJ'] = round(d / 1e3, 3)
                row[key + '_clk_nJ'] = round(c / 1e3, 3)
                row[key + '_leak_nJ'] = round(l / 1e3, 3)
                tot += d + c + l
            acc = stats[wid]['ifetch'] + stats[wid]['load'] + stats[wid]['store']
            row['logic_uJ'] = round(tot / 1e6, 4)
            row['sram_accesses'] = acc
            row['sram_uJ'] = round(acc * E_SRAM_PJ / 1e6, 4)
            row['total_uJ'] = round((tot + acc * E_SRAM_PJ) / 1e6, 4)
            row['avg_logic_power_mW@%dMHz' % F_MHZ] = round(tot / cyc * F_MHZ * 1e-3, 3)
            row['time_ms@%dMHz' % F_MHZ] = round(cyc / (F_MHZ * 1e3), 3)
            rows.append(row)
            print(row)
    keys = []
    for r in rows:
        keys += [k for k in r if k not in keys]
    with open(os.path.join(ROOT, 'results/energy.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=keys)
        w.writeheader()
        w.writerows(rows)


if __name__ == '__main__':
    main()
