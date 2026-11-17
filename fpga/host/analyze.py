"""
analyze.py : TVLA and CPA on measured FPGA traces (from capture.py), mirroring the
gate-level analysis (sim/sca.py, analysis/sca_eval.py, analysis/tvla_masked.py).

  python3 analyze.py tvla traces_tvla_0.npz
  python3 analyze.py cpa  traces_cpa_0.npz --s0 <true secret coefficient, optional>

CPA target: the low coefficient s0 of the first coefficient pair of s_hat[0]
(window 'B' of sw/fw/sca_app.c); model HW(s0 * u0 mod q) after regressing out the
leakage of the public ciphertext words (as in sim/sca.py). The true s0 for the
default coins is printed by: fpga/sim/gen_vec --s0
"""
import argparse
import numpy as np

Q = 3329
HW = np.array([bin(i).count('1') for i in range(1 << 16)], dtype=np.float32)


def welch(A, B):
    return (A.mean(0) - B.mean(0)) / np.sqrt(A.var(0, ddof=1) / len(A) + B.var(0, ddof=1) / len(B))


def tvla(path):
    d = np.load(path)
    T, c = d['traces'], d['meta'].astype(int)
    for n in (1000, 2000, 5000, 10000, 20000, len(T)):
        if n > len(T):
            continue
        t = welch(T[:n][c[:n] == 0], T[:n][c[:n] == 1])
        print('n=%6d  max|t| = %.2f  leaky samples = %d' % (n, np.abs(t).max(), (np.abs(t) > 4.5).sum()))


def cpa(path, s0=None, integrate=0):
    d = np.load(path)
    X, co = d['traces'].astype(np.float64), d['meta'].astype(np.int64)
    N = np.concatenate([np.ones((len(co), 1)), HW[co], co / 4096.0], 1)     # public-input leakage
    X = X - N @ np.linalg.lstsq(N, X, rcond=None)[0]
    if integrate:
        c = np.cumsum(np.pad(X, ((0, 0), (1, 0))), axis=1)
        X = c[:, integrate:] - c[:, :-integrate]
    k = np.arange(Q)
    H = HW[(co[:, 0:1] * k[None, :]) % Q]
    for n in (100, 500, 1000, 5000, 10000, 20000, len(X)):
        if n > len(X):
            continue
        Xn = X[:n] - X[:n].mean(0); Hn = H[:n] - H[:n].mean(0)
        rho = np.abs((Hn.T @ Xn) / (np.sqrt((Hn ** 2).sum(0))[:, None] * np.sqrt((Xn ** 2).sum(0))[None, :] + 1e-12))
        rho = np.nan_to_num(rho).max(1); rho[0] = 0
        best = int(np.argmax(rho))
        msg = 'n=%6d  best s0 = %4d (rho %.3f)' % (n, best, rho[best])
        if s0 is not None:
            msg += '  rank of true s0 = %d' % int((rho > rho[s0]).sum())
        print(msg)


if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument('kind', choices=['tvla', 'cpa'])
    ap.add_argument('path')
    ap.add_argument('--s0', type=int)
    ap.add_argument('--integrate', type=int, default=0)
    a = ap.parse_args()
    tvla(a.path) if a.kind == 'tvla' else cpa(a.path, a.s0, a.integrate)
