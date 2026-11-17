"""
network.py : end-to-end benchmark of session-key establishment in a networked
IoT topology (objective 4), driven by the measured numbers of this project.

Topology: N_NODES battery nodes in a star around a mains-powered gateway, IEEE
802.15.4 2.4 GHz (O-QPSK, 250 kbit/s), 6LoWPAN fragmentation, unslotted
CSMA-CA with acknowledgements, single shared channel. Every node runs an
ephemeral key exchange with the gateway:
  X25519           : node keygen + shared secret, 32 B up / 32 B down
  ML-KEM-512       : node KeyGen + Decaps, pk 800 B up / ct 768 B down
                     (gateway Encaps; the gateway is not energy-constrained)
  Hybrid           : X25519 + ML-KEM-512 (both shares, concatenated)
Node compute time and energy come from the RTL cycle counts (sim/rtlwin,
sim/x25519_run.log) and the gate-level energy (results/energy.csv) at F_MHZ.
X25519 has no gate-level energy run: its energy uses the baseline core's
measured average energy per cycle during the reference KEM (stated as an
estimate in the output).

Radio model (TI CC2420 datasheet, 3.0 V): TX 17.4 mA at 0 dBm, RX 18.8 mA.
802.15.4 timing: 32 us/byte, 6-byte PHY header, aTurnaroundTime 192 us,
unit backoff 320 us, macMinBE = 3 (mean initial backoff 3.5 units), CCA 128 us,
11-byte ACK. Frame: 127-byte PSDU, 25 B MAC header + FCS, 4/5 B 6LoWPAN
FRAG1/FRAGN header, 10 B compressed IPv6/UDP in the first fragment.
Output: results/network.csv, results/network_scaling.csv
"""
import csv
import os
import re
import numpy as np

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
F_MHZ = 100.0
V_RADIO, I_TX, I_RX = 3.0, 17.4e-3, 18.8e-3
BYTE_US, PHY_HDR, TURN_US, BO_US, CCA_US, ACK_B = 32.0, 6, 192.0, 320.0, 128.0, 11
PSDU, MAC_OVH, IPHC, FRAG1, FRAGN = 127, 25, 10, 4, 5


def frames(payload):
    """6LoWPAN fragmentation -> list of PSDU sizes"""
    room = PSDU - MAC_OVH
    if payload + IPHC <= room:
        return [MAC_OVH + IPHC + payload]
    out, left = [], payload
    first = (room - FRAG1 - IPHC) // 8 * 8
    out.append(MAC_OVH + FRAG1 + IPHC + first); left -= first
    nxt = (room - FRAGN) // 8 * 8
    while left > 0:
        c = min(nxt, left); out.append(MAC_OVH + FRAGN + c); left -= c
    return out


def tx_cost(payload, rng=None, contenders=0):
    """(time s, sender energy J, receiver energy J, bytes on air) for one message"""
    t = e_s = e_r = 0.0
    air = 0
    for psdu in frames(payload):
        be_units = 3.5 * (1 + 0.5 * contenders)            # longer backoff under contention
        t_bo = be_units * BO_US
        t_frame = (PHY_HDR + psdu) * BYTE_US
        t_ack = (PHY_HDR + ACK_B) * BYTE_US
        t += t_bo + CCA_US + TURN_US + t_frame + TURN_US + t_ack
        e_s += V_RADIO * (I_RX * (CCA_US + TURN_US + t_ack) + I_TX * t_frame) * 1e-6
        e_r += V_RADIO * (I_RX * t_frame + I_TX * t_ack) * 1e-6
        air += PHY_HDR + psdu + PHY_HDR + ACK_B
    return t * 1e-6, e_s, e_r, air


