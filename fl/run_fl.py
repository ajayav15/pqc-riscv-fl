"""
run_fl.py : federated side-channel anomaly detection experiments (objective 2).

For each trace source (gate-level ML-KEM traces of this design; measured ASCAD
traces) and each seed:
  * N_NODES edge nodes with node-specific benign environments (non-IID);
    each node's training stream contains only 2 of the 4 campaign types,
    its test stream contains all 4 (generalisation through federation)
  * methods: local-only MLP, FedAvg, FedProx, DP-FedAvg (client-level),
    centralized (pooled raw features; privacy-violating upper bound),
    one-class Mahalanobis on benign data only (unsupervised baseline)
  * the int8-quantized global model (what the node runs) is evaluated too
Outputs results/fl_<source>.json and results/fl_summary.csv
"""
import csv
import json
import os
import sys
import time
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import scenarios as S   # noqa: E402
import fedlearn as F    # noqa: E402
import datasets as D    # noqa: E402

ROOT = os.path.join(HERE, '..')
N_NODES, N_TRAIN, N_TEST = 10, 2000, 1000
ROUNDS, SEEDS = 40, (0, 1, 2)
N_ATK = 2           # attack types present in each node's training stream (non-IID degree)
DP = dict(clip=1.0, noise=0.8)


def build(src, seed):
    rng = np.random.default_rng(100 + seed)
    nodes = []
    for k in range(N_NODES):
        env = S.node_environment(rng, k)
        atk = list(rng.choice(S.ATTACKS, N_ATK, replace=False))
        X, y, kd, ev, tpl = D.stream(src, rng, env, atk, N_TRAIN)
        Xt, yt, kdt, evt, _ = D.stream(src, rng, env, S.ATTACKS, N_TEST, template=tpl)
        mu, sd = X[y == 0].mean(0), X[y == 0].std(0) + 1e-6      # local benign calibration
        nodes.append(dict(X=(X - mu) / sd, y=y, Xt=(Xt - mu) / sd, yt=yt, kt=kdt, evt=evt, atk=atk))
    return nodes


def per_type(prob, nodes, thr=0.5):
    p = np.concatenate(prob)
    y = np.concatenate([n['yt'] for n in nodes])
    k = np.concatenate([n['kt'] for n in nodes])
    ev = np.concatenate([n['evt'] for n in nodes])
    out = F.metrics(y, p, thr)
    for t in S.ATTACKS:
        m = k == t
        out['tpr_' + t] = float((p[m] >= thr).mean())
        out['tpr_' + t + '_evasive'] = float((p[m & ev] >= thr).mean()) if (m & ev).any() else None
    unseen = [(pp[np.isin(n['kt'], [a for a in S.ATTACKS if a not in n['atk']])] >= thr)
              for pp, n in zip(prob, nodes)]
    unseen = np.concatenate(unseen) if unseen else np.array([])
    out['tpr_unseen'] = float(unseen.mean()) if len(unseen) else None
    return out


def mahalanobis(nodes, fpr=0.02):
    prob = []
    for n in nodes:
        B = n['X'][n['y'] == 0]
        mu = B.mean(0)
        C = np.cov(B.T) + 1e-3 * np.eye(B.shape[1])
        Ci = np.linalg.inv(C)
        d = lambda Z: np.einsum('ij,jk,ik->i', Z - mu, Ci, Z - mu)
        thr = np.quantile(d(B), 1 - fpr)
        prob.append(1 / (1 + np.exp(-(d(n['Xt']) - thr) / (thr * 0.1))))
    return prob


