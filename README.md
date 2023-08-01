# ICONS 2023 tutorial - From Training to Deployment: Build a Spiking FPGA on a $300 Budget

This is the code used in the C++ part of the tutorial. Here's the project directory structure: 

```bash
├── cc
│   ├── include # Headers.
│       └── hls4nm
│           ├── lif.h
│           ├── params.h # Parameters of the neuron.
│           └── utils.h
├── LICENSE
└── test
    ├── dut.cc # The design under test. 
    ├── dut.h
    ├── gen_weights.cc # Weights generation.
    ├── hls_cosim.tcl # Scripts for Vitis HLS.
    ├── hls_sim.tcl
    ├── hls_syn.tcl
    ├── hls_vivado.tcl
    ├── main.cc # Our main (testbench).
    ├── main.h # Simulation parameters.
    └── Makefile # File to simplify the compilation process.
```

Before running the HLS scripts, you should set the environment by running `source <path-to-xilinx-programs>/Vitis_HLS/2023.1/settings64.sh`.
