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

inline double random_double()
{
    // 返回一个[0, 1)之间的随机小数
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    // 返回一个[min, max)之间的随机小数
    return min + (max - min) * random_double();
}

// 将x限制在[min,max]区间之中
inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

// 公共头文件
#include "ray.h"
#include "vec3.h"
#include "color.h"

#endif