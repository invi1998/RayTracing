#ifndef __RAY_H__
#define __RAY_H__

#include "vec3.h"

// 光线类
class ray
{
public:
    point3 orig;
    vec3 dir;

public:
    ray() {}

    ray(const point3 &origin, const vec3 &direction) : orig(origin), dir(direction) {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    vec3 at(double t) const
    {
        return orig + t * dir;
    }
};

#endif