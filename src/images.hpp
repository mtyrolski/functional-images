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

/**
 * @brief makes const functional image
 * @tparam T img type
 * @param t img property
 * @return const functional image
 */
template <class T> Base_image<T> constant(const T &t) {
  using namespace std::placeholders;

  return std::bind([]([[maybe_unused]] const Point p, const T &t) { return t; },
                   _1, t);
}

/**
 * @brief rotates image with given angle
 * @tparam T img type
 * @param image
 * @param phi angle
 * @return rotated functional image
 */
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

/**
 * @brief moves image with given vector
 * @tparam T img type
 * @param image
 * @param v 2d vector
 * @return translated functional image
 */
template <class T>
Base_image<T> translate(const Base_image<T> &image, const Vec2 &v) {
  using namespace std::placeholders;

  auto fun = [](const Point p, const Base_image<T> &image, const Vec2 &v) {
    assert(!p.is_polar);
    return image(Point(p.first - v.first, p.second - v.second));
  };

  return std::bind(fun, _1, image, v);
}

/**
 * @brief scales image
 * @tparam T img type
 * @param image
 * @param s scale factor
 * @return scaled functional image
 */
template <class T> Base_image<T> scale(const Base_image<T> &image, double s) {
  using namespace std::placeholders;

  auto fun = [](const Point p, const Base_image<T> &image, double s) {
    return image(Point(p.first / s, p.second / s, p.is_polar));
  };

  return std::bind(fun, _1, image, s);
}

/**
 * @brief draws circle
 * @tparam T img type
 * @param q circle center
 * @param r radius
 * @param inner - inner functional image
 * @param outer - outer functional image
 * @return circle functional image
 */
template <class T>
Base_image<T> circle(const Point q, double r, const T &inner, const T &outer) {
  using namespace std::placeholders;

  auto fun = [](const Point p, const Point q_, double r, const T &inner,
                const T &outer) {
    return distance(p, q_) <= r ? inner : outer;
  };

  return std::bind(fun, _1, q, r, inner, outer);
}

/**
 * @brief draws vertial stripe
 * @tparam T img type
 * @param d width
 * @param this_way first background
 * @param that_way second background
 * @return stripe functional image
 */
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

/**
 * @brief draws checker
 * @tparam T img type
 * @param d width
 * @param this_way first background
 * @param that_way second background
 * @return checker functional image
 */
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

/**
 * @brief draws polar checker
 * @tparam T img type
 * @param d width
 * @param n number of stripes
 * @param this_way first background
 * @param that_way second background
 * @return polar checker functional image
 */
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

/**
 * @brief draws rings
 * @tparam T img type
 * @param q center
 * @param d width
 * @param this_way first background
 * @param that_way second background
 * @return rings functional image
 */
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

/**
 * @brief makes conditional image
 * @param region boolean functional images
 * @param this_way if region(p) then takes this_way background
 * @param that_way otherwise takes that_way background
 * @return conditional functional image
 */
Image cond(const Region &region, const Image &this_way, const Image &that_way);

/**
 * @brief makes linear interpolation with given blend
 * @param blend
 * @param this_way first background
 * @param that_way second background
 * @return
 */
Image lerp(const Blend &blend, const Image &this_way, const Image &that_way);

/**
 * @brief makes img darker
 * @param image
 * @param blend
 * @return darkened functional image
 */
Image darken(const Image &image, const Blend &blend);

/**
 * @brief makes img lighter
 * @param image
 * @param blend
 * @return lightened functional image
 */
Image lighten(const Image &image, const Blend &blend);

#endif // FUNCTIONAL_IMAGES_H