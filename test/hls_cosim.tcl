open_project prj
open_solution solution1
add_files -cflags "-I../cc/include" -tb "main.cc ../cc/src/utils.cc"
cosim_design
exit
