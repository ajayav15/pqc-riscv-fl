"""
netlist.py : liberty parser, zero-delay gate-level simulator with
toggle-based power, and a simple NLDM static timing analyser for
Yosys JSON netlists mapped to the NanGate 45nm Open Cell Library.

Power model per clock cycle (per simulated instance; energies in pJ, liberty
internal-power tables are converted from fJ):
  E = sum_{net toggles} 1/2 * C_net * Vdd^2          (switching)
    + sum_{cell output toggles} E_int(cell, C_load)   (internal, liberty tables)
    + sum_{flops} E_int(CK rise+fall)                 (clock pin internal energy)
    + P_leak * T_clk                                  (leakage)
C_net = sum of fanout pin capacitances + wire-load model (5K_hvratio_1_1).
Zero-delay simulation ignores glitches, so dynamic power is a lower bound
(typically 10-30% below sign-off numbers on arithmetic logic).
"""
import json
import re
import numpy as np

VDD = 1.1

# ----------------------------------------------------------------------------
# liberty parsing
# ----------------------------------------------------------------------------
_tok = re.compile(r'"(?:[^"\\]|\\.)*"|[{}();:,]|[^\s{}();:,"]+')


def _parse_groups(text):
    """Return a nested structure: list of (name, args, body) for groups and (key, value) attributes."""
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    text = text.replace('\\\n', ' ')
    toks = _tok.findall(text)
    pos = 0

    def parse_body():
        nonlocal pos
        items = []
        while pos < len(toks):
            t = toks[pos]
            if t == '}':
                pos += 1
                return items
            name = t
            pos += 1
            if pos < len(toks) and toks[pos] == ':':
                pos += 1
                val = toks[pos]; pos += 1
                if pos < len(toks) and toks[pos] == ';':
                    pos += 1
                items.append((name, val.strip('"')))
            elif pos < len(toks) and toks[pos] == '(':
                pos += 1
                args = []
                while toks[pos] != ')':
                    if toks[pos] != ',':
                        args.append(toks[pos].strip('"'))
                    pos += 1
                pos += 1
                if pos < len(toks) and toks[pos] == '{':
                    pos += 1
                    items.append((name, args, parse_body()))
                else:
                    if pos < len(toks) and toks[pos] == ';':
                        pos += 1
                    items.append((name, args))
            else:
                pass
        return items

    return parse_body()


def _table(group):
    d = {}
    for it in group[2]:
        if len(it) == 2 and isinstance(it[1], list):
            if it[0] in ('index_1', 'index_2'):
                d[it[0]] = np.array([float(x) for x in it[1][0].split(',')])
            elif it[0] == 'values':
                d['values'] = np.array([[float(x) for x in row.split(',')] for row in it[1]])
    if 'values' in d and 'index_2' not in d:
        d['values'] = d['values'].reshape(1, -1)
        d['index_2'] = d.get('index_1', np.array([0.0]))
        d['index_1'] = np.array([0.0])
    return d


def lut(tab, slew, load):
    """bilinear interpolation (with extrapolation) in an NLDM table"""
    i1, i2, v = tab['index_1'], tab['index_2'], tab['values']
    def idx(ax, x):
        if len(ax) == 1:
            return 0, 0, 0.0
        j = int(np.clip(np.searchsorted(ax, x) - 1, 0, len(ax) - 2))
        f = (x - ax[j]) / (ax[j + 1] - ax[j])
        return j, j + 1, f
    a0, a1, fa = idx(i1, slew)
    b0, b1, fb = idx(i2, load)
    if v.shape[0] == 1:
        return v[0, b0] * (1 - fb) + v[0, b1] * fb
    return ((v[a0, b0] * (1 - fb) + v[a0, b1] * fb) * (1 - fa) +
            (v[a1, b0] * (1 - fb) + v[a1, b1] * fb) * fa)


class Cell:
    pass


