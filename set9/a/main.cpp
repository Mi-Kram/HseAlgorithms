#include <iostream>

int common_prefix(const std::string& s1, const std::string& s2, int offset) {
  int i = offset;
  while (i < s1.size() && i < s2.size()) {
    if (s1[i] != s2[i]) break;
    ++i;
  }
  return i;
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
    int cp = common_prefix(begin[i], mid[j], lcp);
    if (begin[i].compare(cp, std::string::npos, mid[j], cp, std::string::npos) < 0) merged[k++] = std::move(begin[i++]);
    else merged[k++] = std::move(mid[j++]);
  }

  while (begin + i < mid) merged[k++] = std::move(begin[i++]);
  while (mid + j < end) merged[k++] = std::move(mid[j++]);
  std::move(merged, merged + (end - begin), begin);

  delete[] merged;
}

int main() {
  int n;
  std::cin >> n;

  std::string* arr = new std::string[n];
  for (int i = 0; i < n; ++i) std::cin >> arr[i];

  string_mergesort_lcp(arr, arr + n, 0);
  for (int i = 0; i < n; ++i) std::cout << arr[i] << '\n';
  
  delete[] arr;
  return 0;
}
