#ifndef HLS4NM_TEST_MAIN_H_
#define HLS4NM_TEST_MAIN_H_

constexpr unsigned TIMESTEPS = 80;
constexpr unsigned LEAK = 126; // 0 < LEAK < 127
constexpr unsigned THRES = 20; // 0 < THRES < 127
// Spike rate for the inputs.
constexpr float SPIKE_RATE = 0.3;

#endif // HLS4NM_TEST_MAIN_H_
