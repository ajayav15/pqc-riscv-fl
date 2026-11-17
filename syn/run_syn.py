"""
run_syn.py : Yosys + ABC synthesis of the design units to the NanGate FreePDK45
Open Cell Library (typical corner, 1.1 V, 25 C), followed by
  * cell area from the liberty file,
  * static timing (NLDM tables + 5K_hvratio wire load) with netlist.py,
  * leakage power.
Results go to results/synthesis.csv; netlists to syn/out/.
"""
import csv
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.join(HERE, '..')
sys.path.insert(0, HERE)
import netlist as NL  # noqa: E402

LIB = os.environ.get('NANGATE_LIB', '/home/claude/tools/pdk/orfs/flow/platforms/nangate45/lib/'
                     'NangateOpenCellLibrary_typical.lib')
YOSYS = os.environ.get('YOSYS', '/home/claude/tools/oss-cad-suite/bin/yosys')
OUT = os.path.join(HERE, 'out')

PICO_PARAMS = ('chparam -set ENABLE_COUNTERS 1 -set ENABLE_COUNTERS64 0 -set BARREL_SHIFTER 1 '
               '-set ENABLE_PCPI 1 -set ENABLE_MUL 0 -set ENABLE_FAST_MUL 1 -set ENABLE_DIV 1 '
               '-set COMPRESSED_ISA 0 -set ENABLE_IRQ 0 -set CATCH_MISALIGN 1 -set CATCH_ILLINSN 1 picorv32')

UNITS = [
    # name, top, sources, extra yosys commands before synth
    ('kyber_modmul', 'kyber_modmul', ['rtl/kyber_modmul.v'], ''),
    ('kyber_ise', 'kyber_ise', ['rtl/kyber_ise.v', 'rtl/kyber_modmul.v'], ''),
    ('picorv32', 'picorv32', ['ext/picorv32/picorv32.v'], PICO_PARAMS),
    ('keccak_ise', 'keccak_ise', ['rtl/keccak_ise.v'], ''),
    # clock-gated state register (rtl/keccak_ise.v -DKECCAK_CG: latch-based clock gate,
    # DLL_X1 + AND2_X1; a CLKGATE_X1 blackbox makes Yosys 0.70 dev drop the gated logic)
    ('keccak_ise_cg', 'keccak_ise', ['rtl/keccak_ise.v'], ''),
]

NAND2_AREA = 0.798  # um^2, NAND2_X1 in NanGate45 -> gate equivalents


def abc_script():
    """ABC flow with delay-driven mapping, buffering of high-fanout nets and
    gate sizing (the default Yosys 0.70 script omits buffer/upsize/dnsize)."""
    d = int(os.environ.get('ABC_D', '2000'))   # target delay in ps
    cmds = ['strash', '&get -n', '&fraig -x', '&put', 'scorr', 'dc2', 'dretime', 'strash',
            '&get -n', '&dch -f', '&nf -D %d' % d, '&put', 'buffer -p', 'upsize -D %d' % d,
            'dnsize -D %d' % d, 'stime -p']
    return '+' + ';'.join(c.replace(' ', ',') for c in cmds)


def synth(name, top, srcs, pre):
    os.makedirs(OUT, exist_ok=True)
    out = os.path.join(OUT, name)
    cg = name.endswith('_cg')
    script = '\n'.join([
        'read_verilog ' + ('-DKECCAK_CG ' if cg else '') + ' '.join(os.path.join(ROOT, s) for s in srcs),
        pre,
        'hierarchy -check -top %s' % top,
        'synth -top %s -flatten' % top,
        'dfflibmap -liberty %s' % LIB,
        'abc -liberty %s -script %s' % (LIB, abc_script()),
        'opt_clean -purge',
        'hilomap -hicell LOGIC1_X1 Z -locell LOGIC0_X1 Z',
        'setundef -zero',
        'opt_clean -purge',
        'rename -enumerate -pattern n% w:*',      # short net names shared by JSON and Verilog
        'rename -enumerate -pattern u% c:*',
        'tee -o %s.stat.txt stat -liberty %s' % (out, LIB),
        'write_verilog -noattr -noexpr %s.v' % out,
        'write_json %s.json' % out,
    ])
    with open(out + '.ys', 'w') as f:
        f.write(script + '\n')
    r = subprocess.run([YOSYS, '-q', '-l', out + '.log', '-s', out + '.ys'], capture_output=True, text=True)
    if r.returncode:
        print(r.stdout[-3000:], r.stderr[-3000:])
        raise SystemExit('yosys failed for ' + name)
    return out


def main():
    cells, wl = NL.load_liberty(LIB)
    rows = []
    only = sys.argv[1:]
    prev = {}
    p = os.path.join(ROOT, 'results/synthesis.csv')
    if only and os.path.exists(p):
        prev = {r['unit']: r for r in csv.DictReader(open(p))}
    for name, top, srcs, pre in UNITS:
        if only and name not in only:
            if name in prev:
                rows.append(prev[name])
            continue
        out = synth(name, top, srcs, pre)
        nl = NL.Netlist(out + '.json', top, cells, wl)
        if nl.pin_fix:   # repair the aliased pin names in the Verilog netlist too
            txt = open(out + '.v').read()
            for bad, pin in nl.pin_fix.items():
                txt = txt.replace('.\\' + bad + ' (', '.' + pin + '(')
            open(out + '.v', 'w').write(txt)
            print('  repaired pin aliases:', nl.pin_fix)
        tcrit, depth, endp = nl.sta()
        ncells = len(nl.cells)
        nff = len(nl.ffs)
        rows.append(dict(unit=name, cells=ncells, flops=nff, area_um2=round(nl.area, 1),
                         area_kGE=round(nl.area / NAND2_AREA / 1000, 2),
                         crit_path_ns=round(tcrit, 3), fmax_MHz=round(1000 / tcrit, 1),
                         logic_depth=depth, leakage_uW=round(nl.leak_nw / 1000, 2)))
        print(rows[-1], 'endpoint:', endp)
    with open(os.path.join(ROOT, 'results/synthesis.csv'), 'w', newline='') as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0]))
        w.writeheader()
        w.writerows(rows)


if __name__ == '__main__':
    main()
