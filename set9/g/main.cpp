#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  int k;
  std::cin >> k;
  std::vector<int> codes(k);
  for (int i = 0; i < k; ++i) {
    std::cin >> codes[i];
  }

  std::vector<std::string> dict(10001);
  for (int i = 0; i < 128; ++i) {
    dict[i] = std::string(1, char(i));
  }

  int next_code = 128;
  std::string w = dict[codes[0]];
  std::string result = w;

  for (int i = 1; i < k; ++i) {
    int curr_code = codes[i];
    std::string entry;

    if (curr_code < next_code && !dict[curr_code].empty()) {
      entry = dict[curr_code];
    } else if (curr_code == next_code) {
      entry = w + w[0];
    } else {
      std::cerr << "Ошибка: недопустимый код " << curr_code << std::endl;
      return 1;
    }

    result += entry;
    dict[next_code++] = w + entry[0];
    w = entry;
  }

  std::cout << result << std::endl;
  return 0;
}
