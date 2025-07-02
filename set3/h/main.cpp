#include <bitset>
#include <iostream>
#include <random>
#include <vector>

const int MAX_N = 4000;
using matrix_row = std::bitset<MAX_N>;
using matrix = std::vector<matrix_row>;

matrix readMatrix(int n);
bool verifyProduct(const matrix& a, const matrix& b, const matrix& c, int n, int trials = 5);

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

matrix readMatrix(int n) {
  matrix matrix(n);
  std::string hexRow;
  int pos, value;

  for (int i = 0; i < n; ++i) {
    std::cin >> hexRow;
    pos = 0;
    for (char c : hexRow) {
      value = (isdigit(c) ? c - '0' : c - 'A' + 10);
      for (int j = 3; j >= 0; --j)
        if (pos < n) matrix[i][pos++] = (value >> j) & 1;
    }
  }

  return matrix;
}

bool verifyProduct(const matrix& a, const matrix& b, const matrix& c, int n, int trials) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, 1);

  for (int t = 0; t < trials; ++t) {
    matrix_row x;
    for (int i = 0; i < n; ++i) x[i] = dist(gen);

    matrix_row ax, bx, abx;
    for (int i = 0; i < n; ++i)
      if (x[i]) ax ^= a[i];

    for (int j = 0; j < n; ++j)
      if (ax[j]) abx ^= b[j];

    for (int i = 0; i < n; ++i)
      if (x[i]) bx ^= c[i];

    if (abx != bx) return false;
  }

  return true;
}

// #include <iostream>
// #include <sstream>

// class matrix {
//  public:
//   matrix();
//   explicit matrix(size_t n);
//   matrix(size_t n, const std::string& s);
//   matrix(const matrix& m);
//   matrix(matrix&& m);
//   ~matrix();

//   matrix& operator=(const matrix& m);
//   matrix& operator=(matrix&& m);

//   bool operator==(const matrix& m) const;
//   bool operator!=(const matrix& m) const;
//   matrix operator*(const matrix& m) const;

//   bool at(size_t row, size_t col) const;
//   size_t size() const;

//   std::string toString() const;

//  private:
//   void parse(size_t n, const std::string& s);
//   void convert(size_t row, size_t col, char digit);
//   char convert(size_t row, size_t col) const;

//   static bool** multiply(bool **const a, bool **const b, size_t size);
//   static bool** extract(bool** matrix, size_t row, size_t col, size_t m);
//   static void freeMatrix(bool** m, size_t size);

//   size_t n;
//   size_t real_n;
//   bool** arr;
// };

// void print(const matrix& m) {
//   for (size_t i = 0; i < m.size(); i++) {
//     for (size_t j = 0; j < m.size(); j++) {
//       std::cout << (m.at(i, j) ? '1' : '0') << ' ';
//     }
//     std::cout << '\n';
//   }
// }

// int main() {
//   std::ios::sync_with_stdio(false);
//   std::cin.tie(nullptr);

//   size_t n;
//   std::string line;
//   std::cin >> n;
//   std::cin.ignore(16, '\n');

//   std::getline(std::cin, line);
//   matrix a(n, line);

//   std::getline(std::cin, line);
//   matrix b(n, line);

//   std::getline(std::cin, line);
//   matrix c(n, line);

//   matrix ab = a * b;
//   std::cout << (ab == c ? "YES" : "NO") << '\n';

//   return 0;
// }

// matrix::matrix() : n(0), real_n(0), arr(nullptr) {
// }

// matrix::matrix(size_t n) : n(n), real_n(0), arr(nullptr) {
//   if (!n) return;

//   real_n = 1;
//   while (real_n < n) real_n <<= 1;

//   arr = new bool*[real_n];
//   for (size_t i = 0; i < n; i++)
//     arr[i] = new bool[real_n]{};
// }

// matrix::matrix(size_t n, const std::string& s) : n(0), real_n(0), arr(nullptr) {
//   parse(n, s);
// }

// matrix::matrix(const matrix& m) : n(m.n), real_n(m.real_n), arr(nullptr) {
//   if (!n) return;
//   arr = new bool*[real_n];
//   for (size_t i = 0; i < real_n; i++) {
//     arr[i] = new bool[real_n];
//     for (size_t j = 0; j < real_n; j++)
//       arr[i][j] = m.arr[i][j];
//   }
// }

// matrix::matrix(matrix&& m) : n(m.n), real_n(m.real_n), arr(m.arr) {
//   m.arr = nullptr;
// }

// matrix::~matrix() {
//   freeMatrix(arr, real_n);
// }

// matrix& matrix::operator=(const matrix& m) {
//   matrix tmp(m);
//   *this = std::move(tmp);
//   return *this;
// }

// matrix& matrix::operator=(matrix&& m) {
//   if (this == &m) return *this;

//   if (arr) {
//     for (size_t i = 0; i < real_n; i++)
//       delete[] arr[i];
//   }
//   delete[] arr;

//   n = m.n;
//   real_n = m.real_n;
//   arr = m.arr;
//   m.arr = nullptr;
//   return *this;
// }

// bool matrix::operator==(const matrix& m) const {
//   if (n != m.n) return false;

//   for (size_t i = 0; i < n; i++)
//     for (size_t j = 0; j < n; j++)
//       if (arr[i][j] != m.arr[i][j])
//         return false;

