"""figures.py : manuscript figures from results/*.csv|json -> figs/*.png and *.pdf"""
import csv
import json
import os
import re
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
FIG = os.path.join(ROOT, 'figs')
C = ['#2a78d6', '#eb6834', '#1baf7a', '#eda100', '#e87ba4', '#008300', '#6250d6', '#e34948']
INK, INK2, GRID = '#0b0b0b', '#52514e', '#e4e3df'
plt.rcParams.update({'font.family': 'DejaVu Sans', 'font.size': 9, 'axes.edgecolor': INK2,
                     'axes.labelcolor': INK, 'xtick.color': INK2, 'ytick.color': INK2,
                     'axes.spines.top': False, 'axes.spines.right': False, 'axes.grid': True,
                     'grid.color': GRID, 'grid.linewidth': 0.6, 'axes.axisbelow': True,
                     'legend.frameon': False, 'savefig.dpi': 300, 'figure.dpi': 110,
                     'pdf.fonttype': 42, 'ps.fonttype': 42})   # TrueType fonts in PDFs (no Type 3)


def rd(name):
    return list(csv.DictReader(open(os.path.join(ROOT, 'results', name))))


def save(fig, name):
    os.makedirs(FIG, exist_ok=True)
    if not fig.legends:
        fig.tight_layout()
    for ext in ('png', 'pdf'):
        fig.savefig(os.path.join(FIG, '%s.%s' % (name, ext)))
    plt.close(fig)


def winlog(v):
    out = {}
    for ln in open(os.path.join(ROOT, 'sim/rtlwin/%s.log' % v)):
        if ln.startswith('WIN'):
            out[int(ln.split()[1])] = int(re.search(r'cycles=(\d+)', ln).group(1))
    return out


def fig_speed():
    ops = ['NTT', 'INTT', 'BaseMul\n(K=2)', 'KeyGen', 'Encaps', 'Decaps']
    vs = (('ref', 'Reference C (RV32IM)'), ('ise', 'Kyber ISE'), ('isek', 'Kyber ISE + Keccak unit'),
          ('isek_mitig', 'ISE + Keccak, mitigation on'))
    w = {v: winlog(v) for v, _ in vs}
    fig, ax = plt.subplots(1, 2, figsize=(7.2, 2.9))
    for a, idx, unit, div, best in ((ax[0], [0, 1, 2], 'kcycles', 1e3, 'ise'), (ax[1], [3, 4, 5], 'Mcycles', 1e6, 'isek')):
        x = np.arange(len(idx))
        for j, (v, lab) in enumerate(vs):
            a.bar(x + (j - 1.5) * 0.2, [w[v][i] / div for i in idx], 0.19, color=C[j], label=lab)
        for k, i in enumerate(idx):
            a.text(k, w['ref'][i] / div * 1.02, '%.1fx' % (w['ref'][i] / w[best][i]), ha='center',
                   va='bottom', color=INK, fontsize=8)
        a.set_xticks(x); a.set_xticklabels([ops[i] for i in idx]); a.set_ylabel(unit)
        a.set_ylim(0, max(w['ref'][i] for i in idx) / div * 1.15)
    h, l = ax[0].get_legend_handles_labels()
    fig.legend(h, l, loc='upper center', ncol=2, fontsize=8)
    fig.tight_layout(rect=(0, 0, 1, 0.86))
    save(fig, 'fig_speedup')


