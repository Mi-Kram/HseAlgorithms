#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class UnionFind {
 public:
  UnionFind(int size);
  int find(int x);
  void unite(int x, int y);

 private:
  std::vector<int> parent;
  std::vector<int> rank;
};

class Dinic {
 public:
  explicit Dinic(int n);
  void add_edge(int u, int v, size_t capacity);
  bool bfs(int s, int t);
  size_t dfs(int u, int t, size_t pushed);
  size_t max_flow(int s, int t);

 private:
  class Edge {
   public:
    int a, b;
    size_t capacity;
    size_t weight;
    Edge(int a, int b, size_t cap, size_t w) : a(a), b(b), capacity(cap), weight(w) {
    }
  };

  int n;
  std::vector<std::vector<Edge>> graph;
  std::vector<int> arr;
  std::vector<int> ptr;
};

int getIdx(std::unordered_map<std::string, int>& arrIndex, const std::string& name, int& idx) {
  auto it = arrIndex.find(name);
  if (it != arrIndex.end()) {
    return it->second;
  }
  arrIndex[name] = idx++;
  return idx - 1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;

  std::unordered_map<std::string, int> arrIndex;
  std::vector<std::pair<std::string, std::string>> edges;
  std::vector<std::pair<std::string, std::string>> promts;

  int idx = 0;

  for (int i = 0; i < m; ++i) {
    std::string u_str, v_str;
    std::cin >> u_str >> v_str;
    edges.emplace_back(u_str, v_str);
    getIdx(arrIndex, u_str, idx);
    getIdx(arrIndex, v_str, idx);
  }

  for (int i = 0; i < k; ++i) {
    std::string a_str, b_str;
    std::cin >> a_str >> b_str;
    promts.emplace_back(a_str, b_str);
    getIdx(arrIndex, a_str, idx);
    getIdx(arrIndex, b_str, idx);
  }

  int total_nodes = idx;
  UnionFind uf(total_nodes);

  for (const auto& edge : edges) 
    uf.unite(arrIndex[edge.first], arrIndex[edge.second]);

  std::vector<std::pair<int, int>> directed_edges;
  for (const auto& edge : edges) {
    directed_edges.emplace_back(arrIndex[edge.first], arrIndex[edge.second]);
    directed_edges.emplace_back(arrIndex[edge.second], arrIndex[edge.first]);
  }

  for (const auto& request : promts) {
    const std::string& strA = request.first;
    const std::string& strB = request.second;

    if (strA == strB) {
      std::cout << "0\n";
      continue;
    }

    auto itA = arrIndex.find(strA);
    auto itB = arrIndex.find(strB);
    if (itA == arrIndex.end() || itB == arrIndex.end()) {
      std::cout << "0\n";
      continue;
    }

    if (uf.find(itA->second) != uf.find(itB->second)) {
      std::cout << "0\n";
      continue;
    }

    Dinic dinic(total_nodes);
    for (const auto& e : directed_edges) dinic.add_edge(e.first, e.second, 1);

    std::cout << dinic.max_flow(itA->second, itB->second) << '\n';
  }

  return 0;
}
UnionFind::UnionFind(int size) {
  parent.resize(size);
  rank.resize(size, 0);
  for (int i = 0; i < size; ++i) parent[i] = i;
}

int UnionFind::find(int x) {
  if (parent[x] != x) parent[x] = find(parent[x]);
  return parent[x];
}

void UnionFind::unite(int x, int y) {
  int xRoot = find(x);
  int yRoot = find(y);
  if (xRoot == yRoot) return;

  if (rank[xRoot] < rank[yRoot]) parent[xRoot] = yRoot;
  else {
    parent[yRoot] = xRoot;
    if (rank[xRoot] == rank[yRoot]) ++rank[xRoot];
  }
}

Dinic::Dinic(int n) : n(n), graph(n), arr(n), ptr(n) {
}

void Dinic::add_edge(int u, int v, size_t capacity) {
  graph[u].emplace_back(v, static_cast<int>(graph[v].size()), capacity, 0);
  graph[v].emplace_back(u, static_cast<int>(graph[u].size() - 1), 0, 0);
}

bool Dinic::bfs(int s, int t) {
  std::fill(arr.begin(), arr.end(), -1);
  std::queue<int> q;
  q.push(s);
  arr[s] = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (const Edge& e : graph[u]) {
      if (e.capacity - e.weight > 0 && arr[e.a] == -1) {
        arr[e.a] = arr[u] + 1;
        q.push(e.a);
        if (e.a == t) return true;
      }
    }
  }

  return false;
}

size_t Dinic::dfs(int u, int t, size_t pushed) {
  if (u == t || !pushed) return pushed;

  for (int& i = ptr[u]; i < graph[u].size(); ++i) {
    Edge& e = graph[u][i];
    if (arr[e.a] != arr[u] + 1 || !(e.capacity - e.weight)) continue;

    size_t res = dfs(e.a, t, std::min(pushed, e.capacity - e.weight));
    if (0 < res) {
      e.weight += res;
      graph[e.a][e.b].weight -= res;
      return res;
    }
  }

  return 0;
}

size_t Dinic::max_flow(int s, int t) {
  size_t flow = 0;
  while (bfs(s, t)) {
    std::fill(ptr.begin(), ptr.end(), 0);
    while (size_t pushed = dfs(s, t, std::numeric_limits<size_t>::max())) flow += pushed;
  }
  return flow;
}
