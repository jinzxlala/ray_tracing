//
//  triangle.cpp
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#include "triangle.h"
double triangle::xray(point zero, point dir){
    double t = inf;
    double temp = -(d + n % zero)/(n % dir);
    if(pre(temp) > 0){;
        point p0 = zero + dir * temp;
        if(intriangle(p0)){
            t = temp;
        }
    }
    return t;
}
triangle::triangle(){}
bool triangle::intriangle(point test){
    point e0 = p1 - p0;
    point e1 = p2 - p0;
    point e2 = test - p0;
    double u = ((e1 % e1) * (e2 % e0) - (e1 % e0) * (e2 % e1))/((e0 % e0) * (e1 % e1) - (e1 % e0) *(e0 % e1));
    double v = ((e0 % e0) * (e2 % e1) - (e0 % e1) * (e2 % e0))/((e0 % e0) * (e1 % e1) - (e1 % e0) * (e0 % e1));
    if(u >= 0 && v >= 0 && u + v <= 1){
        return true;
    }
    return false;
    //point e0 = p0 - test , e1 = p1 - test , e2 = p2 - test;
    //point ee0 = e0 * e1 , ee1 = e1 * e2, ee2 = e2 * e0;
    //return pre(ee0 % ee1) >= 0 && pre(ee1 % ee2) >= 0 && pre(ee2 % ee0) >= 0;
}
double triangle::xray(line l){
    double t = inf;
    //cout << "hello~" << endl;
    if(n % l.dir == 0){
        return t;
    }
    double temp = -(d + n % l.zero)/(n % l.dir);
    if(pre(temp)> 0){
        point p0 = l.zero + l.dir * temp;
        if(intriangle(p0)){
            t = temp;
        }
    }
    return t;
}
point triangle::norm(){
    n = ((p1 - p0) * (p2 - p0)).normal();
    //cout << n.x << " " << n.y << " " << n.z << endl;
    return n;
}
istream &operator>>(istream &is , triangle &p){
    is >>p.p0;
    is >> p.p1;
    is >> p.p2;
    p.n = p.norm();
    p.d = -(p.n % p.p0);
    return is;
}
triangle &triangle::operator=(triangle &p){
    p0 = p.p0;
    p1 = p.p1;
    p2 = p.p2;
    n = p.n;
    d = p.d;
    return *this;
}