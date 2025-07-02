#include <iostream>
#include <vector>

template <typename T>
void ternary_string_quicksort(T* begin, T* end, int d) {
  if (end - begin <= 1) return;

  T* mid = begin + (end - begin) / 2;
  int pivot = (*mid)[d], t;

  T* lt = begin;
  T* gt = end;
  T* i = begin;

  while (i < gt) {
    t = (*i)[d];
    if (t < pivot) std::swap(*lt++, *i++);
    else if (t > pivot) std::swap(*--gt, *i);
    else ++i;
  }

  ternary_string_quicksort(begin, lt, d);
  if (pivot >= 0) ternary_string_quicksort(lt, gt, d + 1);
  ternary_string_quicksort(gt, end, d);
}

template <typename T>
void msd_radix_sort_with_quick(T* begin, T* end, size_t d, size_t threshold) {
  if (end - begin <= 1) return;
  if (end - begin <= threshold) {
    ternary_string_quicksort(begin, end, d);
    return;
  }

  const int R = 256 + 1;
  std::vector<std::vector<T>> buckets(R);

  for (T* it = begin; it < end; ++it) {
    int c = (*it)[d] + 1;
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
    if (buckets[i].size() > 1 && i > 0) msd_radix_sort_with_quick(ptr, next, d + 1, threshold);
    ptr = next;
  }
}

int main() {
  int n;
  std::cin >> n;

  std::string* arr = new std::string[n];
  for (int i = 0; i < n; ++i) std::cin >> arr[i];

  msd_radix_sort_with_quick(arr, arr + n, 0, 74);
  for (int i = 0; i < n; ++i) std::cout << arr[i] << '\n';
  
  delete[] arr;
  return 0;
}
