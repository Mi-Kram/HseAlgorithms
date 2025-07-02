#include <iostream>
#include <sstream>

std::string parse(const std::string& pattern);
std::string parse(const std::string& pattern, size_t& idx);

int main() {
  std::string s;
  std::getline(std::cin, s);

  std::cout << parse(s) << '\n';
  return 0;
}

std::string parse(const std::string& pattern) {
  size_t idx = 0;
  return parse(pattern, idx);
}

std::string parse(const std::string& pattern, size_t& idx) {
  int number = 0;
  std::ostringstream os;
  std::string s;

  while (idx < pattern.length()) {
    if (pattern[idx] == ']') {
      return os.str();
    } else if (pattern[idx] == '[') {
      s = parse(pattern, ++idx);

      for (; number; --number) {
        os << s;
      }
    } else if (pattern[idx] >= '0' && pattern[idx] <= '9') {
      number *= 10;
      number += pattern[idx] - '0';
    } else {
      os << pattern[idx];
    }

    ++idx;
  }

  return os.str();
}
