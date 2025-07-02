#include <iostream>

#include "splay-tree.h"

int main() {
  SplayTree tree;

  tree.insert(5);
  tree.insert(3);
  tree.insert(4);
  std::cout << tree.splay(tree.find(4)) << '\n';

  return 0;
}
