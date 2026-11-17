"""
det_lite.py : cheaper on-node detector variants (feature subsets) trained with
FedAvg on the same non-IID gate-level window streams as fl/run_fl.py.
  full  : all 38 features
  noFFT : without the 8 spectral band features (the 128-point FFT is the most
          expensive part of the C detector)
  lite  : without the spectral bands and the two correlation features
Output: results/det_lite.csv (mean over the seeds of fl/run_fl.py)
"""
import csv
import os
import sys
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
sys.path.insert(0, os.path.join(ROOT, 'fl'))
import scenarios as S   # noqa: E402
import fedlearn as F    # noqa: E402
import datasets as D    # noqa: E402
import run_fl as R      # noqa: E402

N = S.FEATURE_NAMES
BANDS = [N.index('band%d' % i) for i in range(8)]
RHO = [N.index('rho_template'), N.index('rho_prev')]
VARIANTS = {'full': [i for i in range(len(N))],
            'noFFT': [i for i in range(len(N)) if i not in BANDS],
            'lite': [i for i in range(len(N)) if i not in BANDS + RHO]}


def main():
    src = D.KEMSource()
    rows = []
    for seed in R.SEEDS:
        nodes = R.build(src, seed)
        for name, cols in VARIANTS.items():
            sub = [dict(n, X=n['X'][:, cols], Xt=n['Xt'][:, cols]) for n in nodes]
            g, _ = F.fedavg([(n['X'], n['y']) for n in sub], len(cols), rounds=R.ROUNDS, seed=seed)
            gq = g.quantized()
            m = R.per_type([gq.predict(n['Xt']) for n in sub], sub)
            m.update(variant=name, seed=seed, nin=len(cols), macs=g.macs())
            rows.append(m)
            print(seed, name, round(m['f1'], 3), round(m['fpr'], 4), round(m['tpr_unseen'], 3), flush=True)
    keys = ['variant', 'seed', 'nin', 'macs', 'f1', 'auc', 'fpr', 'tpr_unseen', 'tpr_CC', 'tpr_REP', 'tpr_EMP', 'tpr_GLT',
            'tpr_REP_evasive', 'tpr_EMP_evasive', 'tpr_GLT_evasive']
    with open(os.path.join(ROOT, 'results', 'det_lite.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=keys, extrasaction='ignore'); w.writeheader(); w.writerows(rows)
    for name in VARIANTS:
        rr = [r for r in rows if r['variant'] == name]
        print(name, {k: round(float(np.mean([r[k] for r in rr])), 3) for k in keys[2:]})


if __name__ == '__main__':
    main()
