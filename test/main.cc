#include "main.h"
#include "dut.h"

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "hls4nm/lif.h"
#include "hls4nm/params.h"
#include "hls4nm/utils.h"
#include "hls_stream.h"

using namespace std;
using namespace hls4nm;

int main(void) {
  auto in_spk = gen_in_spikes(TIMESTEPS, SPIKE_RATE);

  cout << "\n" << endl;
  cout << "Here are the input spikes!" << endl;
  plot_in_spikes(in_spk);

  hls::stream<array<spike_t, M>> inputStream("inputStream");
  hls::stream<array<spike_t, N>> outputStream("outputStream");

  vector<array<spike_t, N>> out_spk;

  // Loading the spikes in.
  for (const auto& input_val: in_spk) {
    inputStream << input_val;
    dut(inputStream, outputStream);
    out_spk.push_back(outputStream.read());
  }

  cout << "\n" << endl;
  cout << "Here are the output spikes!" << endl;
  plot_out_spikes(out_spk);

  return 0;
}
