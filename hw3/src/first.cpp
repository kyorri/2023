#ifndef _IOSTREAM_H
#define _IOSTREAM_H
#include <iostream>
#endif

#include "../include/header.h"

int main(void) {
    Point p1(3.14, 2.71);
    Point p2 = p1 + Point(1.0, 0.0);
    Point p3 = p1 + p2;
    std::cout << "hello, world!" << std::endl;
    return 0;
}