def fig_profile():
    rows = rd('profile.csv')
    groups = [('Keccak (SHA3/SHAKE)', ('Keccak',)),
              ('Polynomial arithmetic\n(NTT, base mul, reduction)', ('NTT', 'Base', 'Modular')),
              ('Sampling (matrix, CBD)', ('Matrix', 'CBD')),
              ('Other (pack, verify, mem)', ('Compress', 'Verify', 'memcpy', 'Other'))]
    bars = [(v, op) for op in ('KeyGen', 'Encaps', 'Decaps') for v in ('ref', 'ise', 'isek')]
    fig, ax = plt.subplots(figsize=(7.2, 3.4))
    left = np.zeros(len(bars))
    for gi, (gname, keys) in enumerate(groups):
        vals = np.array([sum(int(r['cycles']) for r in rows if r['variant'] == v and r['op'] == op
                             and r['category'].startswith(keys)) for v, op in bars]) / 1e6
        ax.barh(np.arange(len(bars)), vals, left=left, color=C[gi], label=gname, height=0.62,
                edgecolor='white', linewidth=1)
        left += vals
    ax.set_yticks(np.arange(len(bars)))
    ax.set_yticklabels(['%s  %s' % (op, {'ref': 'ref', 'ise': 'ISE', 'isek': 'ISE+Keccak'}[v]) for v, op in bars])
    ax.invert_yaxis(); ax.set_xlabel('Mcycles on PicoRV32 (cycle-accurate RTL)')
    h, l = ax.get_legend_handles_labels()
    fig.legend(h, [x.replace('\n', ' ') for x in l], loc='upper center', ncol=2, fontsize=7.5)
    fig.tight_layout(rect=(0, 0, 1, 0.84))
    save(fig, 'fig_profile')


def fig_tvla():
    rows = rd('tvla.csv')
    fig, ax = plt.subplots(figsize=(3.5, 2.7))
    for i, cfg in enumerate(('none', 'hiding', 'hiding+dvfs')):
        r = [x for x in rows if x['config'] == cfg]
        ax.plot([int(x['n_per_group']) for x in r], [float(x['max_abs_t']) for x in r], '-o', ms=4,
                lw=2, color=C[i], label={'none': 'unprotected', 'hiding': 'dummy + shuffle',
                                         'hiding+dvfs': 'dummy + shuffle + DVFS'}[cfg])
    ax.axhline(4.5, color=INK2, lw=1, ls='--'); ax.text(1300, 4.0, 'threshold |t| = 4.5', color=INK2, fontsize=7.5)
    ax.set_xscale('log'); ax.set_yscale('log'); ax.set_xlabel('traces per group'); ax.set_ylabel('max |t|')
    from matplotlib.ticker import FixedLocator, NullLocator, ScalarFormatter
    ax.xaxis.set_major_locator(FixedLocator([250, 500, 1000, 2000, 6000])); ax.xaxis.set_minor_locator(NullLocator())
    ax.yaxis.set_major_locator(FixedLocator([2, 5, 10, 20, 50])); ax.yaxis.set_minor_locator(NullLocator())
    for a in (ax.xaxis, ax.yaxis):
        a.set_major_formatter(ScalarFormatter())
    ax.legend(fontsize=7.5)
    save(fig, 'fig_tvla')


def fig_cpa(name='cpa.csv', key='config', out='fig_cpa'):
    rows = rd(name)
    fig, axs = plt.subplots(1, 2, figsize=(7.2, 2.7), sharey=True)
    cfgs = list(dict.fromkeys(r[key] for r in rows))
    for a, att in zip(axs, ('pointwise', 'integrated')):
        for i, cfg in enumerate(cfgs):
            r = [x for x in rows if x[key] == cfg and x['attack'] == att]
            a.plot([int(x['n_traces']) for x in r], [int(x['rank']) + 1 for x in r], '-o', ms=4, lw=2,
                   color=C[i], label={'none': 'unprotected', 'hiding': 'dummy + shuffle',
                                      'hiding+dvfs': 'dummy + shuffle + DVFS'}.get(cfg, cfg))
        a.set_xscale('log'); a.set_yscale('log'); a.set_xlabel('attack traces')
        a.set_title('%s CPA' % att, fontsize=9, color=INK)
    axs[0].set_ylabel('rank of true s0 (+1)')
    h, l = axs[0].get_legend_handles_labels()
    fig.legend(h, l, loc='upper center', ncol=len(l), fontsize=7.5)
    fig.tight_layout(rect=(0, 0, 1, 0.88))
    save(fig, out)


