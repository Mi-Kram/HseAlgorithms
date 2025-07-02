#include <bitset>
#include <iostream>
#include <random>
#include <vector>

const int MAX_N = 4000;

std::vector<std::bitset<MAX_N>> readMatrix(int n) {
  std::vector<std::bitset<MAX_N>> matrix(n);
  std::string hexRow;
  int pos, value;

  for (int i = 0; i < n; ++i) {
    std::cin >> hexRow;
    pos = 0;
    for (char c : hexRow) {
      value = (isdigit(c) ? c - '0' : c - 'A' + 10);
      for (int j = 3; j >= 0; --j) {
        if (pos < n) {
          matrix[i][pos++] = (value >> j) & 1;
        }
      }
    }
  }

  return matrix;
}

bool verifyProduct(const std::vector<std::bitset<MAX_N>>& a, const std::vector<std::bitset<MAX_N>>& b, const std::vector<std::bitset<MAX_N>>& c, int n) {
  std::random_device rd{};
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, 1);

  for (int t = 0; t < 5; ++t) {
    std::bitset<MAX_N> x;
    for (int i = 0; i < n; ++i) {
      x[i] = dist(gen);
    }

    std::bitset<MAX_N> ax, bx, abx;
    for (int i = 0; i < n; ++i) {
      if (x[i]) {
        ax ^= a[i];
      }
    }

    for (int j = 0; j < n; ++j) {
      if (ax[j]) {
        abx ^= b[j];
      }
    }
      
    for (int i = 0; i < n; ++i) {
      if (x[i]) {
        bx ^= c[i];
      }
    }
      
    if (abx != bx) {
      return false;
    }
  }

  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  auto A = readMatrix(n);
  auto B = readMatrix(n);
  auto C = readMatrix(n);

  std::cout << (verifyProduct(A, B, C, n) ? "YES" : "NO");
  return 0;
}

