#include <cstdio>
#include <iostream>
#include <list>

class HeroManager {
 public:
  HeroManager() : lst(), middle(lst.end()) {
  }

  void readCommand() {
    char key;
    int id;

    std::cin >> key;
    switch (key) {
      case '+':
        std::cin >> id;
        addDemonHunter(id);
        break;
      case '*':
        std::cin >> id;
        addPillar(id);
        break;
      case '-':
        attack();
        break;
    }
  }

 private:
  void addDemonHunter(int id) {
    lst.push_back(id);

    if (lst.size() == 2) --middle;
    else if (lst.size() != 1 && lst.size() % 2) ++middle;
  }

  void addPillar(int id) {
    lst.insert(middle, id);
    if (lst.size() % 2 == 0)
      --middle;
  }

  void attack() {
    std::cout << lst.front() << '\n';
    lst.pop_front();
    if (lst.size() % 2)
      ++middle;
  }

 private:
  std::list<int> lst;
  std::list<int>::iterator middle;
};

int main() {
  std::ios::sync_with_stdio(false);  // Отключить синхронизацию между iostream и stdio.
  std::cin.tie(nullptr);             // Отключить синхронизацию между std::cin и std::cout.

  int t;
  std::cin >> t;

  HeroManager manager;
  for (; t; --t) {
    manager.readCommand();
  }

  return 0;
}
