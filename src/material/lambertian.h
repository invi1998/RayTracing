// 漫反射材质
#ifndef __LAMBERTIAN_H__
#define __LAMBERTIAN_H__

#include "material.h"
#include "../include/texture.h"

class lambertian : public material
{
private:
    std::shared_ptr<texture> albedo;

public:
    lambertian(const color &a) : albedo(std::make_shared<solid_color>(a)) {}
    lambertian(std::shared_ptr<texture> a) : albedo(a) {}

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

    scattered = ray(rec.p, scatter_dirction, r_in.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
}

#endif