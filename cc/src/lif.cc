
#include "hls4nm/lif.h"

#include <cstdint>

#include "hls4nm/params.h"
#include "hls4nm/utils.h"
#include "hls_stream.h"

namespace hls4nm {

// Constructor that loads the weights and initializes the membranes.
LIF_FC::LIF_FC(const weight_t weights[M][N], leak_t leak, thres_t thres)
    : _leak(leak), _thres(thres) {
  reset();
  for (auto m = 0; m < M; m++) {
    for (auto n = 0; n < N; n++) {
      _weights[m][n] = weights[m][n];
    }
  }
}

// State initialization.
void LIF_FC::reset(void) {
  for (auto n = 0; n < N; n++) {
    _states[n] = 0;
  }
}

// Method that run the layer on an input spikes vector.
void LIF_FC::run(hls::stream<std::array<spike_t, M>>& dinStream,
                 hls::stream<std::array<spike_t, N>>& doutStream) {
  // Reading the input spikes.
  auto in_spk = dinStream.read();

  // Synaptic currents.
  int currents[N];

  // Currents initialization.
  for (auto n = 0; n < N; n++) {
    currents[n] = 0;
  }

  // Reading the input spikes and accumulating synaptic currents.
  for (auto m = 0; m < M; m++) {
    if (in_spk[m]) {
      for (auto n = 0; n < N; n++) {
        currents[n] += _weights[m][n];
      }
    }
  }

  std::array<spike_t, N> out_spk;

  // Updating the membranes and spiking out.
  for (auto n = 0; n < N; n++) {
    int next_state = _states[n] * _leak;
    next_state = quantize(next_state);
    next_state += currents[n];
    if (next_state >= _thres) {
      out_spk[n] = 1;
      next_state -= _thres;
    } else {
      out_spk[n] = 0;
    }
    _states[n] = next_state;
  }

  doutStream << out_spk;
}

}  // namespace hls4nm
