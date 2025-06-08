#include "alg.h"

#define MATRIX_IMPL
#include "matrix/src/matrix.hpp"

double gauss_func(double x, double StDev) {
    double e_part = exp(- x*x / (2*StDev*StDev));
    double factor = sqrt(2*PI*StDev*StDev);
    return e_part / factor;
}

Image gauss_blur(
    const Image& original, 
    int conv_size,
    double StDev,
    ColorRGBA missing_color
) {
    Convolution conv(conv_size);
    Point2 midpoint = {(double)(conv.matrix.a-1)/2.0, (double)(conv.matrix.b-1)/2.0};
    
    for (int y=0; y<conv.matrix.a; y++) {
        for (int x=0; x<conv.matrix.b; x++) {
            double tx = (double)x - midpoint.x;
            double ty = (double)y - midpoint.y;
            conv.matrix[y][x] = gauss_func(tx, StDev) * gauss_func(ty, StDev);
        }
    }

    return conv(original, missing_color);
}

Image algorythm(const Image& original) {
    // Image preprocess = gauss_blur(original, 13, 1);

    Image bw = to_grayscale(original);
    ColorRGBA missing_color(1,1,1);
    
    int conv_size = 9;
    int conv_size_diff = 1;

    double StBase = 0.75;
    double StDiff = 0.1;

    Image g1 = gauss_blur(bw, conv_size, StBase, missing_color);
    Image g2 = gauss_blur(bw, conv_size+conv_size_diff, StBase+StDiff, missing_color);
    
    Image modified = (g2 - g1)/2 + (g1 - g2)/2;

    ColorRGBA max_clr;
    double k;
    
    max_clr = get_color_at_int(modified, max(modified, to_gray));
    k = to_gray(max_clr);
    modified = (modified/k);

    modified = modified * 5;

    return modified;
}