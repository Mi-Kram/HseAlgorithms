#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <functional>
#include <cstdint>
#include <vector>

template <class KeyType, class ValueType>
struct Node {
  KeyType key;
  ValueType value;
  Node* next;

  Node(KeyType key, ValueType value) : key(key), value(value), next(nullptr) {
  }
};

template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
 public:
  HashTable() : HashTable(100, 0.5, Func()) {
  }

  HashTable(Func hasher) : HashTable(100, 0.5, hasher) {
  }

  HashTable(size_t capacity, double loadFactor, Func hasher = Func())
    : capacity_(capacity)
    , size_(0)
    , loadFactor_((loadFactor > 0 && loadFactor <= 1) ? loadFactor : 0.5)
    , hasher_(hasher)
    , table_(capacity, nullptr) {
  }

  ~HashTable() {
    for (size_t i = 0; i < capacity_; ++i) {
      Node<KeyType, ValueType>* current = table_[i];
      while (current) {
        Node<KeyType, ValueType>* toDelete = current;
        current = current->next;
        delete toDelete;
      }
    }
  }

  void insert(KeyType key, ValueType value) {
    size_t idx = hasher_(key) % capacity_;
    Node<KeyType, ValueType>* current = table_[idx];

    while (current) {
      if (current->key == key) {
        current->value = value;
        return;
      }
      current = current->next;
    }

    Node<KeyType, ValueType>* newNode = new Node<KeyType, ValueType>(key, value);
    newNode->next = table_[idx];
    table_[idx] = newNode;
    ++size_;

    if (!isLoadFactor()) rehash();
  }

  ValueType* find(KeyType key) {
    size_t idx = hasher_(key) % capacity_;
    Node<KeyType, ValueType>* current = table_[idx];

    while (current) {
      if (current->key == key) {
        return &current->value;
      }
      current = current->next;
    }
    return nullptr;
  }

  void erase(KeyType key) {
    size_t idx = hasher_(key) % capacity_;
    Node<KeyType, ValueType>* current = table_[idx], *prev = nullptr;

    while (current) {
      if (current->key == key) {
        if (prev) prev->next = current->next;
        else table_[idx] = current->next;

        delete current;
        --size_;
        return;
      }

      prev = current;
      current = current->next;
    }
  }

  Node<KeyType, ValueType>& operator[](uint64_t idx) {
    if (idx >= capacity_) {
      throw std::out_of_range("");
    }
    if (!table_[idx]) {
      throw std::runtime_error("");
    }
    return *table_[idx];
  }

  Node<KeyType, ValueType> at(uint64_t idx) {
    return (*this)[idx];
  }

  size_t size() const {
    return size_;
  }

  size_t capacity() const {
    return capacity_;
  }

 private:
  size_t capacity_;
  size_t size_;
  double loadFactor_;
  Func hasher_;
  std::vector<Node<KeyType, ValueType>*> table_;

  bool isLoadFactor() {
    return static_cast<double>(size_) / capacity_ <= loadFactor_;
  }

  void rehash() {
    size_t newCapacity = capacity_ * 2;
    std::vector<Node<KeyType, ValueType>*> newTable(newCapacity, nullptr);

    for (size_t i = 0; i < capacity_; ++i) {
      Node<KeyType, ValueType>* current = table_[i];
      while (current) {
        Node<KeyType, ValueType>* next = current->next;
        size_t newIndex = hasher_(current->key) % newCapacity;

        current->next = newTable[newIndex];
        newTable[newIndex] = current;

        current = next;
      }
    }
    table_ = std::move(newTable);
    capacity_ = newCapacity;
  }
};

#endif
