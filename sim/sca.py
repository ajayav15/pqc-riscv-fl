"""
sca.py : side-channel evaluation of the synthesized kyber_ise netlist.

Traces are per-cycle energies (pJ) from gate-level simulation of the
secret-dependent step of ML-KEM decapsulation (basemul of the NTT-domain secret
s_hat with the ciphertext-derived u_hat, K = 2, two coefficient-pair words),
see ise_trace.py. On top of the noiseless gate-level energy we model the
measurement chain and the DVFS countermeasure:

  observed[t] = g * E[warp(t)] + N(0, sigma^2)
    g      : per-trace gain; 1 without DVFS, (V/1.1)^2 with V ~ U[0.9, 1.1] V
             when the DVFS mitigation is active (dynamic energy ~ V^2)
    warp   : with DVFS the clock period changes per trace (f ~ U[0.8, 1.2] f0)
             while the probe samples at a fixed rate of one sample per
             nominal cycle (linear interpolation of the energy waveform)
    sigma  : measurement noise (pJ); default chosen from the trace statistics

Analyses
  * TVLA (fixed-vs-random secret, Welch t-test, |t| > 4.5)
  * CPA on one 12-bit secret coefficient s0 (3329 hypotheses) with the
    Hamming weight of the multiplier product registers as leakage model;
    both a point-wise attack and an "integrated" attack (moving sum over a
    window, the standard answer to shuffling / random delays) are run.
"""
import os
import sys
import time
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(HERE, '..', 'sw'))
import ise_trace as IT   # noqa: E402
import golden as G       # noqa: E402

Q = G.Q
CFG_OFF = 0
CFG_HW = 0x1 | 0x2 | (8 << 4) | (3 << 8)      # dummy (p=1/2, 1..4 per op) + issue shuffle
ZETAS = [G.ZETAS[64], (Q - G.ZETAS[64]) % Q]
HW = np.array([bin(i).count('1') for i in range(1 << 16)], dtype=np.float32)


def hw(x):
    x = np.asarray(x, dtype=np.int64)
    return HW[x & 0xFFFF] + HW[(x >> 16) & 0xFFFF]


def gen(n, cfg, s_fixed=None, u_mode='random', rng=None, batch=1500):
    """noiseless gate-level traces. s,u: (n, K=2, words=2) packed words."""
    rng = rng or np.random.default_rng()
    pk = lambda a: (a[..., 1] << 16) | a[..., 0]
    if s_fixed is None:
        s = pk(rng.integers(0, Q, (n, 2, 2, 2)))
    else:
        s = np.broadcast_to(s_fixed, (n, 2, 2)).copy()
    if u_mode == 'random':
        u = pk(rng.integers(0, Q, (n, 2, 2, 2)))
    elif u_mode == 'fixed':
        u = np.broadcast_to(pk(rng.integers(0, Q, (1, 2, 2, 2))), (n, 2, 2)).copy()
    elif u_mode == 'chosen':
        # structured chosen ciphertexts (e.g. plaintext-checking / key-mismatch attacks):
        # a single small non-zero coefficient per polynomial, the rest zero
        c = np.zeros((n, 2, 2, 2), dtype=np.int64)
        c[:, :, 0, 0] = rng.integers(0, 8, (n, 2))
        u = pk(c)
    else:
        raise ValueError(u_mode)
    out, L = [], None
    for i in range(0, n, batch):
        sl = slice(i, min(n, i + batch))
        seeds = rng.integers(1, 2 ** 31, sl.stop - sl.start)
        T, mism = IT.simulate(s[sl], u[sl], ZETAS, cfg=cfg, seeds=seeds, maxcyc=600)
        if mism:
            raise RuntimeError('gate-level result mismatch: %d' % mism)
        out.append(T)
    L = max(t.shape[1] for t in out)
    out = [np.pad(t, ((0, 0), (0, L - t.shape[1])), mode='edge') for t in out]
    return np.concatenate(out), s, u


