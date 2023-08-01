# ICONS 2023 tutorial - From Training to Deployment: Build a Spiking FPGA on a $300 Budget

This is the code used in the tutorial. Both the Python scripts for the quantization aware training (QAT) and the high level synthesis parts can be found in this repository.

## Training

In `python` you can find two Jupyter notebooks: the cheatsheet, which is the pre-compiled one, that you can read during the tutorial to follow along; the other one, instead, is empty and you can use it to follow Jason while he codes up during the tutorial. Try it!

## Deploying

In `cc`, the C++ code used by Fabrizio is contained. In particular, in `cc/include/hls4nm/lif.h` you can find the C++ class describing the fully connected LIF layer. 
In `hls-mlp`, a `728-1024-10` LIF multy-layer percerptron implemented in C++ is contained. Be aware, the compilation can take a bit of time! Experiment a bit, add layers and see what the synthesizer puts out!

For more information about Vitis HLS, visit [https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/Introduction](https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/Introduction). If you want to download the latest version of Vitis HLS and Vivado, visit [https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vitis.html](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vitis.html). For the HLS part, before running the scripts, you should set the environment by running `source <path-to-xilinx-programs>/Vitis_HLS/2023.1/settings64.sh`.
