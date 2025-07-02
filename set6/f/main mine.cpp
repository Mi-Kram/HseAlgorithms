#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

struct Storage {
  int weight;
  std::vector<int> way;

  Storage() : weight(0), way() {
  }

  Storage(int value) : weight(value), way() {
  }
};

std::unordered_map<int, int> getWays(int n, int year) {
  std::string str = std::to_string(year);
  std::unordered_map<int, int> result;
  int shift, sum;

  for (size_t len = 1; len <= str.length(); ++len) {
    for (size_t i = 0; i <= str.length() - len; ++i) {
      shift = 0;
      sum = 0;

      for (size_t j = 0; j < len; ++j) {
        shift *= 10;
        shift += str[i + j] - '0';
        sum += str[i + j] - '0';
      }

      if (!shift) continue;

      if (year + shift <= n) result[shift] = sum;
      if (shift < year) result[-shift] = sum;
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

  std::vector<Storage> arr(n + 1, Storage(std::numeric_limits<int>::max()));
  arr[a].weight = 0;

  std::queue<int> queue;
  queue.push(a);

  int year, nextYear;
  while (!queue.empty()) {
    year = queue.front();
    queue.pop();

    std::unordered_map<int, int> ways = getWays(n, year);

    for (auto &&way : ways) {
      nextYear = year + way.first;
      if (arr[year].weight + way.second < arr[nextYear].weight) {
        arr[nextYear].weight = arr[year].weight + way.second;
        arr[nextYear].way = arr[year].way;
        arr[nextYear].way.push_back(way.first);

        if (nextYear != b) queue.push(nextYear);
      }
    }
  }

  if (arr[b].weight == std::numeric_limits<int>::max()) {
    std::cout << "-1\n";
    return 0;
  }


  std::cout << arr[b].weight << '\n';
  std::cout << arr[b].way.size() << '\n';

  for (int w : arr[b].way) {
    if (0 < w) std::cout << '+';
    std::cout << w << '\n';
  }

  return 0;
}
