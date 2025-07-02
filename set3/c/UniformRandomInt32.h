#ifndef UNIFORM_RANDOM_INT32_H
#define UNIFORM_RANDOM_INT32_H

#include <random>

class UniformRandomInt32 {
  mutable std::random_device _rd{};
  mutable std::mt19937 _gen{_rd()};
  mutable std::uniform_int_distribution<std::mt19937::result_type> _dist;

 public:
  UniformRandomInt32() {
    setRange(0, 1);
  }

  UniformRandomInt32(int low, int high) {
    setRange(low, high);
  }

  void setRange(int low, int high) {
    std::uniform_int_distribution<std::mt19937::result_type>::param_type param(low, high);
    _dist.param(param);
  }

  int operator()() const {
    return _dist(_gen);
  }
};



#endif
