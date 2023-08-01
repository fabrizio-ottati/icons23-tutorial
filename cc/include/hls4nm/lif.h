#ifndef HLS4NM_INCLUDE_LIF_H_
#define HLS4NM_INCLUDE_LIF_H_

#include <array>

#include "hls4nm/utils.h"
#include "hls4nm/params.h"
#include "hls_stream.h"

namespace hls4nm {

template <unsigned M, unsigned N>
class LIF_FC {
 public:
  // Default constructor.
  LIF_FC(void) = default;

  // Constructor to save the weights.
  LIF_FC(const weight_t weights[M][N], leak_t leak, thres_t thres);

  void run(hls::stream<std::array<spike_t, M>>& dinStream,
           hls::stream<std::array<spike_t, N>>& doutStream);

  void reset(void);

 private:
  // The layer weights.
  weight_t _weights[M][N];
  state_t _states[N];
  const leak_t _leak;
  const thres_t _thres;
};


// Constructor that loads the weights and initializes the membranes.
template <unsigned M, unsigned N>
LIF_FC<M, N>::LIF_FC(const weight_t weights[M][N], leak_t leak, thres_t thres)
    : _leak(leak), _thres(thres) {
  reset();
  for (auto m = 0; m < M; m++) {
    for (auto n = 0; n < N; n++) {
      _weights[m][n] = weights[m][n];
    }
  }
}

// State initialization.
template <unsigned M, unsigned N>
void LIF_FC<M, N>::reset(void) {
  for (auto n = 0; n < N; n++) {
    _states[n] = 0;
  }
}

// Method that run the layer on an input spikes vector.
template <unsigned M, unsigned N>
void LIF_FC<M, N>::run(hls::stream<std::array<spike_t, M>>& dinStream,
                 hls::stream<std::array<spike_t, N>>& doutStream) {
  constexpr unsigned STATE_MIN = -128;
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
    _states[n] = next_state < STATE_MIN ? STATE_MIN : next_state;
  }

  doutStream << out_spk;
}


}  // namespace hls4nm

#endif  //  HLS4NM_INCLUDE_LIF_H_