def fig_fl():
    rows = rd('fl_summary.csv')
    meth = ['local', 'oneclass', 'fedavg', 'fedprox', 'dp_fedavg', 'fedavg_int8', 'centralized']
    lab = ['Local only', 'One-class', 'FedAvg', 'FedProx', 'DP-FedAvg', 'FedAvg int8', 'Centralized*']
    fig, axs = plt.subplots(1, 2, figsize=(7.2, 2.7), sharey=True)
    for a, (src, title) in zip(axs, (('kem_gate', 'Gate-level ML-KEM traces'), ('ascad', 'ASCAD (measured)'))):
        x = np.arange(len(meth))
        for j, (k, nm) in enumerate((('f1', 'F1'), ('tpr_unseen', 'TPR on unseen attack types'))):
            v = [float(next(r for r in rows if r['source'] == src and r['method'] == m)[k]) for m in meth]
            e = [float(next(r for r in rows if r['source'] == src and r['method'] == m)[k + '_sd']) for m in meth]
            a.bar(x + (j - 0.5) * 0.38, v, 0.36, yerr=e, color=C[j], label=nm, error_kw=dict(lw=0.8, ecolor=INK2))
        a.set_xticks(x); a.set_xticklabels(lab, rotation=35, ha='right'); a.set_title(title, fontsize=9)
        a.set_ylim(0, 1.05)
    h, l = axs[0].get_legend_handles_labels()
    fig.legend(h, l, loc='upper center', ncol=2, fontsize=8)
    fig.tight_layout(rect=(0, 0, 1, 0.9))
    fig.text(0.99, 0.01, '* pools raw features centrally (privacy-violating upper bound)', ha='right', fontsize=7, color=INK2)
    save(fig, 'fig_fl')


def fig_energy():
    cl = json.load(open(os.path.join(ROOT, 'results', 'closed_loop.json')))
    e = cl['energy_uJ_per_decaps']
    F = 'Final (ISE+gated Keccak)'
    sel = [('Reference software, unprotected', 'Reference (no ISE), unprotected', 0),
           ('ISE + clock-gated Keccak, unprotected', F + ', unprotected', 0),
           ('Hiding, always on', F + ', always-on hiding+DVFS', 1),
           ('Hiding, adaptive (detector every decaps)', F + ', adaptive hiding, detector every decaps', 1),
           ('Hiding, adaptive (detector every 4th)', F + ', adaptive hiding, detector every 4th decaps', 1),
           ('Hardened masking, always on', F + ', always-on masking v2 (measured)', 2),
           ('Masking, adaptive (detector every decaps)', F + ', adaptive masking v2, detector every decaps', 2),
           ('Masking, adaptive (detector every 4th)', F + ', adaptive masking v2, detector every 4th decaps', 2)]
    fig, ax = plt.subplots(figsize=(7.2, 2.9))
    y = np.arange(len(sel))
    vals = [e[k] for _, k, _ in sel]
    ax.barh(y, vals, color=[C[c] for _, _, c in sel], height=0.62)
    for i, v in enumerate(vals):
        ax.text(v + max(vals) * 0.01, i, '%.0f \u00b5J' % v, va='center', fontsize=8, color=INK)
    ax.set_yticks(y); ax.set_yticklabels([l for l, _, _ in sel], fontsize=8); ax.invert_yaxis()
    ax.set_xlabel('\u00b5J per ML-KEM-512 decapsulation, gate level (logic + SRAM)')
    ax.set_xlim(0, max(vals) * 1.15)
    save(fig, 'fig_energy')


def fig_network():
    rows = rd('network.csv')
    fig, ax = plt.subplots(figsize=(7.2, 2.6))
    y = np.arange(len(rows))
    comp = np.array([float(r['node_compute_uJ']) / 1e3 for r in rows])
    rad = np.array([float(r['node_radio_mJ']) for r in rows])
    ax.barh(y, rad, color=C[0], height=0.6, label='radio (802.15.4, CC2420)', edgecolor='white')
    ax.barh(y, comp, left=rad, color=C[1], height=0.6, label='computation (100 MHz)', edgecolor='white')
    for i, r in enumerate(rows):
        ax.text(rad[i] + comp[i] + 0.05, i, '%s ms' % r['handshake_latency_ms'], va='center', fontsize=7.5)
    ax.set_yticks(y); ax.set_yticklabels([r['scheme'] for r in rows], fontsize=8); ax.invert_yaxis()
    ax.set_xlabel('node energy per key exchange, mJ  (labels: end-to-end latency)')
    ax.set_xlim(0, (rad + comp).max() * 1.22)
    h, l = ax.get_legend_handles_labels()
    fig.legend(h, l, loc='upper center', ncol=2, fontsize=8)
    fig.tight_layout(rect=(0, 0, 1, 0.9))
    save(fig, 'fig_network')


