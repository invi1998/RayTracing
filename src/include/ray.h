#ifndef __RAY_H__
#define __RAY_H__

#include "vec3.h"

// 光线类
class ray
{
private:
    point3 orig;
    vec3 dir;
    double tm;

public:
    ray() {}

    ray(const point3 &origin, const vec3 &direction, double time = 0.0) : orig(origin), dir(direction), tm(time) {}

    inline point3 origin() const { return orig; }
    inline vec3 direction() const { return dir; }
    inline double time() const { return tm; }

    vec3 at(double t) const
    {
        return orig + t * dir;
    }
};

#endif