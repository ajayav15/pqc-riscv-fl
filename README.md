# Side-channel-aware ML-KEM acceleration on RISC-V with federated leakage detection

Reproducible implementation for the manuscript
*Micro-Architectural Acceleration of Side-Channel Resistant Post-Quantum Cryptography
for RISC-V IoT Edge Devices Using Federated Intelligence*.

| Objective | What is implemented | Where |
|---|---|---|
| 1. Profiling + RTL + 45 nm synthesis | PC-level cycle profile of ML-KEM-512; custom-0 ISE for NTT/INTT/base multiplication (PCPI coprocessor, 3-stage Barrett multiplier); Yosys/ABC synthesis to NanGate45; STA; gate-level energy | `rtl/`, `syn/`, `analysis/profile.py`, `analysis/gate_energy.py` |
| 2. Federated leakage/attack detection | Trace-driven FL (FedAvg, FedProx, DP-FedAvg) on gate-level ML-KEM traces and the measured ASCAD database, non-IID nodes, int8 deployment, fixed-point RV32 detector | `fl/`, `sw/fw/detector.c` |
| 3. Adaptive mitigation | ISE CFG register: random dummy multiplications, randomized issue order, DVFS request; software butterfly shuffling; detector-triggered closed loop; TVLA + CPA evaluation on the synthesized netlist | `rtl/kyber_ise.v`, `sim/sca.py`, `analysis/sca_eval.py`, `analysis/closed_loop.py` |
| 4. Cycle-accurate emulation and end-to-end benchmark | Verilator/iverilog RTL simulation of PicoRV32 (+ISE) running full ML-KEM-512 and X25519; gate-level SoC simulation; 802.15.4 network model | `tb/`, `sim/`, `analysis/network.py` |
| Extension: Keccak acceleration | `keccak_ise` coprocessor (custom-1): 1600-bit state, 24-cycle permutation, shift-chain I/O (`kk.swap`, `kk.perm`) | `rtl/keccak_ise.v`, `sw/kyber/fips202.c` (`USE_KECCAK_ISE`) |
| Extension: masked decapsulation | First-order masked ML-KEM-512 decapsulation (masked decoding/compression, Keccak, CBD, comparison); hardware masking PRNG (`krng`, xoshiro128**) in `kyber_ise`; leakage assessment on the RTL core | `sw/fw/masked.c`, `sw/fw/tvla.c`, `analysis/tvla_masked.py` |
| Extension: ablations | FL sensitivity to nodes, non-IID degree, sensor noise, local epochs (3 seeds, 95% CI); CPA with 100,000 traces against hiding | `analysis/fl_ablation.py`, `analysis/sca_more.py` |
| Extension: hardened masking (v2) | Transition- and glitch-robust first-order masking: per-share kernels run through a clearing trampoline (`share_run`), ISW AND in assembly (`msk_and32p`), no secret-dependent division, branches or addresses; v1 kept for comparison | `sw/fw/masked.c`, `sw/fw/masked_asm.S`, `sw/fw/masked_v1.c`, `sw/check_kernels.py` |
| Extension: glitch-aware gate-level simulator | Timing-annotated event-driven simulation of the synthesized SoC netlist (NLDM delays at wire-load caps, inertial gate delays, per-toggle energy) with the same testbench as the RTL; TVLA and CPA traces with 4 time bins per cycle | `sim/gsim/`, `analysis/leak_campaign.py`, `analysis/tvla2.py`, `analysis/cpa_gsim.py` |
| Extension: Keccak clock gating | Latch-based clock gate on the 1,600-bit state (`-DKECCAK_CG`), synthesized and verified in RTL; energy correction from enabled-cycle counts | `rtl/keccak_ise.v`, `analysis/keccak_cg.py`, `analysis/energy_final.py` |
| Extension: FPGA lab kit | Arty A7 SoC + UART measurement firmware + ChipWhisperer capture/analysis; Xilinx 7-series resource estimate | `fpga/` (see `fpga/README.md`), `sw/fw/sca_app.c` |

## Toolchain used
- Verilator 5.053, Icarus Verilog 12, Yosys 0.70 (OSS CAD Suite 2026-10-17); NanGate FreePDK45 Open Cell Library (typical)
- clang/lld (RISC-V rv32im target), Python 3.13 + NumPy + Matplotlib
- Cores and code: PicoRV32 (YosysHQ), pq-crystals Kyber reference (round-3 / ML-KEM-512 parameters, `ext/kyber`), Monocypher (X25519 baseline)
- ASCAD fixed-key database (ANSSI), file `ASCAD.h5`, SHA-256 `f56625977fb6db8075ab620b1f3ef49a2a349ae75511097505855376e9684f91`

