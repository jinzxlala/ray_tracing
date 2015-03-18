//
//  Rgb.h
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#ifndef __ray_traicing2__Rgb__
#define __ray_traicing2__Rgb__

#include <iostream>
using namespace std;
class Rgb{
public:
    double r , g , b;
    Rgb(double r0 = 0 , double g0 = 0 , double b0 = 0){
        r = r0 , b = b0, g = g0;
    }
    Rgb operator+(const Rgb &a);
    Rgb operator*(double p);
    Rgb &operator=(const Rgb &a);
    friend istream &operator>>(istream &is , Rgb &a);
};


#endif /* defined(__ray_traicing2__Rgb__) */
