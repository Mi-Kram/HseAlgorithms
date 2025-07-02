#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Point {
  int x;
  int y;
};

bool dfs(size_t u, const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& match);

int main() {
  int n, m, a, b;
  std::cin >> n >> m >> a >> b;

  std::vector<std::string> grid(n);
  for (int i = 0; i < n; ++i) std::cin >> grid[i];

  std::vector<Point> arrA, arrB;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == '*') {
        if ((i + j) % 2) arrB.push_back({i, j});
        else arrA.push_back({i, j});
      }
    }
  }

  int free = arrA.size() + arrB.size();
  if (!free) {
    std::cout << "0\n";
    return 0;
  }

  if (2 * b <= a) {
    std::cout << free * b << '\n';
    return 0;
  }

  std::vector<std::vector<int>> graph(arrA.size());
  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {1, 0, -1, 0};

  for (size_t i = 0; i < arrA.size(); ++i) {
    Point p = arrA[i];
    for (int dir = 0; dir < 4; ++dir) {
      int nx = p.x + dx[dir];
      int ny = p.y + dy[dir];

      if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '*') {
        auto it = std::find_if(arrB.begin(), arrB.end(), [nx, ny](const Point& pt) {
          return pt.x == nx && pt.y == ny;
        });

        if (it != arrB.end()) {
          graph[i].push_back(std::distance(arrB.begin(), it));
        }
      }
    }
  }

  std::vector<int> match(arrB.size(), -1);
  int cnt = 0;

  for (size_t u = 0; u < arrA.size(); ++u) {
    std::vector<bool> visited(arrA.size(), false);
    if (dfs(u, graph, visited, match)) ++cnt;
  }

  int res = cnt * a + (free - 2 * cnt) * b;
  std::cout << res << '\n';
  return 0;
}

bool dfs(size_t u, const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& match) {
  if (visited[u]) return false;
  visited[u] = true;

  for (int v : graph[u]) {
    if (match[v] == -1 || dfs(match[v], graph, visited, match)) {
      match[v] = u;
      return true;
    }
  }
  
  return false;
}
