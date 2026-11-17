"""
datasets.py : window streams for the federated side-channel anomaly detector.

Two trace sources share one stream generator:

  KEMSource   gate-level power traces (pJ/cycle) of the synthesized kyber_ise
              netlist executing the secret-key base multiplication of ML-KEM
              decapsulation (analysis/sca_eval.py -> data/kem_traces.npz)
                benign : fixed device key, random valid ciphertexts
                CC     : structured chosen ciphertexts (one small non-zero
                         coefficient), as used by plaintext-checking / key-
                         mismatch side-channel attacks on Kyber
  ASCADSource ASCAD fixed-key database (ANSSI; masked AES-128 on an ATMega8515,
              measured power, 700 samples)
                benign : random plaintexts
                CC     : plaintexts restricted to a small attacker-chosen set
                         (emulated through the S-box label, a bijection of the
                         plaintext byte under the fixed key)

A node stream alternates benign periods and attack campaigns (geometric
lengths). Campaign types:
  CC  chosen-input campaign          (input statistics change the activity profile)
  REP fixed-input repetition         (one input replayed for averaging)
  EMP near-field EM probe coupling   (synthetic signature, scenarios.py)
  GLT glitch-assisted acquisition    (synthetic signature, scenarios.py)
EMP and GLT physical signatures are parametric models (no public trace set
labels them); CC and REP come from the trace sources themselves.
"""
import os
import sys
import numpy as np

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import scenarios as S  # noqa: E402

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')


class KEMSource:
    name = 'kem_gate'

    def __init__(self, path=os.path.join(ROOT, 'data', 'kem_traces.npz'), sigma=0.25, L=128, seed=0):
        d = np.load(path)
        if 'ck_corrected' not in d:
            raise RuntimeError('run analysis/sca_eval.py eval first (clock offset correction)')
        rng = np.random.default_rng(seed)
        ben = d['cpa_off'][:, :L]
        cc = d['det_cc'][:, :L]
        # on-chip sensor: same measurement-noise model as the side-channel analysis
        ben = ben + rng.normal(0, sigma, ben.shape)
        cc = cc + rng.normal(0, sigma, cc.shape)
        mu, sd = ben.mean(), ben.std()
        self.ben, self.cc = (ben - mu) / sd, (cc - mu) / sd
        self.L = L

    def benign(self, rng):
        return self.ben[int(rng.integers(len(self.ben)))].copy()

    def chosen(self, rng, cc_state):
        return self.cc[int(rng.integers(len(self.cc)))].copy()

    def new_cc_state(self, rng):
        return None


class ASCADSource:
    name = 'ascad'

    def __init__(self, path=os.path.join(ROOT, '..', 'data', 'ascad', 'ascad_fixed.npz'), limit=60000):
        if not os.path.exists(path):
            path = os.path.join('/home/claude/data/ascad/ascad_fixed.npz')
        d = np.load(path)
        tr = d['traces'][:limit].astype(np.float32)
        self.tr = (tr - tr.mean()) / tr.std()
        self.lab = d['labels'][:limit].astype(int)
        self.by_label = [np.where(self.lab == v)[0] for v in range(256)]
        self.L = tr.shape[1]

    def benign(self, rng):
        return self.tr[int(rng.integers(len(self.tr)))].copy()

    def new_cc_state(self, rng):
        return rng.choice(256, 4, replace=False)   # attacker-chosen input set for this campaign

    def chosen(self, rng, cc_state):
        v = int(cc_state[int(rng.integers(len(cc_state)))])
        idx = self.by_label[v]
        return self.tr[int(idx[int(rng.integers(len(idx)))])].copy()


H_WIN, R_DIM = 8, 32


def residual(x, template):
    """template-removed residual (gain/offset drift regressed out), block-averaged to R_DIM"""
    L = min(len(x), len(template))
    A = np.stack([template[:L], np.ones(L)], 1)
    coef, *_ = np.linalg.lstsq(A, x[:L], rcond=None)
    r = x[:L] - A @ coef
    r = r[:(L // R_DIM) * R_DIM].reshape(R_DIM, -1).mean(1)
    return (r - r.mean()) / (r.std() + 1e-9)


def history_features(r, hist):
    """cross-window statistics over the last H_WIN residuals: input repetition (REP)
    and restricted chosen-input sets (CC) make residuals coherent across windows."""
    if not hist:
        return [0.0, 0.0, 1.0 / H_WIN]
    c = np.array([float(r @ h) / len(r) for h in hist])
    M = np.mean(list(hist) + [r], axis=0)
    coh = float((M ** 2).mean())                 # ~1/(k+1) for independent residuals, ~1 for repeats
    return [float(c.mean()), float(c.max()), coh]


def stream(src, rng, env, attacks, n, p_attack=0.35, mean_benign=30, mean_campaign=20, evasive=0.5,
           template=None):
    """one node's window stream. Returns X (n, F), y (n,), kind (n,), evasive flag (n,)."""
    X, y, kinds, evs = [], [], [], []
    hist = []
    if template is None:
        template = np.mean([src.benign(rng) for _ in range(256)], axis=0)
    prev = src.benign(rng)
    state, left = None, int(rng.geometric(1 / mean_benign))
    rep_base, cc_state, ev = None, None, False
    while len(y) < n:
        if left <= 0:
            if state is None and attacks and rng.random() < p_attack / (1 - p_attack) * (mean_benign / mean_campaign):
                state = attacks[int(rng.integers(len(attacks)))]
                left = int(rng.geometric(1 / mean_campaign))
                rep_base, cc_state = src.benign(rng), src.new_cc_state(rng)
                ev = rng.random() < evasive
            else:
                state, left = None, int(rng.geometric(1 / mean_benign))
            continue
        if state == 'CC':
            base = src.chosen(rng, cc_state)
        elif state == 'REP':
            base = rep_base.copy()
        else:
            base = src.benign(rng)
        x = S.apply_benign(rng, base, env)
        if state in ('EMP', 'GLT'):
            x = S.apply_attack(rng, x, state, strength=rng.uniform(0.3, 1.0))
        lr, rej = S.telemetry(rng, env, state, ev)
        r = residual(x, template)
        hf = history_features(r, hist)
        hist = (hist + [r])[-H_WIN:]
        X.append(np.concatenate([S.features(x, prev, template), hf, [lr, rej]]))
        y.append(int(state is not None)); kinds.append(state or 'BEN'); evs.append(bool(state and ev))
        prev = x
        left -= 1
    return np.array(X), np.array(y), np.array(kinds), np.array(evs), template
