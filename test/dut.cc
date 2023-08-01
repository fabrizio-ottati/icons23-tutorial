#include "dut.h"
#include "hls4nm/lif.h"
#include "weights.h"
#include "main.h"

using namespace std;
using namespace hls4nm;

void dut(hls::stream<array<spike_t, M>>& inputStream,
    hls::stream<array<spike_t, N>>& outputStream) {
  static LIF_FC<M, N> layer(WEIGHTS, LEAK, THRES);
  layer.run(inputStream, outputStream);
}
