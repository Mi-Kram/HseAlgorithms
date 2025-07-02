#include <iostream>
#include <limits>
#include <vector>

int main() {
  int l, n;
  std::cin >> l >> n;

  std::vector<int> cuts(n + 2);
  cuts[0] = 0;
  for (int i = 1; i <= n; ++i) {
    std::cin >> cuts[i];
  }
  cuts[n + 1] = l;

  std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2, 0));

  for (int len = 2; len <= n + 1; ++len) {
    for (int i = 0; i + len <= n + 1; ++i) {
      int j = i + len;
      dp[i][j] = std::numeric_limits<int>::max();
      for (int k = i + 1; k < j; ++k) {
        dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j] + cuts[j] - cuts[i]);
      }
    }
  }

  std::cout << dp[0][n + 1] << '\n';
  return 0;
}
