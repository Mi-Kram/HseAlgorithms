#include <iostream>
#include <map>
#include <stack>
#include <vector>

struct DSU {
  std::vector<int> parent, size;

  DSU(int n);

  int find(int v);
  void unite(int u, int v);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<std::pair<int, int>> edges(m);
  std::map<std::pair<int, int>, bool> edge_deleted;
  std::vector<std::pair<std::string, std::pair<int, int>>> operations(k);
  std::vector<std::string> results;

  for (auto &[u, v] : edges) {
    std::cin >> u >> v;
    edge_deleted[{u, v}] = false;
    edge_deleted[{v, u}] = false;
  }

  std::string type;
  int u, v;

  for (int i = 0; i < k; ++i) {
    std::cin >> type >> u >> v;
    operations[i] = {type, {u, v}};
    
    if (type == "cut") {
      edge_deleted[{u, v}] = true;
      edge_deleted[{v, u}] = true;
    }
  }

  DSU dsu(n);

  for (auto &[u, v] : edges) {
    if (!edge_deleted[{u, v}]) {
      dsu.unite(u, v);
    }
  }

  for (int i = k - 1; i >= 0; --i) {
    auto [type, nodes] = operations[i];
    int u = nodes.first, v = nodes.second;

    if (type == "ask") results.push_back(dsu.find(u) == dsu.find(v) ? "YES" : "NO");
    else dsu.unite(u, v);
  }

  for (int i = results.size() - 1; i >= 0; --i) {
    std::cout << results[i] << '\n';
  }

  return 0;
}

DSU::DSU(int n) : parent(n + 1), size(n + 1, 1) {
  for (int i = 1; i <= n; ++i) parent[i] = i;
}

int DSU::find(int v) {
  if (parent[v] == v) return v;
  return parent[v] = find(parent[v]);
}

void DSU::unite(int u, int v) {
  u = find(u), v = find(v);
  if (u != v) {
    if (size[u] < size[v]) std::swap(u, v);
    parent[v] = u;
    size[u] += size[v];
  }
}