def load_compute():
    win = {}
    for v in ('ref', 'ise', 'ise_mitig', 'isek', 'isek_mitig', 'isek_masked'):
        win[v] = {}
        for ln in open(os.path.join(ROOT, 'sim/rtlwin/%s.log' % v)):
            if ln.startswith('WIN'):
                win[v][int(ln.split()[1])] = int(re.search(r'cycles=(\d+)', ln).group(1))
    en = {}
    p = os.path.join(ROOT, 'results/energy.csv')
    if os.path.exists(p):
        for r in csv.DictReader(open(p)):
            en[(r['variant'], r['op'])] = float(r['total_uJ'])
    for extra in ('results/energy_cg.csv', 'results/energy_final.csv'):     # final configuration
        q = os.path.join(ROOT, extra)
        if os.path.exists(q):
            for r in csv.DictReader(open(q)):
                en[(r['variant'], r['op'])] = float(r['total_uJ'])
    for v in ('isek_masked2',):
        q = os.path.join(ROOT, 'sim/cg/cg_%s.log' % v)
        if os.path.exists(q):
            win[v] = {int(ln.split()[1]): int(re.search(r'cycles=(\d+)', ln).group(1))
                      for ln in open(q) if ln.startswith('WIN')}
    xc = {}
    for ln in open(os.path.join(ROOT, 'sim/x25519_run.log')):
        m = re.match(r'(x25519_\w+)=(\d+)', ln)
        if m:
            xc[m.group(1)] = int(m.group(2))
    return win, en, xc


