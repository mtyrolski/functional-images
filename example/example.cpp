#include "../src/bmp.hpp"
#include "../src/color.hpp"
#include "../src/coordinate.hpp"
#include "../src/functional.hpp"
#include "../src/images.hpp"
#include <cassert>
#include <cmath>
#include <cstdint>

int main() {
  const uint32_t width = 400;
  const uint32_t height = 300;
  const Region rc = circle(Point(50., 100.), 10., true, false);
  const Image vs = vertical_stripe(100, Colors::Caribbean_blue, Colors::blue);
  const Blend cb = constant<Fraction>(.42);

  create_BMP("init.bmp", width, height, vs);
  create_BMP("init2.bmp", width, height, vs);
  create_BMP("constant.bmp", width, height, constant(Colors::Caribbean_blue));

  create_BMP("rotate.bmp", width, height, rotate(vs, M_PI / 4.));
  create_BMP("translate.bmp", width, height, translate(vs, Vec2(100., 0.)));
  create_BMP("scale.bmp", width, height, scale(vs, 2.));
  create_BMP(
      "circle.bmp", width, height,
      circle(Point(50., 100.), 10., Colors::Caribbean_blue, Colors::blue));
  create_BMP("checker.bmp", width, height,
             checker(10., Colors::Caribbean_blue, Colors::blue));
  create_BMP("polar_checker.bmp", width, height,
             polar_checker(10., 4, Colors::Caribbean_blue, Colors::blue));
  create_BMP(
      "rings.bmp", width, height,
      rings(Point(50., 100.), 10., Colors::Caribbean_blue, Colors::blue));
  create_BMP("vertical_stripe.bmp", width, height, vs);
  create_BMP(
      "cond.bmp", width, height,
      cond(rc, constant(Colors::Caribbean_blue), constant(Colors::blue)));
  create_BMP("lerp.bmp", width, height,
             lerp(cb, constant(Colors::blue), constant(Colors::white)));
  create_BMP("dark_vs.bmp", width, height, darken(vs, cb));
  create_BMP("light_vs.bmp", width, height, lighten(vs, cb));
}