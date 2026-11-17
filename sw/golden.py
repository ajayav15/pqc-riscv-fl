"""
Golden (bit-exact) model of the kyber_ise instructions and of the ISE-based
NTT / INTT / base multiplication. Used to
  * verify the Barrett datapath exhaustively,
  * generate test vectors for the RTL testbench,
  * cross-check the C firmware results.
"""
import numpy as np

Q = 3329
M = (1 << 24) // Q          # 5039
ROOT = 17


def brv7(x):
    return int('{:07b}'.format(x)[::-1], 2)


ZETAS = [pow(ROOT, brv7(k), Q) for k in range(128)]   # plain domain
NINV = pow(128, -1, Q)                                  # 3303


def barrett(p):
    t = (p * M) >> 24
    r = p - t * Q
    return r - Q if r >= Q else r


def madd(a, b):
    s = a + b
    return s - Q if s >= Q else s


def msub(a, b):
    d = a - b
    return d + Q if d < 0 else d


def mmul(a, b):
    return barrett(a * b)


def pack(lo, hi):
    return (hi << 16) | lo


def unpack(w):
    return w & 0xFFF, (w >> 16) & 0xFFF


# ---------------- instruction semantics ----------------
class ISE:
    def __init__(self):
        self.z = 0
        self.b = 0

    def kzeta(self, v):
        self.z = v & 0xFFF

    def kct_a(self, rs1, rs2):
        a0, a1 = unpack(rs1)
        b0, b1 = unpack(rs2)
        t0, t1 = mmul(self.z, b0), mmul(self.z, b1)
        self.b = pack(msub(a0, t0), msub(a1, t1))
        return pack(madd(a0, t0), madd(a1, t1))

    def kct_b(self):
        return self.b

    def kgs_a(self, rs1, rs2):
        a0, a1 = unpack(rs1)
        b0, b1 = unpack(rs2)
        self.b = pack(mmul(self.z, msub(a0, b0)), mmul(self.z, msub(a1, b1)))
        return pack(madd(a0, b0), madd(a1, b1))

    kgs_b = kct_b

    def kbmul(self, rs1, rs2):
        a0, a1 = unpack(rs1)
        b0, b1 = unpack(rs2)
        c0 = madd(mmul(a0, b0), mmul(self.z, mmul(a1, b1)))
        c1 = madd(mmul(a0, b1), mmul(a1, b0))
        return pack(c0, c1)

    def kmulz(self, rs1):
        x0, x1 = unpack(rs1)
        return pack(mmul(self.z, x0), mmul(self.z, x1))

    @staticmethod
    def kaddq(rs1, rs2, sub=False):
        a0, a1 = unpack(rs1)
        b0, b1 = unpack(rs2)
        f = msub if sub else madd
        return pack(f(a0, b0), f(a1, b1))


# ---------------- transforms on packed words (w[i] = {c[2i+1], c[2i]}) ----
def ntt_packed(w):
    w = list(w)
    u = ISE()
    k = 1
            # len counts coefficients; words are len/2 apart
    length = 128
    while length >= 2:
        half = length // 2
        for start in range(0, 128, length):
            u.kzeta(ZETAS[k]); k += 1
            for j in range(start, start + half):
                w[j], w[j + half] = u.kct_a(w[j], w[j + half]), None
                w[j + half] = u.kct_b()
        length //= 2
    return w


def invntt_packed(w):
    w = list(w)
    u = ISE()
    k = 127
    length = 2
    while length <= 128:
        half = length // 2
        for start in range(0, 128, length):
            u.kzeta(Q - ZETAS[k]); k -= 1
            for j in range(start, start + half):
                w[j] = u.kgs_a(w[j], w[j + half])
                w[j + half] = u.kgs_b()
        length *= 2
    u.kzeta(NINV)
    return [u.kmulz(x) for x in w]


def basemul_packed(a, b):
    u = ISE()
    r = []
    for i in range(64):
        u.kzeta(ZETAS[64 + i]);     r.append(u.kbmul(a[2 * i], b[2 * i]))
        u.kzeta(Q - ZETAS[64 + i]); r.append(u.kbmul(a[2 * i + 1], b[2 * i + 1]))
    return r


def to_packed(c):
    return [pack(int(c[2 * i]) % Q, int(c[2 * i + 1]) % Q) for i in range(128)]


def from_packed(w):
    out = []
    for x in w:
        lo, hi = unpack(x)
        out += [lo, hi]
    return out


# ---------------- schoolbook reference in R_q = Z_q[X]/(X^256+1) ----
def polymul_schoolbook(a, b):
    r = [0] * 256
    for i in range(256):
        for j in range(256):
            k = i + j
            v = a[i] * b[j]
            if k >= 256:
                r[k - 256] -= v
            else:
                r[k] += v
    return [x % Q for x in r]


if __name__ == '__main__':
    # 1) exhaustive Barrett check over every product of canonical inputs
    p = np.arange(Q * Q, dtype=np.int64)  # all p in [0, q^2); covers every x*y
    t = (p * M) >> 24
    r = p - t * Q
    assert r.min() >= 0 and r.max() < 2 * Q, "Barrett bound violated"
    r = np.where(r >= Q, r - Q, r)
    assert np.array_equal(r, p % Q)
    print('Barrett (k=24, m=5039): exhaustive check over [0, q^2) passed;'
          ' max pre-correction remainder =', int((p - t * Q).max()))

    # 2) NTT -> basemul -> INTT equals negacyclic schoolbook product
    rng = np.random.default_rng(1)
    for trial in range(5):
        a = rng.integers(0, Q, 256).tolist()
        b = rng.integers(0, Q, 256).tolist()
        A, B = ntt_packed(to_packed(a)), ntt_packed(to_packed(b))
        c = from_packed(invntt_packed(basemul_packed(A, B)))
        assert c == polymul_schoolbook(a, b), 'polynomial product mismatch'
        assert from_packed(invntt_packed(A)) == a, 'INTT(NTT(a)) != a'
    print('ISE NTT/basemul/INTT: 5 random negacyclic products match schoolbook')
