#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "ray.h"

struct hit_record
{
    vec3 p;
    vec3 normal;
    double t;
    bool front_face; // 是否是外表面，通过光线方向向量和物体表面法线做点乘，点乘结果可以用于判断内外（小于0，说明和法线方向相反，不是外表面，反之相反）

    inline void set_face_normal(const ray &r, const vec3 &outwart_normal)
    {
        front_face = dot(r.direction(), outwart_normal) < 0;
        normal = front_face ? outwart_normal : -outwart_normal;
    }
};

// 该基类用于定义任何可能与光线交互的物体，继承该基类时，要求子类需要实现自己的碰撞方法
class hittable
{
public:
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;

    virtual ~hittable(){};
};

#endif