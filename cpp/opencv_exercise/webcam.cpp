#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// 参考：http://opencv.jp/opencv-2svn/cpp/reading_and_writing_images_and_video.html
int webcam(void)
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
        return -1;

    cv::Mat edges;
    cv::namedWindow("edges", 1);
    for (;;)
    {
        cv::Mat frame;
        cap >> frame; // カメラから新しいフレームを取得
        cv::cvtColor(frame, edges, CV_BGR2GRAY);
        cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);
        cv::Canny(edges, edges, 0, 30, 3);
        cv::imshow("edges", edges);
        if (cv::waitKey(30) >= 0) break;
    }

    return 0;

}