"""
tvla_masked.py : first-order fixed-vs-random TVLA of the masking gadgets from the
RTL-simulated leakage of the whole core (sim/tvla/t*/leak.bin, tb_soc.v -DLEAKTRACE).

Leakage models (per cycle):
  value       HW(register-file write) + HW(data-bus transfer)
  transition  HD(previous register write, current register write)
Gaussian noise (sigma = 1 bit) is added so that constant samples do not produce
infinite t values. Pass: max |t| < 4.5 over all samples.
Output: results/tvla_masked.csv
"""
import csv
import os
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
NAMES = {0: ('Decoding (8 coeff.)', 'masked'), 1: ('Decoding (8 coeff.)', 'unmasked'),
         2: ('Keccak-f, 2 rounds', 'masked'), 3: ('Keccak-f, 2 rounds', 'unmasked'),
         4: ('CBD eta=2 (8 coeff.)', 'masked'), 5: ('CBD eta=2 (8 coeff.)', 'unmasked')}


def load(t):
    d = os.path.join(ROOT, 'sim', 'tvla', 't%d' % t)
    raw = np.fromfile(os.path.join(d, 'leak.bin'), dtype=np.uint8)
    log = open(os.path.join(d, 'run.log')).read()
    cls = np.array([int(c) for c in log.split('\n')[0] if c in '01'])
    traces, pos = [], 0
    while pos < len(raw):
        n = int(raw[pos:pos + 4].view(np.uint32)[0]); pos += 4
        traces.append(raw[pos:pos + 2 * n].reshape(n, 2)); pos += 2 * n
    lens = {len(x) for x in traces}
    L = min(lens)
    T = np.stack([x[:L] for x in traces]).astype(np.float32)
    return T, cls[:len(T)], lens


def welch(A, B):
    return (A.mean(0) - B.mean(0)) / np.sqrt(A.var(0, ddof=1) / len(A) + B.var(0, ddof=1) / len(B))


def main():
    rng = np.random.default_rng(0)
    rows = []
    for t in range(6):
        T, cls, lens = load(t)
        T = T + rng.normal(0, 1.0, T.shape)
        row = dict(gadget=NAMES[t][0], variant=NAMES[t][1], traces=len(T),
                   samples=T.shape[1], equal_length=len(lens) == 1)
        for ch, nm in ((0, 'value'), (1, 'transition')):
            tt = welch(T[cls == 0, :, ch], T[cls == 1, :, ch])
            tt = np.nan_to_num(tt)
            row['max_t_' + nm] = round(float(np.abs(tt).max()), 2)
            row['leaky_' + nm] = int((np.abs(tt) > 4.5).sum())
        row['pass_value'] = row['max_t_value'] < 4.5
        row['pass_transition'] = row['max_t_transition'] < 4.5
        rows.append(row)
        print(row)
    with open(os.path.join(ROOT, 'results', 'tvla_masked.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0])); w.writeheader(); w.writerows(rows)


if __name__ == '__main__':
    main()
