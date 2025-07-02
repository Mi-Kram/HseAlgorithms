#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int64_t>> dist(n, std::vector<int64_t>(n, std::numeric_limits<int64_t>::max()));

  for (int i = 0; i < n; ++i) dist[i][i] = 0;

  int u, v;
  int64_t w;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v >> w;
    dist[u][v] = std::min(dist[u][v], w);
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dist[i][k] < std::numeric_limits<int64_t>::max() && dist[k][j] < std::numeric_limits<int64_t>::max()) {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        if (dist[i][j] == std::numeric_limits<int64_t>::max()) std::cout << i << ' ' << j << " -1\n";
        else std::cout << i << ' ' << j << ' ' << dist[i][j] << '\n';
      }
    }
  }

  return 0;
}
