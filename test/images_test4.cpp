#include "../src/images.hpp"
#include "test.hpp"
#include <cassert>

int
main()
{
  const double dc = 20;
  const double lo = 0.;
  const double hi = 0.42;
  const Point o(0., 0.);
  const Point q(0.42, 0.42);

  // cond
  assert(functions_equality(
    cond(vertical_stripe<bool>(dc, true, false),
         constant(Colors::Caribbean_blue),
         constant(Colors::blue)),
    vertical_stripe<Color>(dc, Colors::Caribbean_blue, Colors::blue)));

  // lerp
  assert(
    functions_equality(lerp(vertical_stripe<Fraction>(dc, lo, hi),
                            constant(Colors::Caribbean_blue),
                            constant(Colors::blue)),
                       lift(
                         [](const double w, const Color c1, const Color c2) {
                           return c1.weighted_mean(c2, w);
                         },
                         vertical_stripe<Fraction>(dc, lo, hi),
                         constant(Colors::Caribbean_blue),
                         constant(Colors::blue))));

  // darken
  assert(functions_equality(darken(constant(Colors::Caribbean_blue),
                                   vertical_stripe<Fraction>(dc, lo, hi)),
                            lerp(vertical_stripe<Fraction>(dc, lo, hi),
                                 constant(Colors::Caribbean_blue),
                                 constant(Colors::black))));

  // lighten
  assert(functions_equality(lighten(constant(Colors::Caribbean_blue),
                                    vertical_stripe<Fraction>(dc, lo, hi)),
                            lerp(vertical_stripe<Fraction>(dc, lo, hi),
                                 constant(Colors::Caribbean_blue),
                                 constant(Colors::white))));
}
