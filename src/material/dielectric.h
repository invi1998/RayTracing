// 玻璃材质
#ifndef __DIELECTRIC_H__
#define __DIELECTRIC_H__

#include "material.h"

class dielectric : public material
{
private:
    double ir;

public:
    dielectric(double index_of_refraction) : ir(index_of_refraction) {}
    ~dielectric(){};

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
};

bool dielectric::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
{
    attenuation = color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

    vec3 unit_direction = unit_vector(r_in.direction());

    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3 direction;

    if (cannot_refract)
    {
        direction = reflect(unit_direction, rec.normal);
    }
    else
    {
        direction = refract(unit_direction, rec.normal, refraction_ratio);
    }

    scattered = ray(rec.p, direction);
    return true;
}

#endif