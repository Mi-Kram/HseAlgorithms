#ifndef STRING_GENERATOR_H
#define STRING_GENERATOR_H

#include <algorithm>
#include <random>
#include <string>
#include <sstream>

class StringGenerator {
 public:
  StringGenerator(int minLen, int maxLen, int maxArraySize, unsigned int seed = 234);

  std::string* generateRandomArray();
  std::string* generateReversedArray();
  std::string* generateAlmostSortedArray(float swapsPercentage = 0.05);

 private:
  std::string generateRandomString(int length);

  int minLength;
  int maxLength;
  int maxSize;
  std::mt19937 rng;
  std::uniform_int_distribution<int> lengthDist;
  std::uniform_int_distribution<int> charDist;

  static const std::string allowedChars;
};

std::string getAllowedCharacters() {
  std::ostringstream os;
  for (char i = 'A'; i <= 'Z'; ++i) os << i;
  for (char i = 'a'; i <= 'z'; ++i) os << i;
  for (char i = '0'; i <= '9'; ++i) os << i;
  os << "!@#%:;^&*()-";
  return os.str();
}

const std::string StringGenerator::allowedChars = getAllowedCharacters();

StringGenerator::StringGenerator(int minLen, int maxLen, int maxArraySize, unsigned int seed)
  : minLength(minLen)
  , maxLength(maxLen)
  , maxSize(maxArraySize)
  , rng(seed)
  , lengthDist(minLen, maxLen)
  , charDist(0, allowedChars.size() - 1) {
}

std::string StringGenerator::generateRandomString(int length) {
  std::ostringstream os;
  for (int i = 0; i < length; ++i) os << allowedChars[charDist(rng)];
  return os.str();
}

std::string* StringGenerator::generateRandomArray() {
  std::string* arr = new std::string[maxSize];
  for (int i = 0; i < maxSize; ++i) arr[i] = generateRandomString(lengthDist(rng));
  return arr;
}

std::string* StringGenerator::generateReversedArray() {
  std::string* arr = generateRandomArray();
  std::sort(arr, arr + maxSize, std::greater<>());
  return arr;
}

std::string* StringGenerator::generateAlmostSortedArray(float swapsPercentage) {
  std::string* arr = generateRandomArray();
  std::sort(arr, arr + maxSize, std::greater<>());
  
  std::uniform_int_distribution<int> indexDist(0, maxSize - 1);
  int swaps = swapsPercentage * maxSize;
  for (int i = 0; i < swaps; ++i) std::swap(arr[indexDist(rng)], arr[indexDist(rng)]);
  return arr;
}

#endif
