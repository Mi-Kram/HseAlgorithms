#include <iostream>

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

int main() {
  int n;
  std::cin >> n;

  std::string* arr = new std::string[n];
  for (int i = 0; i < n; ++i) std::cin >> arr[i];

  ternary_string_quicksort(arr, arr + n, 0);
  for (int i = 0; i < n; ++i) std::cout << arr[i] << '\n';
  
  delete[] arr;
  return 0;
}