def run(src):
    res = {}
    for seed in SEEDS:
        t0 = time.time()
        nodes = build(src, seed)
        nin = nodes[0]['X'].shape[1]
        clients = [(n['X'], n['y']) for n in nodes]
        Xv = np.concatenate([n['Xt'] for n in nodes]); yv = np.concatenate([n['yt'] for n in nodes])
        r = {}
        loc = [F.train_central(n['X'], n['y'], nin, epochs=2 * ROUNDS // 2, seed=seed) for n in nodes]
        r['local'] = per_type([m.predict(n['Xt']) for m, n in zip(loc, nodes)], nodes)
        g, hist = F.fedavg(clients, nin, rounds=ROUNDS, seed=seed, val=(Xv, yv))
        r['fedavg'] = per_type([g.predict(n['Xt']) for n in nodes], nodes)
        r['fedavg']['f1_by_round'] = [h['f1'] for h in hist]
        gq = g.quantized()
        r['fedavg_int8'] = per_type([gq.predict(n['Xt']) for n in nodes], nodes)
        gp, _ = F.fedavg(clients, nin, rounds=ROUNDS, seed=seed, prox_mu=0.01)
        r['fedprox'] = per_type([gp.predict(n['Xt']) for n in nodes], nodes)
        gd, _ = F.fedavg(clients, nin, rounds=ROUNDS, seed=seed, dp_clip=DP['clip'], dp_noise=DP['noise'])
        r['dp_fedavg'] = per_type([gd.predict(n['Xt']) for n in nodes], nodes)
        r['dp_fedavg']['epsilon'] = F.rdp_epsilon(DP['noise'], ROUNDS)
        Xc = np.concatenate([c[0] for c in clients]); yc = np.concatenate([c[1] for c in clients])
        gc = F.train_central(Xc, yc, nin, epochs=ROUNDS // 2, seed=seed)
        r['centralized'] = per_type([gc.predict(n['Xt']) for n in nodes], nodes)
        r['oneclass'] = per_type(mahalanobis(nodes), nodes)
        r['meta'] = dict(nparams=g.nparams(), macs=g.macs(), nin=nin,
                         bytes_per_round_fp32=2 * N_NODES * g.nparams() * 4,
                         bytes_per_round_int8=2 * N_NODES * g.nparams(),
                         attack_fraction=float(yv.mean()))
        res[seed] = r
        print(src.name, 'seed', seed, '%.0fs' % (time.time() - t0),
              {m: round(r[m]['f1'], 3) for m in r if m != 'meta'}, flush=True)
    return res


def summarize(all_res):
    rows = []
    for srcname, res in all_res.items():
        methods = [m for m in res[SEEDS[0]] if m != 'meta']
        for m in methods:
            row = dict(source=srcname, method=m)
            for k in ('f1', 'auc', 'fpr', 'rec', 'tpr_unseen', 'tpr_CC', 'tpr_REP', 'tpr_EMP', 'tpr_GLT',
                      'tpr_CC_evasive', 'tpr_REP_evasive', 'tpr_EMP_evasive', 'tpr_GLT_evasive'):
                v = [res[s][m][k] for s in SEEDS if res[s][m].get(k) is not None]
                row[k] = '%.3f' % np.mean(v) if v else ''
                row[k + '_sd'] = '%.3f' % np.std(v) if v else ''
            if m == 'dp_fedavg':
                row['epsilon'] = '%.1f' % res[SEEDS[0]][m]['epsilon']
            rows.append(row)
    keys = []
    for r in rows:
        keys += [k for k in r if k not in keys]
    with open(os.path.join(ROOT, 'results', 'fl_summary.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=keys); w.writeheader(); w.writerows(rows)
    return rows


def main():
    which = sys.argv[1:] or ['kem', 'ascad']
    all_res = {}
    for w in which:
        src = D.KEMSource() if w == 'kem' else D.ASCADSource()
        res = run(src)
        json.dump(res, open(os.path.join(ROOT, 'results', 'fl_%s.json' % src.name), 'w'), indent=1,
                  default=lambda o: o.item() if hasattr(o, 'item') else str(o))
        all_res[src.name] = res
    for name in ('kem_gate', 'ascad'):
        p = os.path.join(ROOT, 'results', 'fl_%s.json' % name)
        if name not in all_res and os.path.exists(p):
            all_res[name] = {int(k): v for k, v in json.load(open(p)).items()}
    for r in summarize(all_res):
        print(r['source'], r['method'], 'F1', r['f1'], 'AUC', r['auc'], 'FPR', r['fpr'],
              'unseen-TPR', r['tpr_unseen'])


if __name__ == '__main__':
    main()
