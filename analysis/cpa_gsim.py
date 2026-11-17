"""
cpa_gsim.py : CPA on glitch-aware gate-level traces of the full SoC core
(sim/gsim, firmware sw/fw/cpa_gs.c) against the first secret coefficient s0
of s_hat[0], hypothesis HW(s0 * u0 mod q) as in sim/sca.py, after regressing
out the leakage of the public ciphertext lanes.

Samples: the four time bins of every clock cycle (0-1, 1-2, 2-4, 4-10 ns),
i.e. a 400 MS/s view of the glitch-aware power, plus Gaussian noise (sigma
0.125 pJ per bin). DVFS (hiding + DVFS) is applied on top as in sim/sca.py:
per-trace V^2 gain and clock-period warp at a fixed sampling rate.
Also reported: the same attack on the zero-delay (functional toggle) energy.

  python3 analysis/cpa_gsim.py <dir_mode0> <dir_mode1> [--chosen]
Output: results/cpa_gsim.csv (known random ciphertexts) or results/cpa_gsim_chosen.csv
(chosen ciphertexts with zero lanes, firmware built with -DCHOSEN=1)
"""
import csv
import os
import sys
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
sys.path.insert(0, os.path.join(ROOT, 'sim'))
import sca  # noqa: E402

STEPS = [100, 200, 500, 1000, 2000, 5000, 10000, 15000, 17500]


def load(d):
    log = open(os.path.join(d, 'grun.log')).read().split('\n')
    s0 = int(log[0].split('=')[1], 16) & 0xFFF
    us = [l for l in log[1:] if len(l) == 16 and all(c in '0123456789abcdef' for c in l)]
    U = np.array([[int(l[:8], 16), int(l[8:], 16)] for l in us], dtype=np.int64)
    raw = np.fromfile(os.path.join(d, 'gleak.bin'), dtype=np.uint8)
    T, pos = [], 0
    while pos < len(raw):
        n = int(raw[pos:pos + 4].view(np.uint32)[0]); pos += 4
        if pos + 10 * n > len(raw):                              # run stopped mid-window
            break
        T.append(raw[pos:pos + 10 * n].view(np.uint16).reshape(n, 5).astype(np.float32) * 0.01); pos += 10 * n
    n = min(len(T), len(U))
    L = max(len(t) for t in T[:n])
    T = np.stack([np.pad(t, ((0, L - len(t)), (0, 0)), mode='edge') for t in T[:n]])
    return s0, U[:n], T


def attack(X, U, s0, steps, chosen=False):
    u = U.reshape(len(U), 2, 1)
    X = sca.remove_public(X.astype(np.float64), u).astype(np.float32)
    steps = [s for s in steps if s <= len(X)]
    if not chosen:
        H = sca.cpa_models(U[:, 0] & 0xFFF)
        r_pt, _ = sca.cpa_rank(X, H, s0, steps)
        r_in, _ = sca.cpa_rank(X, H, s0, steps, integrate=16)
        return steps, r_pt, r_in
    # chosen ciphertext u0 = (0, v), u1 = 0: the product s0 * v follows a zero
    # product in the multiplier; models: HW of the reduced and of the raw product
    v = (U[:, 0] >> 16) & 0xFFF
    k = np.arange(sca.Q, dtype=np.int64)
    best_pt, best_in = None, None
    for H in (sca.cpa_models(v), sca.hw(v[:, None] * k[None, :]).astype(np.float32)):
        r_pt, _ = sca.cpa_rank(X, H, s0, steps)
        r_in, _ = sca.cpa_rank(X, H, s0, steps, integrate=16)
        best_pt = r_pt if best_pt is None else [min(a, b) for a, b in zip(best_pt, r_pt)]
        best_in = r_in if best_in is None else [min(a, b) for a, b in zip(best_in, r_in)]
    return steps, best_pt, best_in


def main():
    chosen = '--chosen' in sys.argv
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    rows = []
    rng = np.random.default_rng(5)
    for mode, d in enumerate(args[:2]):
        s0, U, T = load(d)
        print('mode', mode, 'traces', T.shape, 's0', s0, flush=True)
        G = T[:, :, :4].reshape(len(T), -1)                      # glitch-aware, 4 bins per cycle
        Z = T[:, :, 4]                                           # zero-delay, per cycle
        configs = [('glitch-aware', G, 0.125), ('zero-delay', Z, 0.25)]
        for name, X, sig in configs:
            variants = [(False,)] if mode == 0 else [(False,), (True,)]
            for (dvfs,) in variants:
                Xo = sca.observe(X, sig, dvfs=dvfs, rng=rng)
                steps, rp, ri = attack(Xo, U, s0, STEPS, chosen)
                cfg = ['unprotected', 'hiding', 'hiding+dvfs'][mode + int(dvfs)]
                for n, a, b in zip(steps, rp, ri):
                    rows.append(dict(config=cfg, power_model=name, n_traces=n, rank_pointwise=a, rank_integrated=b))
                print(cfg, name, 'pointwise', rp, 'integrated', ri, flush=True)
    with open(os.path.join(ROOT, 'results', 'cpa_gsim%s.csv' % ('_chosen' if chosen else '')), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0])); w.writeheader(); w.writerows(rows)


if __name__ == '__main__':
    main()
