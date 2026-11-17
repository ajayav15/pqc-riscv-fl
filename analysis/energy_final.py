"""
energy_final.py : energy of the final configuration (PicoRV32 + Kyber ISE +
clock-gated Keccak unit) including the transition/glitch-hardened masked
decapsulation (masked.c version 2).

Masked v2 was measured with the gate-level simulator sim/gsim in zero-delay
mode on the same netlists as the isek_masked row of results/energy.csv
(syn/out_energy_masked + keccak_ise; the two energy models agree within 1 % on
common windows, see README). SRAM energy as in gate_energy.py. The clock-gating
correction of analysis/keccak_cg.py is applied with the enabled-cycle counts of
the RTL run (sim/cg/cg_isek_masked2.log).

Output: results/energy_final.csv (rows for the final configuration)
"""
import csv
import os
import re
import sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
sys.path.insert(0, os.path.join(ROOT, 'analysis'))
E_SRAM_PJ = 10.0
F_MHZ = 100.0


def wine(path):
    out = {}
    for ln in open(path):
        if ln.startswith('WINE'):
            f = ln.split()
            p = dict(x.split('=') for x in f[2:6])
            out[int(f[1])] = dict(cycles=int(p['cycles']), sram=int(p['sram_accesses']), logic=float(p['logic_zd_uJ']))
    return out


def win(path):
    out = {}
    for ln in open(path):
        if ln.startswith('WIN '):
            p = dict(x.split('=') for x in ln.split()[2:])
            out[int(ln.split()[1])] = {k: int(v) for k, v in p.items()}
    return out


def main():
    import keccak_cg as KC   # noqa: F401  (documents the dependency; numbers come from its CSV)
    cg = {(r['variant'], r['op']): r for r in csv.DictReader(open(os.path.join(ROOT, 'results', 'energy_cg.csv')))}
    en = {(r['variant'], r['op']): r for r in csv.DictReader(open(os.path.join(ROOT, 'results', 'energy.csv')))}
    g = wine(os.path.join(ROOT, 'sim', 'genergy', 'isek_masked2.log'))
    w = win(os.path.join(ROOT, 'sim', 'cg', 'cg_isek_masked2.log'))
    rows = []
    # per-cycle clock-gating saving of the isek netlist, from the measured unmasked Decaps
    d_u = float(en[('isek_masked', 'Decaps')]['total_uJ']) - float(cg[('isek_masked_cg', 'Decaps')]['total_uJ'])
    per_idle_cycle = d_u * 1e6 / (int(en[('isek_masked', 'Decaps')]['cycles']) - int(cg[('isek_masked_cg', 'Decaps')]['kk_en_cycles']))
    for wid, op in ((5, 'Decaps'), (6, 'MaskedDecaps')):
        x = g[wid]
        if w[wid]['cycles'] != x['cycles']:
            raise SystemExit('cycle mismatch in window %d' % wid)
        sram = (w[wid]['ifetch'] + w[wid]['load'] + w[wid]['store'])
        tot = x['logic'] + sram * E_SRAM_PJ * 1e-6
        tot_cg = tot - per_idle_cycle * (x['cycles'] - w[wid]['kk_en']) * 1e-6
        for var, t in (('isek_masked2', tot), ('isek_masked2_cg', tot_cg)):
            rows.append(dict(variant=var, op=op, cycles=x['cycles'], logic_uJ=round(x['logic'], 4), sram_accesses=sram,
                             total_uJ=round(t, 4), avg_power_mW=round(t * 1e-6 / (x['cycles'] / (F_MHZ * 1e6)) * 1e3, 3),
                             source='gsim zero-delay' + (' + clock-gating correction' if var.endswith('_cg') else '')))
        print(rows[-2]); print(rows[-1])
    with open(os.path.join(ROOT, 'results', 'energy_final.csv'), 'w', newline='') as f:
        wr = csv.DictWriter(f, fieldnames=list(rows[0])); wr.writeheader(); wr.writerows(rows)


if __name__ == '__main__':
    main()
