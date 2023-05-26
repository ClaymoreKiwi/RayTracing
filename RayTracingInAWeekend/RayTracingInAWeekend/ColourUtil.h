#pragma once
#ifndef COLOR_H
#define COLOR_H

#include "vec3Class.h"

void write_color(colour pixel_color) {
    // Write the translated [0,255] value of each color component.
    std::cout << static_cast<int>(255.999 * pixel_color.X()) << ' '
        << static_cast<int>(255.999 * pixel_color.Y()) << ' '
        << static_cast<int>(255.999 * pixel_color.Z()) << '\n';
}

#endif