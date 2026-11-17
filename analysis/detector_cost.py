"""detector_cost.py : on-node detector cost from the RTL run (sim/det_run.log) and the
baseline core's gate-level energy per cycle (results/energy.csv) -> results/detector_cost.csv"""
import csv
import os
import re
ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
log = open(os.path.join(ROOT, 'sim/det_run.log')).read()
g = lambda k: int(re.search(k + r'=(\d+)', log).group(1))
en = list(csv.DictReader(open(os.path.join(ROOT, 'results/energy.csv'))))
ref = [r for r in en if r['variant'] == 'ref' and r['op'] in ('KeyGen', 'Encaps', 'Decaps')]
e_cyc_pJ = sum(float(r['total_uJ']) for r in ref) * 1e6 / sum(int(r['cycles']) for r in ref)
dec = next(r for r in en if r['variant'] == 'ise' and r['op'] == 'Decaps')
# final configuration (ISE + Keccak unit): the detector runs on the same SoC, whose
# idle units still clock and leak, so its energy uses that SoC's measured pJ/cycle
deck = [r for r in en if r['variant'] == 'isek' and r['op'] in ('KeyGen', 'Encaps', 'Decaps')]
e_cyc_k = sum(float(r['total_uJ']) for r in deck) * 1e6 / sum(int(r['cycles']) for r in deck)
deck_dec = next(r for r in deck if r['op'] == 'Decaps')
row = dict(avg_cycles=g('det_avg_cycles'), max_cycles=g('det_max_cycles'),
           c_vs_python_agreement='%d/%d' % (g('det_agree'), g('det_n')),
           core_pJ_per_cycle=round(e_cyc_pJ, 2), uJ_per_window=round(g('det_avg_cycles') * e_cyc_pJ / 1e6, 2),
           ms_per_window_100MHz=round(g('det_avg_cycles') / 1e5, 2),
           pct_of_ise_decaps_cycles=round(100 * g('det_avg_cycles') / int(dec['cycles']), 1),
           isek_pJ_per_cycle=round(e_cyc_k, 2),
           uJ_per_window_isek=round(g('det_avg_cycles') * e_cyc_k / 1e6, 2),
           pct_of_isek_decaps_cycles=round(100 * g('det_avg_cycles') / int(deck_dec['cycles']), 1))
# final configuration with the clock-gated Keccak unit (analysis/keccak_cg.py)
cgp = os.path.join(ROOT, 'results/energy_cg.csv')
if os.path.exists(cgp):
    cg = [r for r in csv.DictReader(open(cgp)) if r['variant'] == 'isek_cg' and r['op'] in ('KeyGen', 'Encaps', 'Decaps')]
    e_cyc_cg = sum(float(r['total_uJ']) for r in cg) * 1e6 / sum(int(r['cycles']) for r in cg)
    row['isek_cg_pJ_per_cycle'] = round(e_cyc_cg, 2)
    row['uJ_per_window_isek_cg'] = round(g('det_avg_cycles') * e_cyc_cg / 1e6, 2)
with open(os.path.join(ROOT, 'results/detector_cost.csv'), 'w', newline='') as f:
    w = csv.DictWriter(f, fieldnames=list(row)); w.writeheader(); w.writerow(row)
print(row)
