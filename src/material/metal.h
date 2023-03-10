// 金属材质类

#ifndef __METAL_H__
#define __METAL_H__

#include "material.h"

class metal : public material
{
private:
    color albedo; // 反射率；漫反射系数
    double fuzz;

public:
    metal(const color &a, double f) : albedo(a), fuzz(f < 1 ? f : 1){};

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
};

bool metal::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
{
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

#endif