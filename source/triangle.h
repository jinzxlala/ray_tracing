//
//  triangle.h
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#ifndef __ray_traicing2__triangle__
#define __ray_traicing2__triangle__

#include <iostream>
#include "point.h"
#include "line.h"
using namespace std;
class triangle{
public:
    point p0, p1 , p2;
    point n;
    double d;
    triangle();
    triangle(point a , point b, point c):p0(a), p1(b), p2(c){
        point e1 = p1 - p0;
        point e2 = p2 - p0;
        n = (e1 * e2).normal();
        d = -(n % p0);
    }
    point norm();
    double xray(point zero , point dir);
    double xray(line l);
    bool intriangle(point test);
    triangle &operator=(triangle &p);
    friend istream &operator>>(istream &is , triangle &p);
};


#endif /* defined(__ray_traicing2__triangle__) */
