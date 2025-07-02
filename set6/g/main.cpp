#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

class TwoSAT {
  int n;
  std::vector<std::vector<int>> adj, adj_rev;
  std::vector<int> assignment;
  std::vector<bool> visited;
  std::stack<int> order;

  void dfs1(int v);
  void dfs2(int v, int comp_id, std::vector<int>& component);

 public:
  TwoSAT(int vars);

  void add_clause(int i, bool neg_i, int j, bool neg_j);
  bool solve();
  void print_solution();
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  while (std::cin >> n >> m) {
    TwoSAT solver(n);
    int i1, e1, i2, e2;

    for (int i = 0; i < m; ++i) {
      std::cin >> i1 >> e1 >> i2 >> e2;
      solver.add_clause(i1, !e1, i2, !e2);
    }

    solver.solve();
    solver.print_solution();
  }

  return 0;
}

void TwoSAT::dfs1(int v) {
  visited[v] = true;
  for (int u : adj[v]) {
    if (!visited[u]) dfs1(u);
  }
  order.push(v);
}

void TwoSAT::dfs2(int v, int comp_id, std::vector<int>& component) {
  component[v] = comp_id;
  for (int u : adj_rev[v]) {
    if (component[u] == -1) dfs2(u, comp_id, component);
  }
}

TwoSAT::TwoSAT(int vars) : n(vars), adj(2 * vars), adj_rev(2 * vars), assignment(vars, -1) {
}

void TwoSAT::add_clause(int i, bool neg_i, int j, bool neg_j) {
  int x = 2 * i + neg_i;
  int nx = 2 * i + (1 - neg_i);
  int y = 2 * j + neg_j;
  int ny = 2 * j + (1 - neg_j);

  adj[nx].push_back(y);
  adj[ny].push_back(x);
  adj_rev[y].push_back(nx);
  adj_rev[x].push_back(ny);
}

bool TwoSAT::solve() {
  visited.assign(2 * n, false);
  for (int i = 0; i < 2 * n; ++i) {
    if (!visited[i]) dfs1(i);
  }

  std::vector<int> component(2 * n, -1);
  int comp_id = 0;
  while (!order.empty()) {
    int v = order.top();
    order.pop();
    if (component[v] == -1) dfs2(v, comp_id++, component);
  }

  for (int i = 0; i < n; ++i) {
    if (component[2 * i] == component[2 * i + 1]) return false;
    assignment[i] = component[2 * i] > component[2 * i + 1];
  }

  return true;
}

void TwoSAT::print_solution() {
  for (int i = 0; i < n; ++i) std::cout << (assignment[i] ^ 1);
  std::cout << '\n';
}
