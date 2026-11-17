"""
fedlearn.py : lightweight federated learning for side-channel anomaly
detection on edge nodes (pure NumPy, no deep-learning framework needed).

  * TinyMLP     : int8-deployable MLP (in -> 32 -> 16 -> 1), sigmoid output
  * fedavg()    : FedAvg / FedProx with optional client-level DP
                  (L2 clipping + Gaussian noise, RDP accounting)
  * local_only(), centralized() : baselines
"""
import numpy as np


def sigmoid(x):
    return 1.0 / (1.0 + np.exp(-np.clip(x, -30, 30)))


class TinyMLP:
    def __init__(self, nin, h1=32, h2=16, seed=0):
        r = np.random.default_rng(seed)
        self.p = {
            'W1': r.normal(0, np.sqrt(2 / nin), (nin, h1)), 'b1': np.zeros(h1),
            'W2': r.normal(0, np.sqrt(2 / h1), (h1, h2)), 'b2': np.zeros(h2),
            'W3': r.normal(0, np.sqrt(2 / h2), (h2, 1)), 'b3': np.zeros(1),
        }

    # parameters <-> flat vector
    def get(self):
        return np.concatenate([self.p[k].ravel() for k in sorted(self.p)])

    def set(self, v):
        i = 0
        for k in sorted(self.p):
            n = self.p[k].size
            self.p[k] = v[i:i + n].reshape(self.p[k].shape).copy()
            i += n

    def nparams(self):
        return sum(v.size for v in self.p.values())

    def forward(self, X):
        p = self.p
        z1 = X @ p['W1'] + p['b1']; a1 = np.maximum(z1, 0)
        z2 = a1 @ p['W2'] + p['b2']; a2 = np.maximum(z2, 0)
        z3 = a2 @ p['W3'] + p['b3']
        return sigmoid(z3[:, 0]), (X, z1, a1, z2, a2)

    def grads(self, X, y, pos_weight=1.0):
        p = self.p
        out, (X, z1, a1, z2, a2) = self.forward(X)
        w = np.where(y > 0.5, pos_weight, 1.0)
        d3 = ((out - y) * w / len(y))[:, None]
        g = {'W3': a2.T @ d3, 'b3': d3.sum(0)}
        d2 = (d3 @ p['W3'].T) * (z2 > 0)
        g['W2'] = a1.T @ d2; g['b2'] = d2.sum(0)
        d1 = (d2 @ p['W2'].T) * (z1 > 0)
        g['W1'] = X.T @ d1; g['b1'] = d1.sum(0)
        return g

    def train(self, X, y, epochs=1, lr=0.01, bs=64, seed=0, prox_mu=0.0, w_glob=None, pos_weight=1.0):
        r = np.random.default_rng(seed)
        # Adam state is local to each call (stateless clients)
        m = {k: np.zeros_like(v) for k, v in self.p.items()}
        s = {k: np.zeros_like(v) for k, v in self.p.items()}
        t = 0
        if w_glob is not None:
            ref = TinyMLP.__new__(TinyMLP); ref.p = {k: v.copy() for k, v in self.p.items()}; ref.set(w_glob)
        for _ in range(epochs):
            idx = r.permutation(len(y))
            for i in range(0, len(y), bs):
                b = idx[i:i + bs]
                g = self.grads(X[b], y[b], pos_weight)
                t += 1
                for k in self.p:
                    gk = g[k]
                    if prox_mu > 0 and w_glob is not None:
                        gk = gk + prox_mu * (self.p[k] - ref.p[k])
                    m[k] = 0.9 * m[k] + 0.1 * gk
                    s[k] = 0.999 * s[k] + 0.001 * gk * gk
                    mh = m[k] / (1 - 0.9 ** t); sh = s[k] / (1 - 0.999 ** t)
                    self.p[k] -= lr * mh / (np.sqrt(sh) + 1e-8)

    def predict(self, X):
        return self.forward(X)[0]

    def quantized(self):
        """symmetric per-tensor int8 copy (what is deployed on the RV32 node)"""
        q = TinyMLP.__new__(TinyMLP)
        q.p = {}
        for k, v in self.p.items():
            sc = np.max(np.abs(v)) / 127 if np.max(np.abs(v)) > 0 else 1.0
            q.p[k] = np.round(v / sc).clip(-127, 127) * sc
        return q

    def macs(self):
        W = [self.p['W1'], self.p['W2'], self.p['W3']]
        return sum(w.size for w in W)


