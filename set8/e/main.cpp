#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int levenshtein(const std::string& a, const std::string& b) {
  int n = a.size();
  int m = b.size();

  std::vector<int> prev(m + 1), curr(m + 1);

  for (int j = 0; j <= m; ++j) prev[j] = j;

  for (int i = 1; i <= n; ++i) {
    curr[0] = i;
    for (int j = 1; j <= m; ++j) {
      int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
      curr[j] = std::min({
        prev[j] + 1,
        curr[j - 1] + 1,
        prev[j - 1] + cost
      });
    }
    std::swap(prev, curr);
  }

  return prev[m];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<std::string> strings(2 * n);
  std::string dummy;
  std::getline(std::cin, dummy);

  for (int i = 0; i < 2 * n; ++i)
    std::getline(std::cin, strings[i]);

  for (int i = 0; i < n; ++i) {
    int dist = levenshtein(strings[2 * i], strings[2 * i + 1]);
    std::cout << dist << ' ';
  }

  return 0;
}
