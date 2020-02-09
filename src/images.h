#ifndef FUNCTIONAL_IMAGES_H
#define FUNCTIONAL_IMAGES_H

#include <cassert>
#include <cmath>
#include <functional>

#include "color.h"
#include "coordinate.h"
#include "functional.h"

using Fraction = double;

template <typename T> using Base_image = std::function<T(const Point)>;
using Region = Base_image<bool>;
using Image = Base_image<Color>;
using Blend = Base_image<Fraction>;

template <class T> Base_image<T> constant(const T &t) {
  using namespace std::placeholders;

  return std::bind([]([[maybe_unused]] const Point p, const T &t) { return t; },
                   _1, t);
}

template <class T>
Base_image<T> rotate(const Base_image<T> &image, double phi) {
  using namespace std::placeholders;

  auto fun = [](const Point p, const Base_image<T> &image, double phi) {
    assert(!p.is_polar);
    return image(Point(p.first * std::cos(phi) - p.second * std::sin(phi),
                       p.second * std::cos(phi) + p.first * std::sin(phi)));
  };

  return std::bind(fun, _1, image, -phi);
}

template <class T>
Base_image<T> translate(const Base_image<T> &image, const Vector &v) {
  using namespace std::placeholders;

  auto fun = [](const Point p, const Base_image<T> &image, const Vector &v) {
    assert(!p.is_polar);
    return image(Point(p.first - v.first, p.second - v.second));
  };

  return std::bind(fun, _1, image, v);
}

template <class T> Base_image<T> scale(const Base_image<T> &image, double s) {
  using namespace std::placeholders;

  auto fun = [](const Point p, const Base_image<T> &image, double s) {
    return image(Point(p.first / s, p.second / s, p.is_polar));
  };

  return std::bind(fun, _1, image, s);
}

template <class T>
Base_image<T> circle(const Point q, double r, const T &inner, const T &outer) {
  using namespace std::placeholders;

  auto fun = [](const Point p, const Point q_, double r, const T &inner,
                const T &outer) {
    return distance(p, q_) <= r ? inner : outer;
  };

  return std::bind(fun, _1, q, r, inner, outer);
}

#endif // FUNCTIONAL_IMAGES_H