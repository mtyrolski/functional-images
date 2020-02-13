#include "../src/images.hpp"
#include "test.hpp"
#include <cassert>

int
main()
{
  const double d = 42.;
  const double dc = 20;
  const double r = d / 2.;
  const double lo = 0.;
  const double hi = 0.42;
  const Point o(0., 0.);
  const Point q(0.42, 0.42);
  const Vector v(1., 0.);

  // rotate
  assert(functions_equality(
    rotate<double>(vertical_stripe<double>(dc, lo, hi), M_PI / 2.),
    [=](const Point p) { return std::abs(p.second) <= dc / 2. ? lo : hi; }));

  // translate
  assert(functions_equality(
    translate<double>(vertical_stripe<double>(dc, lo, hi), v),
    [=](const Point p) {
      return std::abs(p.first - v.first) <= dc / 2. ? lo : hi;
    }));

  // scale
  assert(functions_equality(
    scale<double>(circle<double>(o, r, lo, hi), 2.),
    [=](const Point p) { return distance(p, o) <= 2 * r ? lo : hi; }));
}
