#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <algorithm>

template <typename T>
static void merge(T* begin, T* middle, T* end);

template <typename T>
void mergesort(T* begin, T* end) {
  if (end - begin <= 1) return;

  T* middle = begin + (end - begin) / 2;

  mergesort(begin, middle);
  mergesort(middle, end);
  merge(begin, middle, end);
}

template <typename T>
static void merge(T* begin, T* middle, T* end) {
  int left_size = middle - begin;
  int right_size = end - middle;

  T* buffer = new T[left_size + right_size];
  std::copy(begin, end, buffer);

  int i = 0, j = left_size, k = 0;

  while (i < left_size && j < left_size + right_size)
    begin[k++] = (buffer[i] <= buffer[j]) ? buffer[i++] : buffer[j++];

  while (i < left_size) begin[k++] = buffer[i++];
  while (j < left_size + right_size) begin[k++] = buffer[j++];

  delete[] buffer;
}

#endif
