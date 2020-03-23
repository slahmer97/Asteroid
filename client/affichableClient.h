
#ifndef AFFICHABLE_CLIENT_H
#define AFFICHABLE_CLIENT_H

#include <utility>
#include <vector>
#include <initializer_list>
#include "graphiqueSDL.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace web;                        // Common features like URIs.


class affichableClient
{
public:
    virtual void afficherSurFenetre(graphiqueSDL& fenetre) const = 0;
};


class polygoneAC: public affichableClient
{
public:
    polygoneAC(std::initializer_list<point>&& liste) : points{liste}
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

    polygoneAC(std::vector<point>  p) : points{std::move(p)}
    {}

    void afficherSurFenetre(graphiqueSDL& fenetre) const override
    {
        for (int i = 0; i < points.size() - 1; ++i)
            fenetre.dessinerLigne(points[i], points[i + 1]);
    }
    point m_center{};

    inline std::string to_string(){
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

    static polygoneAC json_to_polygoneAC(const std::string& p_object){

        json::array obj = json::value::parse(p_object)["points"].as_array();
        long size = obj.size();
        std::vector<point> res;
        //initialize vector with size
        for (auto& o : obj)
            res.emplace_back(o["x"].as_integer(),o["y"].as_integer());
        return polygoneAC(res);
    }
private:
    std::vector<point> points;
};



class alphaNumAC: public affichableClient // ???
{
public:
    // ??? CONSTRUCTEURS
    
    void afficherSurFenetre(graphiqueSDL& fenetre) const override
    {
        // ???
    }
private:
    // ???
    // ???
    // ???
};

#endif //AFFICHABLE_CLIENT_H
