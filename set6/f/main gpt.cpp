#include <iostream>
#include <limits>
#include <queue>
#include <unordered_set>
#include <vector>

struct State {
  int year, cost;
  std::vector<int> path;

  bool operator>(const State& other) const {
    return cost > other.cost;
  }
};

std::vector<std::pair<int, int>> getWays(int n, int year) {
  std::string str = std::to_string(year);
  std::vector<std::pair<int, int>> result;

  for (size_t len = 1; len <= str.length(); ++len) {
    for (size_t i = 0; i <= str.length() - len; ++i) {
      int shift = 0, sum = 0;

      for (size_t j = 0; j < len; ++j) {
        shift = shift * 10 + (str[i + j] - '0');
        sum += str[i + j] - '0';
      }

      if (shift == 0) continue;

      if (year + shift <= n) result.emplace_back(shift, sum);
      if (shift < year) result.emplace_back(-shift, sum);
    }
  }

  return result;
}

int main() {
  int n, a, b;
  std::cin >> n >> a >> b;

  if (a == b) {
    std::cout << "0\n0\n";
    return 0;
  }

  std::vector<int> minCost(n + 1, std::numeric_limits<int>::max());
  minCost[a] = 0;

  std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
  pq.push({a, 0, {}});

  while (!pq.empty()) {
    State current = pq.top();
    pq.pop();

    if (current.year == b) {
      std::cout << current.cost << '\n';
      std::cout << current.path.size() << '\n';
      for (int step : current.path) {
        std::cout << (step > 0 ? "+" : "") << step << '\n';
      }
      return 0;
    }

    for (auto [shift, cost] : getWays(n, current.year)) {
      int nextYear = current.year + shift;
      int newCost = current.cost + cost;

      if (newCost < minCost[nextYear]) {
        minCost[nextYear] = newCost;
        std::vector<int> newPath = current.path;
        newPath.push_back(shift);
        pq.push({nextYear, newCost, newPath});
      }
    }
  }

  std::cout << "-1\n";
  return 0;
}
