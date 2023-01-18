#include "Point.hpp"


Point Point::operator* (float x) {
    Point res(*this);
    res.pos *= x;
    res.colour *= x;
    res.norm *= x;
    res.uv *= x;
    
    return res;
}

Point Point::operator+ (const Point& p) {
    Point res(*this);

    res.pos += p.pos;
    res.colour += p.colour;
    res.norm += p.norm;
    res.uv += p.uv;

    return res;
}