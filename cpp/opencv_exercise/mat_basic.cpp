#include "mat_basic.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

void matBasic(void)
{
    cv::Mat img = cv::imread("..\\img\\board.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // http://book.mycom.co.jp/support/pc/opencv2/c3/opencv_mat.html#mat-various-properties

    // 行数
    std::cout << "rows: " << img.rows << std::endl;
    // 列数
    std::cout << "cols: " << img.cols << std::endl;


    // 次元数（画像なので縦・横の2次元）
    std::cout << "dims: " << img.dims << std::endl;
    // サイズ（2次元の場合）
    std::cout << "size[]: " << img.size().width << "," << img.size().height << std::endl;
    // ビット深度ID
    std::cout << "depth (ID): " << img.depth() << "(=" << CV_8U << ")" << std::endl;
    // チャンネル数
    std::cout << "channels: " << img.channels() << std::endl;
    // （複数チャンネルから成る）1要素のサイズ [バイト単位]
    std::cout << "elemSize: " << img.elemSize() << "[byte]" << std::endl;
    // 1要素内の1チャンネル分のサイズ [バイト単位]
    std::cout << "elemSize1 (elemSize/channels): " << img.elemSize1() << "[byte]" << std::endl;
    // タイプ
    std::cout << "type (ID): " << img.type() << "(=" << CV_8UC3 << ")" << std::endl;
    // 要素の総数
    std::cout << "total: " << img.total() << std::endl;
    // ステップ数 [バイト単位]
    std::cout << "step: " << img.step << "[byte]" << std::endl;
    // 1ステップ内のチャンネル総数
    std::cout << "step1 (step/elemSize1): " << img.step1() << std::endl;
    // データは連続か？
    std::cout << "isContinuous: " << (img.isContinuous() ? "true" : "false") << std::endl;
    // 部分行列か？
    std::cout << "isSubmatrix: " << (img.isSubmatrix() ? "true" : "false") << std::endl;
    // データは空か？
    std::cout << "empty: " << (img.empty() ? "true" : "false") << std::endl;

}
