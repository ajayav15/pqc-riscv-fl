"""
keccak_cg.py : energy of the SoC with the clock-gated Keccak unit
(rtl/keccak_ise.v -DKECCAK_CG, synthesized as syn/out/keccak_ise_cg).

The gated design is functionally identical (same cycle counts and outputs in RTL
simulation, sim/cg/*.log). In the energy model of analysis/gate_energy.py the
Keccak unit's clock energy is (flops x per-flop clock-pin energy) every cycle.
With the gate, the 1600 state flops are clocked only in the cycles in which the
state register is enabled (kk_en, counted by tb_soc.v in every window); the
remaining 48 flops and the clock gate (latch clock pin + AND2) are clocked every
cycle. Leakage uses the gated netlist. Dynamic data toggles of the unit are
taken from the ungated gate-level runs (the state does not change in disabled
cycles in either design, so they are the same up to the removed feedback muxes).

Output: results/energy_cg.csv
"""
import csv
import os
import sys
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
sys.path.insert(0, os.path.join(ROOT, 'syn'))
import netlist as NL  # noqa: E402

LIB = os.environ.get('NANGATE_LIB', '/home/claude/tools/pdk/orfs/flow/platforms/nangate45/lib/'
                     'NangateOpenCellLibrary_typical.lib')
F_MHZ = 100.0
N_STATE = 1600


def pin_e(lc, pin, load=0.0):
    es = []
    for pw in lc.pins[pin]['pwr']:
        for k in ('rise_power', 'fall_power'):
            if k in pw:
                es.append(NL.lut(pw[k], 0.02, load))
    return float(np.mean(es)) * 1e-3 if es else 0.0      # pJ per transition


def main():
    lib, wl = NL.load_liberty(LIB)
    cg = NL.Netlist(os.path.join(ROOT, 'syn', 'out', 'keccak_ise_cg.json'), 'keccak_ise', lib, wl)
    pl = NL.Netlist(os.path.join(ROOT, 'syn', 'out_energy_netlists', 'keccak_ise.json'), 'keccak_ise', lib, wl)
    e_ff = cg.e_ck / len(cg.ffs)                          # pJ per flop per cycle (rise + fall)
    # clock gate: latch enable pin switches every cycle (2 transitions); AND2 output
    # (gated clock) switches only in enabled cycles
    e_latch = 2 * pin_e(lib['DLL_X1'], 'GN')
    e_and = 2 * pin_e(lib['AND2_X1'], 'ZN')
    print('per-flop clock %.4f pJ/cycle, latch %.4f pJ/cycle, AND2 %.4f pJ/enabled cycle' % (e_ff, e_latch, e_and))
    print('leakage: ungated %.1f uW, gated %.1f uW' % (pl.leak_nw / 1000, cg.leak_nw / 1000))
    rows = []
    en = list(csv.DictReader(open(os.path.join(ROOT, 'results', 'energy.csv'))))
    for var in ('isek', 'isek_mitig', 'isek_masked'):
        wins = {}
        for ln in open(os.path.join(ROOT, 'sim', 'cg', 'cg_%s.log' % var)):
            if ln.startswith('WIN'):
                p = dict(x.split('=') for x in ln.split()[2:])
                wins[int(ln.split()[1])] = {k: int(v) for k, v in p.items()}
        ops = ['NTT', 'INTT', 'BaseMulAcc', 'KeyGen', 'Encaps', 'Decaps', 'MaskedDecaps']
        for r in en:
            if r['variant'] != var:
                continue
            wid = ops.index(r['op'])
            w = wins.get(wid)
            cyc = int(r['cycles'])
            if w is None or w['cycles'] != cyc:
                raise SystemExit('window mismatch %s %s' % (var, r['op']))
            kk = w['kk_en']
            clk_cg = ((len(cg.ffs) - N_STATE) * cyc + N_STATE * kk) * e_ff + cyc * e_latch + kk * e_and
            leak_cg = cg.leak_nw * 1e-9 * cyc / (F_MHZ * 1e6) * 1e12
            old_clk = float(r['kise_clk_nJ']) * 1e3             # nJ -> pJ
            old_leak = float(r['kise_leak_nJ']) * 1e3
            d = (old_clk - clk_cg) + (old_leak - leak_cg)          # pJ saved
            tot = float(r['total_uJ']) - d * 1e-6
            rows.append(dict(variant=var + '_cg', op=r['op'], cycles=cyc, kk_en_cycles=kk,
                             kise_clk_nJ=round(clk_cg * 1e-3, 3), kise_leak_nJ=round(leak_cg * 1e-3, 3),
                             total_uJ=round(tot, 4), total_uJ_ungated=float(r['total_uJ']),
                             saving_pct=round(100 * d * 1e-6 / float(r['total_uJ']), 2),
                             avg_power_mW=round(tot * 1e-6 / (cyc / (F_MHZ * 1e6)) * 1e3, 3)))
            print(rows[-1])
    with open(os.path.join(ROOT, 'results', 'energy_cg.csv'), 'w', newline='') as f:
        wr = csv.DictWriter(f, fieldnames=list(rows[0])); wr.writeheader(); wr.writerows(rows)


if __name__ == '__main__':
    main()
