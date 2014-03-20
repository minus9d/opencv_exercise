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

cv::Rect box;
bool drawing_box = false;

void draw_box(cv::Mat* img, cv::Rect rect){
    cv::rectangle(*img, cv::Point2d(box.x, box.y), cv::Point2d(box.x + box.width, box.y + box.height),
        cv::Scalar(0xff, 0x00, 0x00));
}

// Implement mouse callback
void my_mouse_callback(int event, int x, int y, int flags, void* param){
    cv::Mat* image = (cv::Mat*)param;

    switch (event){
    case CV_EVENT_MOUSEMOVE:
        if (drawing_box){
            box.width = x - box.x;
            box.height = y - box.y;
        }
        break;

    case CV_EVENT_LBUTTONDOWN:
        drawing_box = true;
        box = cv::Rect(x, y, 0, 0);
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
    box = cv::Rect(-1, -1, 0, 0);

    cv::Mat image(cv::Size(960, 540), CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat temp = image.clone();

    // ウィンドウを生成
    cv::namedWindow(name, CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

    // コールバックを設定
    cv::setMouseCallback(name, my_mouse_callback, (void *)&image);

    // Main loop
    while (1){
        image.copyTo(temp);
        if (drawing_box)
            draw_box(&temp, box);
        cv::imshow(name, temp);

        // Escで終了
        if (cvWaitKey(15) == 27)
            break;
    }

    return 0;
}
