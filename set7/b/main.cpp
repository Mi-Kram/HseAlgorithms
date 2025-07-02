#include <iostream>
#include <vector>

class Kune {
 public:
  Kune(int n, int m);
  void connect(int i, int j);
  void printResult();

 private:
  bool dfs(int u);

  std::vector<std::vector<int>> adj;
  std::vector<int> match;
  std::vector<bool> visited;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  Kune kune(n, m);

  int v;
  for (int i = 0; i < n; i++) {
    while (true) {
      std::cin >> v;
      if (!v) break;
      kune.connect(i, v - 1);
    }
  }

  kune.printResult();

  return 0;
}

Kune::Kune(int n, int m) : adj(n), match(m, -1), visited(n) {
}

void Kune::connect(int i, int j) {
  adj[i].push_back(j);
}

void Kune::printResult() {
  int maxMatching = 0;
  for (int i = 0; i < visited.size(); ++i) {
    visited.assign(visited.size(), false);
    if (dfs(i)) ++maxMatching;
  }

  std::cout << maxMatching << '\n';
  for (int v = 0; v < match.size(); v++) {
    if (match[v] != -1) std::cout << (match[v] + 1) << ' ' << (v + 1) << '\n';
  }
}

bool Kune::dfs(int u) {
  if (visited[u]) return false;

  visited[u] = true;
  for (int v : adj[u]) {
    if (match[v] == -1 || dfs(match[v])) {
      match[v] = u;
      return true;
    }
  }

  return false;
}