## Reproduce
```sh
export PATH=<oss-cad-suite>/bin:$PATH
python3 sw/golden.py                         # exhaustive Barrett check, NTT/INTT vs schoolbook
make -C sw all build/kern_ref.hex build/kern_ise.hex build/bench_x25519.hex
# RTL models (Verilator), then benchmarks
verilator --binary --timing -O3 --top-module tb_soc -Mdir sim/obj_ise -o vsoc_ise tb/tb_soc.v ext/picorv32/picorv32.v rtl/kyber_ise.v rtl/kyber_modmul.v
verilator --binary --timing -O3 --top-module tb_soc -DNO_ISE -Mdir sim/obj_ref -o vsoc_ref tb/tb_soc.v ext/picorv32/picorv32.v
sim/obj_ref/vsoc_ref +fw=sw/build/bench_ref.hex ; sim/obj_ise/vsoc_ise +fw=sw/build/bench_ise.hex
python3 analysis/profile.py                  # needs -DPROFILE models and sw/build/prof/*
python3 syn/run_syn.py                       # synthesis, area, STA, leakage -> results/synthesis.csv
python3 syn/cells_from_lib.py syn/out/picorv32.v syn/out/kyber_ise.v > syn/out/nangate_cells.v
#   gate-level SoC (-DGATE -DCOVWIN --coverage-toggle) running sw/build/energy/*.hex, then
python3 analysis/gate_energy.py              # -> results/energy.csv
python3 analysis/sca_eval.py gen eval        # gate-level traces, TVLA, CPA
python3 fl/run_fl.py kem ascad               # federated detection experiments
python3 fl/export_model.py                   # int8 model -> sw/fw/det_model.h; then bench_det on RTL
python3 analysis/detector_cost.py; python3 analysis/closed_loop.py; python3 analysis/network.py
python3 analysis/figures.py
# hardened masking, leakage campaigns and the glitch-aware simulator
g++ -O3 -o sim/gsim/gsim sim/gsim/gsim.cpp
python3 sim/gsim/export.py                    # core + Kyber ISE netlist -> sim/gsim/soc.gnl (add --keccak for the full SoC)
verilator --binary --timing -O3 --top-module tb_soc -DNO_KECCAK -DLEAKTRACE -Mdir sim/objl2_ise -o vsoc tb/tb_soc.v ext/picorv32/picorv32.v rtl/kyber_ise.v rtl/kyber_modmul.v
python3 analysis/leak_campaign.py build v2r v2 20000 1 2 1 0 && python3 analysis/leak_campaign.py rtl v2r && python3 analysis/tvla2.py v2r rtl
python3 analysis/leak_campaign.py build g2 v2 2000 1 2 1 11 && python3 analysis/leak_campaign.py gsim g2 0,4 && python3 analysis/tvla2.py g2 gsim 0,4
#   (v1 = value-model masking, v2z = control with all masks zero; see the script docstrings)
python3 analysis/cpa_gsim.py sim/leak/cpa0 sim/leak/cpa1   # traces from sw/fw/cpa_gs.c on gsim
python3 syn/run_syn.py keccak_ise_cg && python3 analysis/keccak_cg.py && python3 analysis/energy_final.py
python3 analysis/detector_cost.py && python3 analysis/closed_loop.py energy && python3 analysis/network.py
```

## Verification performed
- Barrett multiplier: exhaustive over all products of canonical inputs; ISE NTT -> base mul -> INTT equals negacyclic schoolbook products.
- Full ML-KEM-512 KAT hash identical for reference, ISE and ISE-with-mitigation firmware, natively and on the RTL.
- Verilator and Icarus give identical cycle counts; the synthesized gate-level netlists of the core and the ISE reproduce the RTL checksums and cycle counts exactly.
- Every ISE result in the gate-level side-channel simulation is checked against the golden model (0 mismatches).
- The fixed-point C detector agrees with the bit-exact Python int8 reference on all exported test windows.
- With the Keccak unit the full ML-KEM-512 KAT hash is unchanged (0xa3e59b3c).
- Masked decapsulation equals the reference decapsulation in 400/400 native trials (200 valid, 200 tampered ciphertexts, fresh masks) and in every RTL run.
- Masked v2 equals the reference in 400/400 native trials and in every RTL run (also inside the energy firmware); `sw/check_kernels.py` finds no divide instruction, no unexpected stack frame and only public branches in the kernels.
- The glitch-aware simulator reproduces the RTL cycle counts exactly (e.g. 981,543 cycles and identical checksums for the kernel benchmark, identical TVLA window lengths) with no timing violation at 100 MHz; in zero-delay mode its energy agrees with the Verilator-toggle model of `gate_energy.py` within 1 % (NTT 1.311 vs 1.302 uJ, Decaps 65.84 vs 65.22 uJ logic).
- The clock-gated Keccak unit gives identical outputs and cycle counts to the ungated one in RTL simulation (all energy firmware).
- The FPGA SoC passes a protocol-level simulation (keygen, decapsulation in all three modes, CPA window, all TVLA gadgets).
- The FPGA analysis script recovers the known key coefficient from simulated traces in the capture format.

