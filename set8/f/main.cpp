#include <iostream>
#include <string>
#include <vector>

long long countPalindromes(const std::string& s) {
  int n = s.size();
  std::vector<int> d1(n), d2(n);
  long long total = 0;

  for (int i = 0, l = 0, r = -1; i < n; ++i) {
    int k = (i > r) ? 1 : std::min(d1[l + r - i], r - i + 1);
    while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) ++k;
    d1[i] = k--;
    total += d1[i];
    if (i + k > r) {
      l = i - k;
      r = i + k;
    }
  }

  for (int i = 0, l = 0, r = -1; i < n; ++i) {
    int k = (i > r) ? 0 : std::min(d2[l + r - i + 1], r - i + 1);
    while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;
    d2[i] = k--;
    total += d2[i];
    if (i + k > r) {
      l = i - k - 1;
      r = i + k;
    }
  }

  return total;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::getline(std::cin, s);

  std::cout << countPalindromes(s) << '\n';

  return 0;
}
