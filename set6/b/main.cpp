#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

struct Edge {
  int u, v, weight;
  bool operator<(const Edge &other) const;
};

struct DSU {
  std::vector<int> parent, rank;
  DSU(int n);

  int find(int v);
  bool unite(int a, int b);
};

std::pair<int, int> findTwoMST(int n, std::vector<Edge> &edges);

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> edges(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    edges[i].u--, edges[i].v--;
  }

  auto [s1, s2] = findTwoMST(n, edges);
  std::cout << s1 << ' ' << s2;

  return 0;
}

bool Edge::operator<(const Edge &other) const {
  return weight < other.weight;
}

DSU::DSU(int n) : parent(n), rank(n, 0) {
  for (int i = 0; i < n; ++i) parent[i] = i;
}

int DSU::find(int v) {
  return (parent[v] == v) ? v : (parent[v] = find(parent[v]));
}

bool DSU::unite(int a, int b) {
  a = find(a);
  b = find(b);
  if (a == b) return false;

  if (rank[a] < rank[b]) std::swap(a, b);

  parent[b] = a;
  if (rank[a] == rank[b]) ++rank[a];

  return true;
}

std::pair<int, int> findTwoMST(int n, std::vector<Edge> &edges) {
  DSU dsu(n);
  std::vector<Edge> mstEdges;
  int mstWeight = 0;

  std::sort(edges.begin(), edges.end());

  for (const auto &edge : edges) {
    if (dsu.unite(edge.u, edge.v)) {
      mstWeight += edge.weight;
      mstEdges.push_back(edge);
    }
  }

  int secondMSTWeight = std::numeric_limits<int>::max();
  for (const Edge& removedEdge : mstEdges) {
    DSU dsu2(n);
    int weight = 0, count = 0;

    for (const Edge& edge : edges) {
      if (edge.u == removedEdge.u && edge.v == removedEdge.v && edge.weight == removedEdge.weight) continue;
      
      if (dsu2.unite(edge.u, edge.v)) {
        weight += edge.weight;
        ++count;
      }
    }
    
    if (count == n - 1) secondMSTWeight = std::min(secondMSTWeight, weight);
  }
  return {mstWeight, secondMSTWeight};
}

