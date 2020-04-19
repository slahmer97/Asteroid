//
// Created by parallels on 4/13/20.
//

#ifndef ASTEROID_INTERSECTION_H
#define ASTEROID_INTERSECTION_H

#include <algorithm>

template<typename P, typename T = float>
class intersection {
public:
    bool operator()(const P& p1, const P& q1, const P& p2, const P& q2)
    {
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);
        if (o1 != o2 && o3 != o4) return true;
        if (o1 == 0 && aligner(p1, p2, q1)) return true;
        if (o2 == 0 && aligner(p1, q2, q1)) return true;
        if (o3 == 0 && aligner(p2, p1, q2)) return true;
        if (o4 == 0 && aligner(p2, q1, q2)) return true;
        return false;
    }

private:
    bool aligner(const P& p, const P& q, const P& r) {
        bool b1 = q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x);
        bool b2 = q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
        return b1 && b2;
    }
    T orientation(const P& p, const P& q, const P& r) {
        int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0) return 0;
        return (val > 0)? 1: 2;
    }
};

#endif //ASTEROID_INTERSECTION_H
