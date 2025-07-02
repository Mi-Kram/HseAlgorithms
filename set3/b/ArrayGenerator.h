#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include "algorithm"

#include "UniformRandomInt32.h"

class ArrayGenerator {
 public:
  int* GenerateArray(int n, int from, int to) {
    int* res = new int[n];
    UniformRandomInt32 rand(from, to);

    for (int i = 0; i < n; i++)
      res[i] = rand();

    return res;
  }

  int* GenerateSortedArray(int n, int from, int to) {
    int* res = GenerateArray(n, from, to);
    std::sort(res, res + n, std::greater<int>());
    return res;
  }

  int* GenerateAlmostSortedArray(int n, int from, int to) {
    int* res = GenerateSortedArray(n, from, to);

    int k = n / 10 + 1;
    UniformRandomInt32 rand(0, n - 1);

    for (int i = 0; i < k; i++)
      std::swap(res[rand()], res[rand()]);

    return res;
  }
};

#endif
