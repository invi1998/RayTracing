// 纹理
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "rtweekend.h"
#include "perlin.h"

class texture
{
public:
    virtual color value(double u, double v, const point3 &p) const = 0;
};

class solid_color : public texture
{
private:
    color color_value;

public:
    solid_color() {}
    solid_color(color c) : color_value(c) {}

    solid_color(double red, double green, double blue) : solid_color(color(red, green, blue)) {}

    virtual color value(double u, double v, const point3 &p) const override
    {
        return color_value;
    }
};

class cheker_texture : public texture
{
public:
    std::shared_ptr<texture> odd;
    std::shared_ptr<texture> even;

public:
    cheker_texture() {}

    cheker_texture(std::shared_ptr<texture> _evem, std::shared_ptr<texture> _odd) : even(_evem), odd(_odd) {}

    cheker_texture(color c1, color c2) : even(std::make_shared<solid_color>(c1)), odd(std::make_shared<solid_color>(c2)) {}

    virtual color value(double u, double v, const point3 &p) const override
    {
        auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());

        if (sines < 0)
        {
            return odd->value(u, v, p);
        }
        else
        {
            return even->value(u, v, p);
        }
    }
};

class noise_texture : public texture
{
private:
    perlin noise;
    double scale;

public:
    noise_texture() {}
    noise_texture(double sc) : scale(sc) {}
    ~noise_texture() {}

    virtual color value(double u, double v, const point3 &p) const override
    {
        return color(1, 1, 1) * noise.noise(p * scale);
    }
};

#endif