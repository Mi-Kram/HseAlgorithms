#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int endpoint, reverseIndex, capacity, flow;
  bool isOriginal;
};

class FlowNetwork {
 public:
  FlowNetwork(int nodeCount, int sourceNode, int sinkNode);

  void addEdge(int from, int to, int capacity, bool isOriginal = true);
  int findMaxFlow();
  std::vector<std::vector<int>> retrievePaths();

 private:
  bool buildLevelGraph();
  int sendFlow(int node, int currentFlow);

  std::vector<std::vector<Edge>> adjList;
  std::vector<int> level, pointer;
  int totalNodes, source, sink;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int nodes, edges, source, sink;
  std::cin >> nodes >> edges >> source >> sink;

  FlowNetwork network(nodes, source, sink);
  int u, v;

  for (int i = 0; i < edges; ++i) {
    std::cin >> u >> v;
    network.addEdge(u, v, 1);
  }

  int maxFlow = network.findMaxFlow();
  if (maxFlow < 2) {
    std::cout << "NO";
    return 0;
  }

  auto paths = network.retrievePaths();
  if (paths.size() < 2) {
    std::cout << "NO";
    return 0;
  }

  std::cout << "YES\n";
  for (const auto &path : paths) {
    for (size_t i = 0; i < path.size(); ++i) {
      if (i > 0) std::cout << ' ';
      std::cout << path[i];
    }
    std::cout << '\n';
  }

  return 0;
}

FlowNetwork::FlowNetwork(int nodeCount, int sourceNode, int sinkNode)
  : adjList(nodeCount + 1)
  , level(nodeCount + 1)
  , pointer(nodeCount + 1)
  , totalNodes(nodeCount)
  , source(sourceNode)
  , sink(sinkNode) {
}

void FlowNetwork::addEdge(int from, int to, int capacity, bool isOriginal) {
  Edge forward = {to, (int)adjList[to].size(), capacity, 0, isOriginal};
  Edge backward = {from, (int)adjList[from].size(), 0, 0, false};
  adjList[from].push_back(forward);
  adjList[to].push_back(backward);
}

bool FlowNetwork::buildLevelGraph() {
  std::fill(level.begin(), level.end(), -1);
  std::queue<int> queue;
  queue.push(source);
  level[source] = 0;

  while (!queue.empty()) {
    int currentNode = queue.front();
    queue.pop();

    for (Edge &edge : adjList[currentNode]) {
      if (level[edge.endpoint] == -1 && edge.flow < edge.capacity) {
        level[edge.endpoint] = level[currentNode] + 1;
        queue.push(edge.endpoint);
      }
    }
  }
  return level[sink] != -1;
}

int FlowNetwork::sendFlow(int node, int currentFlow) {
  if (node == sink || currentFlow == 0) return currentFlow;

  for (int &i = pointer[node]; i < adjList[node].size(); ++i) {
    Edge &edge = adjList[node][i];

    if (level[edge.endpoint] == level[node] + 1) {
      int pushed = sendFlow(edge.endpoint, std::min(currentFlow, edge.capacity - edge.flow));

      if (pushed > 0) {
        edge.flow += pushed;
        adjList[edge.endpoint][edge.reverseIndex].flow -= pushed;
        return pushed;
      }
    }
  }

  return 0;
}

int FlowNetwork::findMaxFlow() {
  int maxFlow = 0;

  while (buildLevelGraph()) {
    std::fill(pointer.begin(), pointer.end(), 0);
    while (int flow = sendFlow(source, 1e9)) maxFlow += flow;
  }

  return maxFlow;
}

std::vector<std::vector<int>> FlowNetwork::retrievePaths() {
  std::vector<std::vector<int>> paths;
  std::vector<std::vector<bool>> visited(totalNodes + 1);

  for (int u = 1; u <= totalNodes; ++u)
    visited[u].resize(adjList[u].size(), false);

  for (int k = 0; k < 2; ++k) {
    std::vector<int> path;
    int currentNode = source;
    path.push_back(currentNode);

    while (currentNode != sink) {
      bool progress = false;

      for (int i = 0; i < adjList[currentNode].size(); ++i) {
        Edge &edge = adjList[currentNode][i];

        if (edge.isOriginal && edge.flow > 0 && !visited[currentNode][i]) {
          visited[currentNode][i] = true;
          edge.flow--;
          currentNode = edge.endpoint;
          path.push_back(currentNode);
          progress = true;
          break;
        }
      }

      if (!progress) break;
    }

    if (currentNode != sink) return {};
    paths.push_back(path);
  }

  return paths;
}
