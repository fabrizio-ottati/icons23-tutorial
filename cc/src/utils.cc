#include "hls4nm/utils.h"

#include <array>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "hls4nm/params.h"

using namespace std;

namespace hls4nm {

void plot_out_spikes(const vector<array<spike_t, N>>& spk) {
  const auto T = spk.size();

  cout << endl;
  for (auto n = 0; n < N; n++) {
    cout << "#" << setw(2) << setfill('0') << n << ' ';
    for (auto t = 0; t < T; t++) {
      if (spk[t][n]) {
        cout << upArrow;
      } else {
        cout << ' ';
      }
    }
    cout << endl;
  }
  cout << string(4, ' ') << string(T, '-') << ">\n" << endl;
}

void plot_in_spikes(const vector<array<spike_t, M>>& spk) {
  const auto T = spk.size();

  cout << endl;
  for (auto m = 0; m < M; m++) {
    cout << "#" << setw(2) << setfill('0') << m << ' ';
    for (auto t = 0; t < T; t++) {
      if (spk[t][m]) {
        cout << upArrow;
      } else {
        cout << ' ';
      }
    }
    cout << endl;
  }
  cout << string(4, ' ') << string(T, '-') << ">\n" << endl;
}

vector<array<spike_t, M>> gen_in_spikes(unsigned T, float SPIKE_RATE) {
  // Seed the random number generator with a time-based value
  random_device rd;
  mt19937 gen(rd());

  // Create the uniform distribution object
  uniform_int_distribution<> distribution(0, 100);

  vector<array<spike_t, M>> spk(T);

  for (auto m = 0; m < M; m++) {
    for (auto t = 0; t < T; t++) {
      auto random_val = distribution(gen);
      spk[t][m] = random_val < unsigned(SPIKE_RATE * 100);
    }
  }
  return spk;
}

void gen_weights(const std::string& fname) {
  // Seed the random number generator with a time-based value
  random_device rd;
  mt19937 gen(rd());

  // Create the uniform distribution object
  const weight_t MAX_WEIGHT_VAL = (1 << (WEIGHT_BITW - 1)) - 1;
  uniform_int_distribution<> distribution(-MAX_WEIGHT_VAL * 3 / 4,
                                          MAX_WEIGHT_VAL);

  weight_t weights[M][N];

  ofstream ofs(fname);

  if (!ofs.is_open()) {
    throw runtime_error("ERROR: Unable to open the file.");
  }

  ofs << "#ifndef HLS4NM_WEIGHTS_H_" << endl;
  ofs << "#define HLS4NM_WEIGHTS_H_\n" << endl;

  ofs << "#include \"hls4nm/params.h\"\n" << endl;

  ofs << "const hls4nm::weight_t WEIGHTS[" << M << "][" << N << "] = {" << endl;
  for (auto m = 0; m < M; m++) {
    ofs << "{";
    for (auto n = 0; n < N; n++) {
      weights[m][n] = distribution(gen);
      ofs << int(weights[m][n])
          << (n < N - 1 ? ", " : (m < M - 1 ? "}," : "}};\n"));
    }
  }

  ofs << "#endif // HLS4NM_WEIGHTS_H_" << endl;
  ofs.close();
}

}  // namespace hls4nm
