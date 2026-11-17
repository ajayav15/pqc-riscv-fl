"""
leak_campaign.py : fixed-vs-random TVLA campaigns of the masking gadgets on
  * the RTL core with register-level leakage models (tb_soc.v -DLEAKTRACE:
    value, register-write transition, extended datapath transition), and
  * the glitch-aware timing-annotated gate-level simulator (sim/gsim).

  python3 analysis/leak_campaign.py build  <tag> <ver> <ntr> <ndec> <ncbd> <knr> <seed> [targets] [nbm]
  python3 analysis/leak_campaign.py rtl    <tag> [targets]
  python3 analysis/leak_campaign.py gsim   <tag> [targets]
<ver>: v1 = value-model masking (sw/fw/masked_v1.c), v2 = transition/glitch
hardened masking (sw/fw/masked.c + masked_asm.S); suffix z (v1z, v2z) = control
build with all masks forced to zero. Firmware and traces go to
sim/leak/<tag>/t<k>/.  Two targets run in parallel (two cores).
"""
import os
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
SW = os.path.join(ROOT, 'sw')
CF = ('--target=riscv32 -march=rv32im -mabi=ilp32 -O2 -ffreestanding -nostdlib -fno-builtin '
      '-fno-stack-protector -msmall-data-limit=0 -DKYBER_K=2 -Ikyber -Ifw -Iinclude -Wno-unused-parameter').split()
KSRC = ('kyber/kem.c kyber/indcpa.c kyber/polyvec.c kyber/poly.c kyber/ntt.c kyber/cbd.c kyber/reduce.c '
        'kyber/verify.c kyber/fips202.c kyber/symmetric-shake.c').split()
RTL = os.path.join(ROOT, 'sim', 'objl2_ise', 'vsoc')
GSIM = os.path.join(ROOT, 'sim', 'gsim', 'gsim')
GNL = os.path.join(ROOT, 'sim', 'gsim', 'soc.gnl')


def tdir(tag, t):
    d = os.path.join(ROOT, 'sim', 'leak', tag, 't%d' % t)
    os.makedirs(d, exist_ok=True)
    return d


def build(tag, ver, ntr, ndec, ncbd, knr, seed=0, targets=range(6), nbm=8):
    msrc = ['fw/masked_v1.c'] if ver.startswith('v1') else ['fw/masked.c', 'fw/masked_asm.S']
    extra = ['-DMASK_ZERO'] if ver.endswith('z') else []      # control: masks forced to zero
    for t in targets:
        d = tdir(tag, t)
        elf = os.path.join(d, 'fw.elf')
        cmd = ['clang'] + CF + ['-DUSE_ISE', '-DMASK_HW_RNG', '-DTVLA_API', '-DTARGET=%d' % t, '-DNTR=%d' % ntr,
                                '-DNDEC=%d' % ndec, '-DNCBD=%d' % ncbd, '-DKNR=%d' % knr, '-DSEED=%d' % seed, '-DNBM=%d' % nbm] + extra + KSRC + \
              ['fw/start.S', 'fw/libc_min.c', 'fw/tvla.c', 'fw/ise_poly.c'] + msrc + \
              ['-fuse-ld=lld', '-Wl,-T,fw/link.ld', '-o', elf]
        subprocess.run(cmd, cwd=SW, check=True)
        subprocess.run(['llvm-objcopy', '-O', 'binary', elf, os.path.join(d, 'fw.bin')], check=True)
        subprocess.run(['python3', os.path.join(SW, 'bin2hex.py'), os.path.join(d, 'fw.bin'),
                        os.path.join(d, 'fw.hex')], check=True)
        with open(os.path.join(d, 'config.txt'), 'w') as f:
            f.write('ver=%s ntr=%d ndec=%d ncbd=%d knr=%d seed=%d nbm=%d\n' % (ver, ntr, ndec, ncbd, knr, seed, nbm))
    print('built', tag)


def run_one(kind, tag, t):
    d = tdir(tag, t)
    if kind == 'rtl':
        cmd = [RTL, '+fw=' + os.path.join(d, 'fw.hex'), '+maxcyc=2000000000']
        log = os.path.join(d, 'run.log')
    else:
        cmd = [GSIM, GNL, os.path.join(d, 'fw.hex'), '-o', os.path.join(d, 'gleak.bin'), '-maxcyc', '2000000000']
        log = os.path.join(d, 'grun.log')
    with open(log, 'w') as f:
        subprocess.run(cmd, cwd=d, stdout=f, stderr=subprocess.STDOUT, check=False)
    return t, open(log).read()[-300:]


def main():
    kind, tag = sys.argv[1], sys.argv[2]
    if kind == 'build':
        tg = [int(x) for x in sys.argv[9].split(',')] if len(sys.argv) > 9 else range(6)
        nbm = int(sys.argv[10]) if len(sys.argv) > 10 else 8
        build(tag, sys.argv[3], *[int(x) for x in sys.argv[4:9]], targets=tg, nbm=nbm)
        return
    targets = [int(x) for x in sys.argv[3].split(',')] if len(sys.argv) > 3 else list(range(6))
    with ThreadPoolExecutor(2) as ex:
        for t, tail in ex.map(lambda t: run_one(kind, tag, t), targets):
            print('t%d' % t, tail.strip().split('\n')[-1][:200], flush=True)


if __name__ == '__main__':
    main()
