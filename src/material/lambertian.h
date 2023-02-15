// 漫反射材质
#ifndef __LAMBERTIAN_H__
#define __LAMBERTIAN_H__

#include "material.h"

class lambertian : public material
{
private:
    color albedo;

public:
    lambertian(const color &a) : albedo(a) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
};

bool lambertian::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
{
    auto scatter_dirction = rec.normal + random_unit_vector();

    //
    if (scatter_dirction.near_zero())
    {
        scatter_dirction = rec.normal;
    }

    scattered = ray(rec.p, scatter_dirction);
    attenuation = albedo;
    return true;
}

#endif