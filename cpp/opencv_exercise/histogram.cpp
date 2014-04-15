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

    // ヒストグラムのスケーリング
    // ヒストグラムのbinの中で、頻度数最大のbinの高さが、ちょうど画像の縦幅と同じ値になるようにする
    double max_val = 0.0;
    cv::minMaxLoc(hist, 0, &max_val);
    hist = hist * (max_val ? img_height / max_val : 0.0);

    // ヒストグラムのbinの数だけ矩形を書く
    for (int j = 0; j < nbins; ++j){
        // saturate_castは、安全に型変換するための関数。桁あふれを防止
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
    int hsize[] = { nbins }; // 今回は1次元のヒストグラムを作るので要素数は一つ
    float range[] = { 0, 255 };  // 扱うデータの最小値、最大値　今回は輝度データなので値域は[0, 255]
    const float *ranges[] = { range }; // 今回は1次元のヒストグラムを作るので要素数は一つ
    int chnls[] = { 0 }; // cv::Matの何番目のチャネルを使うか　今回は白黒画像なので0番目のチャネル以外選択肢なし

    // 白黒画像から輝度のヒストグラムデータ（＝各binごとの出現回数をカウントしたもの）を生成
    cv::MatND hist;
    cv::calcHist(&img, 1, chnls, cv::Mat(), hist, 1, hsize, ranges);

    // テキスト形式でヒストグラムデータを確認
    std::cout << hist << std::endl;

    // ヒストグラムデータを表示用の画像に変換
    // OpenCVでは関数が用意されていないので自前で用意する必要がある
    cv::Mat hist_img;
    make_histogram_image(hist, hist_img, nbins);
    cv::imshow("histogram image", hist_img);

    // 画像表示のためのwait
    cv::waitKey(-1);
}