#include <algorithm>
#include <iostream>
#include <vector>

struct segment {
  int a, b;
};

bool cmp(const segment& a, const segment& b) {
  if (a.a < b.a) return true;
  if (b.a < a.a) return false;
  return a.b < b.b;
}

int main() {
  int n;
  std::cin >> n;

  std::vector<segment> arr(n);
  std::vector<int> res;
  res.reserve(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i].a >> arr[i].b;
  }

  std::sort(arr.begin(), arr.end(), cmp);

  int r = arr[0].b;
  for (int i = 1; i < n; ++i) {
    if (r < arr[i].a) {
      res.push_back(r);
      r = arr[i].b;
      continue;
    }

    if (arr[i].b < r) r = arr[i].b;
  }
  
  res.push_back(r);
  std::cout << res.size() << '\n';
  for (int dot : res) std::cout << dot << ' ';

  return 0;
}