def fig_fl_ablation():
    rows = rd('fl_ablation.csv')
    pars = [('n_atk', 'attack types per node\n(4 = IID)'), ('nodes', 'number of nodes'),
            ('sigma', 'sensor noise sigma (pJ)'), ('epochs', 'local epochs per round')]
    fig, axs = plt.subplots(1, 4, figsize=(7.2, 2.5), sharey=True)
    for a, (p, lab) in zip(axs, pars):
        r = [x for x in rows if x['parameter'] == p]
        xs = np.arange(len(r))
        for j, (tag, nm) in enumerate((('fedavg', 'FedAvg'), ('local', 'Local only'))):
            m = [float(x[tag + '_f1']) for x in r]; e = [float(x[tag + '_f1_ci95']) for x in r]
            a.errorbar(xs, m, yerr=e, fmt='-o', ms=4, lw=2, capsize=3, color=C[j], label=nm)
        a.set_xticks(xs); a.set_xticklabels([x['value'] for x in r]); a.set_xlabel(lab, fontsize=8)
        a.set_ylim(0.4, 1.0)
    axs[0].set_ylabel('F1 (mean, 95% CI, 3 seeds)')
    h, l = axs[0].get_legend_handles_labels()
    fig.legend(h, l, loc='upper center', ncol=2, fontsize=8)
    fig.tight_layout(rect=(0, 0, 1, 0.88))
    save(fig, 'fig_fl_ablation')


def fig_tvla_masked():
    rows = rd('tvla_masked.csv')
    gad = list(dict.fromkeys(r['gadget'] for r in rows))
    fig, axs = plt.subplots(1, 2, figsize=(7.2, 2.6), sharey=True)
    for a, (ch, title) in zip(axs, (('value', 'value model: HW of register writes + bus'),
                                     ('transition', 'transition model: HD of consecutive writes'))):
        x = np.arange(len(gad))
        for j, v in enumerate(('unmasked', 'masked')):
            vals = [float(next(r for r in rows if r['gadget'] == g and r['variant'] == v)['max_t_' + ch]) for g in gad]
            a.bar(x + (j - 0.5) * 0.36, vals, 0.34, color=C[j], label=v)
        a.axhline(4.5, color=INK2, ls='--', lw=1)
        a.set_yscale('log'); a.set_xticks(x); a.set_xticklabels([g.replace(' (', '\n(').replace(', ', ',\n') for g in gad], fontsize=7.5)
        a.set_title(title, fontsize=8.5)
    axs[0].set_ylabel('max |t| (4,000 traces)')
    h, l = axs[0].get_legend_handles_labels()
    fig.legend(h, l, loc='upper center', ncol=2, fontsize=8)
    fig.tight_layout(rect=(0, 0, 1, 0.88))
    save(fig, 'fig_tvla_masked')


