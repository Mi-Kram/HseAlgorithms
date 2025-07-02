#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Edge {
  int to, rev;
  int64_t cap, flow;
};

class Dinic {
 public:
  Dinic(int n);

  void addEdge(int u, int v, int64_t cap);
  int64_t maxFlow(int s, int t);

 private:
  int n;
  std::vector<std::vector<Edge>> adj;
  std::vector<int> arr, ptr;

  bool bfs(int s, int t);
  int64_t dfs(int v, int t, int64_t pushed);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  Dinic dinic(n);
  int u, v, c;
  for (int i = 0; i < m; i++) {
    std::cin >> u >> v >> c;
    dinic.addEdge(u - 1, v - 1, c);
  }

  std::cout << dinic.maxFlow(0, n - 1);
  return 0;
}

Dinic::Dinic(int n) : n(n), adj(n), arr(n), ptr(n) {
}

void Dinic::addEdge(int u, int v, int64_t cap) {
  adj[u].push_back({v, (int)adj[v].size(), cap, 0});
  adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0});
}

int64_t Dinic::maxFlow(int s, int t) {
  int64_t flow = 0, pushed;
  while (bfs(s, t)) {
    std::fill(ptr.begin(), ptr.end(), 0);
    while (pushed = dfs(s, t, std::numeric_limits<int64_t>::max())) flow += pushed;
  }

  return flow;
}

bool Dinic::bfs(int s, int t) {
  std::fill(arr.begin(), arr.end(), -1);

  std::queue<int> q;
  q.push(s);
  arr[s] = 0;

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (Edge &e : adj[v]) {
      if (arr[e.to] == -1 && e.flow < e.cap) {
        arr[e.to] = arr[v] + 1;
        q.push(e.to);
      }
    }
  }
  
  return arr[t] != -1;
}

int64_t Dinic::dfs(int v, int t, int64_t pushed) {
  if (pushed == 0) return 0;
  if (v == t) return pushed;

  int64_t tr;
  for (int &i = ptr[v]; i < adj[v].size(); i++) {
    Edge& e = adj[v][i];
    if (arr[v] + 1 == arr[e.to] && e.flow < e.cap) {
      tr = dfs(e.to, t, std::min(pushed, e.cap - e.flow));
      if (tr == 0) continue;

      e.flow += tr;
      adj[e.to][e.rev].flow -= tr;
      return tr;
    }
  }

  return 0;
}

 