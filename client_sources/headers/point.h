
#ifndef ASTEROID_POINT_H
#define ASTEROID_POINT_H

struct point {
    int x, y;

    point() = default;

    point(int x, int y) noexcept: x(x), y(y) {}
};

#endif //ASTEROID_POINT_H
