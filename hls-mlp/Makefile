CXX := g++

XILINX_PATH := /eda/xilinx/Vitis_HLS/2023.1

INCLUDES := -I../cc/include
INCLUDES += -I$(XILINX_PATH)/include
CXXFLAGS := -std=c++11 $(INCLUDES)

MINIZED := xc7z007sclg225-1
KRIA := xck26-sfvc784-2LV-c

FPGA_DEVICE := $(KRIA)

export FPGA_DEVICE

all: weights hls

hls: hls_sim hls_syn hls_vivado hls_cosim

gcc_run: main.o dut.o
	$(CXX) $(INCLUDES) main.o dut.o -o main
	./main

weights: gen_weights.o
	$(CXX) $(INCLUDES) gen_weights.o -o gen_weights
	./gen_weights

hls_sim:
	vitis_hls -f hls_sim.tcl

hls_syn:
	vitis_hls -f hls_syn.tcl

hls_vivado:
	vitis_hls -f hls_vivado.tcl

hls_cosim:
	vitis_hls -f hls_cosim.tcl

clean: 
	rm -r prj gen_weights main *.o vitis_hls.log weights*.h
