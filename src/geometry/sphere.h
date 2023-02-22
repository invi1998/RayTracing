// 球体

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "..\include\hittable.h"
#include "..\include\vec3.h"
#include "..\material\material.h"

class sphere : public hittable
{
private:
    vec3 center;
    double radius;
    std::shared_ptr<material> mat_ptr;

public:
    sphere() {}
    sphere(vec3 cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m){};

    ~sphere() {}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center;

    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
        return false;

    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;

    if (root < t_min || root > t_max)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max)
        {
            return false;
        }
    }
    rec.t = root;
    rec.p = r.at(rec.t);
    // 光线入射面判定
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool sphere::bounding_box(double time0, double time1, aabb &output_box) const
{
    output_box = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
    return true;
}

#endif