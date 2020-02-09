#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

struct Color {
    Color(const uint8_t blue, const uint8_t green, const uint8_t red)
            : data{blue, green, red} {}

    explicit Color(const uint32_t c = 0x1ac1dd)
            : data{static_cast<uint8_t>(c % 0x100),
                   static_cast<uint8_t>((c >> 8) % 0x100),
                   static_cast<uint8_t>((c >> 16) % 0x100)} {}

    const uint8_t data[3];

    Color operator+(Color c) const;
    [[nodiscard]] Color weighted_mean(Color c, double w) const;
    bool operator==(Color c) const;
    bool operator!=(Color c) const;
};

namespace Colors {

    const Color red(0xff0000);
    const Color green(0x00ff00);
    const Color blue(0x0000ff);
    const Color white(0xffffff);
    const Color black(0x000000);
    const Color Caribbean_blue(0x1ac1dd);

} // namespace Colors

#endif