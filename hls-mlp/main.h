#ifndef HLS4NM_TEST_MAIN_H_
#define HLS4NM_TEST_MAIN_H_

constexpr unsigned TIMESTEPS = 80;
constexpr unsigned LEAK = 126; // 0 < LEAK < 127
constexpr unsigned THRES = 20; // 0 < THRES < 127
 
// Spike rate for the inputs.
constexpr float SPIKE_RATE = 0.3;

// Layer size 
constexpr unsigned M = 32;
constexpr unsigned N = 16;

// Simple network.
constexpr unsigned MLP_M[] = {784, 1024};
constexpr unsigned MLP_N[] = {1024, 10};

#endif // HLS4NM_TEST_MAIN_H_
