"""
profile.py : map the cycle-level PC profile (tb_soc.v -DPROFILE) to firmware
functions and to the ML-KEM kernel categories used in the paper.
Output: results/profile.csv  (variant, op, category, cycles, share)
"""
import csv
import os
import subprocess
from collections import defaultdict

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
OPS = ['KeyGen', 'Encaps', 'Decaps']

CATS = [  # first match wins
    ('Keccak (SHA3/SHAKE)', ('Keccak', 'keccak', 'shake', 'sha3', 'kyber_shake', 'store64', 'load64')),
    ('NTT / INTT', ('ntt', 'fqmul', 'invntt')),
    ('Base multiplication', ('basemul',)),
    ('Matrix rejection sampling', ('rej_uniform', 'gen_matrix')),
    ('CBD noise sampling', ('cbd', 'getnoise')),
    ('Compress / pack', ('compress', 'tobytes', 'frombytes', 'msg', 'pack')),
    ('Modular reduction / poly add', ('poly_add', 'poly_sub', 'reduce', 'barrett', 'montgomery', 'tomont', 'canon')),
    ('Verify / cmov', ('verify', 'cmov')),
    ('memcpy / memset', ('memcpy', 'memset', 'memcmp')),
]


def symbols(elf):
    out = subprocess.run(['llvm-nm', '--numeric-sort', '--defined-only', '-S', elf],
                         capture_output=True, text=True, check=True).stdout
    syms = []
    for ln in out.splitlines():
        p = ln.split()
        if len(p) == 4 and p[2] in 'tT':
            syms.append((int(p[0], 16), int(p[1], 16), p[3]))
    return syms


def lookup(syms, pc):
    for a, s, n in syms:
        if a <= pc < a + s:
            return n
    return '?'


def category(fn):
    for c, keys in CATS:
        if any(k in fn for k in keys):
            return c
    return 'Other (hash glue, control)'


def main():
    rows = []
    fnrows = []
    for v in ('ref', 'ise', 'isek'):
        for i, op in enumerate(OPS):
            syms = symbols(os.path.join(ROOT, 'sw/build/prof/%s_%d.elf' % (v, i)))
            per_fn = defaultdict(int)
            with open(os.path.join(ROOT, 'sim/prof/%s_%d.txt' % (v, i))) as f:
                for ln in f:
                    pc, c = ln.split()
                    per_fn[lookup(syms, int(pc, 16))] += int(c)
            tot = sum(per_fn.values())
            per_cat = defaultdict(int)
            for fn, c in per_fn.items():
                per_cat[category(fn)] += c
                fnrows.append((v, op, fn, c, c / tot))
            for c, n in sorted(per_cat.items(), key=lambda x: -x[1]):
                rows.append((v, op, c, n, n / tot))
            print('%-4s %-7s total=%9d  ' % (v, op, tot) +
                  '  '.join('%s=%.1f%%' % (c.split(' ')[0], 100 * n / tot)
                            for c, n in sorted(per_cat.items(), key=lambda x: -x[1])))
    os.makedirs(os.path.join(ROOT, 'results'), exist_ok=True)
    with open(os.path.join(ROOT, 'results/profile.csv'), 'w', newline='') as f:
        w = csv.writer(f)
        w.writerow(['variant', 'op', 'category', 'cycles', 'share'])
        w.writerows(rows)
    with open(os.path.join(ROOT, 'results/profile_functions.csv'), 'w', newline='') as f:
        w = csv.writer(f)
        w.writerow(['variant', 'op', 'function', 'cycles', 'share'])
        w.writerows(sorted(fnrows, key=lambda r: (r[0], r[1], -r[3])))


if __name__ == '__main__':
    main()
