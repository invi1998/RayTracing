// 立方体
#ifndef __BOX_H__
#define __BOX_H__

#include "../include/rtweekend.h"

#include "../include/aarect.h"
#include "../include/hittable_list.h"

class box : public hittable
{
private:
    point3 box_min;
    point3 box_max;
    hittable_list sides;

public:
    box() {}
    box(const point3 &p0, const point3 &p1, std::shared_ptr<material> ptr);
    ~box() {}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override;
};

box::box(const point3 &p0, const point3 &p1, std::shared_ptr<material> ptr)
{
    box_min = p0;
    box_max = p1;

    sides.add(std::make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    sides.add(std::make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    sides.add(std::make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    sides.add(std::make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    sides.add(std::make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
    sides.add(std::make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
}

bool box::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    return sides.hit(r, t_min, t_max, rec);
}

bool box::bounding_box(double time0, double time1, aabb &output_box) const
{
    output_box = aabb(box_min, box_max);
    return true;
}

#endif