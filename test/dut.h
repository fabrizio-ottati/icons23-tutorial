#ifndef HLS4NM_TEST_DUT_H_
#define HLS4NM_TEST_DUT_H_

#include <array>

#include "hls4nm/params.h"
#include "hls_stream.h"

void dut(hls::stream<std::array<hls4nm::spike_t, hls4nm::M>>& inputStream,
         hls::stream<std::array<hls4nm::spike_t, hls4nm::N>>& outputStream);

#endif  // HLS4NM_TEST_DUT_H_
