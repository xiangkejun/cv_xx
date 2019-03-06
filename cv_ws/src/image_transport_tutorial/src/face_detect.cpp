#include <ros/ros.h>    //ros系统头文件集合
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h> 
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

//用于人脸检测的模型文件（另附）
const std::string face_cascade_name = "haarcascade_frontalface_alt.xml";
//用于眼睛检测的模型文件（另附）
const std::string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;

//图像显示窗口的标题名称
static const std::string OPENCV_WINDOW = "Image window";

class ImageConverter
{
  //节点句柄
  ros::NodeHandle nh_; 
  //用来发布和订阅ROS系统的图像
  image_transport::ImageTransport it_;
  //订阅主题的变量 
  image_transport::Subscriber image_sub_;
  //发布主题的变量
  image_transport::Publisher image_pub_;

public:
  ImageConverter(): it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/camera/image", 1, &ImageConverter::imageCb2, this); 
    //"/camera/rgb/image_color "为Kinect输出彩色图像的Topic

    //发布主题
    image_pub_ = it_.advertise("/image_converter/output_video", 1);
    
    //加载级联分类器文件
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); };
    
    //命名窗口
    cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }
  
  //订阅主题的回调函数
  void imageCb2(const sensor_msgs::ImageConstPtr& msg)//Callback2
  {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      //将sensor_msgs::Image数据类型转换为cv::Mat类型（即opencv的IplImage格式）
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    
    //至此，ROS图像和OpenCV图像转换完毕
    if(!cv_ptr->image.empty())
    { 
      //利用OpenCV对图像进行处理
      detectAndDisplay(cv_ptr->image);
    }
    else 
    {
      printf(" No captured frame. Break");
    }
    
    cv::waitKey(3);
    
    // Output modified video stream
    image_pub_.publish(cv_ptr->toImageMsg());
  }
  
  //图像处理过程（人脸检测和眼睛检测）
  void detectAndDisplay( Mat frame )
  {
    std::vector<Rect> faces;
    cv::Mat frame_gray;

    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- 多尺寸检测人脸
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( int i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar  ( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- 在每张人脸上检测双眼
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

        for( int j = 0; j < eyes.size(); j++ )
        {
            Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
            int radius = cvRound( (eyes[j].width + eyes[i].height)*0.25 );
            circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    
    //-- 显示结果图像
    imshow( OPENCV_WINDOW, frame );
  }
};

//主函数
int main(int argc, char** argv)
{
  //ros节点的初始化
  ros::init(argc, argv, "image_converter");
  
  //图像获取处理并显示的类，初始化实例的过错即为处理的过程
  ImageConverter ic;
  
  //ros::spin()进入自循环，当ros::ok()返回FALSE时，ros::spin()就立刻跳出循环
  //这很可能是ros::shutdown()被调用，或者用户按下了Ctrl+C退出组合键
  ros::spin();
  
  return 0;
}