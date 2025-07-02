#include <iostream>

void countingSort(int* arr, int n);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  int* arr = new int[n];
  for (int i = 0; i < n; i++)
    std::cin >> arr[i];
  
  countingSort(arr, n);

  for (int i = 0; i < n; i++)
    std::cout << arr[i] << ' ';
  
  delete[] arr;
  return 0;
}

void countingSort(int* arr, int n) {
  int max = arr[0];
  auto min = arr[0];

  for (int i = 1; i < n; i++) {
    max = std::max(max, arr[i]);
    min = std::min(min, arr[i]);
  }

  int cn = max - min + 1;
  int* counting = new int[cn]{};

  for (auto i = 0; i < n; ++i)
    ++counting[arr[i] - min];

  int k = 0;
  for (auto i = 0; i < cn; ++i) {
    while (counting[i]) {
      arr[k] = min + i;
      --counting[i];
      ++k;
    }
  }

  delete[] counting;
}