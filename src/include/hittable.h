#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "rtweekend.h"
#include "aabb.h"

class material;

struct hit_record
{
    vec3 p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
    double t;
    double u;
    double v;
    bool front_face; // 是否是外表面，通过光线方向向量和物体表面法线做点乘，点乘结果可以用于判断内外（小于0，说明和法线方向相反，不是外表面，反之相反）

    inline void set_face_normal(const ray &r, const vec3 &outwart_normal)
    {
        front_face = dot(r.direction(), outwart_normal) < 0;
        normal = front_face ? outwart_normal : -outwart_normal;
    }
};

// 该基类用于定义任何可能与光线交互的物体，继承该基类时，要求子类需要实现自己的碰撞方法和boundingbox（包围盒）
class hittable
{
public:
    virtual ~hittable(){};

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
    virtual bool bounding_box(double time0, double time1, aabb &output_box) const = 0;
};

// 物体变换
class translate : public hittable
{
public:
    std::shared_ptr<hittable> ptr;
    vec3 offset;

public:
    translate(std::shared_ptr<hittable> p, const vec3 &displacement) : ptr(p), offset(displacement) {}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override;
};

bool translate::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    ray moved_r(r.origin() - offset, r.direction(), r.time());

    if (!ptr->hit(moved_r, t_min, t_max, rec))
    {
        return false;
    }

    rec.p += offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}

bool translate::bounding_box(double time0, double time1, aabb &output_box) const
{
    if (!ptr->bounding_box(time0, time1, output_box))
    {
        return false;
    }

    output_box = aabb(output_box.min() + offset, output_box.max() + offset);
    return true;
}

// 绕Y轴旋转
class rotate_y : public hittable
{
public:
    std::shared_ptr<hittable> ptr;
    double sin_theta;
    double cos_theta;
    bool hasbox;
    aabb bbox;

public:
    rotate_y(std::shared_ptr<hittable> p, double angle);

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override
    {
        output_box = bbox;
        return hasbox;
    }
};

rotate_y::rotate_y(std::shared_ptr<hittable> p, double angle) : ptr(p)
{
    auto radians = degress_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasbox = ptr->bounding_box(0, 1, bbox);

    point3 min(infinity, infinity, infinity);
    point3 max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                auto x = i * bbox.max().x() + (1 - i) * bbox.min().x();
                auto y = j * bbox.max().y() + (1 - j) * bbox.min().y();
                auto z = k * bbox.max().z() + (1 - k) * bbox.min().z();

                auto newx = cos_theta * x + sin_theta * z;
                auto newz = -sin_theta * x + cos_theta * z;

                vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++)
                {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = aabb(min, max);
}

bool rotate_y::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
    origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

    direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
    direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

    ray rotated_r(origin, direction, r.time());

    if (!ptr->hit(rotated_r, t_min, t_max, rec))
    {
        return false;
    }

    auto p = rec.p;
    auto normal = rec.normal;

    p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
    p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

    normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.p = p;
    rec.set_face_normal(rotated_r, normal);

    return true;
}

#endif