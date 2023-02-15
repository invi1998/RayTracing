// 金属材质类

#ifndef __METAL_H__
#define __METAL_H__

#include "material.h"

class metal : public material
{
private:
    color albedo;

public:
    metal(const color &a) : albedo(a){};

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
};

bool metal::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
{
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

#endif