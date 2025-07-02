#ifndef SORT_TESTER_H
#define SORT_TESTER_H

#include <chrono>

#include "ArrayGenerator.h"


using generation = int* (*)(int n, int from, int to);
using sorter = int64_t (*)(int* arr, int left, int right);

class SortTester {
 public:
  SortTester() : _from(0), _to(100) {
  }

  SortTester(int from, int to) : _from(from), _to(to) {
  }

  int64_t Test(generation gen, size_t size, sorter sort) {
    if (size <= 1) return 0;

    int* arr = gen(size, _from, _to);

    auto start = std::chrono::high_resolution_clock::now();
    sort(arr, 0, size - 1);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    delete[] arr;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
  }

 private:
  int _from;
  int _to;
};

#endif
