#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, limit;
  std::cin >> n >> limit;

  std::vector<int> m(n);
  std::vector<int> c(n);

  for (int i = 0; i < n; ++i) std::cin >> m[i];
  for (int i = 0; i < n; ++i) std::cin >> c[i];

  std::vector<int> dp(limit + 1, 0);

  for (int i = 0; i < n; ++i) {
    for (int j = limit; j >= m[i]; --j) {
      dp[j] = std::max(dp[j], dp[j - m[i]] + c[i]);
    }
  }

  std::cout << dp[limit] << '\n';
  return 0;
}
