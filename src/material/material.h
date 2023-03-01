// 材质抽象类
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "../include/rtweekend.h"
#include "../include/hittable.h"
#include "../include/texture.h"

struct hit_record;

class material
{
public:
    virtual ~material(){};

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const = 0;

    virtual color emitted(double u, double v, const point3 &p) const
    {
        return color(0, 0, 0);
    }
};

class diffuse_light : public material
{
public:
    std::shared_ptr<texture> emit;

public:
    diffuse_light(std::shared_ptr<texture> a) : emit(a) {}

    diffuse_light(color c) : emit(std::make_shared<solid_color>(c)) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        return false;
    }

    virtual color emitted(double u, double v, const point3 &p) const override
    {
        return emit->value(u, v, p);
    }
};

class isotropic : public material
{
public:
    std::shared_ptr<texture> albedo; // 反射率；漫反射系数

public:
    isotropic(color c) : albedo(std::make_shared<solid_color>(c)) {}
    isotropic(std::shared_ptr<texture> a) : albedo(a) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        scattered = ray(rec.p, random_in_unit_sphere(), r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }
};

#endif