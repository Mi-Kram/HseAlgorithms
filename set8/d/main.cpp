#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string p, t;
  std::getline(std::cin, p);
  std::getline(std::cin, t);

  int m = p.length();
  int n = t.length();

  if (m == 0 || n == 0 || m > n) {
    std::cout << '0';
    return 0;
  }

  const int ALPHABET_SIZE = 256;
  int shift[ALPHABET_SIZE];

  for (int i = 0; i < ALPHABET_SIZE; ++i) shift[i] = m;
  for (int i = 0; i < m - 1; ++i) shift[static_cast<unsigned char>(p[i])] = m - i - 1;

  std::vector<int> result;
  int i = 0;

  while (i <= n - m) {
    int j = m - 1;
    while (j >= 0 && t[i + j] == p[j]) --j;
    if (j < 0) {
      result.push_back(i);
      i += shift[static_cast<unsigned char>(t[i + m - 1])];
    } else {
      i += shift[static_cast<unsigned char>(t[i + m - 1])];
    }
  }

  std::cout << result.size() << '\n';
  for (int pos : result) std::cout << pos << '\n';

  return 0;
}
