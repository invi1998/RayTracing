// 轴对齐摄像机类
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "rtweekend.h"

class camera
{
private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
    double time0; // 射线生成时间
    double time1; // 射线结束时间

public:
    camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_radio, double aperture, double focus_dist, double _time0 = 0, double _time1 = 0);
    ~camera();

    ray get_ray(double u, double v) const;
};

camera::camera(point3 lookfrom, point3 lookat, vec3 vup, double vfov, double aspect_radio, double aperture, double focus_dist, double _time0, double _time1)
{
    auto theta = degress_to_radians(vfov);
    auto h = tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_radio * viewport_height;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

    lens_radius = aperture / 2;

    time0 = _time0;
    time1 = _time1;
}

camera::~camera()
{
}

ray camera::get_ray(double s, double t) const
{
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();

    return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, random_double(time0, time1));
}

#endif