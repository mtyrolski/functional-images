#include "bmp.hpp"
#include "images.hpp"
#include <cstdint>
#include <fstream>
#include <string>

namespace {
#pragma pack(push)
#pragma pack(2)
class BMP_header {
public:
  BMP_header(const uint32_t width, const uint32_t height)
      : bfSize(sizeof(BMP_header) + data_size(width, height) +
               sizeof(Padding) * height),
        biWidth(width), biHeight(height) {}

  const char *operator&() const { return reinterpret_cast<const char *>(this); }

private:
  using Padding = uint16_t;

  static uint32_t data_size(const uint32_t width, const uint32_t height) {
    return width * height * 3;
  }

  const uint16_t bfType = 19778; // 19778 == 0x4d42 == 'B''M'
  const uint32_t bfSize;
  const uint16_t bfReserved1 = 0;
  const uint16_t bfReserved2 = 0;
  const uint32_t bfOffBits = 54;
  const uint32_t biSize = 40;
  const uint32_t biWidth;
  const uint32_t biHeight;
  const uint16_t biPlanes = 1;
  const uint16_t biBitCount = 24;
  const uint32_t biCompression = 0;
  const uint32_t biSizeImage = 0;
  const uint32_t biXPelsPerMeter = 0;
  const uint32_t biYPelsPerMeter = 0;
  const uint32_t biClrUsed = 0;
  const uint32_t biClrImportant = 0;
};
#pragma pack(pop)
} // namespace

void create_BMP(const std::string &filename, const uint32_t width,
                const uint32_t height, const Image &f) {
  const BMP_header header(width, height);
  std::ofstream file(filename.c_str(),
                     std::ios::out | std::ios::trunc | std::ios::binary);
  file.write(&header, sizeof(header));
  for (uint32_t j = 0; j < height; j++) {
    for (uint32_t i = 0; i < width; i++) {
      Point p(static_cast<Coordinate>(i) - (width / 2.),
              static_cast<Coordinate>(j) - (height / 2.));
      const Color c(f(p));
      file.write(reinterpret_cast<const char *>(c.data), 3);
    }
  }
}