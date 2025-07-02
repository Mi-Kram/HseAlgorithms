#include <iostream>
#include <set>
#include <vector>

int hammingDistance(const std::vector<int>& arr, size_t shift);

int main() {
  size_t n;
  std::cin >> n;

  std::vector<int> arr(n);
  std::set<std::vector<int>> set;

  for (size_t i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  set.emplace(arr);

  int max_distance = 0, distance;

  for (size_t i = 1; i < n; i++) {
    distance = hammingDistance(arr, i);
    if (distance < max_distance) {
      continue;
    }

    if (max_distance < distance) {
      max_distance = distance;
      set.clear();
    }

    std::vector<int> tmp(n);
    for (size_t j = 0; j < n; j++) {
      tmp[j] = arr[(i + j) % n];
    }
    set.emplace(tmp);
  }

  std::cout << set.size() << '\n';
  return 0;
}

int hammingDistance(const std::vector<int>& arr, size_t shift) {
  int cnt = 0;
  for (size_t i = 0; i < arr.size(); i++) {
    if (arr[i] != arr[shift]) ++cnt;
    if (++shift == arr.size()) shift = 0;
  }

  return cnt;
}
