#include <cstdint>
#include <iostream>
#include <vector>

const int64_t MOD = 1e9 + 179;

int k;
using Matrix = std::vector<std::vector<int64_t>>;

Matrix mul(const Matrix& A, const Matrix& B) {
  int sz = A.size();
  Matrix C(sz, std::vector<int64_t>(sz, 0));
  for (int i = 0; i < sz; ++i)
    for (int k = 0; k < sz; ++k)
      for (int j = 0; j < sz; ++j) C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
  return C;
}

Matrix pow(Matrix A, int64_t exp) {
  int sz = A.size();
  Matrix res(sz, std::vector<int64_t>(sz, 0));
  for (int i = 0; i < sz; ++i) res[i][i] = 1;
  while (exp > 0) {
    if (exp % 2) res = mul(res, A);
    A = mul(A, A);
    exp /= 2;
  }
  return res;
}

int state(int h, int dir) {
  return h * 2 + dir;
}

int main() {
  int64_t n;
  std::cin >> n >> k;

  int sz = 2 * k;
  Matrix T(sz, std::vector<int64_t>(sz, 0));

  for (int h = 0; h < k; ++h) {
    for (int nh = 0; nh < h; ++nh) T[state(nh, 1)][state(h, 0)] = 1;
    for (int nh = h + 1; nh < k; ++nh) T[state(nh, 0)][state(h, 1)] = 1;
  }

  std::vector<int64_t> start(sz, 0);
  for (int h = 0; h < k; ++h) {
    start[state(h, 0)] = 1;
    start[state(h, 1)] = 1;
  }

  if (n == 1) {
    std::cout << k << "\n";
    return 0;
  }

  Matrix T_exp = pow(T, n - 1);

  int64_t result = 0;
  for (int i = 0; i < sz; ++i)
    for (int j = 0; j < sz; ++j) result = (result + T_exp[i][j] * start[j]) % MOD;

  std::cout << result << "\n";
  return 0;
}
