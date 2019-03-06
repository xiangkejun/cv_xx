//读取视频

#include <opencv2/opencv.hpp>
using namespace cv;

int main(){

    VideoCapture capture("/home/xx/ros_space_xx/cv_ws/1.mp4");

    while (true) {
        Mat frame;
        Mat edge;
        capture >> frame;

        if (frame.empty())
            break;

        cvtColor(frame, edge, COLOR_BGR2GRAY);

        // blur(edge, edge, Size(7,7));

        // Canny(edge, edge, 10, 30);

        imshow("Video", frame);
        imshow("After canny", edge);

        //等待50ms，如果从键盘输入的是q、Q、或者是Esc键，则退出
        int key = waitKey(50);
        if (key == 'q' || key == 'Q' || key == 27)
            break;
    }

    return 0;
}
