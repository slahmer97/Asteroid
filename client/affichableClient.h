
#ifndef AFFICHABLE_CLIENT_H
#define AFFICHABLE_CLIENT_H

#include <utility>
#include <vector>
#include <initializer_list>
#include "graphiqueSDL.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace web;                        // Common features like URIs.

class polygoneAC
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

    explicit polygoneAC(std::vector<point>  p) : points{std::move(p)}
    {

    }


public:
    point m_center{};
    std::vector<point> points;
};




class pologoneSer : polygoneAC{
public:
    inline pologoneSer(std::initializer_list<point>&& liste): polygoneAC(liste) {}
    inline explicit pologoneSer(std::vector<point> points): polygoneAC(std::move(points)) {}

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

    static pologoneSer json_to_polygoneAC(const std::string& p_object){

        json::array obj = json::value::parse(p_object)["points"].as_array();
       // unsigned long size = obj.size();
        std::vector<point> res;
        //initialize vector with size
        for (auto& o : obj)
            res.emplace_back(o["x"].as_integer(),o["y"].as_integer());
        return pologoneSer(res);
    }

};

class affichableClient : polygoneAC
{
public:
    inline affichableClient(std::initializer_list<point>&& liste): polygoneAC(liste) {}
    inline explicit affichableClient(std::vector<point> points): polygoneAC(std::move(points)) {}
    void afficherSurFenetre(graphiqueSDL& fenetre) const
    {
        for (unsigned long i = 0; i < points.size() - 1; ++i)
            fenetre.dessinerLigne(points[i], points[i + 1]);

        std::cout<<std::endl;
    }
    bool DrawFilledPolygon(const SDL_Color color, SDL_Renderer* renderer) {
        int topY;
        int topCnt;
        int leftCnt;
        int rightCnt;
        int startX;
        int endX;
        int cntY;
        int leftSlope;
        int rightSlope;
        int cnt;
        int numVerts = this->points.size();
        int numVertsProc = 1;

        point center = this->m_center;
        point *verts = &this->points[0];

        topY = verts[0].y;
        topCnt = 0;


        for(cnt = 1; cnt < numVerts; cnt++)
        {
            if(verts[cnt].y < topY)
            {
                topY = verts[cnt].y;
                topCnt = cnt;
            }
        }


        leftCnt = topCnt - 1;
        if(leftCnt < 0)
            leftCnt = numVerts - 1;
        rightCnt = topCnt + 1;
        if(rightCnt >= numVerts)
            rightCnt = 0;

        startX = endX = (verts[topCnt].x + center.x) << 16;
        cntY = verts[topCnt].y;

        if(verts[leftCnt].y != verts[topCnt].y)
            leftSlope = ((verts[leftCnt].x - verts[topCnt].x) << 16) / (verts[leftCnt].y - verts[topCnt].y);
        if(verts[rightCnt].y != verts[topCnt].y)
            rightSlope = ((verts[rightCnt].x - verts[topCnt].x) << 16) / (verts[rightCnt].y - verts[topCnt].y);

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        // find slopes
        while(numVertsProc < numVerts)
        {
            while(cntY < verts[leftCnt].y && cntY < verts[rightCnt].y)
            {
                SDL_RenderDrawLine(renderer, startX >> 16, cntY + center.y, endX >> 16, cntY + center.y);
                cntY++;
                startX += leftSlope;
                endX += rightSlope;
            }

            if(verts[leftCnt].y <= cntY)
            {
                topCnt = leftCnt;
                leftCnt--;
                if(leftCnt < 0)
                    leftCnt = numVerts - 1;
                if(verts[leftCnt].y != verts[topCnt].y)
                    leftSlope = ((verts[leftCnt].x - verts[topCnt].x) << 16) / (verts[leftCnt].y - verts[topCnt].y);    // find the left side slope

                startX = (verts[topCnt].x + center.x) << 16;
                numVertsProc++;
            }

            if(verts[rightCnt].y <= cntY)
            {
                topCnt = rightCnt;
                rightCnt++;
                if(rightCnt == numVerts)
                    rightCnt = 0;
                if(verts[rightCnt].y != verts[topCnt].y)
                    rightSlope = ((verts[rightCnt].x - verts[topCnt].x) << 16) / (verts[rightCnt].y - verts[topCnt].y); // find the right side slope

                endX = (verts[topCnt].x + center.x) << 16;
                numVertsProc++;
            }
            SDL_RenderDrawLine(renderer, startX >> 16, cntY + center.y, endX >> 16, cntY + center.y);
        }

        return true;            // return success
    }
};






class alphaNumAC: public affichableClient
{
public:
    // ??? CONSTRUCTEURS
    
    //void afficherSurFenetre(graphiqueSDL& fenetre) const
    //{
        // ???
    //}
private:
    // ???
    // ???
    // ???
};

#endif //AFFICHABLE_CLIENT_H
