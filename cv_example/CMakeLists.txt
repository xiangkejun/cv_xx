cmake_minimum_required(VERSION 2.8)

#SET(OpenCV_DIR "/home/xx/opencv_build/opencv-3.4.4/build")
project(cv_example)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)
find_package(OpenCV REQUIRED)

include_directories(
  include
  #/usr/include/
)
add_executable(RGB_fenge  src/RGB_fenge.cpp )
 target_link_libraries(RGB_fenge
   ${OpenCV_LIBS}
 )

 add_executable(video_save  src/video_save.cpp )
 target_link_libraries(video_save
   ${OpenCV_LIBS}
 )
