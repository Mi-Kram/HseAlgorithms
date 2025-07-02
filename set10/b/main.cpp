#include <iostream>
#include <vector>

int main() {
  int n, l, r;
  std::cin >> n >> l >> r;
  --l, --r;

  std::vector<int> arr(n);
  
  int i = (l + r) / 2;
  int j = i + 1;
  int cur = n;

  while (cur) {
    if (i < 0) break;
    arr[i--] = cur--;

    if (!cur || n <= j) break;
    arr[j++] = cur--;
  }
  
  while (0 <= i) arr[i--] = cur--;
  while (j < n) arr[j++] = cur--;
  
  for (int item : arr) std::cout << item << ' ';

  return 0;
}