//   return true;
// }

// bool matrix::operator!=(const matrix& m) const {
//   return !(*this == m);
// }

// matrix matrix::operator*(const matrix& m) const {
//   if (n != m.n) return matrix(0);

//   matrix res;
//   res.n = n;
//   res.real_n = real_n;
//   res.arr = multiply(arr, m.arr, real_n);
//   return res;
// }

// bool** matrix::multiply(bool **const a, bool **const b, size_t size) {
//   bool** res = new bool*[size];
//   for (size_t i = 0; i < size; i++)
//     res[i] = new bool[size]{};

//   if (size <= 64) {
//     for (size_t i = 0; i < size; i++)
//       for (size_t j = 0; j < size; j++)
//         for (size_t k = 0; k < size; k++)
//           res[i][j] ^= a[i][k] & b[k][j];
//     return res;
//   }

//   // Karazuba algorithm.
//   size_t half = size / 2;
//   bool **a11 = extract(a, 0, 0, half),     **a12 = extract(a, 0, half, half);
//   bool **a21 = extract(a, half, 0, half),  **a22 = extract(a, half, half, half);
//   bool **b11 = extract(b, 0, 0, half),     **b12 = extract(b, 0, half, half);
//   bool **b21 = extract(b, half, 0, half),  **b22 = extract(b, half, half, half);

//   bool** p1 = multiply(a11, b11, half);
//   bool** p2 = multiply(a12, b21, half);
//   bool** p3 = multiply(a11, b12, half);
//   bool** p4 = multiply(a12, b22, half);
//   bool** p5 = multiply(a21, b11, half);
//   bool** p6 = multiply(a22, b21, half);
//   bool** p7 = multiply(a21, b12, half);
//   bool** p8 = multiply(a22, b22, half);

//   for (size_t i = 0; i < half; i++) {
//     for (size_t j = 0; j < half; j++) {
//       res[i][j]           = p1[i][j] ^ p2[i][j];
//       res[i][half+j]      = p3[i][j] ^ p4[i][j];
//       res[half+i][j]      = p5[i][j] ^ p6[i][j];
//       res[half+i][half+j] = p7[i][j] ^ p8[i][j];
//     }
//   }

//   delete[] a11; delete[] a12; delete[] a21; delete[] a22;
//   delete[] b11; delete[] b12; delete[] b21; delete[] b22;
//   freeMatrix(p1,  half); freeMatrix(p2,  half);
//   freeMatrix(p3,  half); freeMatrix(p4,  half);
//   freeMatrix(p5,  half); freeMatrix(p6,  half);
//   freeMatrix(p7,  half); freeMatrix(p8,  half);

//   return res;
// }

// bool** matrix::extract(bool** matrix, size_t row, size_t col, size_t m) {
//   bool** res = new bool*[m];
//   for (size_t i = 0; i < m; i++) {
//     res[i] = matrix[row+i] + col;
//   }
//   return res;
// }

// void matrix::freeMatrix(bool** m, size_t size) {
//   if (!m) return;
//   for (size_t i = 0; i < size; i++) delete[] m[i];
//   delete[] m;
// }

// bool matrix::at(size_t row, size_t col) const {
//   return arr[row][col];
// }

// size_t matrix::size() const {
//   return n;
// }

// std::string matrix::toString() const {
//   std::ostringstream oss;

//   for (size_t j = 0; j < n; j += 4)
//     oss << convert(0, j);

//   for (size_t i = 1; i < n; i++) {
//     oss << ' ';
//     for (size_t j = 0; j < n; j += 4)
//       oss << convert(i, j);
//   }

//   return oss.str();
// }

// void matrix::parse(size_t n, const std::string& s) {
//   if (s.empty()) {
//     *this = matrix(0);
//     return;
//   }

//   if (arr) {
//     for (size_t i = 0; i < real_n; i++) delete[] arr[i];
//     delete[] arr;
//   }

//   this->n = n;
//   real_n = 1;
//   while (real_n < n) real_n <<= 1;

//   arr = new bool*[real_n];

//   size_t k = n / 4 + (n % 4 != 0) + 1;

//   for (size_t i = 0; i < n; i++) {
//     arr[i] = new bool[real_n]{};
//     for (size_t j = n / 4 + (n % 4 != 0); j; --j)
//       convert(i, 4 * j - 1, s[k * i + j - 1]);
//   }

//   for (size_t i = n; i < real_n; i++)
//     arr[i] = new bool[real_n]{};
// }

// void matrix::convert(size_t row, size_t col, char digit) {
//   int num = ('0' <= digit && digit <= '9') ? (digit - '0') : (digit - 'A' + 10);
//   for (int j = 0; j < 4; j++) {
//     arr[row][col-j] = (col - j < n) ? (num & 1) : 0;
//     num >>= 1;
//   }
// }

// char matrix::convert(size_t row, size_t col) const {
//   int num = 0;
//   for (int i = 0; i < 3; i++) {
//     if (col + i < n && arr[row][col+i]) num |= 1;
//     num <<= 1;
//   }
//   if (col + 3 < n && arr[row][col+3]) num |= 1;

//   return (num < 10) ? (num + '0') : (num - 10 + 'A');
// }
