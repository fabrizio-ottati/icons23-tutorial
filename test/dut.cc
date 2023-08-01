#include "dut.h"

#include "hls4nm/lif.h"
#include "main.h"
#include "weights.h"
#include "weights_layer0.h"
#include "weights_layer1.h"

using namespace std;
using namespace hls4nm;

void dut(hls::stream<array<spike_t, MLP_M[0]>>& inputStream,
         hls::stream<array<spike_t, MLP_N[1]>>& outputStream) {
  hls::stream<array<spike_t, MLP_N[0]>> stream0("stream0");
  static LIF_FC<MLP_M[0], MLP_N[0]> layer0(WEIGHTS_LAYER0, LEAK, THRES);
  static LIF_FC<MLP_M[1], MLP_N[1]> layer1(WEIGHTS_LAYER1, LEAK, THRES);

#pragma HLS dataflow
  layer0.run(inputStream, stream0);
  layer1.run(stream0, outputStream);
}
