#ifndef _IOSTREAM_H
#define _IOSTREAM_H
#include <iostream>
#endif

#include "../include/header.h"

Point Point::operator+(const Point& op) {
    Point p = Point(0, 0);
    p.x = this->x + op.x;
    p.y = this->y + op.y;
    return p;
}