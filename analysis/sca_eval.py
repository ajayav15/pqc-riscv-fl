"""
sca_eval.py : gate-level side-channel evaluation of the ISE (objective 3) and
generation of the ML-KEM trace corpus for the federated detector (objective 2).

  gen   : simulate and store noiseless gate-level traces  -> data/kem_traces.npz
  eval  : TVLA + CPA for  none / hiding (dummy+shuffle) / hiding+DVFS
          -> results/tvla.csv, results/cpa.csv, results/sca_summary.json
"""
import csv
import json
import os
import sys
import time
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
sys.path.insert(0, os.path.join(ROOT, 'sim'))
import sca  # noqa: E402

DATA = os.path.join(ROOT, 'data', 'kem_traces.npz')
N_TVLA = 6000          # per group
N_CPA = 20000
N_CC, N_REP = 6000, 6000
SIGMA = 0.25           # pJ measurement noise (data-dependent sd ~0.12 pJ per sample)


def gen():
    rng = np.random.default_rng(2026)
    d = {}
    t0 = time.time()
    s_fix = ((rng.integers(0, sca.Q, (2, 2, 2))) * np.array([1, 1 << 16])).sum(-1)
    d['s_fix'] = s_fix
    for tag, cfg in (('off', sca.CFG_OFF), ('hw', sca.CFG_HW)):
        T, s, u = sca.gen(N_TVLA, cfg, s_fixed=s_fix, rng=rng); d['tvla_fix_' + tag] = T
        T, s, u = sca.gen(N_TVLA, cfg, rng=rng);                d['tvla_rnd_' + tag] = T
        T, s, u = sca.gen(N_CPA, cfg, s_fixed=s_fix, rng=rng)
        d['cpa_' + tag], d['cpa_u_' + tag] = T, u
        print(tag, 'done', round(time.time() - t0), 's', flush=True)
    # detector corpus (unprotected device): benign random ciphertexts, chosen and repeated ones
    T, s, u = sca.gen(N_CC, sca.CFG_OFF, rng=rng, u_mode='chosen');  d['det_cc'] = T
    T, s, u = sca.gen(N_REP, sca.CFG_OFF, rng=rng, u_mode='fixed');  d['det_rep'] = T
    T, s, u = sca.gen(N_CC, sca.CFG_HW, rng=rng, u_mode='chosen');   d['det_cc_hw'] = T
    os.makedirs(os.path.dirname(DATA), exist_ok=True)
    d['ck_corrected'] = np.array(0.0)          # generated with the corrected energy model
    np.savez_compressed(DATA, **d)
    print('saved', DATA, round(time.time() - t0), 's')


def pad_to(A, L):
    return np.pad(A, ((0, 0), (0, L - A.shape[1])), mode='edge') if A.shape[1] < L else A[:, :L]


def fix_clock_offset():
    """Corpora generated before the clock-pin energy fix (netlist.py) carry a
    constant extra e_ck_legacy - e_ck pJ in every cycle; remove it once."""
    d = dict(np.load(DATA))
    if 'ck_corrected' in d:
        return
    nl = sca.IT.load_netlist()
    delta = nl.e_ck_legacy - nl.e_ck
    for k in list(d):
        if k.startswith(('tvla_', 'det_')) or (k.startswith('cpa_') and not k.startswith('cpa_u_')):
            d[k] = d[k] - delta
    d['ck_corrected'] = np.array(delta)
    np.savez_compressed(DATA, **d)
    print('clock offset corrected by %.3f pJ/cycle' % delta)


def evaluate():
    fix_clock_offset()
    d = np.load(DATA)
    rng = np.random.default_rng(7)
    s0 = int(d['s_fix'][0, 0] & 0xFFF)          # target: low coefficient of word 0, k = 0
    configs = [('none', 'off', False), ('hiding', 'hw', False), ('hiding+dvfs', 'hw', True)]
    steps_t = [250, 500, 1000, 2000, 4000, 6000]
    steps_c = [25, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000]
    tv_rows, cpa_rows, summ = [], [], {'sigma_pJ': SIGMA, 'target_s0': s0}
    for name, tag, dvfs in configs:
        A, B = d['tvla_fix_' + tag], d['tvla_rnd_' + tag]
        L = max(A.shape[1], B.shape[1])
        A = sca.observe(pad_to(A, L), SIGMA, dvfs, rng)
        B = sca.observe(pad_to(B, L), SIGMA, dvfs, rng)
        for n in steps_t:
            t = sca.welch_t(A[:n], B[:n])
            tv_rows.append(dict(config=name, n_per_group=n, max_abs_t=round(float(np.abs(t).max()), 2),
                                leaky_samples=int((np.abs(t) > 4.5).sum()), samples=L))
        print('TVLA', name, tv_rows[-1], flush=True)
        X = sca.remove_public(sca.observe(d['cpa_' + tag], SIGMA, dvfs, rng), d['cpa_u_' + tag])
        H = sca.cpa_models(d['cpa_u_' + tag][:, 0, 0] & 0xFFF)
        for integ in (0, 16):
            ranks, rho = sca.cpa_rank(X, H, s0, steps_c, integrate=integ)
            first = next((n for n, r in zip(steps_c, ranks)
                          if r == 0 and all(rr == 0 for rr in ranks[steps_c.index(n):])), None)
            for n, r in zip(steps_c, ranks):
                cpa_rows.append(dict(config=name, attack='integrated' if integ else 'pointwise',
                                     n_traces=n, rank=r))
            summ['%s/%s' % (name, 'integrated' if integ else 'pointwise')] = dict(
                traces_to_rank0=first, final_rank=ranks[-1])
            print('CPA', name, integ, ranks, flush=True)
    os.makedirs(os.path.join(ROOT, 'results'), exist_ok=True)
    for fn, rows in (('tvla.csv', tv_rows), ('cpa.csv', cpa_rows)):
        with open(os.path.join(ROOT, 'results', fn), 'w', newline='') as f:
            w = csv.DictWriter(f, fieldnames=list(rows[0])); w.writeheader(); w.writerows(rows)
    json.dump(summ, open(os.path.join(ROOT, 'results', 'sca_summary.json'), 'w'), indent=2)
    print(json.dumps(summ, indent=2))


if __name__ == '__main__':
    if 'gen' in sys.argv[1:] or not os.path.exists(DATA):
        gen()
    if 'eval' in sys.argv[1:]:
        evaluate()
