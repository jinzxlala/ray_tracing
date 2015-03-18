//
//  scene.h
//  ray_traicing2
//
//  Created by brightking on 14-6-28.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#ifndef __ray_traicing2__scene__
#define __ray_traicing2__scene__

#include <iostream>
#include "point.h"
#include "line.h"
#include "object.h"
#include "ImageFactory.h"
using namespace std;
class scene{
public:
    point viewpoint , direction , light_source , wdir;
    double width , height;
    int size_x , size_y;
    vector<object*>objects;
    ImageFactory factory;
    Rgb getcolor(line light , int k , double ratio , double dist , double &ret);
    point intersectpoint(line light, int k , object *(&current));
    int in_shade(point p);
    void init();
    Rgb phont_model(point light , point p , point v ,  double ii , object *current , bool flag);
    line reflect_light(line light , point p , object *current);
    line refract_light(line light , point p , object *current , int k);
};

#endif /* defined(__ray_traicing2__scene__) */
