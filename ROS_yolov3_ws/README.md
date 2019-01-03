# ROS_yolov3
在自定义数据集上训练yolov3，并封装到ROS中作为一个节点


roslaunch darknet_ros darknet_ros_xx.launch 

roslaunch darknet_ros darknet_ros.launch

rosrun image_transport_tutorial my_publisher loadedtrunk.jpg    //图片放在src同级目录下
rosrun image_transport_tutorial my_publisher 3.jpg 

在cv_ws 空间下
rosrun video_transport_tutorial video_publisher

rosrun rqt_image_view rqt_image_view 
