#include "../src/images.hpp"
#include "test.hpp"
#include <cassert>

int
main()
{
  const double d = 42.;
  const double dc = 20;
  const int n = 4;
  const double r = d / 2.;
  const double lo = 0.;
  const double hi = 0.42;
  const Point o(0., 0.);
  const Point q(0.42, 0.42);

  // constant
  assert(functions_equality(
    constant<double>(hi), [=](const Point) { return hi; }));

  // circle
  assert(functions_equality(
    circle<double>(q, r, lo, hi),
    [=](const Point p) { return distance(p, q) <= r ? lo : hi; }));

  // checker
  assert(functions_equality(
    checker<double>(dc, lo, hi),
    [=](const Point p) {
      return is_even(static_cast<int>(std::floor(p.first / dc) +
                                      std::floor(p.second / dc)))
               ? lo
               : hi;
    }));

  // polar_checker
  assert(functions_equality(
    polar_checker<double>(dc, n, lo, hi),
    [=](const Point p) {
      return compose(
        to_polar,
        [=](const Point q) {
          assert(q.is_polar);
          return Point(q.first, q.second * n * dc / (2 * M_PI), true);
        },
        checker(dc, lo, hi))(p);
    }));

  // rings
  assert(functions_equality(
    rings<double>(q, dc, lo, hi),
    [=](const Point p) {
      return is_even(static_cast<int>(distance(p, q) / dc)) ? lo : hi;
    }));

  // vertical_stripe
  assert(functions_equality(
    vertical_stripe<double>(dc, lo, hi),
    [=](const Point p) { return std::abs(p.first) <= dc / 2. ? lo : hi; }));
}
