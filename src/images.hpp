#ifndef FUNCTIONAL_IMAGES_H
#define FUNCTIONAL_IMAGES_H

#include <cassert>
#include <cmath>
#include <functional>

#include "color.hpp"
#include "coordinate.hpp"
#include "functional.hpp"

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

template <class T>
Base_image<T> vertical_stripe(double d, const T &this_way, const T &that_way) {
  using namespace std::placeholders;

  const double dhalf = d / 2;
  auto fun = [](const Point p, double dhalf, const T &this_way,
                const T &that_way) {
    return std::abs(p.first) <= dhalf ? this_way : that_way;
  };

  return std::bind(fun, _1, dhalf, this_way, that_way);
}

template <class T>
Base_image<T> checker(double d, const T &this_way, const T &that_way) {
  using namespace std::placeholders;

  auto fun = [](const Point p, const T &this_way, const T &that_way) {
    return (static_cast<int64_t>(std::floor(p.first)) +
            static_cast<int64_t>(std::floor(p.second))) %
                   2
               ? that_way
               : this_way;
  };

  Base_image<T> unitchecker = std::bind(fun, _1, this_way, that_way);
  return scale(unitchecker, d);
}

template <class T>
Base_image<T> polar_checker(double d, int n, const T &this_way,
                            const T &that_way) {
  using namespace std::placeholders;
  static constexpr double mul_stripes = 2.0;

  auto fun = [](const Point p, double d, int n) {
    return Point(p.first, d * n * p.second / (mul_stripes * M_PI));
  };

  return compose(to_polar, std::bind(fun, _1, d, n),
                 checker(d, this_way, that_way));
}

template <class T>
Base_image<T> rings(const Point q, double d, const T &this_way,
                    const T &that_way) {
  using namespace std::placeholders;

  auto fun = [](const Base_image<T> &image, const Point q) {
    return translate(image, {q.first, q.second});
  };

  return std::bind(fun, _1, q)(static_cast<Base_image<T>>(
      compose(to_polar, checker(d, this_way, that_way))));
}

Image cond(const Region &region, const Image &this_way, const Image &that_way);
Image lerp(const Blend &blend, const Image &this_way, const Image &that_way);
Image darken(const Image &image, const Blend &blend);
Image lighten(const Image &image, const Blend &blend);

#endif // FUNCTIONAL_IMAGES_H