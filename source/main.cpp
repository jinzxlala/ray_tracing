//
//  main.cpp
//  ray_traicing2
//
//  Created by brightking on 14-6-27.
//  Copyright (c) 2014年 brightking. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "scene.h"
#include "object.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
using namespace std;
Rgb que[1000][1000];
Rgb ans[1000][1000];
double distan[1000][1000];
const int ali = 1;
const double focus = 7 , range = 5 , pi = 3.141592653;
scene camera;
void work(int i , int j){
    ans[i][j] = Rgb(0,0,0);
    int sum = 0;
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            if(i + dx < camera.size_x && i +dx >= 0 && j + dy < camera.size_y && j +dy >= 0){
                ans[i][j] = ans[i][j] + que[i +dx][j + dy];
                sum++;
            }
        }
    }
    ans[i][j] = ans[i][j] * (1.0/sum);
}
int main(int argc, const char * argv[])
{
    camera.init();
    IplImage *image = cvCreateImage(cvSize(camera.size_x, camera.size_y), IPL_DEPTH_8U, 3);
    cvZero(image);
    cvNamedWindow("ray tracing2");
    char filename[50];
    //int counter = 0;
    double delta = 3.6;
    double theta = 0;
    for(int counter = 0; counter < 100; counter++){
        theta = delta * counter;
        camera.viewpoint = point(8.8 * cos(theta/180.0 * pi) , 8.8 * sin(theta/180.0*pi) , 1.5);
        cout <<camera.viewpoint.x << " " << camera.viewpoint.y << " " << camera.viewpoint.z << endl;
        camera.direction = (point(0,0,1.5) - camera.viewpoint).normal() * 5;
        camera.wdir = (camera.direction * point(0,0,1)).normal();
        sprintf(filename, "1-%d.jpg" , counter);
        cout << filename << endl;
    point dy = camera.wdir.normal();
    point dx = (camera.direction * dy).normal();
    point start = camera.viewpoint + camera.direction - dx *(camera.height * 0.5) - dy * (camera.width * 0.5);
    for(int i = 0 ; i < camera.size_y; i++){
        for(int j = 0 ; j < camera.size_x; j++){
            //printf("%d %d\n" , i, j);
            que[i][j] = Rgb(0,0,0);
            point current0 = start;
            point current;
            for(int di = -ali ;di <= ali; di++){
                for(int dj = -ali; dj <= ali ;dj++){
                    current = current0 + dx * (camera.height * (i + di * 0.5) * (1.0 / camera.size_y))
                    + dy *(camera.width * (j + dj * 0.5) * (1.0 / camera.size_x));
                    /*if(i == 295 &&j == 643){
                        object *test;
                        point another = camera.intersectpoint(line(camera.viewpoint , current), -1, test);
                        cout << another.x <<" " << another.y << " " << another.z << endl;
                        cout << "hello~" << endl;
                        camera.in_shade(another);
                        cout << "========" << endl;
                    }*/
                   //if(i == 431 && j == 394){
                     //  object *test = NULL;
                       // point another = camera.intersectpoint(line(camera.viewpoint , current), -1, test);
                        //cout << "*" << test->face.size() << endl;
                    //}
                    //cout << current.x << " " << current.y << " " << current.z << endl;
                    //cout << current.x << " " << current.y << " " << current.z << endl;;
                    Rgb c = camera.getcolor(line(camera.viewpoint, current), -1, 1, 0, distan[i][j]);
                    //cout << c.r << " " << c.g << " " << c.b << endl;
                    que[i][j] = que[i][j] + c;
                    //cout << que[i][j].r << " " << que[i][j].g << " " << que[i][j].b << endl;
                    //cout << "=============" << endl;
                }
            }
            que[i][j] = que[i][j] * (ali?(1.0/9) : 1);
        }
    }
    cout << "the first work over!" << endl;
    for(int i = 0 ; i < camera.size_y; i++){
        for(int j = 0 ; j < camera.size_x; j++){
            if(pre(distan[i][j] - focus / range) < 0 || pre(distan[i][j] - focus * range) > 0){
                work(i,j);
            }
            else{
                ans[i][j] = que[i][j];
            }
        }
    }
    for(int i = 0 ; i < camera.size_y; i++){
        for(int j = 0 ; j < camera.size_x; j++){
            ans[i][j] = que[i][j];
            //cout << ans[i][j].r << " " << ans[i][j].g << " " << ans[i][j].b << endl;
            CvScalar temp;
            temp.val[0] = ans[i][j].b;
            temp.val[1] = ans[i][j].g;
            temp.val[2] = ans[i][j].r;
            cvSet2D(image, i, j, temp);
        }
    }
    while(1){
        cvShowImage("ray tracing2", image);
        if(cvWaitKey(15) == 27){
            break;
        }
    }
    cvSaveImage(filename, image);
    cout << "the second work over!" << endl;
    }
    while(1){
        cvShowImage("ray tracing2", image);
        if(cvWaitKey(15) == 27){
            break;
        }
    }
    cvReleaseImage(&image);
    cvDestroyWindow("ray tracing2");
    return 0;
}

