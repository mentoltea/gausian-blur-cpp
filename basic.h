#ifndef BASIC_H
#define BASIC_H

#include <iostream>
#include <cstdlib>
// #define _USE_MATH_DEFINES
#include <math.h>
// #include <cmath>
#include <fstream>
#include <cstdint>
#include <functional>

#include "stbimg/image.hpp"

#include "matrix/src/matrix.hpp"

# define PI 3.14159265358979323846  

struct Point2 {
    double x, y;
    
    Point2();
    Point2(double x, double y);
    
    double distance2(const Point2 &other = Point2(0,0));
    double distance(const Point2 &other = Point2(0,0));
    
    Point2 operator-() const;
    
    Point2 operator+(const Point2 &other) const;
    Point2 operator-(const Point2 &other) const;

    Point2& operator+=(const Point2 &other) ;
    Point2& operator-=(const Point2 &other) ;
    
    Point2 operator*(double k) const;
    Point2 operator/(double k) const;
    
    bool operator==(const Point2 &other) const;
    bool operator!=(const Point2 &other) const;
};
Point2 operator*(double k, const Point2 &other);

std::ostream& operator<<(std::ostream& os, const Point2& p);


Point2 xy2uv(const Image &img, Point2 xy);

Point2 uv2xy(const Image &img, Point2 uv);

std::pair<int,int> xy2int(const Image &img, Point2 xy);

Point2 int2xy(const Image &img, std::pair<int,int> ixy);


double random_uniform_double();

// r -> [0, 1)
// g -> [0, 1)
// b -> [0, 1)
// a -> [0, 1)
ColorRGBA random_color_nrm();

// x -> [0, 1)
// y -> [0, 1)
Point2 random_point_nrm();

ColorRGBA get_color_at_int(const Image &img, std::pair<int,int> ixy);

ColorRGBA get_color_at_uv(const Image &img, Point2 uv);

void set_color_at_int(Image &img, std::pair<int,int> ixy, ColorRGBA clr);

void set_color_at_uv(Image &img, Point2 uv, ColorRGBA clr);

double to_gray(ColorRGBA clr);

Image to_grayscale(const Image& img);

Image operator+(const Image& i1, const Image& i2);
Image operator-(const Image& i1, const Image& i2);

Image operator*(const Image& image, double k);
Image operator*(double k, const Image& image);
Image operator/(const Image& image, double k);


Image operator*(const Image& image, const Image& gray);

std::pair<int,int> min(const Image& image, const std::function<double(ColorRGBA)> &func);
std::pair<int,int> max(const Image& image, const std::function<double(ColorRGBA)> &func);

Image threashhold(
    const Image& image, 
    const std::function<double(ColorRGBA)> &func,
    double minvalue, 
    ColorRGBA alter_color = ColorRGBA(0,0,0)
);

#endif // BASIC_H