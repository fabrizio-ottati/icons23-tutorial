set FPGA_DEVICE $::env(FPGA_DEVICE)

open_project prj -reset
add_files -cflags "-I../cc/include" "dut.cc"
add_files -cflags "-I../cc/include" "../cc/src/lif.cc"
add_files -cflags "-I../cc/include" "../cc/src/utils.cc"
add_files -cflags "-I../cc/include" -tb "main.cc" 
open_solution solution1 -reset 
set_part $FPGA_DEVICE
set_top dut
csim_design
exit