## Known limitations (state them in the paper)
- Energy: zero-delay toggle simulation for the energy tables (the glitch-aware simulator adds about 3 % dynamic energy in the windows it simulated), no clock tree (clock-net load counted, no buffers), wire-load model instead of extracted parasitics (OpenROAD place and route could not be installed in the build environment); SRAM energy uses an assumed 10 pJ per 32-bit access (`E_SRAM_PJ`). Clock-gating savings are computed from enabled-cycle counts on the ungated toggle data.
- Side-channel traces are simulated per-cycle energies plus a Gaussian measurement-noise model, not oscilloscope measurements; DVFS is modelled at trace level (amplitude V^2 and clock-period jitter), the PMU itself is not in RTL.
- Dummy operations, shuffling and DVFS are hiding countermeasures: a chosen-ciphertext CPA on the full SoC (glitch-aware traces, `sw/fw/cpa_gs.c -DCHOSEN=1`) recovers the key in 100 traces unprotected, about 500 with dummy + shuffle, and ranks it 1 to 3 after 5,000 to 10,000 with DVFS. The ISE-level CPA traces of `sim/sca.py` reset the ISE before every trace, which favours the attacker for known ciphertexts but is not representative of a running core.
- EMP and GLT attack signatures in the FL scenarios are parametric models; CC and REP campaigns come from the trace sources.
- Yosys 0.70 development build aliases some cell pin names after ABC mapping; `syn/netlist.py:repair_pin_names` restores them (verified by the gate-level equivalence runs above).
- Static timing uses an ideal buffer-tree model for nets with fan-out above 16 (a proxy for post-placement buffering), applied identically to every unit.
- Masked code v2: first-order; passes TVLA under the RTL value, register-transition and datapath-transition models (20,000 traces, two independent runs) and in the glitch-aware gate-level simulation (2,000 traces, two runs for decoding, one for CBD; 1,000 traces, one run for the Keccak round); v1 fails the transition models and the gate-level simulation. These are simulations with a modelled leakage function, not measurements; coupling, IR drop and SRAM-internal leakage are not modelled, and the gadget TVLA covers decoding, one Keccak round and CBD, not every line of the decapsulation. Cost: 23.98 M cycles per masked decapsulation (20.6x unmasked). The masking PRNG (xoshiro128**) must be reseeded from a TRNG in silicon.
- Gate-level energy runs use the netlists in `syn/out_energy_netlists` (ISE without the masking PRNG) and `syn/out_energy_masked` (with it); `syn/out` holds the latest synthesis.

## Revision additions (October 2026)
- **Extended leakage assessment.** `sw/fw/tvla.c` targets 6 to 9: masked compress_10 + OR step, compress_4 + OR + final folding, masked sponge G(m||h), share-wise ISE base multiplication. Campaigns: `sim/leak/run_new.sh`, `sim/leak/run_new2.sh` (build, RTL and gate-level runs, analysis with `analysis/tvla2.py`). Two independent RTL runs (20,000 traces) and gate-level runs (600 / 2,000 traces) pass; masks-zero controls fail with |t| 30 to 194.
- **Fix in the masked comparison.** The pass/fail bit is now taken from each accumulator share in its own kernel (`k_acc_bit` in `sw/fw/masked.c`); the earlier code combined the whole accumulator, whose higher bits hold partial ORs. Masked decapsulation still equals the reference in 400/400 native trials; cost about 1,200 cycles more.
- **Delay variation.** `sim/gsim/gsim ... -pvar <sigma> <seed>` gives every gate and flip-flop one delay factor N(1, sigma) clipped to [0.5, 1.5]. With sigma = 0.1, decoding and CBD (masking v2) still pass; controls fail.
- **Replay guard.** `sw/fw/replay_guard.c` (benchmark `sw/fw/bench_guard.c`): positional 32-bit fingerprints of the 128 blocks of u for the last 8 ciphertexts; exact resends are answered from a cache, near-replays raise the alarm. 38,015 cycles per decapsulation, 4.4 KiB RAM.
- **Detector variants.** `analysis/det_lite.py` (F1 of reduced feature sets), `fl/export_model.py --variant noFFT|lite` (int8 models, `det_model_<v>.h`), `sw/fw/detector.c` with `-DDET_SKIP_FFT`, `-DDET_SKIP_RHO`, `-DDET_MODEL_FILE`, `-DDET_VEC_FILE`, profiling with `-DDET_PROF`; closed loop for all variants and the guard: `analysis/closed_loop_variants.py` -> `results/closed_loop_variants.json`.
- Figures are written with TrueType fonts (no Type 3 fonts, as IEEE PDF checks require).

## Not included in this repository
- Large generated data (leakage traces, Verilator builds, synthesized netlists, `data/*.npz`): regenerate with the scripts above.
- The ASCAD database (ANSSI, own licence): download it from the ASCAD project and place `ascad_fixed.npz` in `data/ascad/`.
- The NanGate FreePDK45 Open Cell Library: obtain it with OpenROAD-flow-scripts and point `syn/run_syn.py` to it.
