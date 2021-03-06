#include "opencv2/core/core.hpp"
#include "mat_basic.h"
#include "use_feature2d.h"
#include "use_gui.h"
#include "histogram.h"
#include "webcam.h"
#include "dft.h"

// get version
#define CV_VERSION_STR CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)

// add a suffix
#ifdef _DEBUG
#define CV_EXT_STR "d.lib"
#else
#define CV_EXT_STR ".lib"
#endif

#pragma comment(lib, "opencv_core"            CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_highgui"        CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_imgproc"  CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_calib3d"  CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_gpu"   CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_video"   CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_objdetect"  CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_features2d" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_flann"   CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_ffmpeg"  CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_ts"   CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_contrib"  CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_ml"   CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_legacy"  CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_nonfree" CV_VERSION_STR CV_EXT_STR)

#include <iostream>
/**
* @function main
* @brief Main function
*/
int main(int argc, char** argv)
{
    //std::cout << cv::getBuildInformation() << std::endl;

    matBasic();
    //drawSurfKeypoints();
    //useFeature2d();
    //trackbarSample();
    //showLuminanceHistogramImage();
    //webcam();
    //dftSample();
    return 0;
}

