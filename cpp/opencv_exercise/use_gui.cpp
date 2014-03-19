/**
    @brief GUI sample. original: http://dasl.mem.drexel.edu/~noahKuntz/openCVTut3.html#Step%201
*/

#include <iostream>
#include <vector>

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/legacy/compat.hpp>

using namespace cv;

void my_mouse_callback(int event, int x, int y, int flags, void* param);

CvRect box;
bool drawing_box = false;

void draw_box(IplImage* img, CvRect rect){
    cvRectangle(img, cvPoint(box.x, box.y), cvPoint(box.x + box.width, box.y + box.height),
        cvScalar(0xff, 0x00, 0x00));
}

// Implement mouse callback
void my_mouse_callback(int event, int x, int y, int flags, void* param){
    IplImage* image = (IplImage*)param;

    switch (event){
    case CV_EVENT_MOUSEMOVE:
        if (drawing_box){
            box.width = x - box.x;
            box.height = y - box.y;
        }
        break;

    case CV_EVENT_LBUTTONDOWN:
        drawing_box = true;
        box = cvRect(x, y, 0, 0);
        break;

    case CV_EVENT_LBUTTONUP:
        drawing_box = false;
        if (box.width < 0){
            box.x += box.width;
            box.width *= -1;
        }
        if (box.height < 0){
            box.y += box.height;
            box.height *= -1;
        }
        draw_box(image, box);
        break;
    }
}

int useGUI(void)
{
    const char* name = "Box Example";
    box = cvRect(-1, -1, 0, 0);

    IplImage* image = cvCreateImage(cvSize(960, 540), IPL_DEPTH_8U, 3);;
    cvZero(image);
    IplImage* temp = cvCloneImage(image);

    cvNamedWindow(name);

    // Set up the callback
    cvSetMouseCallback(name, my_mouse_callback, (void*)image);

    // Main loop
    while (1){
        cvCopyImage(image, temp);
        if (drawing_box)
            draw_box(temp, box);
        cvShowImage(name, temp);

        if (cvWaitKey(15) == 27)
            break;
    }

    cvReleaseImage(&image);
    cvReleaseImage(&temp);
    cvDestroyWindow(name);

    return 0;
}
