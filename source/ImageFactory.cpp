//
//  ImageFactory.cpp
//  ray_traicing2
//
//  Created by brightking on 14-6-29.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#include "ImageFactory.h"
void ImageFactory::init(int k){
    number = k;
    for(int i = 0 ; i < k; i++){
        image[i] = cvLoadImage((char(i + '0') + string(".jpg")).c_str());
    }
}
CvScalar tt;
Rgb ImageFactory::getRgb(int k, int size_x, int size_y){
    //cout << image[k]->width << endl;
    //cout << image[k]->height << endl;
    size_x %= image[k]->width;
    size_y %= image[k]->height;
    if(size_x < 0){
        size_x += image[k]->width;
    }
    if(size_y < 0){
        size_y += image[k]->height;
    }
    tt = cvGet2D(image[k], size_y, size_x);
    return Rgb(tt.val[2] , tt.val[1] , tt.val[0]);
}