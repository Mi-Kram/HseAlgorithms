#include <fstream>
#include <iostream>

#include "figure.h"
#include "UniformRandomDouble.h"

void calcSquare(std::ostream& os, const Circle& c1, const Circle& c2, const Circle& c3);

int main() {
  Circle c1{1, 1, 1};
  Circle c2{1.5, 2, std::sqrt(5) / 2};
  Circle c3{2, 1.5, std::sqrt(5) / 2};

  try {
    std::ofstream os("../a/data.txt");
    if (!os.is_open()) {
      std::cout << "Couldn't open file.";
      return 0;
    }
    
    calcSquare(os, c1, c2, c3);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}

void calcSquare(std::ostream& os, const Circle& c1, const Circle& c2, const Circle& c3) {
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
  for (size_t i = 0; i < 100'000; ++i) {
    if (i != 0 && (i - 101) % 500 == 0) {
      os << i - 1 << ' ' << ((double)in / (i - 1) * (x2 - x1) * (y1 - y2)) << '\n';
    }

    rand_point.x = x_rand();
    rand_point.y = y_rand();

    if (c1.distance(rand_point) > c1.r) continue;
    if (c2.distance(rand_point) > c2.r) continue;
    if (c3.distance(rand_point) > c3.r) continue;
    ++in;
  }
}
