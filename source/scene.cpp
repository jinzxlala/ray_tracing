//
//  scene.cpp
//  ray_traicing2
//
//  Created by brightking on 14-6-28.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#include "scene.h"
#include <fstream>
#include <cmath>
using namespace std;
Rgb scene::phont_model(point light, point p, point v, double ii, object *current , bool flag){
    point n = current->norm(p);
    point l = (light - p).normal();
    v = point(0,0,0) - v;
    point h = ((l + v) * 0.5).normal();
    double f = current->rhoa + current->rhod *(n % l) + current->rhos * pow(n % h , current->s);
    f *= ii;
    Rgb origin_color;
    if(current->image_number == -1){
        origin_color = current->color;
    }
    else{
        //cout << "image_number = " << current->image_number << endl;
        origin_color = factory.getRgb(current->image_number, current->getx(p), current->gety(p));
    }
    return Rgb(f, f, f) + origin_color;
}

line scene::reflect_light(line light, point p, object *current){
    point n = current->norm(p);
    point dir = light.dir;
    point new_dir = dir - n * ((dir % n) * 2);
    return line(p, p + new_dir);
}
line scene::refract_light(line light, point p, object *current, int k){
    point n = current->norm(p);
    point dir = light.dir;
    double norm_lenth = -(dir % n);
    double sini , sinr , cosr;
    if(pre(fabs(norm_lenth) - 1) >= 0){
        sini = 0;
    }
    else{
        sini = sqrt(1 - norm_lenth * norm_lenth);
    }
    if(k == -1){
        sinr = sini / current->refraction_ratio;
    }
    else{
        sinr = sini * current->refraction_ratio;
    }
    if(pre(fabs(sinr) - 1) == 0){
        cosr = 0;
    }
    else{
        cosr = sqrt(1 - sinr * sinr);
    }
    if(k == 1){
        cosr = -cosr;
    }
    point cdir = (dir + n * norm_lenth).normal();
    return line(p , p + cdir * sinr - n * cosr);
}
point scene::intersectpoint(line light, int k, object *(&current)){
    double ans = inf;
    for(int i = 0 ; i < objects.size();i++){
        double temp = objects[i]->intersecttime(light, k);
        if(ans > temp){
            ans = temp;
            current = objects[i];
        }
    }
    return light.zero + light.dir * ans;
}
const double stopratio = 0.01, dark_color = -0.3 , init_light = 400;
Rgb refract;
Rgb scene::getcolor(line light, int k, double ratio, double dist, double &ret){
    if(ratio < stopratio){
        return Rgb(0,0,0);
    }
    object *current;
    point p = intersectpoint(light, k, current);
    if(p.r2 > inf || current == NULL){
        return Rgb(0,0,0);
    }
    double dis = dist + (p - light.zero).r;
    ret = dis;
    double another_dist = dis + (p - light_source).r ;
    double temped = 0;
    if(!current){
        return Rgb(0,0,0);
    }
    double ref_c;
    if(current	==(object *)0xbff0000000000000 || current == (object*)0x3ff0000000000000){
        return Rgb(-30, -30 , -30);
    }
    else{
        ref_c = ratio * current->decrease_ratio * current->reflection_ratio ;
    }
    if(ref_c <= 0){
        ref_c = 0;
    }
    line temp = refract_light(light, p, current, k);
    if(temp.zero.r2 < inf){
        refract = getcolor(temp, -k, ratio * (1 - current->reflection_ratio), dis, ret);
    }
    else{
        refract = Rgb(0,0,0);
        ref_c += ratio * (1 - current->reflection_ratio);
    }
    Rgb reflect = getcolor(reflect_light(light, p, current), k, ref_c, dis, temped);
    Rgb ans = phont_model(light_source, p, light.dir, init_light / pow(another_dist , 2), current, 0);
    double shade_c =  (dark_color * in_shade(p) + 1);
    ans = ans * shade_c;
    return ans * ratio + reflect + refract;
}
object *ppt;
int scene::in_shade(point p){
    //cout << p.x << " " << p.y << " " << p.z << endl;
    line light = line(light_source , p);
    //object *ppt = NULL;
    ppt = NULL;
    point temp = intersectpoint(light, 0, ppt);
    if(!ppt){
        return 0;
    }
   // cout << temp.x << " " << temp.y << " " << temp.z << endl;
    if(pre((p - temp).r) > 0){
        //cout << "WTF!!!" << endl;
        //cout << ppt->reflection_ratio << endl;
        if(pre(ppt->reflection_ratio - 1) >= 0){
            return 1;
        }
        return 2;
    }
    else{
        return 0;
    }
}
void scene::init(){
    ifstream fin("data.txt");
    int picture_number;
    fin >> picture_number;
    factory.init(picture_number);
    fin >> light_source >> viewpoint >> direction >> wdir;
    fin >> width >> height >> size_x >> size_y;
    int n;
    fin >> n;
    for(int i = 0 ;i < n ; i++){
        object *data = new object();
        int k = 0;
        fin >> data->isball;
        fin >> k;
        //cout << "k = " << k << endl;
        fin >> data->rhoa >> data->rhod >> data->rhos >> data->s;
        fin >> data->decrease_ratio >> data->reflection_ratio >> data->refraction_ratio;
        fin >> data->image_number;
        fin >> data->color;
        fin >> data->center;
        fin >> data->radius;
        triangle temp;
        data->face.clear();
        for(int j = 0 ; j < k; j++){
            fin >> temp;
            //cout << temp.p0.x << " " << temp.p0.y << " " << temp.p0.z << endl;
            //cout << temp.p1.x << " " << temp.p1.y << " " << temp.p1.z << endl;
           // cout << temp.p2.x << " " << temp.p2.y << " " << temp.p2.z << endl;
            //point e1 = temp.p1 - temp.p0;
            //point e2 = temp.p2 - temp.p0;
            //cout << e1.x <<" " << e1.y << " " << e1.z << endl;
            //cout << e2.x << " " << e2.y << " " << e2.z << endl;
            //cout << temp.norm().x << " " << temp.norm().y << " " << temp.norm().z << endl;
            data->face.push_back(temp);
        }
        objects.push_back(data);
    }
}























