#ifndef HLS4NM_INCLUDE_UTILS_H_
#define HLS4NM_INCLUDE_UTILS_H_

#include <array>
#include <vector>

// Excluding this function if we are in synthesis mode.
#ifndef __SYNTHESIS__

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#endif // __SYNTHESIS__

#include "hls4nm/params.h"

namespace hls4nm {

inline state_t quantize(int val) { return (val >> 8) + ((val >> 7) & 1U); }

// Excluding this function if we are in synthesis mode.
#ifndef __SYNTHESIS__

template <unsigned N>
void plot_spikes(const std::vector<std::array<spike_t, N>>& spk) {
  const auto T = spk.size();

  std::cout << std::endl;
  for (auto n = 0; n < N; n++) {
    std::cout << "#" << std::setw(2) << std::setfill('0') << n << ' ';
    for (auto t = 0; t < T; t++) {
      if (spk[t][n]) {
        std::cout << upArrow;
      } else {
        std::cout << ' ';
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::string(4, ' ') << std::string(T, '-') << ">\n" << std::endl;
}

template <unsigned N>
std::vector<std::array<spike_t, N>> gen_in_spikes(unsigned T,
                                                  float SPIKE_RATE) {
  // Seed the random number generator with a time-based value
  std::random_device rd;
  std::mt19937 gen(rd());

  // Create the uniform distribution object
  std::uniform_int_distribution<> distribution(0, 100);

  std::vector<std::array<spike_t, N>> spk(T);

  for (auto n = 0; n < N; n++) {
    for (auto t = 0; t < T; t++) {
      auto random_val = distribution(gen);
      spk[t][n] = random_val < unsigned(SPIKE_RATE * 100);
    }
  }
  return spk;
}

template <unsigned M, unsigned N>
void gen_weights(const std::string& fname) {
  // Seed the random number generator with a time-based value
  std::random_device rd;
  std::mt19937 gen(rd());

  // Create the uniform distribution object
  const weight_t MAX_WEIGHT_VAL = (1 << (WEIGHT_BITW - 1)) - 1;
  std::uniform_int_distribution<> distribution(-MAX_WEIGHT_VAL, MAX_WEIGHT_VAL);

  weight_t weights[M][N];

  std::ofstream ofs(fname);

  if (!ofs.is_open()) {
    throw std::runtime_error("ERROR: Unable to open the file.");
  }

  ofs << "#ifndef HLS4NM_WEIGHTS_H_" << std::endl;
  ofs << "#define HLS4NM_WEIGHTS_H_\n" << std::endl;

  ofs << "#include \"hls4nm/params.h\"\n" << std::endl;

  ofs << "const hls4nm::weight_t WEIGHTS[" << M << "][" << N << "] = {"
      << std::endl;
  for (auto m = 0; m < M; m++) {
    ofs << "{";
    for (auto n = 0; n < N; n++) {
      weights[m][n] = distribution(gen);
      ofs << int(weights[m][n])
          << (n < N - 1 ? ", " : (m < M - 1 ? "}," : "}};\n"));
    }
  }

  ofs << "#endif // HLS4NM_WEIGHTS_H_" << std::endl;
  ofs.close();
}

#endif  // __SYNTHESIS__

}  // namespace hls4nm

#endif  // HLS4NM_INCLUDE_UTILS_H_
