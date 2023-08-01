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
  auto in_spk = gen_in_spikes<MLP_M[0]>(TIMESTEPS, SPIKE_RATE);

  cout << "\n" << endl;
  cout << "Here are the input spikes!" << endl;
  plot_spikes<MLP_M[0]>(in_spk);

  hls::stream<array<spike_t, MLP_M[0]>> inputStream("inputStream");
  hls::stream<array<spike_t, MLP_N[1]>> outputStream("outputStream");

  vector<array<spike_t, MLP_N[1]>> out_spk;

  // Loading the spikes in.
  for (const auto& input_val: in_spk) {
    inputStream << input_val;
    dut(inputStream, outputStream);
    out_spk.push_back(outputStream.read());
  }

  cout << "\n" << endl;
  cout << "Here are the output spikes!" << endl;
  plot_spikes<MLP_N[1]>(out_spk);

  return 0;
}
