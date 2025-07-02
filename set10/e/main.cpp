#include <algorithm>
#include <iostream>
#include <vector>

struct Interval {
  double b, e, w;
};

bool cmp(const Interval& a, const Interval& b) {
  return a.e < b.e;
}

int main() {
  int n;
  std::cin >> n;

  std::vector<Interval> intervals(n);
  for (int i = 0; i < n; ++i) std::cin >> intervals[i].b >> intervals[i].e >> intervals[i].w;

  std::sort(intervals.begin(), intervals.end(), cmp);

  std::vector<double> ends(n);
  for (int i = 0; i < n; ++i) ends[i] = intervals[i].e;

  std::vector<double> dp(n + 1, 0.0);

  for (int i = 1; i <= n; ++i) {
    int pos = std::upper_bound(ends.begin(), ends.end(), intervals[i - 1].b) - ends.begin();
    --pos;
    if (pos >= 0) dp[i] = std::max(dp[i - 1], dp[pos + 1] + intervals[i - 1].w);
    else dp[i] = std::max(dp[i - 1], intervals[i - 1].w);
  }

  std::cout << dp[n] << '\n';
  return 0;
}
