"""
closed_loop.py : detector-triggered adaptive mitigation (objectives 2+3).

1. Train the FedAvg detector on the gate-level ML-KEM window streams (fl/run_fl.py).
2. Monte-Carlo the controller on every node:
     alarm   when >= K of the last N windows score >= 0.5
     action  write the ISE CFG register (dummy + shuffle + DVFS request) and set
             the software shuffle flag; keep it for HOLD windows after the last alarm
   * benign streams    -> false-alarm rate, fraction of time mitigation is on
   * attack campaigns  -> detection latency (windows) for CC/REP/EMP/GLT, evasive
3. Security: the attacker's CPA on s0 uses the first D traces unprotected (D =
   detection latency) and the rest protected (gate-level traces with hiding +
   DVFS model). Compared with no protection and always-on protection.
4. Energy per decapsulation for no protection / always-on hiding / always-on
   first-order masking (cycle-scaled) / adaptive, from gate-level energy.
Outputs results/closed_loop.json, results/closed_loop_cpa.csv
"""
import csv
import json
import os
import sys
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
sys.path.insert(0, os.path.join(ROOT, 'fl'))
sys.path.insert(0, os.path.join(ROOT, 'sim'))
import scenarios as S   # noqa: E402
import fedlearn as F    # noqa: E402
import datasets as D    # noqa: E402
import run_fl as R      # noqa: E402
import sca              # noqa: E402

K_OF, N_WIN, HOLD = 2, 4, 500
SIGMA = 0.25


def window_scores(model, src, env, tpl, mu, sd, kind, n, rng, evasive=True):
    """detector scores for n consecutive windows of one campaign kind (or 'BEN')"""
    prev, hist, out = src.benign(rng), [], []
    rep, ccs = src.benign(rng), src.new_cc_state(rng)
    for _ in range(n):
        base = src.chosen(rng, ccs) if kind == 'CC' else (rep.copy() if kind == 'REP' else src.benign(rng))
        x = S.apply_benign(rng, base, env)
        if kind in ('EMP', 'GLT'):
            x = S.apply_attack(rng, x, kind, strength=rng.uniform(0.3, 1.0))
        lr, rej = S.telemetry(rng, env, None if kind == 'BEN' else kind, evasive)
        r = D.residual(x, tpl)
        f = np.concatenate([S.features(x, prev, tpl), D.history_features(r, hist), [lr, rej]])
        hist = (hist + [r])[-D.H_WIN:]
        prev = x
        out.append(f)
    return model.predict((np.array(out) - mu) / sd)


def alarms(p):
    flag = (p >= 0.5).astype(int)
    c = np.convolve(flag, np.ones(N_WIN, dtype=int))[:len(flag)]
    return c >= K_OF


def on_fraction(al):
    on, last = 0, -10 ** 9
    for i, a in enumerate(al):
        if a:
            last = i
        on += (i - last) < HOLD
    return on / len(al)


def latency(al):
    idx = np.where(al)[0]
    return int(idx[0]) + 1 if len(idx) else None      # +1: CFG write takes effect next window


