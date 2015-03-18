//
//  point.cpp
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#include "point.h"
#include <cmath>
#include <iostream>
using namespace std;
void point::set(double _x, double _y, double _z){
    x = _x ; y = _y; z = _z;
    r2 = x * x + y * y + z * z;
    r = sqrt(r2);
    
}
void point::print(){
    cout << "(" << x <<"," << y << "," << z << ")"  << endl;
}
point::point(){}
double point::distance(){
    return sqrt(x * x+ y * y + z * z);
}
point point::operator+(const point &p){
    return point(x + p.x , y + p.y , z + p.z);
}
point point::operator-(const point &p){
    return point(x - p.x, y - p.y , z - p.z);
}
point point::operator*(const point &p){
    double _x = y * p.z - z * p.y;
    double _y = z * p.x - x * p.z;
    double _z = x * p.y - y * p.x;
    return point(_x , _y , _z);
}
point point::operator*(const double p){
    return point(x * p, y * p , z * p);
}
double point::operator%(const point &p){
    return x * p.x + y * p.y + z * p.z;
}
istream &operator>>(istream &is , point &p){
    is >> p.x >> p.y >> p.z;
    return is;
}
point &point::operator=(const point &p){
    x = p.x;
    y = p.y;
    z = p.z;
    r2 = p.r2;
    r = p.r;
    return *this;
}
point point::normal(){
    double l = sqrt(x * x + y * y + z * z);
    if(pre(l) == 1){
        return point(x / l , y / l , z / l);
    }
    return point (0,0,0);
}