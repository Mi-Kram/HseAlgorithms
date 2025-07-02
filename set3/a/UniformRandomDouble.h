#ifndef UNIFORM_RANDOM_DOUBLE_H
#define UNIFORM_RANDOM_DOUBLE_H

#include <random>

// source: https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c#answer-69125261
class UniformRandomDouble {
  mutable std::random_device _rd{};
  mutable std::mt19937 _gen{_rd()};
  mutable std::uniform_real_distribution<double> _dist;

 public:
  UniformRandomDouble() {
    setRange(0, 1);
  }

  UniformRandomDouble(double low, double high) {
    setRange(low, high);
  }

  void setRange(double low, double high) {
    std::uniform_real_distribution<double>::param_type param(low, high);
    _dist.param(param);
  }

  double operator()() const {
    return _dist(_gen);
  }
};


#endif
