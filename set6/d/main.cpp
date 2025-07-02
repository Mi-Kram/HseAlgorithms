#include <iostream>
#include <limits>
#include <vector>

struct Edge {
  int u, v, w;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> edges(m);
  for (int i = 0; i < m; i++) {
    std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
  }

  std::vector<int> dist(n, std::numeric_limits<int>::max());
  dist[0] = 0;

  for (int i = 0; i < n - 1; i++) {
    for (const auto &edge : edges) {
      if (dist[edge.u] != std::numeric_limits<int>::max() && dist[edge.u] + edge.w < dist[edge.v]) {
        dist[edge.v] = dist[edge.u] + edge.w;
      }
    }
  }

  std::vector<bool> inNegativeCycle(n, false);
  for (int i = 0; i < n - 1; i++) {
    for (const auto &edge : edges) {
      if (dist[edge.u] != std::numeric_limits<int>::max() && dist[edge.u] + edge.w < dist[edge.v]) {
        dist[edge.v] = std::numeric_limits<int>::min();
        inNegativeCycle[edge.v] = true;
      }

      if (inNegativeCycle[edge.u]) inNegativeCycle[edge.v] = true;
    }
  }

  for (int i = 1; i < n; i++) {
    if (inNegativeCycle[i]) std::cout << "-inf" << '\n';
    else if (dist[i] == std::numeric_limits<int>::max()) std::cout << "inf" << '\n';
    else std::cout << dist[i] << '\n';
  }

  return 0;
}
