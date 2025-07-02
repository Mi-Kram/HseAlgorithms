#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

struct Story {
  int64_t c, w;
  double spec;

  double specific() {
    return (double)c / w;
  }
};

bool compare(const Story& a, const Story& b) {
  return b.spec < a.spec;
}

int main() {
  int n;
  int64_t w;
  std::cin >> n >> w;

  std::vector<Story> stories(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> stories[i].c >> stories[i].w;
    stories[i].spec = stories[i].specific();
  }

  std::sort(stories.begin(), stories.end(), compare);

  double total_discussion_days = 0;
  for (int i = 0; i < n && 0 < w; ++i) {
    if (stories[i].w <= w) {
      total_discussion_days += stories[i].c;
      w -= stories[i].w;
    } else {
      total_discussion_days += stories[i].spec * w;
      w = 0;
    }
  }

  std::cout << std::fixed << std::setprecision(3) << total_discussion_days << '\n';
  return 0;
}
