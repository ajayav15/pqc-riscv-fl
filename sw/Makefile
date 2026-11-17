# Bare-metal ML-KEM-512 firmware for PicoRV32 (RV32IM), clang + lld
CC      = clang
CFLAGS  = --target=riscv32 -march=rv32im -mabi=ilp32 -O2 -ffreestanding -nostdlib \
          -fno-builtin -fno-stack-protector -msmall-data-limit=0 -DKYBER_K=2 \
          -Ikyber -Ifw -Iinclude -Wno-unused-parameter
KSRC    = kyber/kem.c kyber/indcpa.c kyber/polyvec.c kyber/poly.c kyber/ntt.c kyber/cbd.c \
          kyber/reduce.c kyber/verify.c kyber/fips202.c kyber/symmetric-shake.c
COMMON  = fw/start.S fw/libc_min.c fw/bench.c

all: build/bench_ref.hex build/bench_ise.hex

build/bench_ref.elf: $(KSRC) $(COMMON)
	mkdir -p build
	$(CC) $(CFLAGS) $(KSRC) $(COMMON) -fuse-ld=lld -Wl,-T,fw/link.ld -o $@

build/bench_ise.elf: $(KSRC) $(COMMON) fw/ise_poly.c fw/ise.h
	mkdir -p build
	$(CC) $(CFLAGS) -DUSE_ISE $(KSRC) $(COMMON) fw/ise_poly.c -fuse-ld=lld -Wl,-T,fw/link.ld -o $@

build/%.hex: build/%.elf
	llvm-objcopy -O binary $< build/$*.bin
	python3 bin2hex.py build/$*.bin $@

clean:
	rm -rf build

build/bench_x25519.elf: fw/bench_x25519.c ../ext/Monocypher/src/monocypher.c fw/start.S fw/libc_min.c
	mkdir -p build
	$(CC) $(CFLAGS) -I../ext/Monocypher/src fw/start.S fw/libc_min.c fw/bench_x25519.c ../ext/Monocypher/src/monocypher.c -fuse-ld=lld -Wl,-T,fw/link.ld -o $@

build/kern_ref.elf: $(KSRC) fw/start.S fw/libc_min.c fw/bench_kern.c
	mkdir -p build
	$(CC) $(CFLAGS) $(KSRC) fw/start.S fw/libc_min.c fw/bench_kern.c -fuse-ld=lld -Wl,-T,fw/link.ld -o $@
build/kern_ise.elf: $(KSRC) fw/start.S fw/libc_min.c fw/bench_kern.c fw/ise_poly.c
	mkdir -p build
	$(CC) $(CFLAGS) -DUSE_ISE $(KSRC) fw/start.S fw/libc_min.c fw/bench_kern.c fw/ise_poly.c -fuse-ld=lld -Wl,-T,fw/link.ld -o $@
