
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include<unistd.h>    //延时  

using namespace cv;
using namespace std;
int low_r=0, low_g=0, low_b=0;  //纯黑
int high_r=50, high_g=50, high_b=50;

// int low_r=240, low_g=0, low_b=0;  //纯红
// int high_r=250, high_g=0, high_b=0;
Mat img_threshold;
int  x, y, w, h;
int main(int argc, char **argv)
{
    Mat img;
    // use default camera as video source
    VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH ,640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    while(1){
              // get one frame from camera to know frame size and type
    cap >> img;
    // check if we succeeded
    if (img.empty()) {
        cerr << "ERROR! blank frame grabbed\n";
        return -1;
    }

   //imshow("Original", img); 
   	//颜色空间转换 
	//cvtColor(bgr, hsv, COLOR_BGR2HSV);
    inRange(img,Scalar(low_b,low_g,low_r), Scalar(high_b,high_g,high_r),img_threshold);
    imshow("range",img_threshold);

// //用绿色(0, 255, 0)来画出最小的矩形框架
    Rect rect = boundingRect(img_threshold); 
     x = rect.x;
     y = rect.y;
     w = rect.width;
     h = rect.height;
    rectangle(img, Point(x, y), Point(x+w, y+h), Scalar(0, 255, 0),2);  //画矩形
    circle(img,Point(x+w/2,y+h/2),5,Scalar(0,0,200),1);  //画圆
    
    // 显示坐标
    char label[2];
    sprintf(label,"(%d,%d)",x+w/2,y+h/2);  //
    putText(img, label, Point(x+w/2, y+h/2), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 255),1);


    // rectangle(img, Rect(1, 1,100, 100), Scalar(200, 0, 0),5);
    imshow("tangle",img);
    waitKey(30); //延时30ms 

    }
}
