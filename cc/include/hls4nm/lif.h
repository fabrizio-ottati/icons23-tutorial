#ifndef HLS4NM_INCLUDE_LIF_H_
#define HLS4NM_INCLUDE_LIF_H_

#include <array>

#include "hls4nm/params.h"
#include "hls_stream.h"

namespace hls4nm {

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

}  // namespace hls4nm

#endif  //  HLS4NM_INCLUDE_LIF_H_
