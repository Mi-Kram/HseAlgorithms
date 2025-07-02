#ifndef COUNTED_STRING_H
#define COUNTED_STRING_H

#include <string>



class CountedString {
 public:
  CountedString() : value(nullptr) {
  }
  CountedString(const std::string* str) : value(str) {
  }
  CountedString& operator=(const std::string* str) {
    value = str;
    return *this;
  }

  bool operator<(const CountedString& other) const;
  bool operator<=(const CountedString& other) const;
  bool operator>(const CountedString& other) const;
  bool operator>=(const CountedString& other) const;
  bool operator==(const CountedString& other) const;
  bool operator!=(const CountedString& other) const;

  size_t common_prefix(const CountedString& other, size_t offset = 0);
  int compare(const CountedString& other, size_t offset = 0);
  int char_at(size_t pos);

  static long long totalCharComparisons;

 private:
  const std::string* value;
};

long long CountedString::totalCharComparisons = 0;

bool CountedString::operator<(const CountedString& other) const {
  size_t len = std::min(value->size(), other.value->size());
  for (size_t i = 0; i < len; ++i) {
    ++totalCharComparisons;
    if ((*value)[i] < (*other.value)[i]) return true;
    if ((*value)[i] > (*other.value)[i]) return false;
  }
  ++totalCharComparisons;
  return value->size() < other.value->size();
}

bool CountedString::operator<=(const CountedString& other) const {
  return *this == other || *this < other;
}

bool CountedString::operator>(const CountedString& other) const {
  return other < *this;
}

bool CountedString::operator>=(const CountedString& other) const {
  return *this == other || other < *this;
}

bool CountedString::operator==(const CountedString& other) const {
  if (value->size() != other.value->size()) return false;
  for (size_t i = 0; i < value->size(); ++i) {
    ++totalCharComparisons;
    if ((*value)[i] != (*other.value)[i]) return false;
  }
  return true;
}

bool CountedString::operator!=(const CountedString& other) const {
  return !(*this == other);
}

int CountedString::compare(const CountedString& other, size_t offset) {
  size_t len = std::max(value->size(), other.value->size());

  for (size_t i = offset; i < len; ++i) {
    ++totalCharComparisons;
    if ((*value)[i] == (*other.value)[i]) continue;
    return (*value)[i] < (*other.value)[i] ? -1 : 1;
  }

  ++totalCharComparisons;
  if (value->size() == other.value->size()) return 0;
  return value->size() < other.value->size() ? -1 : 1;
}

size_t CountedString::common_prefix(const CountedString& other, size_t offset) {
  size_t i = offset;
  while (i < value->size() && i < other.value->size()) {
    ++totalCharComparisons;
    if ((*value)[i] != (*other.value)[i]) break;
    ++i;
  }
  return i;
}

int CountedString::char_at(size_t pos) {
  ++totalCharComparisons;
  return pos < value->size() ? (*value)[pos] : -1;
}

#endif