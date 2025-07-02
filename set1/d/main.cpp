#include <iostream>
#include <sstream>
#include <stack>

int main() {
  int n, wagon;
  std::cin >> n;

  std::stack<int> dead_end;

  int cnt = 0, num = 1;
  std::ostringstream os;

  for (int i = 0; i < n; i++) {
    std::cin >> wagon;
    dead_end.push(wagon);
    ++cnt;

    if (wagon != num) {
      continue;
    }

    os << "1 " << cnt << '\n';
    cnt = 0;

    while (!dead_end.empty() && dead_end.top() == num) {
      ++num;
      ++cnt;
      dead_end.pop();
    }

    os << "2 " << cnt << '\n';
    cnt = 0;
  }

  if (dead_end.empty()) {
    std::cout << os.str();
  } else {
    std::cout << "0\n";
  }

  return 0;
}
