#include <cstdint>
#include <iostream>

int64_t** readMatrix(size_t n);
void freeMatrix(int64_t** arr, size_t n);

int64_t** multiply(int64_t** a, int64_t** b, size_t n);
int64_t** multiply_naiive(int64_t** a, int64_t** b, size_t n);

int64_t** extract(int64_t** matrix, size_t row, size_t col, size_t m);
void print(int64_t** matrix, size_t n);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  size_t n;
  std::cin >> n;

  int64_t** a = readMatrix(n);
  int64_t** b = readMatrix(n);
  int64_t** c = multiply(a, b, n);

  print(c, n);

  freeMatrix(a, n);
  freeMatrix(b, n);
  freeMatrix(c, n);
  return 0;
}

int64_t** readMatrix(size_t n) {
  int64_t** res = new int64_t*[n];
  for (size_t i = 0; i < n; i++) {
    res[i] = new int64_t[n];
    for (size_t j = 0; j < n; j++) {
      std::cin >> res[i][j];
    }
  }
  return res;
}

void freeMatrix(int64_t** arr, size_t n) {
  for (size_t i = 0; i < n; i++)
    delete[] arr[i];
  delete[] arr;
}

int64_t** multiply_naiive(int64_t** a, int64_t** b, size_t n) {
  int64_t** res = new int64_t*[n];
  for (size_t i = 0; i < n; i++) {
    res[i] = new int64_t[n];
    for (size_t j = 0; j < n; j++) {
      res[i][j] = 0;
      for (size_t k = 0; k < n; k++)
        res[i][j] += a[i][k] * b[k][j];
    }
  }
  return res;
}

int64_t** multiply(int64_t** a, int64_t** b, size_t n) {
  if (n == 1) {
    return new int64_t*[1]{new int64_t[1]{a[0][0] * b[0][0]}};
  }
  if (n <= 64) {
    return multiply_naiive(a, b, n);
  }

  int64_t** res = new int64_t*[n];
  for (size_t i = 0; i < n; i++)
    res[i] = new int64_t[n];

  size_t half = n / 2;
  int64_t **a11 = extract(a, 0, 0, half),     **a12 = extract(a, 0, half, half);
  int64_t **a21 = extract(a, half, 0, half),  **a22 = extract(a, half, half, half);
  int64_t **b11 = extract(b, 0, 0, half),     **b12 = extract(b, 0, half, half);
  int64_t **b21 = extract(b, half, 0, half),  **b22 = extract(b, half, half, half);

  int64_t** p1 = multiply(a11, b11, half);
  int64_t** p2 = multiply(a12, b21, half);
  int64_t** p3 = multiply(a11, b12, half);
  int64_t** p4 = multiply(a12, b22, half);
  int64_t** p5 = multiply(a21, b11, half);
  int64_t** p6 = multiply(a22, b21, half);
  int64_t** p7 = multiply(a21, b12, half);
  int64_t** p8 = multiply(a22, b22, half);

  for (size_t i = 0; i < half; i++) {
    for (size_t j = 0; j < half; j++) {
      res[i][j]           = p1[i][j] + p2[i][j];
      res[i][half+j]      = p3[i][j] + p4[i][j];
      res[half+i][j]      = p5[i][j] + p6[i][j];
      res[half+i][half+j] = p7[i][j] + p8[i][j];
    }
  }

  delete[] a11; delete[] a12; delete[] a21; delete[] a22;
  delete[] b11; delete[] b12; delete[] b21; delete[] b22;
  freeMatrix(p1,  half); freeMatrix(p2,  half);
  freeMatrix(p3,  half); freeMatrix(p4,  half);
  freeMatrix(p5,  half); freeMatrix(p6,  half);
  freeMatrix(p7,  half); freeMatrix(p8,  half);

  return res;
}

int64_t** extract(int64_t** matrix, size_t row, size_t col, size_t m) {
  int64_t** res = new int64_t*[m];
  for (size_t i = 0; i < m; i++) {
    res[i] = matrix[row+i] + col;
  }
  return res;
}

void print(int64_t** matrix, size_t n) {
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << '\n';
  }
}