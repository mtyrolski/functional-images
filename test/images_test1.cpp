#include "../src/images.hpp"
#include <type_traits>

namespace {

template<typename T, typename... Ts>
void
check_types(const auto& f) // -fconcepts
{
  static_assert(
    std::is_same_v<T,
                   decltype(f(std::declval<Ts>()...)(std::declval<Point>()))>);
}

}

int
main()
{
  // Fraction
  static_assert(std::is_floating_point_v<Fraction>);

  // Base_image
  static_assert(
    std::is_same_v<Base_image<bool>, std::function<bool(const Point)>>);
  static_assert(
    std::is_same_v<Base_image<Color>, std::function<Color(const Point)>>);
  static_assert(
    std::is_same_v<Base_image<Fraction>, std::function<Fraction(const Point)>>);

  // Region
  static_assert(std::is_same_v<Region, Base_image<bool>>);

  // Image
  static_assert(std::is_same_v<Image, Base_image<Color>>);

  // Blend
  static_assert(std::is_same_v<Blend, Base_image<Fraction>>);

  // constant
  check_types<bool, bool>(&constant<bool>);
  check_types<Color, Color>(&constant<Color>);
  check_types<Fraction, Fraction>(&constant<Fraction>);

  // rotate
  check_types<bool, Region, double>(&rotate<bool>);
  check_types<Color, Image, double>(&rotate<Color>);
  check_types<Fraction, Blend, double>(&rotate<Fraction>);

  // translate
  check_types<bool, Region, Vector>(&translate<bool>);
  check_types<Color, Image, Vector>(&translate<Color>);
  check_types<Fraction, Blend, Vector>(&translate<Fraction>);

  // scale
  check_types<bool, Region, double>(&scale<bool>);
  check_types<Color, Image, double>(&scale<Color>);
  check_types<Fraction, Blend, double>(&scale<Fraction>);

  // circle
  check_types<bool, Point, double, bool, bool>(&circle<bool>);
  check_types<Color, Point, double, Color, Color>(&circle<Color>);
  check_types<Fraction, Point, double, Fraction, Fraction>(&circle<Fraction>);

  // checker
  check_types<bool, double, bool, bool>(&checker<bool>);
  check_types<Color, double, Color, Color>(&checker<Color>);
  check_types<Fraction, double, Fraction, Fraction>(&checker<Fraction>);

  // polar_checker
  check_types<bool, double, int, bool, bool>(&polar_checker<bool>);
  check_types<Color, double, int, Color, Color>(&polar_checker<Color>);
  check_types<Fraction, double, int, Fraction, Fraction>(
    &polar_checker<Fraction>);

  // rings
  check_types<bool, Point, double, bool, bool>(&rings<bool>);
  check_types<Color, Point, double, Color, Color>(&rings<Color>);
  check_types<Fraction, Point, double, Fraction, Fraction>(&rings<Fraction>);

  // vertical_stripe
  check_types<bool, double, bool, bool>(&vertical_stripe<bool>);
  check_types<Color, double, Color, Color>(&vertical_stripe<Color>);
  check_types<Fraction, double, Fraction, Fraction>(&vertical_stripe<Fraction>);

  // cond
  check_types<Color, Region, Image, Image>(&cond);

  // lerp
  check_types<Color, Blend, Image, Image>(&lerp);

  // darken
  check_types<Color, Image, Blend>(&darken);

  // lighten
  check_types<Color, Image, Blend>(&lighten);
}
