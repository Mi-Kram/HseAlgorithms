#include <iostream>

struct Interval {
  int left;
  int right;

  size_t length() const;
  Interval overlap(const Interval& other) const;
};

int compare(const Interval& a, const Interval& b);

void sort(Interval* arr, size_t n);
void sort(Interval* arr, size_t left, size_t right);

int main() {
  size_t n;
  std::cin >> n;

  if (n <= 1) {
    std::cout << "0\n";
    return 0;
  }

  Interval* arr = new Interval[n];
  for (size_t i = 0; i < n; i++) {
    std::cin >> arr[i].left >> arr[i].right;
  }

  sort(arr, n);

  Interval prev = arr[0];
  Interval result, tmp;
  size_t distance = 0;

  for (size_t i = 1; i < n; i++) {
    tmp = arr[i].overlap(prev);
    if ((distance == tmp.length() &&
         (tmp.left < result.left || 
         (tmp.left == result.left && tmp.right < result.right))) ||
        distance < tmp.length()) {
      result = tmp;
      distance = result.length();
    }
    if (prev.right < arr[i].right) {
      prev = arr[i];
    }
  }

  std::cout << distance << '\n';
  if (distance) {
    std::cout << result.left << ' ' << result.right << '\n';
  }

  delete[] arr;
  return 0;
}

size_t Interval::length() const {
  return right - left + 1;
};

Interval Interval::overlap(const Interval& other) const {
  int mn = std::max(left, other.left);
  int mx = std::min(right, other.right);
  if (mx < mn) return Interval{1, 0};
  return Interval{mn, mx};
}

int compare(const Interval& a, const Interval& b) {
  if (a.left < b.left) return -1;
  if (b.left < a.left) return 1;
  if (a.right < b.right) return -1;
  if (b.right < a.right) return 1;
  return 0;
}

void sort(Interval* arr, size_t n) {
  sort(arr, 0, n - 1);
}

void sort(Interval* arr, size_t left, size_t right) {
  if (left >= right) return;

  Interval pivot = arr[left + (right - left) / 2];
  int leftI = left - 1;
  int rightI = right + 1;

  while (true) {
    while (compare(arr[++leftI], pivot) == -1) ;
    while (compare(arr[--rightI], pivot) == 1) ;
    if (leftI >= rightI) break;
    std::swap(arr[leftI], arr[rightI]);
  }

  sort(arr, left, rightI);
  sort(arr, rightI + 1, right);
}
