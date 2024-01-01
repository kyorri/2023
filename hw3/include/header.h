#ifndef HW3_INCLUDE_HEADER_H
#define HW3_INCLUDE_HEADER_H

#ifndef _IOSTREAM_H
#define _IOSTREAM_H
#include <iostream>
#endif

class Point {
    public:
        Point(double, double);
        Point(const Point&);
        ~Point();
        Point operator+ (const Point& op);
    private:
        double x, y;
};

#endif