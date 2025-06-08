#include "conv.h"

#define MATRIX_IMPL
#include "matrix/src/matrix.hpp"

Convolution::Convolution(int size): matrix(size, size) {}

Image Convolution::operator()(const Image& input) {
    Image modified(input.width, input.height, input.channels);

    for (int y=0; y<input.height; y++) {
        for (int x=0; x<input.width; x++) {
            ColorRGBA final_color;

            for (int my = 0; my < this->matrix.a; my++) {
                for (int mx = 0; mx < this->matrix.b; mx++) {
                    int cur_x = x + mx - this->matrix.b/2;
                    int cur_y = y + my - this->matrix.a/2;
                    ColorRGBA cur_clr;

                    if (cur_x<0 || cur_x>=input.width
                        || cur_y<0 || cur_y>=input.height) 
                    {
                        cur_clr = ColorRGBA(0.5,0.5,0.5); // if point is out of image
                    } else {
                        cur_clr = get_color_at_int(input, {cur_x, cur_y});
                    }

                    final_color += cur_clr * this->matrix[my][mx];
                }
            }

            set_color_at_int(modified, {x,y}, final_color);
        }
    }

    return modified;
}