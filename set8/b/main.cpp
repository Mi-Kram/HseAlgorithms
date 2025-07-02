#include <iostream>
#include <string>

int main() {
  std::string p;
  std::cin >> p;

  int* arr = new int[p.length()];
  arr[0] = 0;

  for (int i = 1; i < p.length(); ++i) {
    int j = arr[i - 1];
    while (j > 0 && p[i] != p[j]) j = arr[j - 1];
    if (p[i] == p[j]) ++j;
    arr[i] = j;
  }

  int period = p.length() - arr[p.length() - 1];
  std::cout << period;

  delete[] arr;
  return 0;
}
