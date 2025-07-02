// Крамаренко
#include <iostream>
#include <random>

#include "big-int.h"

std::string multiply(std::string a, std::string b);

int main() {
  int fail = 5;
  unsigned long long a, b;
  std::string s;
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFF);

  while (fail) {
    a = distribution(generator), b = distribution(generator);
    BigInt b1(a), b2(b);
    s = multiply(std::to_string(a), std::to_string(b));

    if (b1 * b2 != BigInt(s)) {
      std::cout << a << ' ' << b << ' ' << (b1 * b2) << '\n';
      --fail;
    }
  }

  return 0;
}