set HLS4NM_ROOT $::env(HLS4NM_ROOT) 
set FPGA_DEVICE $::env(FPGA_DEVICE)

open_project prj -reset
open_solution -reset solution1 
add_files -cflags "-I../cc/include" "dut.cc"
add_files -cflags "-I../cc/include" -tb "main.cc" 
set_part $FPGA_DEVICE
create_clock -period "200MHz" -name default
config_dataflow -default_channel fifo -fifo_depth 2
set_top dut
csynth_design
exit
