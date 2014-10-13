#include "dft.h"

#include <iostream>
#include <complex>

#define _USE_MATH_DEFINES
#include <cmath>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"  // cv::calcHist

using namespace std;
using namespace cv;


void test(void)
{
    using namespace cv;

    // 次元4の列ベクトル
    const int size = 8;
    cv::Mat vec = (cv::Mat_<double>(size, 1) << 0.2, -0.5, 0.8, 12.0, 2.3, 4.5, -1.2, -0.9);
    cout << vec << endl;

    Mat planes[] = { Mat_<float>(vec), Mat::zeros(vec.size(), CV_32F) };
    Mat vec2;
    merge(planes, 2, vec2);         // Add to the expanded another plane with zeros

    cout << "vec: " << vec2 << endl;

    // それをFFTしたもの
    cv::Mat vec_f;
    cv::dft(vec2, vec_f, cv::DFT_COMPLEX_OUTPUT);
    cout << "fft(vec): " << vec_f << endl;

    // 定義式からフーリエ変換
    for (int i = 0; i < size; ++i)
    {
        complex<double> X = 0.0;
        for (int n = 0; n < size; ++n)
        {
            X += vec.at<double>(n, 0) * exp(complex<double>(0.0, -2.0 * M_PI * n * i / size));
        }
        cout << X << endl;
    }
    
}

// http://docs.opencv.org/trunk/doc/tutorials/core/discrete_fourier_transform/discrete_fourier_transform.html

// サンプルにあった2D FFT
void two_d_fft(Mat& padded)
{
    // 実数 + 複素数の分からなる2chの画像を作る
    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    // 2次元dftする
    dft(complexI, complexI);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    // ReとImに分離する
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    // 複素数の大きさを計算。planes[0]に格納
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    // add oneした後logを取る
    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    // 縦幅・横幅が偶数になるようにする？
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols / 2;
    int cy = magI.rows / 2;

    // 画像を4分割する
    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    // 分割した平面を入れ替える
    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    // 0から1までの範囲に正規化する
    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
    // viewable image form (float between values 0 and 1).

    imshow("spectrum magnitude", magI);
    waitKey(10);
}

// 定義に従い2D DFTする
void two_d_dft_difinition(Mat& padded)
{
    cv::Mat img = Mat_<float>(padded);

    // 定義式からフーリエ変換
    for (int h = 0; h < img.rows; ++h)
    { 
        for (int w = 0; w < img.cols; ++w)
        {
            // X(k, l) = sum_m sum_n { x(m, n) * exp{ -j * 2pi * ( km / M + ln / N ) } }
            complex<double> X = 0.0;
            for (int h2 = 0; h2 < img.rows; ++h2)
            {
                for (int w2 = 0; w2 < img.cols; ++w2)
                {
                    X += img.at<float>(h2, w2)
                        *
                        exp(complex<float>(
                        // Re
                        0.0,
                        // Im
                        -2.0 * M_PI * (h * h2 / img.rows + w * w2 / img.cols)
                        )
                        );
                }
            }
            cout << X << endl;
        }
    }

}

int opencv_fft_sample(void)
{
    const char* filename = "../img/baboon200_rotated.jpg";

    Mat I = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    if (I.empty())
        return -1;
    cout << "original image size: " << I.size() << endl;

    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize(I.rows);
    int n = getOptimalDFTSize(I.cols); // on the border add zero values
    cout << "optimal image size: " << n << " x " << m << endl;
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    // padded imageは右端と下端に黒帯が入る??
    imshow("padded image", padded);
    imshow("original image", I);


    two_d_fft(padded);

    two_d_dft_difinition(padded);

    return 0;
}
void dftSample(void)
{
    test();

    opencv_fft_sample();
}