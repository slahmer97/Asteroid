//
// Created by parallels on 4/4/20.
//

#ifndef ASTEROID_POLYGONE_H
#define ASTEROID_POLYGONE_H

#include <vector>
#include <vec2.h>
#include "point.h"

class polygone
{
public:
    polygone(std::initializer_list<vec2d>&& liste) : m_center{}, points{liste}
    {
        int minX = 0xFFFF, minY = 0xFFFF, maxX = 0, maxY = 0;
        for (const auto& p : points) {
            if (p.x > maxX) maxX = p.x;
            if (p.x < minX) minX = p.x;
            if (p.y > maxY) maxY = p.y;
            if (p.y < minY) minY = p.y;
        }
        this->m_center.x = (minX) + ((maxX - minX) / 2);
        this->m_center.y =  (minY )+ ((maxY - minY) / 2);
    }

    explicit polygone(std::vector<vec2d> p) : m_center{}, points{std::move(p)}
    {}

    polygone() = default;



public:
    vec2d m_center;
    std::vector<vec2d> points;
};


#endif //ASTEROID_POLYGONE_H
