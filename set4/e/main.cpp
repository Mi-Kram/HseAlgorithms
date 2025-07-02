#include <iostream>
#include <math.h>
#include "btree.h"

int main() {
  BTree tree(2);
  tree.insert(2);
  tree.insert(5);
  tree.insert(-1);
  tree.insert(4);
  tree.insert(-5);
  tree.insert(6);
  tree.insert(7);
  tree.insert(3);
  std::cout << "Hello, task e!";
  return 0;
}

