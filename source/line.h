//
//  line.h
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#ifndef __ray_traicing2__line__
#define __ray_traicing2__line__

#include <iostream>
#include "point.h"
using namespace std;
class line{
public:
    point zero, one , dir;
    line();
    line(point a, point b){
        zero = a;
        one = b;
        dir = (one - zero).normal();
    }
    void set(point _zero,  point _dir);
};

#endif /* defined(__ray_traicing2__line__) */
