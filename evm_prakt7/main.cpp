#include <climits>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <chrono>
#include <vector>

constexpr int MAX_FRAGMENTS = 32;
constexpr int OFFSET = 16 * 1024 * 1024 / sizeof(int);
constexpr int TRAVERSES = 20;
constexpr int N = OFFSET*MAX_FRAGMENTS;

void CreateList(int *data, const size_t fragments) {
  for (size_t i = 0; i < OFFSET; ++i) {
    for (size_t j = 0; j < fragments - 1; ++j) {
      data[i + j*OFFSET] = static_cast<int>(i + (j+1)*OFFSET);
    }
    data[i + OFFSET*(fragments-1)] = i + 1;
  }
  data[N-1] = 0;
}

void Measure(int *data, const size_t fragments) {
  CreateList(data, fragments);

  size_t minTime = ULLONG_MAX;
  size_t i, k;

  for (size_t traverseNumber = 0; traverseNumber < TRAVERSES; ++traverseNumber) {
    size_t start = __rdtsc();
    for (k = 0, i = 0; i < N; ++i) {
      k = data[k];
    }
    size_t end = __rdtsc();

    if (k == 123457890) {
      std::cout << "smth" << std::endl;
    }

    minTime = std::min(minTime, end - start);
  }

  std::cout << "Fragments: " << fragments << "\nAverage time: " << minTime/N << std::endl;
}

int main() {
  const auto p1 = std::chrono::steady_clock::now();
  const int warmUpDuration = 15;

  const size_t warmUpDataSize = 10000;
  std::vector<double> warmUpData(warmUpDataSize, 0.1);
  while (std::chrono::steady_clock::now() - p1 < std::chrono::seconds(warmUpDuration)) {
    for (size_t i = 0; i < warmUpDataSize; ++i) {
      for (size_t j = 0; j < warmUpDataSize; ++j) {
        warmUpData[i] = warmUpData[i] + warmUpData[j];
      }
    }
  }

  int *data = new int[N];

  for (size_t fragments = 1; fragments <= MAX_FRAGMENTS; ++fragments) {
    Measure(data, fragments);
  }

  delete [] data;
  return 0;
}
