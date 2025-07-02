#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <algorithm>

template <typename T>
void quicksort(T* begin, T* end) {
  if (end - begin <= 1) return;

  T* left = begin;
  T* right = end - 1;
  T* pivot = begin + (end - begin) / 2;

  while (left <= right) {
    while (*left < *pivot) ++left;
    while (*right > *pivot) --right;

    if (left <= right) {
      std::swap(*left, *right);
      ++left;
      --right;
    }
  }

  quicksort(begin, right + 1);
  quicksort(left, end);
}

#endif