def metrics(y, prob, thr=0.5):
    pred = (prob >= thr).astype(int)
    tp = int(((pred == 1) & (y == 1)).sum()); tn = int(((pred == 0) & (y == 0)).sum())
    fp = int(((pred == 1) & (y == 0)).sum()); fn = int(((pred == 0) & (y == 1)).sum())
    acc = (tp + tn) / max(1, len(y))
    prec = tp / max(1, tp + fp); rec = tp / max(1, tp + fn)
    f1 = 2 * prec * rec / max(1e-12, prec + rec)
    fpr = fp / max(1, fp + tn)
    # ROC AUC (rank based)
    o = np.argsort(prob); ranks = np.empty(len(prob)); ranks[o] = np.arange(1, len(prob) + 1)
    npos, nneg = (y == 1).sum(), (y == 0).sum()
    auc = (ranks[y == 1].sum() - npos * (npos + 1) / 2) / max(1, npos * nneg)
    return dict(acc=acc, prec=prec, rec=rec, f1=f1, fpr=fpr, auc=float(auc))


def rdp_epsilon(noise_mult, rounds, delta=1e-5):
    """client-level Gaussian mechanism, full participation, RDP composition"""
    if noise_mult <= 0:
        return float('inf')
    alphas = np.concatenate([np.linspace(1.1, 10, 90), np.arange(11, 256)])
    eps = rounds * alphas / (2 * noise_mult ** 2) + np.log(1 / delta) / (alphas - 1)
    return float(eps.min())


def fedavg(clients, nin, rounds=40, local_epochs=2, lr=0.005, frac=1.0, prox_mu=0.0,
           dp_clip=None, dp_noise=0.0, seed=0, val=None, pos_weight=1.0, log=None):
    """clients: list of (X, y). Returns global model and per-round history."""
    r = np.random.default_rng(seed)
    g = TinyMLP(nin, seed=seed)
    w = g.get()
    hist = []
    sizes = np.array([len(c[1]) for c in clients], dtype=float)
    for rnd in range(rounds):
        m = max(1, int(round(frac * len(clients))))
        sel = r.choice(len(clients), m, replace=False)
        deltas, wts = [], []
        for ci in sel:
            X, y = clients[ci]
            loc = TinyMLP(nin); loc.set(w)
            loc.train(X, y, epochs=local_epochs, lr=lr, seed=int(r.integers(1 << 30)),
                      prox_mu=prox_mu, w_glob=w if prox_mu > 0 else None, pos_weight=pos_weight)
            d = loc.get() - w
            if dp_clip is not None:
                n = np.linalg.norm(d)
                d = d * min(1.0, dp_clip / (n + 1e-12))
            deltas.append(d); wts.append(sizes[ci])
        if dp_clip is not None:
            # uniform weighting under DP so sensitivity is bounded by clip/m
            agg = np.mean(deltas, axis=0)
            agg += r.normal(0, dp_noise * dp_clip / m, agg.shape)
        else:
            wts = np.array(wts) / np.sum(wts)
            agg = np.sum([wi * di for wi, di in zip(wts, deltas)], axis=0)
        w = w + agg
        g.set(w)
        if val is not None:
            hist.append(metrics(val[1], g.predict(val[0])))
            if log:
                log(rnd, hist[-1])
    return g, hist


def train_central(X, y, nin, epochs=40, lr=0.005, seed=0, pos_weight=1.0):
    m = TinyMLP(nin, seed=seed)
    m.train(X, y, epochs=epochs, lr=lr, seed=seed, pos_weight=pos_weight)
    return m
