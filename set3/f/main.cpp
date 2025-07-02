#include <math.h>

#include <iostream>
#include <queue>
#include <vector>

void radixSort(std::vector<int> &arr, int base) {
  if (arr.size() <= 1) return;

  std::vector<std::queue<int>> a(base);
  std::vector<std::queue<int>> b(base);

  int max = arr[0];
  int cnt = 0, exp = 1;

  for (int item : arr)
    if (max < std::abs(item))
      max = std::abs(item);

  while (max) {
    ++cnt;
    max /= base;
  }

  while (cnt) {
    for (int item : arr) {
      if (0 <= item) a[item / exp % base].push(item);
      else b[std::abs(item / exp % base)].push(item);
    }
    arr.clear();

    for (int i = base - 1; i >= 0; --i) {
      while (!b[i].empty()) {
        arr.push_back(b[i].front());
        b[i].pop();
      }
    }

    for (int i = 0; i < base; ++i) {
      while (!a[i].empty()) {
        arr.push_back(a[i].front());
        a[i].pop();
      }
    }

    exp *= base;
    --cnt;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> arr(n);
  for (int i = 0; i < n; ++i) std::cin >> arr[i];
  
  radixSort(arr, 256);
  for (int item : arr) std::cout << item << ' ';

  return 0;
}