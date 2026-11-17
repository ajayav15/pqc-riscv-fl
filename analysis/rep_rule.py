"""
rep_rule.py : repetition rule next to the federated MLP.

Repeated (or nearly repeated) inputs make consecutive template residuals
coherent. The MLP sees that feature (hist_coherence) but, trained mostly on
non-evasive replays that are also visible in the request rate, it gives it
little weight. The rule flags a window when the node's normalized
hist_coherence exceeds the q-quantile of its own benign training windows times
a margin; the window score becomes max(MLP, rule). The threshold is local (no
data leaves the node).
Output: results/rep_rule.csv (F1/FPR/per-type TPR with and without the rule)
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

IDX = S.FEATURE_NAMES.index('hist_coherence')
Q, MARGIN = 0.999, 1.25


def rule_thr(n):
    b = n['X'][n['y'] == 0][:, IDX]
    return np.quantile(b, Q) * MARGIN


def main():
    src = D.KEMSource()
    rows = []
    for seed in R.SEEDS:
        nodes = R.build(src, seed)
        nin = nodes[0]['X'].shape[1]
        g, _ = F.fedavg([(n['X'], n['y']) for n in nodes], nin, rounds=R.ROUNDS, seed=seed)
        pm = [g.predict(n['Xt']) for n in nodes]
        pr = [np.maximum(p, (n['Xt'][:, IDX] > rule_thr(n)).astype(float)) for p, n in zip(pm, nodes)]
        for name, P in (('fedavg', pm), ('fedavg+rule', pr)):
            m = R.per_type(P, nodes)
            m.update(seed=seed, method=name)
            rows.append(m)
            print(seed, name, {k: round(v, 3) for k, v in m.items() if isinstance(v, float)}, flush=True)
    keys = ['method', 'seed', 'f1', 'auc', 'fpr', 'tpr_unseen', 'tpr_REP', 'tpr_REP_evasive', 'tpr_CC', 'tpr_EMP', 'tpr_GLT',
            'tpr_CC_evasive', 'tpr_EMP_evasive', 'tpr_GLT_evasive']
    with open(os.path.join(ROOT, 'results', 'rep_rule.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=keys, extrasaction='ignore'); w.writeheader(); w.writerows(rows)
    for name in ('fedavg', 'fedavg+rule'):
        rr = [r for r in rows if r['method'] == name]
        print(name, {k: round(float(np.mean([r[k] for r in rr])), 3) for k in keys[2:]})


if __name__ == '__main__':
    main()
