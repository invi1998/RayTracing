// 立方体

#ifndef __CUBE_H__
#define __CUBE_H__

#include "..\include\hittable.h"
#include "..\include\vec3.h"
#include "..\material\material.h"

class cube : public hittable
{
private:
    vec3 position;
    double width;
    double height;
    double length;
    std::shared_ptr<material> mat_ptr;

public:
    cube(vec3 p, double w, double h, double l, std::shared_ptr<material> m) : position(p), width(w), height(h), length(l), mat_ptr(m){};
    ~cube();

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
};

bool cube::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    return true;
}

#endif