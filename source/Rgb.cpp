//
//  Rgb.cpp
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#include "Rgb.h"
#include <iostream>
using namespace std;
Rgb Rgb::operator+(const Rgb &a){
    return Rgb(a.r + r, a.g + g, a.b + b);
}
Rgb Rgb::operator*(double p){
    return Rgb(r * p , g * p , b * p);
}
istream &operator>>(istream &is, Rgb &a){
    is >> a.r >> a.g >> a.b;
    return is;
}
Rgb &Rgb::operator=(const Rgb &a){
    r = a.r;
    g = a.g;
    b = a.b;
    return *this;
}
