//
//  point.h
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#ifndef __ray_traicing2__point__
#define __ray_traicing2__point__

#include <iostream>
#include "pre.h"
#include <cmath>
using namespace std;
class point{
public:
    double x , y , z;
    double r2, r;
    point();
    point(double _x, double _y , double _z):x(_x), y(_y), z(_z){
        r2 = _x * _x + _y * _y + _z * _z;
        r = sqrt(r2);
    }
    double distance();
    void set(double _x, double _y , double _z);
    void print();
    point normal();
    point &operator=(const point &p);
    point operator+(const point &p);
    point operator-(const point &p);
    point operator*(const point &p);
    double operator%(const point &p);
    point operator*(const double p);
    friend istream &operator>>(istream &is, point &p);
};


#endif /* defined(__ray_traicing2__point__) */
