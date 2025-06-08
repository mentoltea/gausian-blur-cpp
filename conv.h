#ifndef CONV_H
#define CONV_H

#include "basic.h"

class Convolution {
    public:
    Matrix<double> matrix;
    
    Convolution(int size);
    
    Image operator()(const Image& input);
};


#endif // CONV_H