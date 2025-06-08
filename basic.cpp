#include "basic.h"

#define STB_IMAGE_WRAPPER_IMPLEMENTATION
#include "stbimg/image.hpp"
#undef STB_IMAGE_WRAPPER_IMPLEMENTATION

Point2::Point2(): x(0), y(0) {}

Point2::Point2(double x, double y): x(x), y(y) {}
    
double Point2::distance2(const Point2 &other) {
    return (this->x-other.x)*(this->x-other.x) 
    + (this->y-other.y)*(this->y-other.y);
}

double Point2::distance(const Point2 &other) {
    return sqrt(this->distance2(other));
}

Point2 Point2::operator-() const {
    return Point2(-x, -y);
}

Point2 Point2::operator+(const Point2 &other) const {
    return Point2(this->x + other.x, this->y + other.y);
}
Point2 Point2::operator-(const Point2 &other) const {
    return Point2(this->x - other.x, this->y - other.y);
}

Point2& Point2::operator+=(const Point2 &other)  {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Point2& Point2::operator-=(const Point2 &other)  {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Point2 Point2::operator*(double k) const {
    return Point2(x*k, y*k);
}

Point2 Point2::operator/(double k) const {
    return Point2(x/k, y/k);
}

bool Point2::operator==(const Point2 &other) const {
    return (this->x==other.x)&&(this->y==other.y);
}
bool Point2::operator!=(const Point2 &other) const {
    return !(*this==other);
}

Point2 operator*(double k, const Point2 &other) {
    return Point2(other.x*k, other.y*k);
}

std::ostream& operator<<(std::ostream& os, const Point2& p) {
    os << " {x: " << p.x << ", y: " << p.y << "}";
    return os;
}






Point2 xy2uv(const Image &img, Point2 xy) {
    double u = xy.x / (double)img.width;
    double v = xy.y / (double)img.height;
    return Point2(u, v);
}

Point2 uv2xy(const Image &img, Point2 uv) {
    double x = uv.x * img.width;
    double y = uv.y * img.height;
    return Point2(x, y);
}

std::pair<int,int> xy2int(const Image &img, Point2 xy) {
    int ix = (int)round(xy.x);
    int iy = (int)round(xy.y);

    if (ix < 0) ix = 0;
    else if (ix >= img.width) ix = img.width-1;
    
    if (iy < 0) iy = 0;
    else if (iy >= img.height) iy = img.height-1;

    return {ix, iy};
}

Point2 int2xy(const Image &img, std::pair<int,int> ixy) {
    int ix = ixy.first;
    int iy = ixy.second;
    return Point2((double)ix, (double)iy);
}

// -> [0, 1)
double random_uniform_double() {
    // std::uniform_real_distribution<double> unif(0,1);
    // std::default_random_engine rng;
    // return unif(rng);
    return (double)rand() / (double)RAND_MAX;
}

ColorRGBA random_color_nrm() {
    return ColorRGBA(random_uniform_double(), random_uniform_double(), random_uniform_double(), random_uniform_double());
}

Point2 random_point_nrm() {
    return Point2(random_uniform_double(), random_uniform_double());
}

ColorRGBA get_color_at_int(const Image &img, std::pair<int,int> ixy) {
    int x = ixy.first;
    int y = ixy.second;
    const uint8_t *data = img.at(x, y);

    ColorRGBA color;

    switch (img.channels) {
        case 1: {
            PixelGray pix = *(PixelGray*)data;
            color = (pix);
        } break;

        case 3: {
            PixelRGB pix = *(PixelRGB*)data;
            color = (pix);
        } break;
        
        case 4: {
            PixelRGBA pix = *(PixelRGBA*)data;
            color = (pix);
        } break;

        default: {
            throw std::runtime_error("Cannot take color from image with number of channels: " + std::to_string(img.channels));
        } break;
    }

    return color;
}

ColorRGBA get_color_at_uv(const Image &img, Point2 uv) {
    std::pair<int,int> ixy = xy2int(img, uv2xy(img, uv));
    return get_color_at_int(img, ixy);
}

void set_color_at_int(Image &img, std::pair<int,int> ixy, ColorRGBA color) {
    int x = ixy.first;
    int y = ixy.second;
    uint8_t *data = img.at(x, y);

    switch (img.channels) {
        case 1: {
            *(PixelGray*)data = (PixelGray)color;
        } break;

        case 3: {
            *(PixelRGB*)data = (PixelRGB)color;
        } break;
        
        case 4: {
            *(PixelRGBA*)data = (PixelRGBA)color;
        } break;

        default: {
            throw std::runtime_error("Cannot write color to image with number of channels: " + std::to_string(img.channels));
        } break;
    }
}

void set_color_at_uv(Image &img, Point2 uv, ColorRGBA color) {
    std::pair<int,int> ixy = xy2int(img, uv2xy(img, uv));
    set_color_at_int(img, ixy, color);
}


Image to_grayscale(const Image& img) {
    if (img.channels==1) {
        return img;
    }

    Image output(img.width, img.height, 1);
    for (int x=0; x<img.width; x++) {
        for (int y=0; y<img.height; y++) {
            ColorRGBA clr;
            switch (img.channels) {
                case 3:
                    clr = *(PixelRGB*)img.at(x,y);
                    break;

                case 4:
                    clr = *(PixelRGBA*)img.at(x,y);
                    break;
                
                default:
                    break;
            }
            int val = (int)(( (clr.r + clr.g + clr.b)/3.0 * (clr.a) )*255);
            if (val < 0) val = 0;
            else if (val > 255) val = 255;

            *output.at(x,y) = (uint8_t) val;
        }
    }

    return output;
}