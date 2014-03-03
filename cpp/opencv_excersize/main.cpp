#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ocl/ocl.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_core248d")
#pragma comment(lib, "opencv_highgui248d")
#pragma comment(lib, "opencv_imgproc248d")
#pragma comment(lib, "opencv_ocl248d")
#else
#pragma comment(lib, "opencv_core248")
#pragma comment(lib, "opencv_highgui248")
#pragma comment(lib, "opencv_imgproc248")
#pragma comment(lib, "opencv_ocl248")
#endif

int main(void){
    cv::Mat img(256 * 16, 256 * 16, CV_8UC3);
    return 0;
}