#ifndef CONV_H
#define CONV_H

#include "basic.h"

class Convolution {
    public:
    Matrix<double> matrix;
    
    Convolution(int size);
    
    Image operator()(const Image& input, ColorRGBA missing_color = ColorRGBA(0,0,0));
};


#endif // CONV_H