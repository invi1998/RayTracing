// 球体

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "..\include\hittable.h"
#include "..\include\vec3.h"

class sphere : public hittable
{
private:
    vec3 center;
    double radius;

public:
    sphere() {}
    sphere(vec3 cen, double r) : center(cen), radius(r){};

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
};

#endif