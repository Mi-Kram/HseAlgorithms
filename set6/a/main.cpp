#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

class Graph {
  int V;
  std::vector<std::vector<int>> adj, revAdj;
  std::vector<bool> visited;
  std::stack<int> Stack;
  std::vector<int> component;
  int componentCount;

 public:
  Graph(int V);

  void addEdge(int u, int v);
  void dfs1(int v);
  void dfs2(int v);
  void findSCC();
  void printSCC();
};

int main() {
  int n, m;
  std::cin >> n >> m;

  Graph g(n);
  int u, v;
  for (int i = 0; i < m; i++) {
    std::cin >> u >> v;
    g.addEdge(u - 1, v - 1);
  }

  g.findSCC();
  g.printSCC();

  return 0;
}

Graph::Graph(int V) : V(V), adj(V), revAdj(V), visited(V, false), component(V, -1), componentCount(0) {
}

void Graph::addEdge(int u, int v) {
  adj[u].push_back(v);
  revAdj[v].push_back(u);
}

void Graph::dfs1(int v) {
  visited[v] = true;
  for (int u : adj[v]) {
    if (!visited[u]) dfs1(u);
  }
  Stack.push(v);
}

void Graph::dfs2(int v) {
  visited[v] = true;
  component[v] = componentCount;
  for (int u : revAdj[v]) {
    if (!visited[u]) dfs2(u);
  }
}

void Graph::findSCC() {
  fill(visited.begin(), visited.end(), false);
  for (int i = 0; i < V; i++) {
    if (!visited[i]) dfs1(i);
  }

  fill(visited.begin(), visited.end(), false);
  while (!Stack.empty()) {
    int v = Stack.top();
    Stack.pop();
    if (!visited[v]) {
      dfs2(v);
      ++componentCount;
    }
  }
}

void Graph::printSCC() {
  std::cout << componentCount << '\n';
  for (int i = 0; i < V; i++) {
    std::cout << component[i] + 1 << ' ';
  }
  std::cout << '\n';
}
