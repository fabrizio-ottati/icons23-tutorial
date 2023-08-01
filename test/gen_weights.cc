#include "hls4nm/utils.h"
#include "main.h"

using namespace hls4nm;

int main(void) {
  gen_weights<M, N>("weights.h");
  return 0;
}
