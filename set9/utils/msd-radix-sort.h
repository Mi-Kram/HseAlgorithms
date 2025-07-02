#ifndef MSD_RADIX_SORT_H
#define MSD_RADIX_SORT_H

#include <vector>

template <typename T>
void msd_radix_sort(T* begin, T* end) {
  msd_radix_sort(begin, end, 0);
}

template <typename T>
void msd_radix_sort(T* begin, T* end, size_t d) {
  if (end - begin <= 1) return;

  const int R = 256 + 1;
  std::vector<std::vector<T>> buckets(R);

  for (T* it = begin; it < end; ++it) {
    int c = it->char_at(d) + 1;
    buckets[c].push_back(std::move(*it));
  }

  T* ptr = begin;
  for (int i = 0; i < R; ++i) {
    for (auto& s : buckets[i]) {
      *ptr++ = std::move(s);
    }
  }

  ptr = begin;
  for (int i = 0; i < R; ++i) {
    T* next = ptr + buckets[i].size();
    if (buckets[i].size() > 1 && i > 0) msd_radix_sort(ptr, next, d + 1);
    ptr = next;
  }
}

#endif
