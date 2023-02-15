// 材质抽象类
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "../include/rtweekend.h"
#include "../include/hittable.h"

struct hit_record;

class material
{
public:
    virtual ~material(){};

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const = 0;
};

#endif