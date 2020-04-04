
#ifndef AFFICHABLE_CLIENT_H
#define AFFICHABLE_CLIENT_H

#include <utility>
#include <vector>
#include <initializer_list>
#include "graphiqueSDL.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace web;                        // Common features like URIs.


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

    explicit polygone(std::vector<point>  p) : m_center{}, points{std::move(p)}
    {}


public:
    point m_center;
    std::vector<point> points;
};


class polyServeur : public polygone {
public:
    polyServeur(std::initializer_list<point>&& liste): polygone(liste) {}
    explicit polyServeur(std::vector<point> points): polygone(std::move(points)) {}

    std::string to_string() {
        json::value o;
        std::vector<json::value> a{};
        for(const auto& p : points){
            json::value tmp;
            tmp["x"] = json::value(p.x);
            tmp["y"] = json::value(p.y);
            a.emplace_back(tmp);
        }

        o["points"] = json::value::array(a);
        o["type"] = json::value(std::string("polygone"));

        std::stringstream s;
        s << o;
        return s.str();
    }

    static polyServeur json_to_polygone(const std::string& p_object) {

        json::array obj = json::value::parse(p_object)["points"].as_array();
       // unsigned long size = obj.size();
        std::vector<point> res;
        //initialize vector with size
        for (auto& o : obj)
            res.emplace_back(o["x"].as_integer(),o["y"].as_integer());
        return polyServeur(res);
    }

};


class affichable
{
public:
    virtual void afficherSurFenetre(graphiqueSDL& fenetre) const = 0;
};


class polyClient : public polygone, public affichable // faire une classe affichable // cette classe doit heriter de poly et de affich
{
public:
    polyClient(std::initializer_list<point>&& liste): polygone(liste) {}
    explicit polyClient(std::vector<point> points): polygone(std::move(points)) {}
    void afficherSurFenetre(graphiqueSDL& fenetre) const override
    {
        const SDL_Color c = {255, 255,255,  255 };
        fenetre.dessinerPolyPlein(c, m_center, points);
    }
};


class alphaNumClient: public affichable
{
public:
    // ??? CONSTRUCTEURS
    
    //void afficherSurFenetre(graphiqueSDL& fenetre) const override
    //{
        // ???
    //}

private:
    // ???
};


#endif //AFFICHABLE_CLIENT_H
