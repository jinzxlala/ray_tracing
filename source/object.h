//
//  object.h
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#ifndef __ray_traicing2__object__
#define __ray_traicing2__object__

#include <iostream>
#include <cmath>
#include <vector>
#include "point.h"
#include "line.h"
#include "triangle.h"
#include "Rgb.h"
using namespace std;
class object{
public:
    vector<triangle> face;
    bool isball;
    int image_number;
    Rgb color;
    point center;
    double radius;
    double rhoa , rhos, rhod ,s;
    double decrease_ratio , reflection_ratio, refraction_ratio;
    triangle c_face;
    object(Rgb rgb = Rgb(), double rr = 1){
        color = rgb;
        reflection_ratio = rr;
    }
    bool intersect(line l);
    double intersecttime(line l , int k);
    point norm(point p);
    double xray(line light);
    int getx(point p);
    int gety(point p);
};
#endif /* defined(__ray_traicing2__object__) */
