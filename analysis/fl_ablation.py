"""
fl_ablation.py : sensitivity of the federated detector (FedAvg vs local-only) on the
gate-level ML-KEM window streams to the number of nodes, the non-IID degree (attack
types per node), the sensor noise and the local epochs. 3 seeds each; mean and 95%
confidence interval (t distribution, n = 3). Output: results/fl_ablation.csv
"""
import csv
import os
import sys
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
sys.path.insert(0, os.path.join(ROOT, 'fl'))
import fedlearn as F   # noqa: E402
import datasets as D   # noqa: E402
import run_fl as R     # noqa: E402

T95 = 4.303            # t(0.975, df = 2)


def one(src, nodes_n, n_atk, epochs, seed):
    R.N_NODES, R.N_ATK = nodes_n, n_atk
    nodes = R.build(src, seed)
    nin = nodes[0]['X'].shape[1]
    Xv = np.concatenate([n['Xt'] for n in nodes]); yv = np.concatenate([n['yt'] for n in nodes])
    g, _ = F.fedavg([(n['X'], n['y']) for n in nodes], nin, rounds=R.ROUNDS, local_epochs=epochs, seed=seed)
    fed = R.per_type([g.predict(n['Xt']) for n in nodes], nodes)
    loc = [F.train_central(n['X'], n['y'], nin, epochs=R.ROUNDS, seed=seed) for n in nodes]
    lo = R.per_type([m.predict(n['Xt']) for m, n in zip(loc, nodes)], nodes)
    return fed, lo


def main():
    base = dict(nodes=10, n_atk=2, sigma=0.25, epochs=2)
    sweeps = [('nodes', [5, 10, 20]), ('n_atk', [1, 2, 3, 4]), ('sigma', [0.1, 0.25, 0.5, 1.0]), ('epochs', [1, 2, 5])]
    rows = []
    srcs = {}
    for par, vals in sweeps:
        for v in vals:
            cfg = dict(base); cfg[par] = v
            if cfg['sigma'] not in srcs:
                srcs[cfg['sigma']] = D.KEMSource(sigma=cfg['sigma'])
            res = [one(srcs[cfg['sigma']], cfg['nodes'], cfg['n_atk'], cfg['epochs'], s) for s in (0, 1, 2)]
            row = dict(parameter=par, value=v)
            for tag, k in (('fedavg', 0), ('local', 1)):
                for met in ('f1', 'auc', 'fpr', 'tpr_unseen'):
                    a = [r[k][met] for r in res if r[k][met] is not None]
                    if a:
                        row['%s_%s' % (tag, met)] = round(float(np.mean(a)), 3)
                        row['%s_%s_ci95' % (tag, met)] = round(float(T95 * np.std(a, ddof=1) / np.sqrt(len(a))), 3)
            rows.append(row)
            print(row, flush=True)
    keys = []
    for r in rows:
        keys += [k for k in r if k not in keys]
    with open(os.path.join(ROOT, 'results', 'fl_ablation.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=keys); w.writeheader(); w.writerows(rows)


if __name__ == '__main__':
    main()
