"""
closed_loop_variants.py : closed loop with the cheaper detector variants
(analysis/det_lite.py) and the replay guard (sw/fw/replay_guard.c).

For each variant the FedAvg model is trained as in closed_loop.py (seed 0) on
its feature subset; benign false alarms, protection-on fraction and detection
latency per campaign type are measured with the 2-of-4 rule and hold 500.
With the replay guard, a replayed or near-replayed ciphertext is flagged from
its second occurrence (positional block fingerprints; benign false-positive
probability about 2.4e-7 per ciphertext, neglected), so REP campaigns raise the
alarm at the second window whatever the detector score.
Energy per decapsulation of the final SoC uses the measured detector and guard
cycle counts (sim/det_variants.log, sim/guard_run.log) and the final SoC's
energy per cycle (results/detector_cost.csv).
Output: results/closed_loop_variants.json
"""
import csv
import json
import os
import re
import sys
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
sys.path.insert(0, os.path.join(ROOT, 'fl'))
sys.path.insert(0, os.path.join(ROOT, 'analysis'))
import scenarios as S   # noqa: E402
import fedlearn as F    # noqa: E402
import datasets as D    # noqa: E402
import run_fl as R      # noqa: E402
import closed_loop as CL  # noqa: E402
import det_lite as DL   # noqa: E402


def feats(src, env, tpl, kind, n, rng, evasive=True):
    prev, hist, out = src.benign(rng), [], []
    rep, ccs = src.benign(rng), src.new_cc_state(rng)
    for _ in range(n):
        base = src.chosen(rng, ccs) if kind == 'CC' else (rep.copy() if kind == 'REP' else src.benign(rng))
        x = S.apply_benign(rng, base, env)
        if kind in ('EMP', 'GLT'):
            x = S.apply_attack(rng, x, kind, strength=rng.uniform(0.3, 1.0))
        lr, rej = S.telemetry(rng, env, None if kind == 'BEN' else kind, evasive)
        r = D.residual(x, tpl)
        out.append(np.concatenate([S.features(x, prev, tpl), D.history_features(r, hist), [lr, rej]]))
        hist = (hist + [r])[-D.H_WIN:]
        prev = x
    return np.array(out)


def main():
    src = D.KEMSource()
    nodes = R.build(src, 0)
    brng = np.random.default_rng(100)
    envs = []
    for k in range(R.N_NODES):
        env = S.node_environment(brng, k)
        atk = list(brng.choice(S.ATTACKS, 2, replace=False))
        X, y, kd, ev, tpl = D.stream(src, brng, env, atk, R.N_TRAIN)
        D.stream(src, brng, env, S.ATTACKS, R.N_TEST, template=tpl)
        envs.append((env, tpl, X[y == 0].mean(0), X[y == 0].std(0) + 1e-6))
    # identical window streams for all variants
    rng = np.random.default_rng(11)
    ben = [feats(src, e, t, 'BEN', 5000, rng) for e, t, _, _ in envs]
    camp = {}
    for kind in S.ATTACKS:
        for ev in (False, True):
            camp[(kind, ev)] = [[feats(src, e, t, kind, 400, rng, evasive=ev) for _ in range(5)] for e, t, _, _ in envs]
    log = open(os.path.join(ROOT, 'sim', 'det_variants.log')).read()
    cyc = {v: int(re.search(r'%s det_avg_cycles=(\d+)' % v, log).group(1)) for v in DL.VARIANTS}
    g_cyc = int(re.search(r'rg_avg_cycles=(\d+)', open(os.path.join(ROOT, 'sim', 'guard_run.log')).read()).group(1))
    det = next(csv.DictReader(open(os.path.join(ROOT, 'results', 'detector_cost.csv'))))
    pj = float(det['isek_cg_pJ_per_cycle'])
    en = {(r['variant'], r['op']): float(r['total_uJ']) for r in csv.DictReader(open(os.path.join(ROOT, 'results', 'energy_final.csv')))}
    e_m, e_um = en[('isek_masked2_cg', 'MaskedDecaps')], en[('isek_masked2_cg', 'Decaps')]
    res = dict(guard_cycles=g_cyc, guard_uJ=g_cyc * pj / 1e6, pJ_per_cycle=pj, variants={})
    for name, cols in DL.VARIANTS.items():
        sub = [dict(n, X=n['X'][:, cols]) for n in nodes]
        g, _ = F.fedavg([(n['X'], n['y']) for n in sub], len(cols), rounds=R.ROUNDS, seed=0)
        sc = lambda Xf, e: g.predict(((Xf - e[2]) / e[3])[:, cols])
        fa, on = [], []
        for Xb, e in zip(ben, envs):
            al = CL.alarms(sc(Xb, e))
            fa.append(float(al.mean())); on.append(CL.on_fraction(al))
        lat = {}
        for (kind, ev), runs in camp.items():
            for guard in (False, True):
                if guard and kind != 'REP':
                    continue
                L = []
                for rr, e in zip(runs, envs):
                    for Xc in rr:
                        al = CL.alarms(sc(Xc, e))
                        if guard:
                            al = al.copy(); al[1:] = True          # flagged from the second ciphertext
                        L.append(CL.latency(al))
                d = [x for x in L if x is not None]
                key = kind + ('_evasive' if ev else '') + (' +guard' if guard else '')
                lat[key] = dict(detected=len(d) / len(L), median=float(np.median(d)) if d else None,
                                p95=float(np.percentile(d, 95)) if d else None)
        f_on = float(np.mean(on))
        e_det = cyc[name] * pj / 1e6
        v = dict(cycles=cyc[name], uJ_per_window=e_det, window_fpr=float(np.mean(fa)), on_fraction=f_on, latency=lat)
        for k in (1, 4):
            v['adaptive_masking_k%d_uJ' % k] = e_um + e_det / k + f_on * (e_m - e_um)
            v['adaptive_masking_k%d_guard_uJ' % k] = v['adaptive_masking_k%d_uJ' % k] + res['guard_uJ']
            v['saving_k%d_guard_pct' % k] = 100 * (1 - v['adaptive_masking_k%d_guard_uJ' % k] / e_m)
        res['variants'][name] = v
        print(name, json.dumps(v, indent=0), flush=True)
    json.dump(res, open(os.path.join(ROOT, 'results', 'closed_loop_variants.json'), 'w'), indent=1)


if __name__ == '__main__':
    main()
