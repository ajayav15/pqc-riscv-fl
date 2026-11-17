"""
tvla2.py : streaming fixed-vs-random Welch t-test on the leakage campaigns of
analysis/leak_campaign.py.

RTL traces (sim/leak/<tag>/t<k>/leak.bin, 3 bytes per cycle):
  value       HW(register write) + HW(data-bus transfer)
  regtrans    HD(previous register write, this register write)
  transition  HD(old, new) of every datapath state element (register-file entry,
              reg_op1, reg_op2 = PCPI rs1/rs2, reg_out, alu_out_q, mem_wdata, mem_rdata)
Gate-level traces (gleak.bin, 5 uint16 per cycle, 0.01 pJ):
  glitch_b0..b3  glitch-aware energy in the time bins [0,1) [1,2) [2,4) [4,10) ns
  zero_delay     energy of the settled (functional) toggles only
Gaussian noise is added to every sample (sigma 1 bit for the RTL models, 0.1 pJ for
the gate level) so that constant samples do not give infinite t values.
Samples whose noise-free value is the same in every trace are excluded (their t
value would only reflect the added noise). Pass: max |t| < 4.5 over all samples.

  python3 analysis/tvla2.py <tag> [rtl|gsim] [targets]
Appends to results/tvla2.csv (one row per tag, target, channel).
"""
import csv
import os
import sys
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
NAMES = {0: 'Decoding', 1: 'Decoding (unmasked)', 2: 'Keccak-f round', 3: 'Keccak-f round (unmasked)',
         4: 'CBD eta=2', 5: 'CBD eta=2 (unmasked)',
         6: 'Compress10 + OR', 7: 'Compress4 + OR + fold', 8: 'Sponge G', 9: 'ISE basemul'}


def traces(path, ch, dtype):
    raw = np.fromfile(path, dtype=np.uint8)
    pos, isz = 0, np.dtype(dtype).itemsize
    while pos < len(raw):
        n = int(raw[pos:pos + 4].view(np.uint32)[0]); pos += 4
        yield raw[pos:pos + n * ch * isz].view(dtype).reshape(n, ch); pos += n * ch * isz


def run(tag, kind, t, rng):
    d = os.path.join(ROOT, 'sim', 'leak', tag, 't%d' % t)
    if kind == 'rtl':
        path, ch, dt, names, sig, scale = os.path.join(d, 'leak.bin'), 3, np.uint8, \
            ['value', 'regtrans', 'transition'], 1.0, 1.0
        log = os.path.join(d, 'run.log')
    else:
        path, ch, dt, names, sig, scale = os.path.join(d, 'gleak.bin'), 5, np.uint16, \
            ['glitch_b0', 'glitch_b1', 'glitch_b2', 'glitch_b3', 'zero_delay'], 0.1, 0.01
        log = os.path.join(d, 'grun.log')
    if not os.path.exists(path):
        return []
    lines = [l for l in open(log).read().split('\n') if l and set(l) <= set('01')]
    cls = [int(c) for c in (lines[0] if lines else '')]     # the class line (other log lines may precede it)
    S = None
    curve = []
    n = 0
    for i, tr in enumerate(traces(path, ch, dt)):
        if i >= len(cls):
            break
        raw_x = tr.astype(np.float64) * scale
        x = raw_x + rng.normal(0, sig, tr.shape)
        if S is None:
            L = len(x)
            S = np.zeros((2, 3, L, ch))
            R = np.zeros((2, L, ch))                 # raw (noise-free) sums for the constant-sample test
            R0 = raw_x[:L].copy()
            varies = np.zeros((L, ch), dtype=bool)
        x = x[:L] if len(x) >= L else np.pad(x, ((0, L - len(x)), (0, 0)))
        raw_x = raw_x[:L] if len(raw_x) >= L else np.pad(raw_x, ((0, L - len(raw_x)), (0, 0)))
        varies |= raw_x != R0
        c = cls[i]
        S[c, 0] += 1; S[c, 1] += x; S[c, 2] += x * x
        n += 1
        if n % 500 == 0 or n == len(cls):
            curve.append((n, (tstat(S) * varies).max(axis=0)))
    if S is None:
        return []
    # a sample whose noise-free value is identical in every trace carries no
    # information; its t value would only test the added Gaussian noise
    tt = tstat(S) * varies
    rows = []
    for k, nm in enumerate(names):
        rows.append(dict(tag=tag, sim=kind, target=t, gadget=NAMES[t], channel=nm, traces=n,
                         samples=tt.shape[0], informative=int(varies[:, k].sum()), max_t=round(float(tt[:, k].max()), 2),
                         leaky=int((tt[:, k] > 4.5).sum()), passed=bool(tt[:, k].max() < 4.5)))
    np.savez_compressed(os.path.join(d, 'tvla_%s.npz' % kind), t=tt, curve_n=[c[0] for c in curve],
                        curve_max=np.array([c[1] for c in curve]), names=names)
    return rows


def tstat(S):
    n0, n1 = S[0, 0], S[1, 0]
    m0, m1 = S[0, 1] / n0, S[1, 1] / n1
    v0 = (S[0, 2] - n0 * m0 * m0) / (n0 - 1)
    v1 = (S[1, 2] - n1 * m1 * m1) / (n1 - 1)
    return np.nan_to_num(np.abs(m0 - m1) / np.sqrt(v0 / n0 + v1 / n1 + 1e-30))


def main():
    tag, kind = sys.argv[1], sys.argv[2] if len(sys.argv) > 2 else 'rtl'
    targets = [int(x) for x in sys.argv[3].split(',')] if len(sys.argv) > 3 else range(6)
    rng = np.random.default_rng(0)
    out = os.path.join(ROOT, 'results', 'tvla2.csv')
    old = []
    if os.path.exists(out):
        old = [r for r in csv.DictReader(open(out))
               if not (r['tag'] == tag and r['sim'] == kind and int(r['target']) in targets)]
    rows = []
    for t in targets:
        for r in run(tag, kind, t, rng):
            print(r, flush=True)
            rows.append(r)
    allr = old + rows
    if allr:
        with open(out, 'w', newline='') as f:
            w = csv.DictWriter(f, fieldnames=list(allr[0])); w.writeheader(); w.writerows(allr)


if __name__ == '__main__':
    main()
