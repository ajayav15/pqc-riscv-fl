"""
export.py : builds the flattened gate-level SoC core (PicoRV32 + kyber_ise, the
synthesized NanGate45 netlists) and writes it in the compact format read by
gsim.cpp, the timing-annotated (glitch-aware) gate-level power simulator.

Per combinational cell output: truth table, and for every input pin the NLDM
rise and fall propagation delays at that input's slew and the output's load
(fan-out pin capacitance + 5K_hvratio wire load; nets with fan-out above 16 are
treated as ideal buffer trees, as in the static timing of syn/netlist.py).
Per net: switching energy 1/2 C V^2 and the internal energy of its driver per
toggle (liberty internal_power), so a glitch costs the same as a functional
toggle. Flops: clock-to-Q delays, D/Q/QN nets, clock-pin energy.

usage: python3 sim/gsim/export.py [netlist_dir] [out_file] [--keccak]
"""
import json
import os
import sys
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.join(HERE, '..', '..')
sys.path.insert(0, os.path.join(ROOT, 'syn'))
import netlist as NL  # noqa: E402

LIB = os.environ.get('NANGATE_LIB', '/home/claude/tools/pdk/orfs/flow/platforms/nangate45/lib/'
                     'NangateOpenCellLibrary_typical.lib')
PO_CAP = 2.0       # fF, external load on every primary output (SRAM / bus input pin)
IN_SLEW = 0.02     # ns


def merge(ndir, lib, keccak=False):
    """PicoRV32 + kyber_ise (+ keccak_ise) as one Yosys-JSON module. The PCPI
    inputs of the coprocessors are the core's PCPI outputs; with both units the
    PCPI return path is the same glue as in tb/tb_soc.v (OR of wr/wait/ready,
    rd = h_ready ? h_rd : k_rd), mapped to OR2_X1 / MUX2_X1 cells."""
    names = [('picorv32', 'cpu'), ('kyber_ise', 'ise')] + ([('keccak_ise', 'kise')] if keccak else [])
    mods = [json.load(open(os.path.join(ndir, n + '.json')))['modules'][n] for n, _ in names]

    def maxbit(m):
        mb = 0
        for c in m['cells'].values():
            for b in c['connections'].values():
                mb = max([mb] + [x for x in b if isinstance(x, int)])
        for p in m['ports'].values():
            mb = max([mb] + [x for x in p['bits'] if isinstance(x, int)])
        return mb
    for m in mods:                      # pin-name repair per source netlist (Yosys 0.70 aliasing)
        fix = NL.repair_pin_names(m, lib)
        for c in m['cells'].values():
            c['connections'] = {fix.get(k, k): v for k, v in c['connections'].items()}
    offs, o = [], 0
    for m in mods:
        offs.append(o)
        o += maxbit(m) + 1
    nxt = [o]

    def newbit():
        nxt[0] += 1
        return nxt[0] - 1
    core = mods[0]
    cp = core['ports']
    maps = [dict() for _ in mods]       # per unit: local bit -> global bit
    for u, m in enumerate(mods):
        if u == 0:
            continue
        for p in ('clk', 'resetn', 'pcpi_valid', 'pcpi_insn', 'pcpi_rs1', 'pcpi_rs2'):
            for bi, bc in zip(m['ports'][p]['bits'], cp[p]['bits']):
                if isinstance(bi, int):
                    maps[u][bi] = bc
    cells = {}
    if not keccak:
        # core PCPI inputs are the ISE outputs
        ip = mods[1]['ports']
        for p in ('pcpi_wr', 'pcpi_rd', 'pcpi_wait', 'pcpi_ready'):
            for bi, bc in zip(ip[p]['bits'], cp[p]['bits']):
                if isinstance(bc, int):
                    maps[0][bc] = bi + offs[1] if isinstance(bi, int) else bi
    else:
        kp, hp = mods[1]['ports'], mods[2]['ports']
        g = lambda u, b: (b + offs[u]) if isinstance(b, int) else b
        for p in ('pcpi_wr', 'pcpi_wait', 'pcpi_ready'):
            cells['glue_or_' + p] = dict(type='OR2_X1', connections={
                'A1': [g(1, kp[p]['bits'][0])], 'A2': [g(2, hp[p]['bits'][0])], 'ZN': [cp[p]['bits'][0]]})
        hr = g(2, hp['pcpi_ready']['bits'][0])
        for i in range(32):
            cells['glue_mux_rd%d' % i] = dict(type='MUX2_X1', connections={
                'A': [g(1, kp['pcpi_rd']['bits'][i])], 'B': [g(2, hp['pcpi_rd']['bits'][i])], 'S': [hr],
                'Z': [cp['pcpi_rd']['bits'][i]]})

    def mapper(u):
        def f(b):
            if not isinstance(b, int):
                return b
            return maps[u].get(b, b + offs[u])
        return f
    nets = {}
    for u, (m, (n, pre)) in enumerate(zip(mods, names)):
        f = mapper(u)
        for cn, c in m['cells'].items():
            cells[pre + '_' + cn] = dict(type=c['type'], connections={k: [f(x) for x in v] for k, v in c['connections'].items()})
        for nn, nt in m['netnames'].items():
            nets[pre + '.' + nn] = dict(bits=[f(x) for x in nt['bits']])
    ports = {}
    for p in ('clk', 'resetn', 'mem_ready', 'mem_rdata', 'irq'):
        ports[p] = dict(direction='input', bits=cp[p]['bits'])
    for p in ('mem_valid', 'mem_instr', 'mem_addr', 'mem_wdata', 'mem_wstrb', 'trap'):
        ports[p] = dict(direction='output', bits=cp[p]['bits'])
    f1 = mapper(1)
    for p in ('dvfs_req', 'mitig_active'):
        ports[p] = dict(direction='output', bits=[f1(x) for x in mods[1]['ports'][p]['bits']])
    return {'modules': {'soc': dict(ports=ports, cells=cells, netnames=nets)}}