def observe(T, sigma, dvfs=False, rng=None):
    rng = rng or np.random.default_rng()
    n, L = T.shape
    X = T.astype(np.float64).copy()
    if dvfs:
        V = rng.uniform(0.9, 1.1, n)
        X *= ((V / 1.1) ** 2)[:, None]
        f = rng.uniform(0.8, 1.2, n)          # clock frequency relative to nominal
        t = np.arange(L)
        for i in range(n):
            X[i] = np.interp(t * f[i], t, X[i], right=X[i, -1])
    return X + rng.normal(0, sigma, X.shape)


def welch_t(A, B):
    ma, mb = A.mean(0), B.mean(0)
    va, vb = A.var(0, ddof=1), B.var(0, ddof=1)
    return (ma - mb) / np.sqrt(va / len(A) + vb / len(B) + 1e-30)


def cpa_models(u_lo):
    """hypothesis matrix (n, 3329) for s0: HW of the reduced product s0*u0 mod q
    (multiplier output register out_r)."""
    k = np.arange(Q, dtype=np.int64)
    return hw(u_lo[:, None].astype(np.int64) * k[None, :] % Q).astype(np.float32)


def public_nuisance(u):
    """regressors for leakage of the public ciphertext operands themselves
    (HW and value of every 12-bit lane of u); u: (n, K, words) packed"""
    lanes = np.stack([(u[:, k, w] >> sh) & 0xFFF for k in range(u.shape[1])
                      for w in range(u.shape[2]) for sh in (0, 16)], 1)
    return np.concatenate([np.ones((len(u), 1)), hw(lanes), lanes / 4096.0], 1)


def remove_public(X, u):
    """the attacker knows u: regress its direct leakage out of the traces so that
    the CPA is not dominated by key-independent ghost peaks (e.g. k = 1)"""
    N = public_nuisance(u)
    return X - N @ np.linalg.lstsq(N, X, rcond=None)[0]


def cpa_rank(X, H, true_k, steps, integrate=0, chunk=5000):
    """rank of the true key after the first n traces for n in steps.
    integrate>0: moving sum of that width (defeats shuffling / random delay).
    Streaming Pearson correlation: sums are accumulated chunk by chunk, so the
    (n x 3329) hypothesis matrix is never copied."""
    if integrate:
        c = np.cumsum(np.pad(X, ((0, 0), (1, 0))), axis=1)
        X = c[:, integrate:] - c[:, :-integrate]
    X = np.asarray(X, dtype=np.float64)
    nk, L = H.shape[1], X.shape[1]
    sh, shh = np.zeros(nk), np.zeros(nk)
    sx, sxx = np.zeros(L), np.zeros(L)
    shx = np.zeros((nk, L))
    ranks, peak, done = [], None, 0
    for n in steps:
        while done < n:
            e = min(n, done + chunk)
            Hc = np.asarray(H[done:e], dtype=np.float64); Xc = X[done:e]
            sh += Hc.sum(0); shh += (Hc * Hc).sum(0)
            sx += Xc.sum(0); sxx += (Xc * Xc).sum(0)
            shx += Hc.T @ Xc
            done = e
        num = shx - np.outer(sh, sx) / n
        den = np.sqrt(np.maximum(shh - sh * sh / n, 0))[:, None] * np.sqrt(np.maximum(sxx - sx * sx / n, 0))[None, :] + 1e-12
        rho = np.nan_to_num(np.abs(num / den)).max(1)
        rho[0] = 0.0                                        # k = 0: constant hypothesis
        ranks.append(int((rho > rho[true_k]).sum()))
        peak = rho
    return ranks, peak


if __name__ == '__main__':
    t0 = time.time()
    T, s, u = gen(64, CFG_OFF, rng=np.random.default_rng(1))
    print('traces', T.shape, 'mean %.2f pJ/cyc, per-sample sd (data) %.3f pJ, %.1fs'
          % (T.mean(), T.std(0).mean(), time.time() - t0))
