#ifndef FIGURE_H
#define FIGURE_H

#include <math.h>

struct Point {
  double x;
  double y;

  Point() : x(0), y(0) { }
  Point(double x, double y) : x(x), y(y) { }

  double distance(Point p) const {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
  }
};

struct Circle : Point {
  double r;

  Circle() : r(0) { }
  Circle(double x, double y, double r) : Point(x, y), r(r) { }
};



#endif