def fig_tvla_hardening():
    """max |t| of the masking gadgets: unmasked, masks forced to zero, masking v1
    (value-model) and v2 (transition/glitch hardened), for the RTL value and
    datapath-transition models and the glitch-aware gate-level simulation"""
    rows = rd('tvla2.csv')
    def mx(tags, sim, tgt, chans):
        v = [float(r['max_t']) for r in rows if r['tag'] in tags and r['sim'] == sim and int(r['target']) == tgt
             and r['channel'] in chans]
        return max(v) if v else np.nan
    gad = [('Decoding', 0), ('Keccak-f round', 2), ('CBD eta=2', 4)]
    series = [('unmasked', {'rtl': ['v1r'], 'gsim': ['g1', 'g1k']}, 1),
              ('masks = 0 (control)', {'rtl': ['v2rz'], 'gsim': ['g2z']}, 0),
              ('masking v1', {'rtl': ['v1r'], 'gsim': ['g1', 'g1k']}, 0),
              ('masking v2 (worst of 2 runs)', {'rtl': ['v2r', 'v2s'], 'gsim': ['g2', 'g2k']}, 0)]
    panels = [('rtl', ['value'], 'RTL value model'), ('rtl', ['transition'], 'RTL datapath transitions'),
              ('gsim', ['glitch_b0', 'glitch_b1', 'glitch_b2', 'glitch_b3'], 'gate level, glitch-aware')]
    fig, axs = plt.subplots(1, 3, figsize=(7.4, 2.7), sharey=True)
    for a, (sim, ch, title) in zip(axs, panels):
        x = np.arange(len(gad))
        for j, (lab, tags, off) in enumerate(series):
            vals = [mx(tags[sim], sim, t + off, ch) for g, t in gad]
            a.bar(x + (j - 1.5) * 0.2, vals, 0.19, color=[C[1], C[3], C[4], C[0]][j], label=lab)
        a.axhline(4.5, color=INK2, ls='--', lw=1)
        a.set_yscale('log'); a.set_xticks(x); a.set_xticklabels([g.replace(' ', '\n', 1) for g, t in gad], fontsize=7.5)
        a.set_title(title, fontsize=8.5)
    axs[0].set_ylabel('max |t|')
    h, l = axs[0].get_legend_handles_labels()
    fig.legend(h, l, loc='upper center', ncol=4, fontsize=7.5)
    fig.tight_layout(rect=(0, 0, 1, 0.86))
    save(fig, 'fig_tvla_hardening')


def fig_cpa_gsim():
    rows = rd('cpa_gsim_chosen.csv') if os.path.exists(os.path.join(ROOT, 'results', 'cpa_gsim_chosen.csv')) else rd('cpa_gsim.csv')
    fig, a = plt.subplots(figsize=(4.6, 2.8))
    k = 0
    for cfg in ('unprotected', 'hiding', 'hiding+dvfs'):
        for pm, ls in (('glitch-aware', '-'), ('zero-delay', ':')):
            rr = [r for r in rows if r['config'] == cfg and r['power_model'] == pm]
            if not rr:
                continue
            n = [int(r['n_traces']) for r in rr]
            rk = [min(int(r['rank_pointwise']), int(r['rank_integrated'])) + 1 for r in rr]
            a.plot(n, rk, ls, marker='o', ms=3, color=C[k], label='%s, %s' % (cfg, pm))
        k += 1
    a.set_xscale('log'); a.set_yscale('log'); a.set_xlabel('traces (chosen ciphertexts)'); a.set_ylabel('rank of true s0 + 1 (best attack)')
    a.legend(fontsize=6.5, loc='upper left', bbox_to_anchor=(1.01, 1.0))
    fig.set_size_inches(6.4, 2.8)
    save(fig, 'fig_cpa_gsim')


def fig_keccak_cg():
    rows = rd('energy_cg.csv')
    en = {(r['variant'], r['op']): float(r['total_uJ']) for r in rd('energy.csv')}
    ops = ['KeyGen', 'Encaps', 'Decaps']
    fig, a = plt.subplots(figsize=(4.4, 2.6))
    x = np.arange(len(ops))
    a.bar(x - 0.2, [en[('isek', o)] for o in ops], 0.38, color=C[1], label='Keccak unit, free-running clock')
    a.bar(x + 0.2, [float(next(r for r in rows if r['variant'] == 'isek_cg' and r['op'] == o)['total_uJ']) for o in ops],
          0.38, color=C[0], label='clock-gated Keccak unit')
    a.set_xticks(x); a.set_xticklabels(ops); a.set_ylabel('energy per operation (µJ)')
    a.legend(fontsize=7.5)
    save(fig, 'fig_keccak_cg')


if __name__ == '__main__':
    for f in (fig_speed, fig_profile, fig_tvla, fig_cpa, fig_fl, fig_energy, fig_network, fig_fl_ablation, fig_tvla_masked,
              fig_tvla_hardening, fig_cpa_gsim, fig_keccak_cg):
        try:
            f(); print('ok', f.__name__)
        except FileNotFoundError as e:
            print('skip', f.__name__, e)
    if os.path.exists(os.path.join(ROOT, 'results', 'closed_loop_cpa.csv')):
        fig_cpa('closed_loop_cpa.csv', 'policy', 'fig_closed_loop_cpa'); print('ok closed loop cpa')
