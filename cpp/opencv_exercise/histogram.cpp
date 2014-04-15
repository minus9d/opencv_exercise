#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"  // cv::calcHist

// 参考
// http://laconsigna.wordpress.com/2011/04/29/1d-histogram-on-opencv/
// http://opencv.jp/cookbook/opencv_img.html


// ヒストグラムデータを表示用の画像に変換
void make_histogram_image(cv::MatND& hist, cv::Mat& hist_img, int nbins)
{
    // histogramを描画するための画像領域を確保
    int img_width = 512;
    int img_height = 512;
    hist_img = cv::Mat(cv::Size(img_width, img_height), CV_8UC3);

    double max_val = 0.0;
    cv::minMaxLoc(hist, 0, &max_val);

    // スケーリング
    hist = hist * (max_val ? img_height / max_val : 0.0);

    for (int j = 0; j < nbins; ++j){
        int bin_w = cv::saturate_cast<int>((double)img_width / nbins);
        cv::rectangle(
            hist_img,
            cv::Point(j*bin_w, hist_img.rows),
            cv::Point((j + 1)*bin_w, hist_img.rows - cv::saturate_cast<int>(hist.at<float>(j))),
            cv::Scalar::all(0), -1);
    }
}

void showLuminanceHistogramImage()
{
    cv::Mat img = cv::imread("..\\img\\baboon200.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // ヒストグラムを生成するために必要なデータ
    int nbins = 64; // ヒストグラムのビンの数
    int hsize[] = { nbins }; // just one dimension
    float range[] = { 0, 255 };
    const float *ranges[] = { range };
    int chnls[] = { 0 };

    // 白黒画像から輝度のヒストグラムデータを生成
    cv::MatND hist;
    cv::calcHist(&img, 1, chnls, cv::Mat(), hist, 1, hsize, ranges);


    short b = cv::saturate_cast<short>(3333.33333);
    uchar a = cv::saturate_cast<uchar>(-100);

    cv::Mat hist_img;
    make_histogram_image(hist, hist_img, nbins);
    cv::imshow("histogram image", hist_img);

    std::cout << hist << std::endl;

    cv::waitKey(-1);

}