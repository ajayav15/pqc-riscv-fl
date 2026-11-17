"""
scenarios.py : benign-environment and side-channel-acquisition scenario
engine shared by the gate-level trace pipeline and the ASCAD adapter.

A "window" is one on-chip power-sensor capture of a decapsulation step plus
the node's cheap telemetry. The detector must separate benign variation
(temperature/supply drift, regulator ripple, radio bursts, sensor jitter,
legitimate traffic) from the physical signatures of an attack campaign:

  CC   chosen/structured-ciphertext campaign   (input statistics change the
                                                 multiplier activity profile)
  REP  fixed-input repetition / averaging       (consecutive windows nearly identical)
  EMP  near-field EM probe coupling             (narrow-band pickup + loading drift)
  GLT  glitch-assisted acquisition              (spikes, stretched cycles)

A fraction of every attack type is "evasive": the attacker paces queries and
uses valid ciphertexts so rate/rejection telemetry looks benign and only the
physical signature remains.
"""
import numpy as np

ATTACKS = ['CC', 'REP', 'EMP', 'GLT']


def node_environment(rng, node_id):
    """node-specific benign environment (drives non-IID data across nodes)"""
    return dict(
        noise=rng.uniform(0.02, 0.10),          # sensor noise (fraction of trace std)
        ripple_amp=rng.uniform(0.0, 0.25),      # DC-DC ripple amplitude
        ripple_f=rng.uniform(0.02, 0.12),       # cycles^-1, node specific regulator
        gain_sd=rng.uniform(0.02, 0.08),        # temperature / supply drift
        radio_p=rng.uniform(0.02, 0.20),        # probability a radio burst overlaps
        jitter=int(rng.integers(0, 3)),         # sensor trigger jitter (samples)
        rate=rng.uniform(0.2, 2.0),             # legitimate decapsulations per second
        rej=rng.uniform(0.002, 0.02),           # benign implicit-rejection rate
    )


def _shift(x, s):
    if s == 0:
        return x
    y = np.roll(x, s)
    if s > 0:
        y[:s] = x[0]
    else:
        y[s:] = x[-1]
    return y


def apply_benign(rng, tr, env):
    """tr: (T,) clean trace normalised to unit std. Returns observed trace."""
    T = len(tr)
    t = np.arange(T)
    g = 1.0 + rng.normal(0, env['gain_sd'])
    x = g * tr + rng.normal(0, env['gain_sd'])
    x = x + env['ripple_amp'] * np.sin(2 * np.pi * env['ripple_f'] * (1 + rng.normal(0, 0.03)) * t
                                       + rng.uniform(0, 2 * np.pi))
    if rng.random() < env['radio_p']:                       # radio TX burst (benign confounder)
        a = int(rng.integers(0, T)); L = int(rng.integers(T // 8, T // 2))
        x[a:a + L] += rng.uniform(0.5, 1.5)
    x = _shift(x, int(rng.integers(-env['jitter'], env['jitter'] + 1)) if env['jitter'] else 0)
    x = x + rng.normal(0, env['noise'] * 3, T)
    return x


def apply_attack(rng, x, kind, strength):
    """add the physical signature of an attack to an already benign-processed trace"""
    T = len(x)
    t = np.arange(T)
    if kind == 'EMP':
        f = rng.uniform(0.30, 0.48)                          # near-Nyquist pickup of the probe
        x = x * (1 - 0.15 * strength) + 0.6 * strength * np.sin(2 * np.pi * f * t + rng.uniform(0, 6.3))
        x = x + rng.normal(0, 0.15 * strength, T)
    elif kind == 'GLT':
        n = int(rng.integers(1, 4))
        for _ in range(n):
            p = int(rng.integers(1, T - 2))
            x[p] += rng.choice([-1, 1]) * rng.uniform(2.0, 4.0) * strength
            # stretched cycle: one sample duplicated
            q = int(rng.integers(1, T - 1))
            x = np.concatenate([x[:q], x[q:q + 1], x[q:-1]])
    return x


def telemetry(rng, env, kind, evasive):
    """(log request rate, implicit rejection flag)"""
    if kind is None or evasive:
        rate = rng.gamma(4.0, env['rate'] / 4.0)
        rej = float(rng.random() < env['rej'])
    else:
        rate = rng.gamma(4.0, rng.uniform(5, 50) / 4.0)       # high-rate trace collection
        rej = float(rng.random() < (0.85 if kind == 'CC' else env['rej'] * 3))
    return np.log1p(rate), rej


def features(x, prev, template, n_ds=16, n_bands=8):
    """cheap on-node feature vector (no FFT library needed on the MCU: bands are
    Goertzel-style sums; here computed with numpy for speed)"""
    T = len(x)
    xc = x - x.mean()
    sd = x.std() + 1e-9
    f = [x.mean(), sd, np.abs(np.diff(x)).mean(), x.max(), x.min(),
         ((xc / sd) ** 3).mean(), ((xc / sd) ** 4).mean()]
    P = np.abs(np.fft.rfft(xc)) ** 2
    bands = np.array_split(P[1:], n_bands)
    tot = P[1:].sum() + 1e-9
    f += [b.sum() / tot for b in bands]
    L = min(len(template), T)
    f.append(np.corrcoef(x[:L], template[:L])[0, 1] if L > 2 else 0.0)
    Lp = min(len(prev), T)
    f.append(np.corrcoef(x[:Lp], prev[:Lp])[0, 1] if prev is not None and Lp > 2 else 0.0)
    ds = x[:(T // n_ds) * n_ds].reshape(n_ds, -1).mean(1)      # block means (as on the node)
    f += list(ds)
    return np.array(f, dtype=float)


FEATURE_NAMES = (['mean', 'std', 'mad_diff', 'max', 'min', 'skew', 'kurt'] +
                 ['band%d' % i for i in range(8)] + ['rho_template', 'rho_prev'] +
                 ['ds%d' % i for i in range(16)] + ['hist_corr_mean', 'hist_corr_max', 'hist_coherence'] +
                 ['log_rate', 'reject'])
