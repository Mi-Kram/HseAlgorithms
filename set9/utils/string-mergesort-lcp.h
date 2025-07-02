#ifndef STRING_MERGESORT_LCP_H
#define STRING_MERGESORT_LCP_H

template <typename T>
void string_mergesort_lcp(T* begin, T* end) {
  string_mergesort_lcp(begin, end, 0);
}

template <typename T>
void string_mergesort_lcp(T* begin, T* end, int lcp) {
  if (end - begin <= 1) return;
  T* mid = begin + (end - begin) / 2;

  string_mergesort_lcp(begin, mid, lcp);
  string_mergesort_lcp(mid, end, lcp);

  T* merged = new T[end - begin];
  int i = 0, j = 0, k = 0;

  while (begin + i < mid && mid + j < end) {
    int cp = begin[i].common_prefix(mid[j], lcp);
    if (begin[i].compare(mid[j], cp) < 0) merged[k++] = std::move(begin[i++]);
    else merged[k++] = std::move(mid[j++]);
  }

  while (begin + i < mid) merged[k++] = std::move(begin[i++]);
  while (mid + j < end) merged[k++] = std::move(mid[j++]);
  std::move(merged, merged + (end - begin), begin);

  delete[] merged;
}

#endif
