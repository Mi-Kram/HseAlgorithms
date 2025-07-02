#include <iostream>
#include <vector>

template <typename T>
void msd_radix_sort(T* begin, T* end, size_t d) {
  if (end - begin <= 1) return;

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
    if (buckets[i].size() > 1 && i > 0) msd_radix_sort(ptr, next, d + 1);
    ptr = next;
  }
}

int main() {
  int n;
  std::cin >> n;

  std::string* arr = new std::string[n];
  for (int i = 0; i < n; ++i) std::cin >> arr[i];

  msd_radix_sort(arr, arr + n, 0);
  for (int i = 0; i < n; ++i) std::cout << arr[i] << '\n';
  
  delete[] arr;
  return 0;
}
