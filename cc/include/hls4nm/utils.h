#ifndef HLS4NM_INCLUDE_UTILS_H_
#define HLS4NM_INCLUDE_UTILS_H_

#include <array>
#include <string>
#include <vector>

#include "hls4nm/params.h"

namespace hls4nm {

inline state_t quantize(int val) { return (val >> 8) + ((val >> 7) & 1U); }

void plot_out_spikes(const std::vector<std::array<spike_t, N>>& spk);

void plot_in_spikes(const std::vector<std::array<spike_t, M>>& spk);

std::vector<std::array<spike_t, M>> gen_in_spikes(unsigned T, float SPIKE_RATE);

void gen_weights(const std::string& fname);

}  // namespace hls4nm

#endif  // HLS4NM_INCLUDE_UTILS_H_
