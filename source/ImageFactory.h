//
//  ImageFactory.h
//  ray_traicing2
//
//  Created by brightking on 14-6-29.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#ifndef __ray_traicing2__ImageFactory__
#define __ray_traicing2__ImageFactory__

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include "Rgb.h"
using namespace std;
class ImageFactory{
public:
    int number;
    IplImage *image[15];
    void init(int k);
    Rgb getRgb(int k , int size_x , int size_y);
};
#endif /* defined(__ray_traicing2__ImageFactory__) */
