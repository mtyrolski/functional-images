#ifndef BMP_H
#define BMP_H

#include "images.hpp"
#include <cstdint>

void create_BMP(const std::string &filename, uint32_t width, uint32_t height,
                const Image &f);

#endif