def truth_table(fn, ins):
    k = len(ins)
    idx = np.arange(1 << k, dtype=np.int64)
    v = {p: ((idx >> i) & 1).astype(np.uint8) for i, p in enumerate(ins)}
    out = np.asarray(fn(v)) & 1
    out = np.broadcast_to(out, idx.shape)
    tt = 0
    for i in range(1 << k):
        if out[i]:
            tt |= 1 << i
    return tt


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    keccak = '--keccak' in sys.argv
    ndir = args[0] if len(args) > 0 else os.path.join(ROOT, 'syn', 'out_energy_masked')
    out = args[1] if len(args) > 1 else os.path.join(HERE, 'soc.gnl')
    lib, wl = NL.load_liberty(LIB)
    tmp = os.path.join(HERE, 'soc_merged%s.json' % ('_k' if keccak else ''))
    json.dump(merge(ndir, lib, keccak), open(tmp, 'w'))
    N = NL.Netlist(tmp, 'soc', lib, wl)
    for b in N.ports['mem_addr'][1] + N.ports['mem_wdata'][1] + N.ports['mem_wstrb'][1] + \
            N.ports['mem_valid'][1] + N.ports['mem_instr'][1]:
        if isinstance(b, int):
            N.cap[b] += PO_CAP
    load, extra = N._buffer_model(16)
    # slews: forward pass with the worst arc (as in the STA)
    slw = np.full(N.nnets, IN_SLEW)
    for (cn, ct, d, q, qn) in N.ffs:
        lc = lib[ct]
        for p, pp in lc.pins.items():
            if pp['dir'] != 'output':
                continue
            net = q if pp['func'] == lc.ff['iq'] else qn
            if net is None:
                continue
            for arc in pp['arcs']:
                for tk in ('rise_transition', 'fall_transition'):
                    if tk in arc:
                        slw[net] = max(slw[net], NL.lut(arc[tk], IN_SLEW, load[net]))
    for i in N.order:
        cn, ct, pin, onet, fn, ins = N.comb[i]
        for arc in lib[ct].pins[pin]['arcs']:
            if arc['rel'] in ins:
                for tk in ('rise_transition', 'fall_transition'):
                    if tk in arc:
                        slw[onet] = max(slw[onet], NL.lut(arc[tk], slw[ins[arc['rel']]], load[onet]))
    ps = lambda ns: max(1, int(round(ns * 1000)))
    esw = 0.5 * NL.VDD * NL.VDD * N.cap * 1e-3          # pJ per toggle
    eint = np.zeros(N.nnets)
    lines = []
    for i in N.order:
        cn, ct, pin, onet, fn, ins = N.comb[i]
        pins = list(ins)
        tt = truth_table(fn, pins)
        dl = []
        for p in pins:
            r = f = None
            for arc in lib[ct].pins[pin]['arcs']:
                if arc['rel'] == p:
                    if 'cell_rise' in arc:
                        r = NL.lut(arc['cell_rise'], slw[ins[p]], load[onet]) + extra[onet]
                    if 'cell_fall' in arc:
                        f = NL.lut(arc['cell_fall'], slw[ins[p]], load[onet]) + extra[onet]
            r = r if r is not None else (f or 0.01)
            f = f if f is not None else r
            dl.append('%d %d %d' % (ins[p], ps(r), ps(f)))
        eint[onet] += N.e_int[i]
        lines.append('G %d %d %x %s' % (onet, len(pins), tt, ' '.join(dl)))
    for j, (cn, ct, d, q, qn) in enumerate(N.ffs):
        lc = lib[ct]
        dr = {}
        for p, pp in lc.pins.items():
            if pp['dir'] != 'output':
                continue
            net = q if pp['func'] == lc.ff['iq'] else qn
            if net is None:
                continue
            r = max(NL.lut(a['cell_rise'], IN_SLEW, load[net]) for a in pp['arcs'] if 'cell_rise' in a)
            f = max(NL.lut(a['cell_fall'], IN_SLEW, load[net]) for a in pp['arcs'] if 'cell_fall' in a)
            dr[net] = (ps(r + extra[net]), ps(f + extra[net]))
            eint[net] += N.e_ffq[j]
        qq = q if q is not None else -1
        qqn = qn if qn is not None else -1
        rq = dr.get(q, (100, 100))
        rqn = dr.get(qn, (100, 100))
        lines.append('F %d %d %d %d %d %d %d' % (d, qq, qqn, rq[0], rq[1], rqn[0], rqn[1]))
    hdr = ['GNL 1', 'nets %d' % N.nnets, 'e_ck %.6f' % N.e_ck,
           'e_leak_per_ns %.9f' % (N.leak_nw * 1e-9 * 1e-9 * 1e12),
           'gates %d' % len(N.comb), 'ffs %d' % len(N.ffs)]
    for pn, (dr, bits) in N.ports.items():
        hdr.append('P %s %s %d %s' % (pn, dr, len(bits), ' '.join(str(b if isinstance(b, int) else (1 if b == '1' else 0))
                                                                   for b in bits)))
    with open(out, 'w') as f:
        f.write('\n'.join(hdr) + '\n')
        f.write('E ' + ' '.join('%.6g' % (esw[n] + eint[n]) for n in range(N.nnets)) + '\n')
        f.write('\n'.join(lines) + '\n')
    sta = N.sta()
    print('nets', N.nnets, 'gates', len(N.comb), 'ffs', len(N.ffs), 'area_um2 %.0f' % N.area,
          'sta_ns %.3f' % sta[0], '->', out)


if __name__ == '__main__':
    main()
