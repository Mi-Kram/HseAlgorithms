#include <iostream>
#include <functional>

#include "hashTable.h"

int main() {
  HashTable<int, int> ht;
  ht.insert(5, 55);
  std::cout << ht.size() << '\n';
  std::cout << ht.capacity() << '\n';
  std::cout << *ht.find(5) << '\n';
  std::cout << ht[std::hash<int>{}(5) % ht.capacity()].value << '\n';
  std::cout << ht.at(std::hash<int>{}(5) % ht.capacity()).value << '\n';


  return 0;
}
