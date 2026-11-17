"""
sca_more.py : extended CPA against the hiding countermeasure (item: stronger
countermeasure evaluation). Adds 80,000 gate-level traces of the protected ISE
(same fixed secret as data/kem_traces.npz) for a total of 100,000, and runs
pointwise and integrated CPA (moving sums of 16 and 48 cycles, and the sum over
the whole first base multiplication) with and without the DVFS model.
Outputs results/cpa_extended.csv
"""
import csv
import os
import sys
import time
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
sys.path.insert(0, os.path.join(ROOT, 'sim'))
import sca  # noqa: E402

EXTRA = os.path.join(ROOT, 'data', 'kem_traces_hw_extra.npz')
N_EXTRA = 80000
SIGMA = 0.25


def gen():
    d = np.load(os.path.join(ROOT, 'data', 'kem_traces.npz'))
    rng = np.random.default_rng(4242)
    t0 = time.time()
    T, s, u = sca.gen(N_EXTRA, sca.CFG_HW, s_fixed=d['s_fix'], rng=rng)
    np.savez_compressed(EXTRA, cpa=T, u=u)
    print('generated', T.shape, round(time.time() - t0), 's', flush=True)


def main():
    if not os.path.exists(EXTRA):
        gen()
    d = np.load(os.path.join(ROOT, 'data', 'kem_traces.npz'))
    e = np.load(EXTRA)
    s0 = int(d['s_fix'][0, 0] & 0xFFF)
    A, B = d['cpa_hw'], e['cpa']
    L = max(A.shape[1], B.shape[1])
    pad = lambda X: np.pad(X, ((0, 0), (0, L - X.shape[1])), mode='edge')
    T = np.concatenate([pad(A), pad(B)])
    U = np.concatenate([d['cpa_u_hw'], e['u']])
    # hypotheses as uint8 (HW <= 12), built in chunks to bound memory
    ul = (U[:, 0, 0] & 0xFFF).astype(np.int64)
    H = np.empty((len(ul), sca.Q), dtype=np.uint8)
    for i in range(0, len(ul), 5000):
        H[i:i + 5000] = sca.cpa_models(ul[i:i + 5000]).astype(np.uint8)
    steps = [1000, 5000, 10000, 20000, 50000, 100000]
    rows = []
    rng = np.random.default_rng(9)
    for dvfs in (False, True):
        X = sca.remove_public(sca.observe(T, SIGMA, dvfs, rng), U).astype(np.float32)
        for integ in (0, 16, 48, L):
            ranks, _ = sca.cpa_rank(X, H, s0, steps, integrate=integ if integ < L else L - 1)
            label = {0: 'pointwise', 16: 'moving sum 16', 48: 'moving sum 48'}.get(integ, 'whole window')
            for n, r in zip(steps, ranks):
                rows.append(dict(config='hiding+dvfs' if dvfs else 'hiding', attack=label, n_traces=n, rank=r))
            print('dvfs' if dvfs else 'hiding', label, ranks, flush=True)
    with open(os.path.join(ROOT, 'results', 'cpa_extended.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0])); w.writeheader(); w.writerows(rows)


if __name__ == '__main__':
    main()
