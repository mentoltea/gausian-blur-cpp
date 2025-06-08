#ifndef ALG_H
#define ALG_H

#include "stbimg/image.hpp"
#include "basic.h"
#include "conv.h"

#include <utility>
#include <vector>
#include <thread>
#include <random>

double gauss_func(double x, double StDev);

Image gauss_blur(
    const Image& original, 
    int conv_size,
    double StDev,
    ColorRGBA missing_color = ColorRGBA(0,0,0)
);

Image algorythm(const Image& original);

#endif // ALG_H