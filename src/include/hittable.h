#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "ray.h"

struct hit_record
{
    vec3 p;
    vec3 normal;
    double t;
};

// 该基类用于定义任何可能与光线交互的物体，继承该基类时，要求子类需要实现自己的碰撞方法
class hittable
{
public:
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};

#endif