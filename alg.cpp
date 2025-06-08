#include "alg.h"

#define MATRIX_IMPL
#include "matrix/src/matrix.hpp"

double gauss_func(double x, double StDev) {
    double e_part = exp(- x*x / (2*StDev*StDev));
    double factor = sqrt(2*PI*StDev*StDev);
    return e_part / factor;
}

Image algorythm(const Image& original) {
    Image bw = to_grayscale(original);

    Convolution conv(9);

    Point2 midpoint = {(double)conv.matrix.a/2.0, (double)conv.matrix.b/2.0};
    double StDev = 2;
    
    for (int y=0; y<conv.matrix.a; y++) {
        for (int x=0; x<conv.matrix.b; x++) {
            double tx = (double)x - midpoint.x;
            double ty = (double)y - midpoint.y;
            conv.matrix[y][x] = gauss_func(tx, StDev) * gauss_func(ty, StDev);
        }
    }

    Image modified = conv(bw);
    
    return modified;
}