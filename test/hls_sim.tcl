set FPGA_DEVICE $::env(FPGA_DEVICE)

open_project prj -reset
add_files -cflags "-I../cc/include" \
  "dut.cc ../cc/src/lif.cc"
add_files -cflags "-I../cc/include" -tb "main.cc ../cc/src/utils.cc"
open_solution solution1 -reset 
set_part $FPGA_DEVICE
set_top dut
csim_design
exit
