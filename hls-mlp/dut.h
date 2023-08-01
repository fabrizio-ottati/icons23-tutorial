#ifndef HLS4NM_TEST_DUT_H_
#define HLS4NM_TEST_DUT_H_

#include <array>

#include "hls4nm/params.h"
#include "hls_stream.h"
#include "main.h"

void dut(hls::stream<std::array<hls4nm::spike_t, MLP_M[0]>>& inputStream,
         hls::stream<std::array<hls4nm::spike_t, MLP_N[1]>>& outputStream);

#endif  // HLS4NM_TEST_DUT_H_
