#include <cstdint>
#include <iostream>

const int64_t limit = 1'000'000'007;

int main() {
  int n;
  std::cin >> n;

  if (n == 1) {
    std::cout << "2";
    return 0;
  }

  if (n == 2) {
    std::cout << "3";
    return 0;
  }
  
  int64_t prev = 2, res = 3;

  for (int i = 2; i < n; ++i) {
    res += prev;
    prev = res - prev;
    res %= limit;
  }
  
  std::cout << res;
  return 0;
}
