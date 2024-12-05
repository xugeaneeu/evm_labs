#include <cstddef>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

constexpr size_t MIN_SIZE = 1024 / sizeof(int);
constexpr size_t MAX_SIZE = 128 * 1024 * 1024 / sizeof(int);
constexpr size_t K = 4;

void Cache_Warming(const int *data, const size_t data_size) {
  size_t i, k;
  for (k = 0, i = 0; i < data_size; ++i) {
    k = data[k];
  }

  if (k == 7890) {
    std::cout << "cache warming" << std::endl;
  }
}

void Measure(const int * data, const size_t size) {
  Cache_Warming(data, size);
  size_t k = 0;

  size_t start = __rdtsc();
  for (size_t i = 0; i < size*K; ++i) {
    k = data[k];
  }
  size_t end = __rdtsc();
  std::cout << (end - start)/(size*K) << std::endl;
}

void Gen_Measure_Forward(int *data, const size_t size) {
  for (size_t i = 0; i < size - 1; ++i) {
    data[i] = i + 1;
  }
  data[size - 1] = 0;
  
  std::cout << "Forward: ";
  Measure(data, size);
}

void Gen_Measure_Backward(int *data, const size_t size) {
  for (size_t i = 1; i < size; ++i) {
    data[i] = i - 1;
  }
  data[0] = size - 1;

  std::cout << "Backward: ";
  Measure(data, size);
}

void Gen_Measure_Random(int *data, const size_t size) {
  std::vector<int> RandPerm;
  for (size_t i = 0; i < size; ++i) {
    RandPerm.push_back(i);
  }

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  std::shuffle(RandPerm.begin(), RandPerm.end(), std::default_random_engine(seed));
  for (size_t i = 0; i < size; ++i) {
    data[RandPerm[i]] = RandPerm[(i+1) % size];
  }

  std::cout << "Random: ";
  Measure(data, size);
}


int main (void) {
  int *data_ = new int[MAX_SIZE];
  
  for (size_t data_size = MIN_SIZE; data_size <= MAX_SIZE; data_size*=1.2) {
    std::cout << "\nData size: " << data_size*sizeof(int)/1024 << "Kb" << std::endl;
    Gen_Measure_Forward(data_, data_size);
    Gen_Measure_Backward(data_, data_size);
    Gen_Measure_Random(data_, data_size);
  }
  
  delete [] data_;

  return 0;
}