def load_liberty(path):
    lib = _parse_groups(open(path).read())
    libgrp = [g for g in lib if len(g) == 3 and g[0] == 'library'][0]
    wl = None
    cells = {}
    for it in libgrp[2]:
        if len(it) == 3 and it[0] == 'wire_load' and it[1][0] == '5K_hvratio_1_1':
            cap = float([x for x in it[2] if x[0] == 'capacitance'][0][1])
            slope = float([x for x in it[2] if x[0] == 'slope'][0][1])
            fl = {int(x[1][0]): float(x[1][1]) for x in it[2] if x[0] == 'fanout_length'}
            wl = (cap, slope, fl)
        if len(it) != 3 or it[0] != 'cell':
            continue
        c = Cell()
        c.name = it[1][0]
        c.area = 0.0
        c.leak = 0.0
        c.pins = {}
        c.ff = None
        for a in it[2]:
            if a[0] == 'area':
                c.area = float(a[1])
            elif a[0] == 'cell_leakage_power':
                c.leak = float(a[1])
            elif a[0] == 'ff' and len(a) == 3:
                c.ff = {'iq': a[1][0], 'iqn': a[1][1]}
                for b in a[2]:
                    c.ff[b[0]] = b[1]
            elif a[0] == 'pin' and len(a) == 3:
                p = {'dir': None, 'cap': 0.0, 'func': None, 'arcs': [], 'pwr': [], 'clock': False}
                for b in a[2]:
                    if b[0] == 'direction':
                        p['dir'] = b[1]
                    elif b[0] == 'capacitance':
                        p['cap'] = float(b[1])
                    elif b[0] == 'function':
                        p['func'] = b[1]
                    elif b[0] == 'clock' and b[1] == 'true':
                        p['clock'] = True
                    elif b[0] == 'timing' and len(b) == 3:
                        arc = {'rel': None, 'type': 'combinational'}
                        for t in b[2]:
                            if len(t) == 2 and not isinstance(t[1], list):
                                if t[0] == 'related_pin':
                                    arc['rel'] = t[1]
                                elif t[0] == 'timing_type':
                                    arc['type'] = t[1]
                            elif len(t) == 3:
                                arc[t[0]] = _table(t)
                        p['arcs'].append(arc)
                    elif b[0] == 'internal_power' and len(b) == 3:
                        pw = {'rel': None}
                        for t in b[2]:
                            if len(t) == 2 and t[0] == 'related_pin':
                                pw['rel'] = t[1]
                            elif len(t) == 3:
                                pw[t[0]] = _table(t)
                        p['pwr'].append(pw)
                c.pins[a[1][0]] = p
        cells[c.name] = c
    return cells, wl


# ----------------------------------------------------------------------------
# boolean function compilation
# ----------------------------------------------------------------------------
def compile_func(expr, pins):
    """liberty boolean expression -> python lambda over a dict of uint8 arrays.
    precedence: ! (prefix) > & (also * or juxtaposition) > ^ > | (also +)"""
    toks = re.findall(r"[A-Za-z_][A-Za-z0-9_]*|[!&|^()+*']|[01]", expr)
    pos = [0]
    def peek():
        return toks[pos[0]] if pos[0] < len(toks) else None
    def take():
        t = toks[pos[0]]; pos[0] += 1; return t
    def p_or():
        x = p_xor()
        while peek() in ('|', '+'):
            take(); x = '(%s | %s)' % (x, p_xor())
        return x
    def p_xor():
        x = p_and()
        while peek() == '^':
            take(); x = '(%s ^ %s)' % (x, p_and())
        return x
    def p_and():
        x = p_un()
        while peek() is not None and (peek() in ('&', '*', '(', '!') or re.match(r'[A-Za-z_01]', peek())):
            if peek() in ('&', '*'):
                take()
            x = '(%s & %s)' % (x, p_un())
        return x
    def p_un():
        t = take()
        if t == '!':
            x = '(1 ^ %s)' % p_un()
        elif t == '(':
            x = p_or(); take()
        elif t in ('0', '1'):
            x = t
        else:
            x = 'v["%s"]' % t
        while peek() == "'":
            take(); x = '(1 ^ %s)' % x
        return x
    py = p_or()
    return eval('lambda v: ' + py)


# ----------------------------------------------------------------------------
# netlist
# ----------------------------------------------------------------------------
def repair_pin_names(module, lib):
    """Work around an IdString aliasing bug in the Yosys 0.70 development build:
    after `abc -liberty` some cell pin names (ZN, C1, C2) are written out under
    the name of an unrelated internal wire. The connectivity is intact, so each
    aliased name is mapped back to the liberty pin that is missing from every
    cell using it. Symmetric pairs (C1/C2 of AOI/OAI cells) are mapped in order.
    Returns {aliased_name: pin}; raises if the mapping is not unique."""
    groups = set()
    for c in module['cells'].values():
        lc = lib[c['type']]
        bad = tuple(sorted(p for p in c['connections'] if p not in lc.pins))
        if bad:
            missing = tuple(sorted(p for p in lc.pins if p not in c['connections']))
            if len(missing) != len(bad):
                raise RuntimeError('cannot repair pins of %s' % c['type'])
            groups.add((bad, missing))
    cand = {}
    changed = True
    while changed:                       # resolve unique assignments first (e.g. INV: ZN)
        changed = False
        for bad, missing in groups:
            b = [x for x in bad if x not in cand]
            m = [x for x in missing if x not in cand.values()]
            if len(b) == 1 and len(m) == 1:
                cand[b[0]] = m[0]
                changed = True
    for bad, missing in sorted(groups):  # remaining symmetric pairs, in order
        b = [x for x in bad if x not in cand]
        m = [x for x in missing if x not in cand.values()]
        for x, p in zip(b, m):
            cand[x] = p
    for bad, missing in groups:          # every cell must now be consistent
        if sorted(cand[x] for x in bad) != list(missing):
            raise RuntimeError('inconsistent pin repair for %s' % (bad,))
    return cand


