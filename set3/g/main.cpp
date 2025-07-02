#include <cstdint>
#include <iostream>

struct Rational {
  int64_t num, den;
  Rational();
  Rational(int64_t num);
  Rational(int64_t num, int64_t den);

  double value() const;
  bool operator==(const Rational& r) const;
  bool operator!=(const Rational& r) const;
  bool operator<(const Rational& r) const;
  bool operator<=(const Rational& r) const;
  bool operator>(const Rational& r) const;
  bool operator>=(const Rational& r) const;
};

std::ostream& operator<<(std::ostream& os, const Rational& r);
std::istream& operator>>(std::istream& is, Rational& r);

void mergeSort(Rational* arr, int left, int right);
void merge(Rational* arr, int left, int mid, int right);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  Rational* arr = new Rational[n];
  for (int i = 0; i < n; i++) std::cin >> arr[i];
  
  mergeSort(arr, 0, n - 1);
  for (int i = 0; i < n; i++) std::cout << arr[i] << ' ';

  delete[] arr;
  return 0;
}


Rational::Rational() : num(0), den(1) {
}
Rational::Rational(int64_t num) : num(num), den(1) {
}
Rational::Rational(int64_t num, int64_t den) : num(num), den(den) {
}

double Rational::value() const {
  return static_cast<double>(num) / den;
}

bool Rational::operator==(const Rational& r) const {
  return value() == r.value();
}

bool Rational::operator!=(const Rational& r) const {
  return value() != r.value();
}

bool Rational::operator<(const Rational& r) const {
  return value() < r.value();
}

bool Rational::operator<=(const Rational& r) const {
  return value() <= r.value();
}

bool Rational::operator>(const Rational& r) const {
  return value() > r.value();
}

bool Rational::operator>=(const Rational& r) const {
  return value() >= r.value();
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
  return os << r.num << '/' << r.den;
}

std::istream& operator>>(std::istream& is, Rational& r) {
  is >> r.num;
  is.ignore(1);
  is >> r.den;
  return is;
}

void mergeSort(Rational* arr, int left, int right) {
  if (left >= right) return;

  int mid = left + (right - left) / 2;
  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);
  merge(arr, left, mid, right);
}

void merge(Rational* arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  Rational* L = new Rational[n1];
  Rational* R = new Rational[n2];

  for (int i = 0; i < n1; i++) L[i] = arr[left + i];
  for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) arr[k++] = L[i++];
    else arr[k++] = R[j++];
  }
  
  while (i < n1) arr[k++] = L[i++];
  while (j < n2) arr[k++] = R[j++];

  delete[] L;
  delete[] R;
}
