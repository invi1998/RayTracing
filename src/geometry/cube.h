// 立方体

#ifndef __CUBE_H__
#define __CUBE_H__

#include "..\include\hittable.h"
#include "..\include\vec3.h"
#include "..\material\material.h"

class cube : public hittable
{
private:
    point3 center;
    double width;
    double height;
    double length;
    std::shared_ptr<material> mat_ptr;
    /*
            p7*-------*p8
            /       /
           /       /
        p3*-------*p4
          |       |
          |  p5*  |    *p6
          |       |
          |       |
        p1*-------*p2

    */

public:
    cube(vec3 p, double w, double h, double l, std::shared_ptr<material> m) : center(p), width(w), height(h), length(l), mat_ptr(m){};
    ~cube();

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    // 求立方体各个顶点的坐标
    vec3 p1() const;
    vec3 p2() const;
    vec3 p3() const;
    vec3 p4() const;
    vec3 p5() const;
    vec3 p6() const;
    vec3 p7() const;
    vec3 p8() const;

    // 判断射线是否和三角形相交
    // 输入参数：r是射线，中间三个参数v0，v1和v2是三角形的三个顶点。
    // 输出参数：t是交点对应的射线方程中的t值，u，v则是交点的纹理坐标值
    bool intersectTriangle(const ray &r, const point3 &v0, const point3 &v1, const point3 &v2, double *t, double *u, double *v) const;
};

bool cube::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center;

    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());

    double *t, *u, *v;
    if (!intersectTriangle(r, p1(), p2(), p3(), t, u, v))
    {
        return false;
    }
    else
    {
    }
    return true;
}

vec3 cube::p1() const
{
    return vec3(center.x() - 0.5 * width, center.y() - 0.5 * height, center.z() + 0.5 * length);
}

vec3 cube::p2() const
{
    return vec3(center.x() + 0.5 * width, center.y() - 0.5 * height, center.z() + 0.5 * length);
}

vec3 cube::p3() const
{
    return vec3(center.x() - 0.5 * width, center.y() + 0.5 * height, center.z() + 0.5 * length);
}

vec3 cube::p4() const
{
    return vec3(center.x() + 0.5 * width, center.y() + 0.5 * height, center.z() + 0.5 * length);
}

vec3 cube::p5() const
{
    return vec3(center.x() - 0.5 * width, center.y() - 0.5 * height, center.z() - 0.5 * length);
}

vec3 cube::p6() const
{
    return vec3(center.x() + 0.5 * width, center.y() - 0.5 * height, center.z() - 0.5 * length);
}

vec3 cube::p7() const
{
    return vec3(center.x() - 0.5 * width, center.y() + 0.5 * height, center.z() - 0.5 * length);
}

vec3 cube::p8() const
{
    return vec3(center.x() + 0.5 * width, center.y() + 0.5 * height, center.z() - 0.5 * length);
}

bool cube::intersectTriangle(const ray &r, const point3 &v0, const point3 &v1, const point3 &v2, double *t, double *u, double *v) const
{
    // Find vectors for two edges sharing vert0
    vec3 edge1 = v1 - v0;
    vec3 edge2 = v2 - v0;

    // Begin calculating determinant - also used to calculate U parameter
    vec3 pvec;
    pvec = cross(r.direction(), edge2);

    // If determinant is near zero, ray lies in plane of triangle
    double det = dot(edge1, pvec);

    vec3 tvec;
    if (det > 0)
    {
        tvec = r.origin() - v0;
    }
    else
    {
        tvec = v0 - r.origin();
        det = -det;
    }
    if (det < 0.0001f)
        return false;
    // Calculate U parameter and test bounds
    *u = dot(tvec, pvec);
    if (*u < 0.0f || *u > det)
        return false;

    // Prepare to test V parameter
    vec3 qvec;
    qvec = cross(tvec, edge1);

    // Calculate V parameter and test bounds
    *v = dot(r.direction(), qvec);
    if (*v < double(0.0f) || *u + *v > det)
        return false;

    *t = dot(edge2, qvec);
    double fInvDet = double(1.0) / det;
    *t *= fInvDet;
    *u *= fInvDet;
    *v *= fInvDet;

    return true;
}

#endif