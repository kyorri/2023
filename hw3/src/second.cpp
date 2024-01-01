#ifndef _IOSTREAM_H
#define _IOSTREAM_H
#include <iostream>
#endif

#include "../include/header.h"

Point::Point(double a, double b) {
    x = a, y = b;
}

Point::Point(const Point &p) {
    this->x = p.x, this->y = p.y; 
}

Point::~Point() {
    std::cout << "Point(" << x << ", " << y << ") removed." << std::endl;
}
