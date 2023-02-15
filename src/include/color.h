// RGB颜色，输出像素点的rgb颜色
#ifndef __COLOR_H__
#define __COLOR_H__

#include "vec3.h"
#include "rtweekend.h"
#include <iostream>

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // 将颜色除以采样点数（混合模糊颜色，进行反走样）
    auto scale = 1.0 / samples_per_pixel;
    // sqrt 添加伽马颜色校正
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