def main():
    win, en, xc = load_compute()
    OPS = ['NTT', 'INTT', 'BaseMulAcc', 'KeyGen', 'Encaps', 'Decaps']
    # baseline core energy per cycle (incl. SRAM) during reference KEM code
    ref_e = [(en.get(('ref', o)), win['ref'][i]) for i, o in enumerate(OPS) if ('ref', o) in en and i >= 3]
    e_per_cyc_ref = (sum(e for e, c in ref_e) / sum(c for e, c in ref_e)) if ref_e else None
    x_cyc = xc['x25519_keygen'] + xc['x25519_shared']
    det = {}
    dp = os.path.join(ROOT, 'results/detector_cost.csv')
    if os.path.exists(dp):
        det = next(csv.DictReader(open(dp)))

    def kem(var, dec_var=None, dec_op='Decaps', dec_id=5):
        dv = dec_var or var
        c = win[var][3] + win[dv][dec_id]
        e = en.get((var, 'KeyGen'), np.nan) + en.get((dv, dec_op), np.nan)
        return c, e
    det_cyc = float(det.get('avg_cycles', 0) or 0)
    det_uJk = float(det.get('uJ_per_window_isek', 0) or 0)
    schemes = []
    c, e = x_cyc, (x_cyc * e_per_cyc_ref if e_per_cyc_ref else np.nan)
    schemes.append(('X25519 (classical)', c, e, 32, 32, 'estimate'))
    c, e = kem('ref'); schemes.append(('ML-KEM-512 reference', c, e, 800, 768, 'gate-level'))
    c, e = kem('ise'); schemes.append(('ML-KEM-512 + Kyber ISE', c, e, 800, 768, 'gate-level'))
    c, e = kem('isek'); schemes.append(('ML-KEM-512 + ISE + Keccak', c, e, 800, 768, 'gate-level'))
    ck, ek = c, e
    c, e = kem('isek_mitig'); schemes.append(('ISE + Keccak, hiding always on', c, e, 800, 768, 'gate-level'))
    c, e = kem('isek', 'isek_masked', 'MaskedDecaps', 6)
    schemes.append(('ISE + Keccak, masking v1 always on', c, e, 800, 768, 'gate-level'))
    schemes.append(('ISE + Keccak + detector (adaptive)', ck + det_cyc, ek + det_uJk, 800, 768,
                    'gate-level + detector'))
    cx, ex = schemes[0][1], schemes[0][2]
    if ('isek_cg', 'KeyGen') in en and 'isek_masked2' in win:
        # final configuration: clock-gated Keccak unit, hardened masking v2
        det_uJg = float(det.get('uJ_per_window_isek_cg', 0) or 0)
        cg_k = win['isek'][3] + win['isek'][5]
        eg = en[('isek_cg', 'KeyGen')] + en[('isek_cg', 'Decaps')]
        schemes.append(('Final: ISE + gated Keccak', cg_k, eg, 800, 768, 'gate-level + CG'))
        schemes.append(('Final, hiding always on', win['isek_mitig'][3] + win['isek_mitig'][5],
                        en[('isek_mitig_cg', 'KeyGen')] + en[('isek_mitig_cg', 'Decaps')], 800, 768, 'gate-level + CG'))
        schemes.append(('Final, masking v2 always on', win['isek'][3] + win['isek_masked2'][6],
                        en[('isek_cg', 'KeyGen')] + en[('isek_masked2_cg', 'MaskedDecaps')], 800, 768, 'gsim + CG'))
        schemes.append(('Final + detector (adaptive)', cg_k + det_cyc, eg + det_uJg, 800, 768, 'gate-level + CG + detector'))
        schemes.append(('Hybrid X25519 + ML-KEM-512 (final)', cg_k + cx, eg + ex, 832, 800, 'mixed'))
    else:
        schemes.append(('Hybrid X25519 + ML-KEM-512 (ISE + Keccak)', ck + cx, ek + ex, 832, 800, 'mixed'))
    rows = []
    for name, cyc, e_uJ, up, down, src in schemes:
        tu, eu_s, eu_r, au = tx_cost(up)
        td, ed_s, ed_r, ad = tx_cost(down)
        t_comp = cyc / (F_MHZ * 1e6)
        radio_mJ = (eu_s + ed_r) * 1e3
        rows.append({'scheme': name, 'node_cycles': int(cyc), 'node_compute_ms': round(t_comp * 1e3, 2),
                     'node_compute_uJ': round(e_uJ, 1), 'energy_source': src,
                     'bytes_up': up, 'bytes_down': down, 'frames': len(frames(up)) + len(frames(down)),
                     'air_bytes': au + ad, 'radio_ms': round((tu + td) * 1e3, 2),
                     'node_radio_mJ': round(radio_mJ, 3),
                     'handshake_latency_ms': round((t_comp + tu + td) * 1e3, 2),
                     'node_total_mJ': round(radio_mJ + e_uJ * 1e-3, 3),
                     'compute_share_%': round(100 * e_uJ * 1e-3 / (radio_mJ + e_uJ * 1e-3), 2)})
        print(rows[-1])
    with open(os.path.join(ROOT, 'results/network.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0])); w.writeheader(); w.writerows(rows)
    # scaling: time for a gateway to re-key N nodes on one channel (sequential airtime,
    # node computations overlap), and FL model-update traffic for comparison
    srows = []
    for n in (1, 10, 25, 50, 100):
        for name, cyc, e_uJ, up, down, src in [schemes[i] for i in (0, 1, 3, 6)]:
            tu = tx_cost(up, contenders=min(n - 1, 4))[0]
            td = tx_cost(down, contenders=min(n - 1, 4))[0]
            t_all = n * (tu + td) + cyc / (F_MHZ * 1e6)
            srows.append({'nodes': n, 'scheme': name, 'rekey_all_s': round(t_all, 3),
                          'channel_bytes': n * (tx_cost(up)[3] + tx_cost(down)[3])})
    fl_bytes = 1697   # int8 detector update per node per round (fl/run_fl.py meta)
    for n in (1, 10, 25, 50, 100):
        tu, eu_s, _, au = tx_cost(fl_bytes)
        td, _, ed_r, ad = tx_cost(fl_bytes)
        srows.append({'nodes': n, 'scheme': 'FL round (int8 model up+down)', 'rekey_all_s': round(n * (tu + td), 3),
                      'channel_bytes': n * (au + ad)})
    with open(os.path.join(ROOT, 'results/network_scaling.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=list(srows[0])); w.writeheader(); w.writerows(srows)


if __name__ == '__main__':
    main()
