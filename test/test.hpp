#ifndef TEST_H
#define TEST_H

#include "../src/images.hpp"
#include <cassert>
#include <cmath>
#include <type_traits>

// Sprawdza, czy liczba całkowita jest parzysta.
template<typename T>
bool
is_even(const T t)
{
  static_assert(std::is_integral_v<T>);
  return (t % 2) == 0;
}

// Sprawdza, czy liczby są równe w sensie numerycznym, tj. z zadaną dokładnością.
template<typename T>
bool
is_equal(const T t1, const T t2, const T prec = 0)
{
  assert(prec >= 0);
  return std::fabs(t1 - t2) <= prec;
}

// Sprawdza, czy funkcje są numerycznie równe na zadanej siatce punktów.
template<typename T, typename U>
bool
functions_equality(const T& t, const U& u)
{
  // Niedopasowanie na poziomie 100 punktów na siatce rozmiaru (2 * 42 + 1)^2
  // jest akceptowalne w ramach testów automatycznych. Oznacza to poziom
  // niedopasowania punktów nie większy niż około 1,4%.
  unsigned int threshold = 100;
  
  unsigned int diffs = 0;
  const double dx = 1.;
  const double dy = 1.;
  for (int i = -42; i <= 42; ++i) {
    for (int j = -42; j <= 42; ++j) {
      const Point p(i * dx, j * dy);
      if constexpr (std::is_same_v<T, Image>) {
        if (t(p) != u(p)) {
          diffs++;
        }
      } else {
        if (!is_equal(t(p), u(p), 0.)) {
          diffs++;
        }
      }
    }
  }
  return diffs <= threshold;
}

#endif
