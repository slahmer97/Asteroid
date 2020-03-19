
#ifndef AFFICHABLE_H
#define AFFICHABLE_H

struct point
{
    float x, y;
};

struct ligne
{
    point a, b;
};

class affichable
{
public:
    affichable(std::initializer_list<ligne> liste) : lignes{liste} {}
protected:
    std::vector<ligne> lignes;
};

#endif //AFFICHABLE_H
