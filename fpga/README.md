# FPGA side-channel target (lab kit)

Puts the same SoC as the ASIC flow (PicoRV32 RV32IM + `kyber_ise` + `keccak_ise`) on a
Digilent Arty A7 so that the gate-level side-channel results can be repeated with
measured power or EM traces.

## What is here

| Path | What |
| --- | --- |
| `rtl/soc_top.v`, `rtl/uart.v` | FPGA SoC: core, both coprocessors, 128 KiB block RAM, UART, scope trigger, LEDs |
| `arty_a7/top_arty.v`, `arty_a7/arty_a7.xdc`, `arty_a7/build.tcl` | Arty A7 top level (25 MHz core clock from the MMCM), pins, Vivado batch build |
| `../sw/fw/sca_app.c` | Measurement firmware: UART command protocol (keygen, mode, decapsulation, CPA window, TVLA gadgets) |
| `sim/tb_fpga.v`, `sim/gen_vec.c` | Protocol-level simulation of the whole FPGA SoC with a UART host model |
| `host/capture.py` | Acquisition with a ChipWhisperer scope + the board's USB-UART |
| `host/analyze.py` | TVLA and CPA on the captured traces (same method as the simulation) |

## Steps

1. **Build the firmware** (from `sw/`):
   ```sh
   C="clang --target=riscv32 -march=rv32im -mabi=ilp32 -O2 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -msmall-data-limit=0 -DKYBER_K=2 -Ikyber -Ifw -Iinclude"
   $C -DUSE_ISE -DUSE_KECCAK_ISE -DMASK_HW_RNG -DTVLA_API kyber/*.c fw/start.S fw/libc_min.c fw/sca_app.c fw/masked.c fw/ise_poly.c \
      -fuse-ld=lld -Wl,-T,fw/link128.ld -o build/sca_app.elf
   llvm-objcopy -O binary build/sca_app.elf build/sca_app.bin && python3 bin2hex.py build/sca_app.bin build/sca_app.hex
   ```
2. **(Optional) simulate** the FPGA design: `fpga/sim` (see the Verilator command in the main README). It runs keygen and decapsulation in all three modes, checks the shared secrets against `vec.hex`, and prints the trigger-window lengths.
3. **Build the bitstream** (Vivado 2020.2 or later): `cd fpga/arty_a7 && vivado -mode batch -source build.tcl -tclargs xc7a35ticsg324-1L ../../sw/build/sca_app.hex`.
   Check the pin locations in `arty_a7.xdc` against the Digilent master XDC for your board revision first.
4. **Measurement set-up.**
   - Power: cut the VCCINT path and insert a 1 to 10 ohm shunt, or (easier) use a near-field EM probe over the FPGA package.
   - Connect the scope input to the shunt or probe. Connect the trigger input (`tio4` on ChipWhisperer) to Pmod JA pin 1 (G13), with a common ground.
5. **Program the board, then run the campaigns**:
   ```sh
   python3 fpga/host/capture.py --port /dev/ttyUSB1 keygen                 # sanity check
   python3 fpga/host/capture.py --port /dev/ttyUSB1 --samples 3000 cpa --mode 0 --n 20000
   python3 fpga/host/capture.py --port /dev/ttyUSB1 --samples 3000 cpa --mode 1 --n 100000
   for t in 0 1 2 3 4 5; do python3 fpga/host/capture.py --port /dev/ttyUSB1 --samples 20000 tvla --target $t --n 20000; done
   python3 fpga/host/analyze.py cpa traces_cpa_0.npz --s0 $(sw/build/native/gen_vec --s0)
   python3 fpga/host/analyze.py tvla traces_tvla_0.npz
   ```
   Adjust `--samples` and `--offset` to the window length you see at 100 MS/s; the trigger-window lengths from the simulation are in `fpga/sim/run.log`.

## Expected outcomes (from the gate-level simulation)

- **Unprotected CPA (mode 0):** the key coefficient is recovered in roughly 100 to 1,000 traces.
- **Hiding (mode 1):** no recovery at 20,000 traces in simulation. On real hardware, collect at least 100,000 traces to bound it.
- **TVLA:**
  - Unmasked targets (1, 3, 5) fail.
  - Masked targets (0, 2, 4) passed in simulation under the value model.
  - On silicon, transition and glitch leakage may appear (see the limitations in the main README). Report what you measure.

## Not verified here

The bitstream build, the pin assignment and the ChipWhisperer settings could not be run in this environment (no Vivado or hardware). The RTL, the firmware and the UART protocol are verified in simulation (`fpga/sim/run.log`).
