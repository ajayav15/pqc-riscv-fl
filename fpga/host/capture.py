"""
capture.py : power/EM trace acquisition from the FPGA target (fpga/arty_a7) with a
NewAE ChipWhisperer scope (Lite or Husky) and the board's USB-UART.

Wiring: scope trigger input <- Pmod JA pin 1 (trigger); scope measurement input
<- shunt / EM probe on the FPGA core supply (VCCINT); common ground.

Campaigns (results saved to traces_<campaign>.npz):
  tvla   --target T --n N          fixed-vs-random gadget traces (targets as in sw/fw/tvla.c)
  cpa    --mode M --n N            base-multiplication window with random ciphertext words,
                                   M = 0 unprotected, 1 hiding, 2 masking (CFG mode only
                                   affects the ISE; masking applies to full decapsulation)
  decaps --mode M --n N            whole decapsulations with fresh random ciphertexts
                                   (timing + trace windows; needs a long capture buffer)

Example:
  python3 capture.py --port /dev/ttyUSB1 keygen
  python3 capture.py --port /dev/ttyUSB1 cpa --mode 0 --n 20000
  python3 capture.py --port /dev/ttyUSB1 tvla --target 0 --n 20000
"""
import argparse
import os
import struct
import time
import numpy as np

Q = 3329
COINS = bytes((i * 7 + 1) & 0xFF for i in range(64))   # same coins as fpga/sim/gen_vec.c


class Target:
    def __init__(self, port, baud=115200):
        import serial
        self.s = serial.Serial(port, baud, timeout=5)
        time.sleep(0.1)
        self.s.reset_input_buffer()

    def cmd(self, c, payload=b'', reply_len=0):
        self.s.write(c + payload)
        r = self.s.read(1)
        if r != c.lower():
            raise RuntimeError('bad reply %r to %r' % (r, c))
        return self.s.read(reply_len) if reply_len else b''


class Scope:
    def __init__(self, samples, offset=0, adc_hz=100e6):
        import chipwhisperer as cw
        self.scope = cw.scope()
        sc = self.scope
        sc.default_setup()
        sc.clock.clkgen_freq = adc_hz           # asynchronous sampling of the 25 MHz target
        sc.clock.adc_src = 'clkgen_x1'
        sc.trigger.triggers = 'tio4'            # trigger pin from Pmod JA1
        sc.adc.basic_mode = 'rising_edge'
        sc.adc.samples = samples
        sc.adc.offset = offset
        sc.gain.db = 25

    def arm(self):
        self.scope.arm()

    def get(self):
        if self.scope.capture():
            raise RuntimeError('capture timed out')
        return np.asarray(self.scope.get_last_trace(), dtype=np.float32)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--port', required=True)
    ap.add_argument('--samples', type=int, default=5000)
    ap.add_argument('--offset', type=int, default=0)
    ap.add_argument('--out', default='.')
    sub = ap.add_subparsers(dest='campaign', required=True)
    sub.add_parser('keygen')
    t = sub.add_parser('tvla'); t.add_argument('--target', type=int, required=True); t.add_argument('--n', type=int, default=20000)
    c = sub.add_parser('cpa'); c.add_argument('--mode', type=int, default=0); c.add_argument('--n', type=int, default=20000)
    d = sub.add_parser('decaps'); d.add_argument('--mode', type=int, default=0); d.add_argument('--n', type=int, default=200)
    a = ap.parse_args()
    rng = np.random.default_rng()
    tgt = Target(a.port)
    tgt.cmd(b'S', os.urandom(4))                       # seed the masking PRNG from the host TRNG
    pk = tgt.cmd(b'K', COINS, 800)
    if a.campaign == 'keygen':
        print('pk[0:16] =', pk[:16].hex()); return
    sc = Scope(a.samples, a.offset)
    traces, meta = [], []
    t0 = time.time()
    if a.campaign == 'tvla':
        for i in range(a.n):
            cls = int(rng.integers(2))
            sc.arm(); tgt.cmd(b'T', bytes([a.target, cls])); traces.append(sc.get()); meta.append(cls)
    elif a.campaign == 'cpa':
        tgt.cmd(b'M', bytes([min(a.mode, 1)]))
        for i in range(a.n):
            co = rng.integers(0, Q, 4)                      # (u0_lo, u0_hi, u1_lo, u1_hi)
            w0 = int(co[0]) | int(co[1]) << 16; w1 = int(co[2]) | int(co[3]) << 16
            sc.arm(); tgt.cmd(b'B', struct.pack('<II', w0, w1)); traces.append(sc.get()); meta.append(co)
    else:
        tgt.cmd(b'M', bytes([a.mode]))
        for i in range(a.n):
            ct = os.urandom(768)                            # random (mostly invalid) ciphertexts
            sc.arm(); tgt.cmd(b'D', ct, 32); traces.append(sc.get()); meta.append(np.frombuffer(ct, np.uint8))
    print('%d traces in %.0f s' % (len(traces), time.time() - t0))
    name = os.path.join(a.out, 'traces_%s_%s.npz' % (a.campaign, a.target if a.campaign == 'tvla' else a.mode))
    np.savez_compressed(name, traces=np.array(traces), meta=np.array(meta), campaign=a.campaign)
    print('saved', name)


if __name__ == '__main__':
    main()
