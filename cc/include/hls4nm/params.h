#ifndef HLS4NM_INCLUDE_PARAMS_H_
#define HLS4NM_INCLUDE_PARAMS_H_

#include <cstdint>
#include "ap_int.h"

namespace hls4nm {

// Input feature size.
constexpr unsigned int M = 16;

// Input features size.
constexpr unsigned int N = 8;

// Type associated to the neuron state.
typedef int8_t state_t;

// Type associated to the neuron leakage.
typedef int8_t leak_t;

// Type associated to the neuron threshold.
typedef int8_t thres_t;

// Type associated to the weights.
constexpr unsigned WEIGHT_BITW = 4;
typedef ap_int<WEIGHT_BITW> weight_t;

// Type associated to spikes.
typedef bool spike_t;

// Upper arrow symbol.
constexpr char upArrow[] = "\u2191";

} // namespace hls4nm

#endif // HLS4NM_INCLUDE_PARAMS_H_
