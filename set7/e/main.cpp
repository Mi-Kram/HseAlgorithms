#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

bool check(const std::unordered_set<std::string> &a, const std::unordered_set<std::string> &b);
bool dfs(int v, const std::vector<std::vector<int>> &graph, std::vector<bool> &visited, std::vector<int> &match);

int main() {
  int n, k;
  std::cin >> n;

  std::vector<std::unordered_set<std::string>> data(n);
  std::string s;

  for (int i = 0; i < n; ++i) {
    std::cin >> k;
    for (int j = 0; j < k; ++j) {
      std::cin >> s;
      data[i].insert(s);
    }
  }

  std::vector<std::vector<int>> graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j && check(data[i], data[j])) graph[i].push_back(j);
    }
  }

  std::vector<int> match(n, -1);
  int res = 0;
  for (int v = 0; v < n; ++v) {
    std::vector<bool> visited(n, false);
    if (dfs(v, graph, visited, match)) ++res;
  }

  std::cout << n - res;
  return 0;
}

bool check(const std::unordered_set<std::string> &a, const std::unordered_set<std::string> &b) {
  for (const auto &comp : a) if (b.find(comp) == b.end()) return false;
  return true;
}

bool dfs(int v, const std::vector<std::vector<int>> &graph, std::vector<bool> &visited, std::vector<int> &match) {
  if (visited[v]) return false;
  visited[v] = true;

  for (int u : graph[v]) {
    if (match[u] == -1 || dfs(match[u], graph, visited, match)) {
      match[u] = v;
      return true;
    }
  }

  return false;
}
