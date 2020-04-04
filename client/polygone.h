//
// Created by parallels on 4/4/20.
//

#ifndef ASTEROID_POLYGONE_H
#define ASTEROID_POLYGONE_H


class polygone
{
public:
    polygone(std::initializer_list<point>&& liste) : m_center{}, points{liste}
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

    explicit polygone(std::vector<point> p) : m_center{}, points{std::move(p)}
    {}


public:
    point m_center;
    std::vector<point> points;
};


#endif //ASTEROID_POLYGONE_H
