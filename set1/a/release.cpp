#include <stdexcept>
#include <unordered_set>

#include "list.h"

List::List() : _size(0), head(nullptr), tail(nullptr) {
}

List::List(const List& other) : List() {
  if (other.empty()) {
    return;
  }

  Node* node = other.head;
  while (node) {
    push_back(node->value);
    node = node->next;
  }
}

List::List(std::vector<int> array) : List() {
  for (int item : array) {
    push_back(item);
  }
}

List::~List() {
  clear();
}

int List::front() {
  return _size ? head->value : 0;
}

int List::back() {
  return _size ? tail->value : 0;
}

void List::push_back(int value) {
  if (++_size == 1) {
    head = tail = new Node(value);
    return;
  }

  tail->next = new Node(tail, nullptr, value);
  tail = tail->next;
}

void List::push_front(int value) {
  if (++_size == 1) {
    head = tail = new Node(value);
    return;
  }

  head->prev = new Node(nullptr, head, value);
  head = head->prev;
}

void List::insert(Node* pos, int value) {
  if (!pos) {
    throw std::runtime_error("Incorrect position!");
  }

  // Проверка, что элемент находится в данном списке.
  Node* node = head;
  while (node != pos) {
    node = node->next;
  }

  if (!node) {
    throw std::runtime_error("Incorrect position!");
  }

  // Добавление элемента.
  ++_size;
  node = new Node(pos, pos->next, value);

  if (tail == pos) {
    tail->next = node;
    tail = node;
    return;
  }

  node->prev->next = node;
  node->next->prev = node;
}

void List::pop_front() {
  if (empty()) {
    throw std::runtime_error("Deleting in empty list");
  }

  if (--_size) {
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
  } else {
    delete head;
    head = tail = nullptr;
  }
}

void List::pop_back() {
  if (empty()) {
    throw std::runtime_error("Deleting in empty list");
  }

  if (--_size) {
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
  } else {
    delete tail;
    head = tail = nullptr;
  }
}

void List::erase(Node* pos) {
  if (!pos) {
    throw std::runtime_error("Incorrect position!");
  }

  if (pos == head) {
    pop_front();
  } else if (pos == tail) {
    pop_back();
  } else {
    --_size;
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
  }
}

void List::clear() {
  Node* tmp;
  while (tail) {
    tmp = tail;
    tail = tail->prev;
    delete tmp;
  }
  head = tail = nullptr;
  _size = 0;
}

void List::reverse() {
  if (_size < 2) {
    return;
  }

  Node* node = head;
  while (node) {
    std::swap(node->prev, node->next);
    node = node->prev;
  }

  std::swap(head, tail);
}

void List::remove_duplicates() {
  if (_size < 2) {
    return;
  }

  std::unordered_set<int> set(_size);
  Node* tmp;
  Node* node = head;

  while (node) {
    tmp = node;
    node = node->next;

    if (set.find(tmp->value) == set.end()) {
      set.insert(tmp->value);
    } else {
      erase(tmp);
    }
  }
}

void List::replace(int old_value, int new_value) {
  Node* node = head;

  while (node) {
    if (node->value == old_value) {
      node->value = new_value;
    }
    node = node->next;
  }
}

void List::merge(const List& other) {
  Node* node = other.head;

  while (node) {
    push_back(node->value);
    node = node->next;
  }
}

bool List::check_cycle() const {
  if (!head) {
    return false;
  }

  Node* slow = head;
  Node* fast = head->next;

  while (fast && fast->next) {
    if (slow == fast) {
      return true;
    }
    slow = slow->next;
    fast = fast->next->next;
  }

  return false;
}

size_t List::size() const {
  return _size;
}

bool List::empty() const {
  return !_size;
}

void List::copy(const List& other) {
  clear();

  Node* node = other.head;
  while (node) {
    push_back(node->value);
    node = node->next;
  }
}
