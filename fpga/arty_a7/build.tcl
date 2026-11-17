# Vivado non-project build of the side-channel target for the Arty A7.
#   vivado -mode batch -source build.tcl -tclargs <part> <firmware.hex>
# part: xc7a35ticsg324-1L (Arty A7-35T, default) or xc7a100tcsg324-1 (A7-100T)
set part     [expr {[llength $argv] > 0 ? [lindex $argv 0] : "xc7a35ticsg324-1L"}]
set firmware [expr {[llength $argv] > 1 ? [lindex $argv 1] : "../../sw/build/sca_app.hex"}]
set here [file dirname [file normalize [info script]]]
set root [file normalize "$here/../.."]
file mkdir "$here/out"
file copy -force $firmware "$here/out/firmware.hex"
cd "$here/out"

read_verilog [list \
    "$root/ext/picorv32/picorv32.v" \
    "$root/rtl/kyber_modmul.v" "$root/rtl/kyber_ise.v" "$root/rtl/keccak_ise.v" \
    "$root/fpga/rtl/uart.v" "$root/fpga/rtl/soc_top.v" "$here/top_arty.v"]
read_xdc "$here/arty_a7.xdc"

synth_design -top top_arty -part $part
report_utilization -file util_synth.rpt
opt_design
place_design
route_design
report_timing_summary -file timing.rpt
report_utilization -hierarchical -file util_hier.rpt
report_power -file power.rpt
write_bitstream -force top_arty.bit
puts "bitstream: $here/out/top_arty.bit"
