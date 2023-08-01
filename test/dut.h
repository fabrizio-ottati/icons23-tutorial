#ifndef HLS4NM_TEST_DUT_H_
#define HLS4NM_TEST_DUT_H_

#include <array>

#include "hls4nm/params.h"
#include "hls_stream.h"
#include "main.h"

void dut(hls::stream<std::array<hls4nm::spike_t, M>>& inputStream,
         hls::stream<std::array<hls4nm::spike_t, N>>& outputStream);

#endif  // HLS4NM_TEST_DUT_H_
