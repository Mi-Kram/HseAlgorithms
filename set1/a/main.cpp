#include <iostream>
#include <vector>

#include "list.h"

void print(Node* node);

int main() {
  List lst;
  lst.push_front(1);   // 1
  lst.push_back(2);    // 1 2
  lst.push_front(11);  // 11 1 2
  lst.push_back(22);   // 11 1 2 22

  lst.insert(lst.head, 5);               // 11 5 1 2 22
  lst.insert(lst.head->next->next, 55);  // 11 5 1 55 2 22
  lst.insert(lst.tail, 555);             // 11 5 1 55 2 22 555

  print(lst.head);
  lst.reverse();
  print(lst.head);

  return 0;
}

void print(Node* node) {
  while (node) {
    std::cout << node->value << ' ';
    node = node->next;
  }
  std::cout << '\n';
}
