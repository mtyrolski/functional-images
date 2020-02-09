#ifndef COORDINATE_H
#define COORDINATE_H

#include <utility>

using Coordinate = double;

struct Point {
  Point(const Coordinate f, const Coordinate s, const bool p = false)
      : first(f), second(s), is_polar(p) {}

  const Coordinate first;
  const Coordinate second;
  const bool is_polar;
};

using Vec2 = std::pair<Coordinate, Coordinate>;

Point to_polar(const Point &p);
Point from_polar(const Point &p);

double distance(const Point &p, const Point &q = {0, 0});

#endif