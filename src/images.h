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

#endif // FUNCTIONAL_IMAGES_H