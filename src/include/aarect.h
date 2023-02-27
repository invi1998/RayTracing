#ifndef __AARECT_H__
#define __AARECT_H__

#include "rtweekend.h"

#include "hittable.h"

class xy_rect : public hittable
{
public:
    xy_rect() {}

    xy_rect(double _x0, double _x1, double _y0, double _y1, double _k,
            std::shared_ptr<material> mat)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat){};

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override
    {
        // The bounding box must have non-zero width in each dimension, so pad the Z
        // dimension a small amount.
        output_box = aabb(point3(x0, y0, k - 0.0001), point3(x1, y1, k + 0.0001));
        return true;
    }

public:
    std::shared_ptr<material> mp;
    double x0, x1, y0, y1, k;
};

bool xy_rect::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    auto t = (k - r.origin().z()) / r.direction().z();

    if (t < t_min || t > t_max)
    {
        return false;
    }

    auto x = r.origin().x() + t * r.direction().x();
    auto y = r.origin().y() + t * r.direction().y();

    if (x < x0 || x > x1 || y < y0 || y > y1)
    {
        return false;
    }

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;

    auto outwart_normal = vec3(0, 0, 1);
    rec.set_face_normal(r, outwart_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}

// -------------------------------------------

class xz_rect : public hittable
{
public:
    std::shared_ptr<material> mp;
    double x0, x1, z0, z1, k;

public:
    xz_rect() {}
    xz_rect(double _x0, double _x1, double _z0, double _z1, double _k, std::shared_ptr<material> mat) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override;
};

bool xz_rect::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    auto t = (k - r.origin().y()) / r.direction().y();

    if (t < t_min || t > t_max)
    {
        return false;
    }

    auto x = r.origin().x() + t * r.direction().x();
    auto z = r.origin().z() + t * r.direction().z();

    if (x < x0 || x > x1 || z < z0 || z > z1)
    {
        return false;
    }

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;

    auto outward_normal = vec3(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}

bool xz_rect::bounding_box(double time0, double time1, aabb &output_box) const
{
    // 边界框在每个维度中（x,y,z）必须具有非零宽度，才能填充Y
    output_box = aabb(point3(x0, k - 0.0001, z0), point3(x1, k + 0.0001, z1));
    return true;
}

// -------------------------------------------

class yz_rect : public hittable
{
public:
    std::shared_ptr<material> mp;
    double y0, y1, z0, z1, k;

public:
    yz_rect() {}

    yz_rect(double _y0, double _y1, double _z0, double _z1, double _k, std::shared_ptr<material> mat) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat){};

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override;
};

bool yz_rect::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    auto t = (k - r.origin().x()) / r.direction().x();

    if (t < t_min || t > t_max)
    {
        return false;
    }

    auto y = r.origin().y() + t * r.direction().y();
    auto z = r.origin().z() + t * r.direction().z();

    if (y < y0 || y > y1 || z < z0 || z > z1)
    {
        return false;
    }

    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = vec3(1, 0, 0);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}

bool yz_rect::bounding_box(double time0, double time1, aabb &output_box) const
{
    // 边界框在每个维度中（x,y,z）必须具有非零宽度，所以填充一个尺寸较小的x
    output_box = aabb(point3(k - 0.0001, y0, z0), point3(k + 0.0001, y1, z1));
    return true;
}

#endif