class Netlist:
    def __init__(self, json_path, top, lib, wl):
        d = json.load(open(json_path))
        m = d['modules'][top]
        self.lib = lib
        self.ports = {}
        for pn, p in m['ports'].items():
            self.ports[pn] = (p['direction'], p['bits'])
        maxbit = 2
        def nb(b):
            if b == '0': return 0
            if b == '1': return 1
            if b in ('x', 'z'): return 0
            return int(b)
        self.pin_fix = repair_pin_names(m, lib)
        self.cells = []
        for cn, c in m['cells'].items():
            conns = {self.pin_fix.get(pin, pin): nb(bits[0]) for pin, bits in c['connections'].items()}
            for v in conns.values():
                maxbit = max(maxbit, v)
            self.cells.append((cn, c['type'], conns))
        for pn, (dr, bits) in self.ports.items():
            for b in bits:
                if isinstance(b, int):
                    maxbit = max(maxbit, b)
        self.nnets = maxbit + 1
        self.names = {}
        for nn, n in m['netnames'].items():
            for i, b in enumerate(n['bits']):
                if isinstance(b, int):
                    self.names.setdefault(b, '%s[%d]' % (nn, i))

        # fanout capacitance + wire load
        cap = np.zeros(self.nnets)
        fo = np.zeros(self.nnets, dtype=int)
        for cn, ct, conns in self.cells:
            lc = lib[ct]
            for pin, net in conns.items():
                if lc.pins[pin]['dir'] == 'input':
                    cap[net] += lc.pins[pin]['cap']
                    fo[net] += 1
        wcap, slope, fl = wl
        kmax = max(fl)
        for n in range(self.nnets):
            f = fo[n]
            if f == 0:
                continue
            L = fl[f] if f in fl else (fl[kmax] + slope * (f - kmax) if f > kmax else
                                       np.interp(f, sorted(fl), [fl[k] for k in sorted(fl)]))
            cap[n] += wcap * L
        cap[0] = cap[1] = 0.0
        self.cap = cap
        self.wl = wl
        self.fanout = fo

        # classify cells
        self.comb = []      # (name, type, out_pin, out_net, fn, in_nets dict)
        self.ffs = []       # (name, type, d_net, q_net, qn_net)
        driver = {}
        for cn, ct, conns in self.cells:
            lc = lib[ct]
            if lc.ff is not None:
                ns = lc.ff['next_state']
                q = [p for p, pp in lc.pins.items() if pp['dir'] == 'output' and pp['func'] == lc.ff['iq']]
                qn = [p for p, pp in lc.pins.items() if pp['dir'] == 'output' and pp['func'] == lc.ff['iqn']]
                self.ffs.append((cn, ct, conns.get(ns), conns.get(q[0]) if q and q[0] in conns else None,
                                 conns.get(qn[0]) if qn and qn[0] in conns else None))
                for n in (self.ffs[-1][3], self.ffs[-1][4]):
                    if n is not None:
                        driver[n] = ('ff', len(self.ffs) - 1)
                continue
            for pin, pp in lc.pins.items():
                if pp['dir'] == 'output' and pin in conns and pp['func'] is None:
                    continue        # integrated clock gate (CLKGATE_X1): ideal clock, not simulated
                if pp['dir'] == 'output' and pin in conns:
                    ins = {p: conns[p] for p, q2 in lc.pins.items() if q2['dir'] == 'input' and p in conns}
                    fn = compile_func(pp['func'], list(ins))
                    self.comb.append((cn, ct, pin, conns[pin], fn, ins))
                    driver[conns[pin]] = ('comb', len(self.comb) - 1)
        self.driver = driver
        self._toposort()
        # per-cell output internal energy (pJ per toggle, avg rise/fall at nominal slew)
        self.e_int = np.zeros(len(self.comb))
        for i, (cn, ct, pin, onet, fn, ins) in enumerate(self.comb):
            self.e_int[i] = self._pin_energy(lib[ct].pins[pin], self.cap[onet])
        # clock-pin internal energy per cycle (one rise + one fall). The liberty
        # lists one internal_power group per mutually exclusive state ('when'
        # D/Q combination), so the groups are averaged, not summed.
        # e_ck_legacy keeps the earlier (summed) value so that traces produced
        # with it can be corrected by the constant e_ck_legacy - e_ck.
        self.e_ck = 0.0
        self.e_ck_legacy = 0.0
        self.e_ffq = np.zeros(len(self.ffs))
        for i, (cn, ct, d, q, qn) in enumerate(self.ffs):
            lc = lib[ct]
            for p, pp in lc.pins.items():
                if pp['dir'] == 'input' and pp['clock']:
                    es = []
                    for pw in pp['pwr']:
                        e = 0.0
                        for k in ('rise_power', 'fall_power'):
                            if k in pw:
                                e += lut(pw[k], 0.02, 0.0)
                        es.append(e * 1e-3)      # fJ -> pJ
                    if es:
                        self.e_ck += float(np.mean(es))
                        self.e_ck_legacy += float(np.sum(es))
            qnet = q if q is not None else qn
            outp = [p for p, pp in lc.pins.items() if pp['dir'] == 'output']
            self.e_ffq[i] = self._pin_energy(lc.pins[outp[0]], self.cap[qnet] if qnet is not None else 0.0)
        self.leak_nw = sum(lib[ct].leak for cn, ct, c in self.cells)
        self.area = sum(lib[ct].area for cn, ct, c in self.cells)

    @staticmethod
    def _pin_energy(pp, load):
        es = []
        for pw in pp['pwr']:
            for k in ('rise_power', 'fall_power'):
                if k in pw:
                    es.append(lut(pw[k], 0.02, load))
        # liberty internal_power tables are in fJ (voltage_unit x capacitive_load_unit)
        return float(np.mean(es)) * 1e-3 if es else 0.0

    def _toposort(self):
        n = len(self.comb)
        deps = [[] for _ in range(n)]
        indeg = np.zeros(n, dtype=int)
        users = {}
        for i, (cn, ct, pin, onet, fn, ins) in enumerate(self.comb):
            for p, net in ins.items():
                dv = self.driver.get(net)
                if dv and dv[0] == 'comb':
                    deps[dv[1]].append(i)
                    indeg[i] += 1
        order = [i for i in range(n) if indeg[i] == 0]
        k = 0
        while k < len(order):
            for j in deps[order[k]]:
                indeg[j] -= 1
                if indeg[j] == 0:
                    order.append(j)
            k += 1
        if len(order) != n:
            raise RuntimeError('combinational loop in netlist')
        self.order = order

    # ------------------------------------------------------------------
    def port_bits(self, name):
        return self.ports[name][1]

    def new_state(self, ninst):
        v = np.zeros((self.nnets, ninst), dtype=np.uint8)
        v[1, :] = 1
        return v

    def set_port(self, v, name, values):
        """values: int or array (ninst,) of ints"""
        bits = self.ports[name][1]
        vals = np.asarray(values, dtype=np.int64)
        for i, b in enumerate(bits):
            if isinstance(b, int):
                v[b, :] = (vals >> i) & 1

    def get_port(self, v, name):
        bits = self.ports[name][1]
        out = np.zeros(v.shape[1], dtype=np.int64)
        for i, b in enumerate(bits):
            if isinstance(b, int):
                out |= v[b, :].astype(np.int64) << i
        return out

    def eval_comb(self, v):
        for i in self.order:
            cn, ct, pin, onet, fn, ins = self.comb[i]
            v[onet, :] = fn({p: v[n, :] for p, n in ins.items()}) & 1

    def clock(self, v):
        """rising edge: all flops capture D simultaneously"""
        d = [v[f[2], :].copy() for f in self.ffs]
        for f, dv in zip(self.ffs, d):
            if f[3] is not None:
                v[f[3], :] = dv
            if f[4] is not None:
                v[f[4], :] = 1 ^ dv

    def cycle_energy(self, v_prev, v_now, tclk_ns):
        """energy (pJ) of one clock cycle per instance, given net values before/after"""
        tog = (v_prev != v_now)
        e_sw = 0.5 * VDD * VDD * (self.cap[:, None] * tog).sum(axis=0) * 1e-3     # fF*V^2 -> pJ
        comb_out = np.array([c[3] for c in self.comb])
        e_int = (self.e_int[:, None] * tog[comb_out, :]).sum(axis=0)
        qn = np.array([f[3] if f[3] is not None else f[4] for f in self.ffs])
        e_ff = (self.e_ffq[:, None] * tog[qn, :]).sum(axis=0) if len(qn) else 0.0
        e_leak = self.leak_nw * 1e-9 * tclk_ns * 1e-9 * 1e12                      # pJ
        return e_sw + e_int + e_ff + self.e_ck + e_leak

    # ------------------------------------------------------------------
    def _buffer_model(self, max_fo):
        """Ideal fan-out buffering as a placement-free proxy for repair_design:
        a net with fan-out > max_fo is driven through L levels of BUF_X4
        (branching max_fo). Returns (load seen by the driver, extra delay ns)."""
        load = self.cap.copy()
        extra = np.zeros(self.nnets)
        if not max_fo or 'BUF_X4' not in self.lib:
            return load, extra
        buf = self.lib['BUF_X4']
        cin = buf.pins['A']['cap']
        wcap, slope, fl = self.wl
        avg_pin = float(np.mean([pp['cap'] for c in self.lib.values() for pp in c.pins.values()
                                 if pp['dir'] == 'input' and pp['cap'] > 0]))
        c_leaf = max_fo * avg_pin + wcap * fl.get(max_fo, fl[max(fl)] + slope * (max_fo - max(fl)))
        arc = [a for a in buf.pins['Z']['arcs'] if 'cell_rise' in a][0]
        d_buf = max(lut(arc['cell_rise'], 0.02, c_leaf), lut(arc['cell_fall'], 0.02, c_leaf))
        for n in np.where(self.fanout > max_fo)[0]:
            fo = int(self.fanout[n])
            L = int(np.ceil(np.log(fo) / np.log(max_fo))) - 1
            nb = int(np.ceil(fo / max_fo ** L))
            load[n] = min(nb, max_fo) * cin + wcap * fl.get(min(nb, max_fo), fl[max(fl)])
            extra[n] = L * d_buf
        return load, extra

    def sta(self, in_slew=0.02, clk_slew=0.02, max_fo=16):
        """worst-case register-to-register / IO path delay (ns); nets with
        fan-out > max_fo are modelled as ideally buffered (see _buffer_model)"""
        self.wl = getattr(self, 'wl', None)
        cap, extra = self._buffer_model(max_fo) if self.wl else (self.cap, np.zeros(self.nnets))
        arr = np.zeros(self.nnets)
        slw = np.full(self.nnets, in_slew)
        # flop clk->Q
        for (cn, ct, d, q, qn) in self.ffs:
            lc = self.lib[ct]
            for p, pp in lc.pins.items():
                if pp['dir'] != 'output':
                    continue
                net = q if pp['func'] == lc.ff['iq'] else qn
                if net is None:
                    continue
                best, bs = 0.0, in_slew
                for arc in pp['arcs']:
                    for k, tk in (('cell_rise', 'rise_transition'), ('cell_fall', 'fall_transition')):
                        if k in arc:
                            dl = lut(arc[k], clk_slew, cap[net]) + extra[net]
                            if dl > best:
                                best, bs = dl, lut(arc[tk], clk_slew, cap[net])
                arr[net], slw[net] = best, bs
        crit = {}
        for i in self.order:
            cn, ct, pin, onet, fn, ins = self.comb[i]
            pp = self.lib[ct].pins[pin]
            best, bs, frm = 0.0, in_slew, None
            for arc in pp['arcs']:
                rel = arc['rel']
                if rel not in ins:
                    continue
                inet = ins[rel]
                for k, tk in (('cell_rise', 'rise_transition'), ('cell_fall', 'fall_transition')):
                    if k in arc:
                        dl = arr[inet] + lut(arc[k], slw[inet], cap[onet]) + extra[onet]
                        if dl > best:
                            best, bs, frm = dl, lut(arc[tk], slw[inet], cap[onet]), inet
            arr[onet], slw[onet] = best, bs
            crit[onet] = frm
        # endpoints: flop D + setup
        worst, wnet = 0.0, None
        for (cn, ct, d, q, qn) in self.ffs:
            lc = self.lib[ct]
            setup = 0.0
            for p, pp in lc.pins.items():
                for arc in pp['arcs']:
                    if arc['type'].startswith('setup'):
                        for k in ('rise_constraint', 'fall_constraint'):
                            if k in arc:
                                setup = max(setup, lut(arc[k], slw[d], clk_slew))
            t = arr[d] + setup
            if t > worst:
                worst, wnet = t, d
        # path depth
        depth, n = 0, wnet
        while n in crit and crit[n] is not None:
            n = crit[n]; depth += 1
        return worst, depth, self.names.get(wnet, str(wnet))
