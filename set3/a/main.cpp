#include <fstream>
#include <iostream>

#include "figure.h"
#include "UniformRandomDouble.h"

double calcSquare(const Circle& c1, const Circle& c2, const Circle& c3);

const size_t SQUARE_N = 50'000;

int main() {
  Circle c1, c2, c3;
  std::cin >> c1.x >> c1.y >> c1.r;
  std::cin >> c2.x >> c2.y >> c2.r;
  std::cin >> c3.x >> c3.y >> c3.r;

  double square = calcSquare(c1, c2, c3);
  std::cout << square << '\n';

  return 0;
}

double calcSquare(const Circle& c1, const Circle& c2, const Circle& c3) {
  // Large rectangle.
  // double x1 = std::min(c1.x - c1.r, std::min(c2.x - c2.r, c3.x - c3.r));  // left x
  // double y1 = std::max(c1.y + c1.r, std::max(c2.y + c2.r, c3.y + c3.r));  // top y
  // double x2 = std::max(c1.x + c1.r, std::max(c2.x + c2.r, c3.x + c3.r));  // right x
  // double y2 = std::min(c1.y - c1.r, std::min(c2.y - c2.r, c3.y - c3.r));  // bottom y

  // Small rectangle.
  double x1 = std::max(c1.x - c1.r, std::max(c2.x - c2.r, c3.x - c3.r));  // left x
  double y1 = std::min(c1.y + c1.r, std::min(c2.y + c2.r, c3.y + c3.r));  // top y
  double x2 = std::min(c1.x + c1.r, std::max(c2.x + c2.r, c3.x + c3.r));  // right x
  double y2 = std::max(c1.y - c1.r, std::min(c2.y - c2.r, c3.y - c3.r));  // bottom y

  size_t in = 0;
  UniformRandomDouble x_rand(x1, x2), y_rand(y2, y1);
  Point rand_point;
  for (size_t i = 0; i < SQUARE_N; ++i) {
    rand_point.x = x_rand();
    rand_point.y = y_rand();

    if (c1.distance(rand_point) > c1.r) continue;
    if (c2.distance(rand_point) > c2.r) continue;
    if (c3.distance(rand_point) > c3.r) continue;
    ++in;
  }

  return (double)in / SQUARE_N * (x2 - x1) * (y1 - y2);
}
