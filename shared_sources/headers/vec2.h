//
// Created by stevlulz on 08/04/2020.
//

#ifndef ASTEROID_VEC2_H
#define ASTEROID_VEC2_H



#include <cmath>
#include<iostream>

template <class T>
class vec2 {
public:
    T x, y;

    vec2() :x(0), y(0) {}
    vec2(T x, T y) : x(x), y(y) {}
    vec2(const vec2& v) : x(v.x), y(v.y) {}

    const vec2<int> operator () () const {
        vec2<int> t{std::lround(this->x), std::lround(this->y)};
        return t;
    }

    vec2& operator=(const vec2& v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    vec2 operator+(vec2& v) {
        return vec2(x + v.x, y + v.y);
    }
    vec2 operator-(vec2& v) {
        return vec2(x - v.x, y - v.y);
    }

    vec2& operator+=(vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    vec2& operator-=(vec2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    vec2 operator+(double s) {
        return vec2(x + s, y + s);
    }
    vec2 operator-(double s) {
        return vec2(x - s, y - s);
    }
    vec2 operator*(double s) {
        return vec2(x * s, y * s);
    }
    vec2 operator/(double s) {
        return vec2(x / s, y / s);
    }


    vec2& operator+=(double s) {
        x += s;
        y += s;
        return *this;
    }
    vec2& operator-=(double s) {
        x -= s;
        y -= s;
        return *this;
    }
    vec2& operator*=(double s) {
        x *= s;
        y *= s;
        return *this;
    }
    vec2& operator/=(double s) {
        x /= s;
        y /= s;
        return *this;
    }
    void inc(){
        this->x += 1.0;
        this->y += 1.0;
    }
    void set(T p_x, T p_y) {
        this->x = p_x;
        this->y = p_y;
    }

    void rotate(double deg, const vec2<double>& center) {
        x -= center.x;
        y -= center.y;
        rotate(deg);
        x += center.x;
        y += center.y;
    }
    vec2& rotate(double deg) {
        double theta = deg / 180.0 * M_PI;
        double c = cos(theta);
        double s = sin(theta);
        double tx = x * c - y * s;
        double ty = x * s + y * c;
        x = tx;
        y = ty;
        return *this;
    }

    static vec2& rotate_s(double deg, vec2 v){
        return v.rotate(deg);
    }
    vec2& normalize() {
        if (length() == 0) return *this;
        *this *= (1.0 / length());
        return *this;
    }

    [[nodiscard]] double dist(vec2 v) const {
        vec2 d(v.x - x, v.y - y);
        return d.length();
    }
    [[nodiscard]] float length() const {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]] vec2& ortho() const {
        return vec2(y, -x);
    }

    static double dot(vec2 v1, vec2 v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }
    static double cross(vec2 v1, vec2 v2) {
        return (v1.x * v2.y) - (v1.y * v2.x);
    }


    void print(){
        std::cout<<"X : "<<this->x<<" -- Y : "<<this->y<<"\n";
    }
};

typedef vec2<float> vec2f;
typedef vec2<double> vec2d;
typedef vec2<int> vec2i;

#endif //ASTEROID_VEC2_H


