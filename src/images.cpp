#include "images.hpp"

Image cond(const Region &region, const Image &this_way, const Image &that_way) {
  using namespace std::placeholders;

  auto fun = [](const Point p, const Region &region, const Image &this_way,
                const Image &that_way) {
    auto reg = [](const Point p, const Region &region, const Color &cthis,
                  const Color &cthat) { return region(p) ? cthis : cthat; };

    return lift(std::bind(reg, p, region, _1, _2), this_way, that_way)(p);
  };
  return std::bind(fun, _1, region, this_way, that_way);
}

Image lerp(const Blend &blend, const Image &this_way, const Image &that_way) {
  using namespace std::placeholders;

  auto fun = [](const Point p, const Blend &blend, const Image &this_way,
                const Image &that_way) {
    auto mean = [this_way, that_way](const Point p, const Color &c,
                                     const Fraction &fr) {
      return this_way(p).weighted_mean(c, fr);
    };
    return lift(std::bind(mean, p, _1, _2), that_way, blend)(p);
  };

  return std::bind(fun, _1, blend, this_way, that_way);
}

Image darken(const Image &image, const Blend &blend) {
  return lerp(blend, image, constant<Color>(Colors::black));
}

Image lighten(const Image &image, const Blend &blend) {
  return lerp(blend, image, constant<Color>(Colors::white));
}
