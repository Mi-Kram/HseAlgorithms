#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string p, t;
  std::getline(std::cin, p);
  std::getline(std::cin, t);

  int m = p.size();
  int n = t.size();

  std::vector<int> arr(m);
  arr[0] = 0;
  for (int i = 1; i < m; ++i) {
    int j = arr[i - 1];
    while (j > 0 && p[i] != p[j]) j = arr[j - 1];
    if (p[i] == p[j]) ++j;
    arr[i] = j;
  }

  std::vector<int> result;
  int j = 0;
  for (int i = 0; i < n; ++i) {
    while (j > 0 && t[i] != p[j]) j = arr[j - 1];
    if (t[i] == p[j]) ++j;
    if (j == m) {
      result.push_back(i - m + 1);
      j = arr[j - 1];
    }
  }

  std::cout << result.size() << '\n';
  for (int pos : result) std::cout << pos << '\n';

  return 0;
}
