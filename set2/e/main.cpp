#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

struct Point {
  int x, y;
  Point() : x(0), y(0) { }
  Point(int x, int y) : x(x), y(y) { }
};

int64_t sqrDst(const Point& a, const Point& b);

bool xComparator(const Point& a, const Point& b);
bool yComparator(const Point& a, const Point& b);

int64_t closestPair2D(std::vector<Point>& p);
int64_t closestPair2D(std::vector<Point>& p, int left, int right);
int64_t findClosest(std::vector<Point>& p, int64_t dist);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int x, y;
  std::vector<Point> points;

  while (std::cin >> x >> y) {
    points.emplace_back(x, y);
  }

  if (points.size() <= 1) {
    std::cout << "0\n";
    return 0;
  }

  int64_t sqr = closestPair2D(points);
  std::cout << static_cast<int>(std::sqrt(sqr)) << "\n";
  return 0;
}

int64_t sqrDst(const Point& a, const Point& b) {
  int64_t x = a.x - b.x, y = a.y - b.y;
  return x * x + y * y;
}

bool xComparator(const Point& a, const Point& b) {
  return a.x < b.x;
}

bool yComparator(const Point& a, const Point& b) {
  return a.y < b.y;
}

int64_t closestPair2D(std::vector<Point>& p) {
  std::sort(p.begin(), p.end(), xComparator);
  return closestPair2D(p, 0, p.size());
}

int64_t closestPair2D(std::vector<Point>& p, int left, int right) {
  if (right - left <= 3) {
    int64_t res = std::numeric_limits<int64_t>::max();
    for (int i = left; i < right; ++i)
      for (int j = i + 1; j < right; ++j)
        res = std::min(res, sqrDst(p[i], p[j]));
    return res;
  }

  int middle = left + (right - left) / 2;
  Point pivot = p[middle];
  int64_t delta1 = closestPair2D(p, left, middle);
  int64_t delta2 = closestPair2D(p, middle, right);
  int64_t delta = std::min(delta1, delta2);

  int64_t d;
  std::vector<Point> tmp;
  for (int i = left; i < right; ++i) {
    d = p[i].x - pivot.x;
    if (d * d < delta)
      tmp.push_back(p[i]);
  }

  return std::min(delta, findClosest(tmp, delta));
}

int64_t findClosest(std::vector<Point>& p, int64_t dist) {
  std::sort(p.begin(), p.end(), yComparator);

  int64_t d;
  for (size_t i = 0; i < p.size(); ++i) {
    for (size_t j = i + 1; j < p.size(); ++j) {
      d = p[j].y - p[i].y;
      if (dist <= d * d)
        break;
      dist = std::min(dist, sqrDst(p[i], p[j]));
    }
  }
  return dist;
}
