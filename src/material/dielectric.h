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
    vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);

    scattered = ray(rec.p, refracted);
    return true;
}

#endif