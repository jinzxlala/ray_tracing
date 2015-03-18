//
//  object.cpp
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#include "object.h"
int object::getx(point p){
    double ans = (p.x + 10) + p.z;
    return ans *30;
}
int object::gety(point p){
    double ans = p.x + 10 - p.z;
    return ans * 30;
}
point object::norm(point p){
    if(isball){
        return (p - center).normal();
    }
    return c_face.norm();
}
bool object::intersect(line l){return true;}
double object::intersecttime(line l , int k){
    double ans = inf;
    if(isball){
        return xray(l);
    }
    for(int i = 0 ; i < face.size(); i++){
        if(k && pre(face[i].n % l.dir) != k)continue;
        double temp = face[i].xray(l);
        if(ans > temp){
            ans = temp;
            c_face = face[i];
        }
    }
    return ans;
}

double object::xray(line light){
    double ans = inf;
    point l = center - light.zero;
    double tp = l % light.dir;
    double d2 = l.r2 - tp * tp;
    double temp = sqrt(radius * radius - d2);
    if(d2 <= radius * radius){
        if(l.r2 >= radius *radius){
            if(tp - temp > 0){
                ans = tp - temp;
            }
        }
        else{
            if(tp + temp > 0){
                ans =tp + temp;
            }
        }
    }
    return ans;
}
