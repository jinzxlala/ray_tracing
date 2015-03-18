//
//  pre.cpp
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#include "pre.h"
int pre(double x){
    if(x > eps){
        return 1;
    }
    if(x < eps){
        return -1;
    }
    return 0;
}