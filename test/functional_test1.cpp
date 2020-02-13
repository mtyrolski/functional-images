#include "../src/functional.hpp"
#include "test.hpp"
#include <cassert>

int
main()
{
  const double prec = 0.;
  const double dx = 1.;
  const auto id = [](auto x) { return x; };
  const auto linear = [](auto x) { return x + 42; };
  const auto quadratic = [](auto x) { return x * x + x + 42; };
  const auto cubic = [](auto x) { return x * x * x + x * x + x + 42; };
  for (int i = 0; i < 42; ++i) {
    // compose: 0 argumentów
    assert(is_equal(compose()(i * dx), i * dx, prec));

    // compose: 1 argument
    assert(is_equal(compose(id)(i * dx), id(i * dx), prec));
    assert(is_equal(compose(linear)(i * dx), linear(i * dx), prec));
    assert(is_equal(compose(quadratic)(i * dx), quadratic(i * dx), prec));
    assert(is_equal(compose(cubic)(i * dx), cubic(i * dx), prec));

    // compose: 2 argumenty
    assert(is_equal(compose(id, linear)(i * dx), linear(id(i * dx)), prec));
    assert(is_equal(
      compose(linear, quadratic)(i * dx), quadratic(linear(i * dx)), prec));
    assert(is_equal(
      compose(quadratic, cubic)(i * dx), cubic(quadratic(i * dx)), prec));
    assert(is_equal(compose(linear, id)(i * dx), id(linear(i * dx)), prec));
    assert(is_equal(
      compose(quadratic, linear)(i * dx), linear(quadratic(i * dx)), prec));
    assert(is_equal(
      compose(cubic, quadratic)(i * dx), quadratic(cubic(i * dx)), prec));
    assert(
      is_equal(compose(linear, linear)(i * dx), linear(linear(i * dx)), prec));
    assert(is_equal(compose(quadratic, quadratic)(i * dx),
                    quadratic(quadratic(i * dx)),
                    prec));
    assert(is_equal(compose(cubic, cubic)(i * dx), cubic(cubic(i * dx)), prec));

    // compose: 3 i więcej argumentów
    assert(is_equal(compose(id, linear, quadratic)(i * dx),
                    quadratic(linear(id(i * dx))),
                    prec));
    assert(is_equal(compose(id, linear, quadratic, cubic)(i * dx),
                    cubic(quadratic(linear(id(i * dx)))),
                    prec));
    assert(is_equal(compose(id, linear, quadratic, cubic, id)(i * dx),
                    id(cubic(quadratic(linear(id(i * dx))))),
                    prec));
    assert(is_equal(compose(id, linear, quadratic, cubic, id, linear)(i * dx),
                    linear(id(cubic(quadratic(linear(id(i * dx)))))),
                    prec));
    assert(is_equal(
      compose(id, linear, quadratic, cubic, id, linear, quadratic)(i * dx),
      quadratic(linear(id(cubic(quadratic(linear(id(i * dx))))))),
      prec));
    assert(is_equal(
      compose(id, linear, quadratic, cubic, id, linear, quadratic, cubic)(i *
                                                                          dx),
      cubic(quadratic(linear(id(cubic(quadratic(linear(id(i * dx)))))))),
      prec));
    assert(is_equal(compose(id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id,
                            id)(i * dx), // złożenie 42 funkcji id
                    i * dx,
                    prec));
  }
}