def energy(res):
    """energy per decapsulation for every policy (gate-level, measured), and the
    break-even condition, for the ISE-only and the final ISE + Keccak configuration"""
    en = {(r['variant'], r['op']): r for r in csv.DictReader(open(os.path.join(ROOT, 'results', 'energy.csv')))}
    E = lambda v, o: float(en[(v, o)]['total_uJ'])
    det = next(csv.DictReader(open(os.path.join(ROOT, 'results', 'detector_cost.csv'))))
    on = res['benign']['mitigation_on_fraction']
    out, be = {}, {}
    for cfg, unp, hid, msk, edet in (
            ('ISE', 'ise', 'ise_mitig', None, float(det['uJ_per_window'])),
            ('ISE+Keccak', 'isek', 'isek_mitig', 'isek_masked', float(det['uJ_per_window_isek']))):
        e_u, e_h = E(unp, 'Decaps'), E(hid, 'Decaps')
        out['%s, unprotected' % cfg] = e_u
        out['%s, always-on hiding+DVFS' % cfg] = e_h
        out['%s, adaptive hiding, detector every decaps' % cfg] = e_u + edet + on * (e_h - e_u)
        out['%s, adaptive hiding, detector every 4th decaps' % cfg] = e_u + edet / 4 + on * (e_h - e_u)
        be['%s: hiding break-even detector energy (uJ)' % cfg] = (1 - on) * (e_h - e_u)
        if msk and (msk, 'MaskedDecaps') in en:
            # masked and unmasked decapsulation measured on the same netlist (ISE with the
            # masking PRNG, which itself costs ~4 uJ per decapsulation because it runs every cycle)
            e_m, e_um = E(msk, 'MaskedDecaps'), E(msk, 'Decaps')
            out['%s+PRNG, unprotected (same netlist as masked)' % cfg] = e_um
            out['%s, always-on first-order masking (measured)' % cfg] = e_m
            out['%s, adaptive masking, detector every decaps' % cfg] = e_um + edet + on * (e_m - e_um)
            out['%s, adaptive masking, detector every 4th decaps' % cfg] = e_um + edet / 4 + on * (e_m - e_um)
            be['%s: masking break-even detector energy (uJ)' % cfg] = (1 - on) * (e_m - e_um)
            be['%s: adaptive masking saving vs always-on, k=1 (%%)' % cfg] = 100 * (1 - out['%s, adaptive masking, detector every decaps' % cfg] / e_m)
            be['%s: adaptive masking saving vs always-on, k=4 (%%)' % cfg] = 100 * (1 - out['%s, adaptive masking, detector every 4th decaps' % cfg] / e_m)
        be['%s: detector energy per window (uJ)' % cfg] = edet
    # final configuration: clock-gated Keccak unit, transition/glitch-hardened masking (v2)
    cgp, fp = os.path.join(ROOT, 'results', 'energy_cg.csv'), os.path.join(ROOT, 'results', 'energy_final.csv')
    if os.path.exists(cgp) and os.path.exists(fp) and 'uJ_per_window_isek_cg' in det:
        for r in list(csv.DictReader(open(cgp))) + list(csv.DictReader(open(fp))):
            en[(r['variant'], r['op'])] = r
        cfg, edet = 'Final (ISE+gated Keccak)', float(det['uJ_per_window_isek_cg'])
        e_u, e_h = E('isek_cg', 'Decaps'), E('isek_mitig_cg', 'Decaps')
        e_m, e_um = E('isek_masked2_cg', 'MaskedDecaps'), E('isek_masked2_cg', 'Decaps')
        out['%s, unprotected' % cfg] = e_u
        out['%s, always-on hiding+DVFS' % cfg] = e_h
        out['%s, adaptive hiding, detector every decaps' % cfg] = e_u + edet + on * (e_h - e_u)
        out['%s, adaptive hiding, detector every 4th decaps' % cfg] = e_u + edet / 4 + on * (e_h - e_u)
        out['%s+PRNG, unprotected (same netlist as masked)' % cfg] = e_um
        out['%s, always-on masking v2 (measured)' % cfg] = e_m
        out['%s, adaptive masking v2, detector every decaps' % cfg] = e_um + edet + on * (e_m - e_um)
        out['%s, adaptive masking v2, detector every 4th decaps' % cfg] = e_um + edet / 4 + on * (e_m - e_um)
        be['%s: hiding break-even detector energy (uJ)' % cfg] = (1 - on) * (e_h - e_u)
        be['%s: masking break-even detector energy (uJ)' % cfg] = (1 - on) * (e_m - e_um)
        be['%s: adaptive masking saving vs always-on, k=1 (%%)' % cfg] = 100 * (1 - out['%s, adaptive masking v2, detector every decaps' % cfg] / e_m)
        be['%s: adaptive masking saving vs always-on, k=4 (%%)' % cfg] = 100 * (1 - out['%s, adaptive masking v2, detector every 4th decaps' % cfg] / e_m)
        be['%s: detector energy per window (uJ)' % cfg] = edet
    out['Reference (no ISE), unprotected'] = E('ref', 'Decaps')
    res['energy_uJ_per_decaps'] = out
    res['break_even'] = be
    res['detector'] = dict(det)
    res['note_sampling'] = ('evaluating every k-th decapsulation divides the detector energy by k and '
                            'multiplies the detection latency (in decapsulations) by about k')
    print(json.dumps({'energy': out, 'break_even': be}, indent=1))


