#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;

  int* pi = new int[s.size()];
  pi[0] = 0;
  
  for (int i = 1; i < s.size(); ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) ++j;
    pi[i] = j;
  }

  for (size_t i = 0; i < s.size(); ++i) {
    std::cout << pi[i];
    if (i != s.size() - 1) std::cout << ' ';
  }
  std::cout << '\n';

  delete[] pi;
  return 0;
}
