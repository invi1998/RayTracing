// 常用函数和常数定义
#ifndef __RTWEEKEND_H__
#define __RTWEEKEND_H__

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degress_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

// 公共头文件
#include "ray.h"
#include "vec3.h"

#endif