def main():
    rng = np.random.default_rng(11)
    src = D.KEMSource()
    nodes = R.build(src, 0)
    nin = nodes[0]['X'].shape[1]
    g, _ = F.fedavg([(n['X'], n['y']) for n in nodes], nin, rounds=R.ROUNDS, seed=0)
    # per-node environments / calibration exactly as in run_fl.build
    brng = np.random.default_rng(100)
    envs = []
    for k in range(R.N_NODES):
        env = S.node_environment(brng, k)
        atk = list(brng.choice(S.ATTACKS, 2, replace=False))
        X, y, kd, ev, tpl = D.stream(src, brng, env, atk, R.N_TRAIN)
        D.stream(src, brng, env, S.ATTACKS, R.N_TEST, template=tpl)
        envs.append((env, tpl, X[y == 0].mean(0), X[y == 0].std(0) + 1e-6))
    res = {'rule': dict(k=K_OF, n=N_WIN, hold=HOLD)}
    on_fr, fa = [], []
    for env, tpl, mu, sd in envs:
        p = window_scores(g, src, env, tpl, mu, sd, 'BEN', 5000, rng)
        al = alarms(p)
        fa.append(float(al.mean())); on_fr.append(on_fraction(al))
    res['benign'] = dict(window_fpr=float(np.mean(fa)), mitigation_on_fraction=float(np.mean(on_fr)),
                         per_node_on_fraction=[round(x, 4) for x in on_fr])
    lat = {}
    for kind in S.ATTACKS:
        for ev in (False, True):
            L = []
            for env, tpl, mu, sd in envs:
                for rep in range(5):
                    p = window_scores(g, src, env, tpl, mu, sd, kind, 400, rng, evasive=ev)
                    L.append(latency(alarms(p)))
            det = [x for x in L if x is not None]
            lat['%s%s' % (kind, '_evasive' if ev else '')] = dict(
                detected=len(det) / len(L), median=float(np.median(det)) if det else None,
                p95=float(np.percentile(det, 95)) if det else None, max=max(det) if det else None)
    res['latency_windows'] = lat
    print(json.dumps(res, indent=1))

    # ---- security of the closed loop: CPA with D unprotected + protected traces ----
    d = np.load(os.path.join(ROOT, 'data', 'kem_traces.npz'))
    s0 = int(d['s_fix'][0, 0] & 0xFFF)
    srng = np.random.default_rng(3)
    Xo = sca.observe(d['cpa_off'], SIGMA, False, srng)
    Xh = sca.observe(d['cpa_hw'], SIGMA, True, srng)
    L = max(Xo.shape[1], Xh.shape[1])
    pad = lambda A: np.pad(A, ((0, 0), (0, L - A.shape[1])), mode='edge')
    Xo, Xh = pad(Xo), pad(Xh)
    uo, uh = d['cpa_u_off'][:, 0, 0] & 0xFFF, d['cpa_u_hw'][:, 0, 0] & 0xFFF
    steps = [25, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000]
    emp = lat['EMP_evasive']
    rows = []
    for label, Dn in (('no protection', None), ('always-on hiding+DVFS', 0),
                      ('adaptive (median latency)', int(emp['median'] or 0)),
                      ('adaptive (worst observed latency)', int(emp['max'] or 0))):
        if Dn is None:
            X, u, uw = Xo, uo, d['cpa_u_off']
        else:
            X = np.concatenate([Xo[:Dn], Xh[:len(Xh) - Dn]]); u = np.concatenate([uo[:Dn], uh[:len(uh) - Dn]])
            uw = np.concatenate([d['cpa_u_off'][:Dn], d['cpa_u_hw'][:len(uh) - Dn]])
        X = sca.remove_public(X, uw)
        H = sca.cpa_models(u)
        for integ in (0, 16):
            ranks, _ = sca.cpa_rank(X, H, s0, steps, integrate=integ)
            for n, r in zip(steps, ranks):
                rows.append(dict(policy=label, unprotected_traces=Dn if Dn is not None else 'all',
                                 attack='integrated' if integ else 'pointwise', n_traces=n, rank=r))
            print(label, Dn, 'integ' if integ else 'point', ranks, flush=True)
    with open(os.path.join(ROOT, 'results', 'closed_loop_cpa.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0])); w.writeheader(); w.writerows(rows)

    energy(res)
    json.dump(res, open(os.path.join(ROOT, 'results', 'closed_loop.json'), 'w'), indent=1)
    print(json.dumps(res['energy_uJ_per_decaps'], indent=1))


if __name__ == '__main__':
    if sys.argv[1:] == ['energy']:          # recompute only the energy policies
        r = json.load(open(os.path.join(ROOT, 'results', 'closed_loop.json')))
        energy(r)
        json.dump(r, open(os.path.join(ROOT, 'results', 'closed_loop.json'), 'w'), indent=1)
    else:
        main()
