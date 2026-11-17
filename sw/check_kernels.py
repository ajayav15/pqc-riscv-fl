"""
check_kernels.py : static checks of the masked-code kernels in a RISC-V ELF
(sw/fw/masked.c, version 2).
  * kernels run with KCLR = 0 must not have a stack frame (their stack is not
    cleared by share_run);
  * no kernel or gadget contains a divide / remainder instruction (the
    multi-cycle divider keeps its operands between instructions);
  * every conditional branch is listed with its operands for manual review
    (all must depend only on loop counters, the share index or public lengths).
usage: python3 check_kernels.py build/x.elf
"""
import re
import subprocess
import sys

FRAMED = {'kr_lin': 64, 'k_dec_mul': 128, 'k_reenc_mul': 128}
PREFIX = ('ks32_', 'ks64_', 'cmp32_', 'cmp64_', 'b2a_', 'cbd_acc', 'kr_', 'sp_', 'k_', 'tv_ld', 'tv_put', 'tv_clr',
          'msk_and32p', 'share_run')


def main():
    dis = subprocess.run(['llvm-objdump', '-d', '--no-show-raw-insn', sys.argv[1]], capture_output=True, text=True).stdout
    funcs = re.split(r'\n(?=[0-9a-f]+ <)', dis)
    bad = 0
    for f in funcs:
        m = re.match(r'([0-9a-f]+) <([^>]+)>', f)
        if not m or not m.group(2).startswith(PREFIX):
            continue
        name = m.group(2)
        ins = [l.split('\t')[1:] for l in f.split('\n')[1:] if '\t' in l]
        ops = [(i[0].strip(), i[1].strip() if len(i) > 1 else '') for i in ins if i]
        fr = [int(a.split(',')[-1].strip(), 0) for o, a in ops if o == 'addi' and a.startswith('sp, sp, -')]
        frame = -fr[0] if fr else 0
        if name in ('share_run',):
            frame = 0
        if frame and frame > FRAMED.get(name, 0):
            print('FRAME  %-16s %d bytes, cleared %d' % (name, frame, FRAMED.get(name, 0)))
            bad += 1
        for o, a in ops:
            if o.startswith(('div', 'rem')):
                print('DIV    %-16s %s %s' % (name, o, a))
                bad += 1
        br = ['%s %s' % (o, a) for o, a in ops if re.match(r'b(eq|ne|lt|ge)', o)]
        print('%-16s frame=%-4d branches: %s' % (name, frame, '; '.join(br) if br else '-'))
    print('violations:', bad)
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
