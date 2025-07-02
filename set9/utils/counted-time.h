#ifndef COUNTED_TIME_H
#define COUNTED_TIME_H

#include <chrono>

class CountedTime {
 public:
  using clock = std::chrono::high_resolution_clock;

  CountedTime() : point(clock::now()) {
  }

  long long end() {
    clock::time_point now = clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - point).count();
  }

 private:
  clock::time_point point;
};

#endif