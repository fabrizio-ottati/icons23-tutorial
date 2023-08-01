#include "hls4nm/utils.h"
#include "main.h"

using namespace hls4nm;

int main(void) {
  gen_weights<M, N>("weights.h");
  gen_weights<MLP_M[0], MLP_N[0]>("weights_layer0.h");
  gen_weights<MLP_M[1], MLP_N[1]>("weights_layer1.h");
  return 0;
}
