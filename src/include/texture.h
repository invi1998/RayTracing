// 纹理
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "rtweekend.h"
#include "perlin.h"
#include "rtw_stb_image.h"

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
        return color(1, 1, 1) * 0.5 * (1 + sin(scale * p.z() + 10 * noise.turb(p)));
    }
};

class image_texture : public texture
{
private:
    unsigned char *data;
    int width, height;
    int bytes_per_scanline;

public:
    const static int bytes_per_pixel = 3;

    image_texture() : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}

    image_texture(const char *filename)
    {
        auto components_per_pixel = bytes_per_pixel;

        data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);

        if (!data)
        {
            std::cerr << "ERROR: Could not load texture image file ' " << filename << " ' \n";
            width = height = 0;
        }

        bytes_per_scanline = bytes_per_pixel * height;
    }

    ~image_texture()
    {
        delete data;
    }

    virtual color value(double u, double v, const point3 &p) const override
    {
        // 如果没有纹理贴图数据，放回cyan颜色作为调试
        if (data == nullptr)
        {
            return color(0, 1, 1);
        }

        // 将输入纹理坐标限制为[0,1]x[1,0]
        u = clamp(u, 0.0, 1.0);
        v = 1.0 - clamp(v, 0.0, 1.0); // 根据图像坐标修正V

        auto i = static_cast<int>(u * width);
        auto j = static_cast<int>(v * height);

        // 整数映射，因为实际坐标应小于1.0
        if (i >= width)
            i = width - 1;
        if (j >= height)
            j = height - 1;

        const auto color_scale = 1.0 / 255.0;
        auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

        return color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
    }
};

#endif