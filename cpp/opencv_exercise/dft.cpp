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
void two_d_fft(Mat& padded, cv::Mat& result)
{
    // 実数 + 複素数の分からなる2chの画像を作る
    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    // 2次元dftする
    dft(complexI, complexI);            // this way the result may fit in the source matrix

    // FFTの結果を返す
    result = complexI;

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

// 定義に従い2D DFTする(教科書p15)
// paddedはheight * width * 1ch
void two_d_dft_difinition(Mat& padded, cv::Mat& result_re, cv::Mat& result_im)
{
    cv::Mat img = Mat_<float>(padded);
    result_re = Mat_<float>(padded);
    result_im = Mat_<float>(padded);

   // 定義式からフーリエ変換
   // 時間がかかりすぎるので左上だけ実行
   //for (int h = 0; h < img.rows; ++h)
   for (int h = 0; h < min(img.rows, 5); ++h)
   {
        //for (int w = 0; w < img.cols; ++w)
        for (int w = 0; w < min(img.cols, 5); ++w)
        {
            // X(k, l) = sum_m sum_n { x(m, n) * exp{ -j * 2pi * ( km / M + ln / N ) } }
            complex<float> X = 0.0;
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
                        -2.0 * M_PI * ((double)h * h2 / img.rows + (double)w * w2 / img.cols)
                        )
                        );
                }
            }
            result_re.at<float>(h, w) = X.real();
            result_im.at<float>(h, w) = X.imag();
        }
    }
}

// 定義に従い1D FFT
void one_d_dft_definition(
    const vector<complex<float>>& src,
    vector<complex<float>>& dst)
{
    int size = src.size();
    dst.resize(src.size());

    // 定義式からフーリエ変換
    for (int i = 0; i < size; ++i)
    {
        complex<float> X = 0.0;
        for (int n = 0; n < size; ++n)
        {
            X += src[n] * exp(complex<float>(0.0, -2.0 * M_PI * n * i / size));
        }
        dst[i] = X;
    }
}

// 行に沿って1D FFTを行った後、列に沿って1D FFTすることで高速に2D FFTする(教科書 p89)
void two_d_dft_difinition_fast(Mat& padded, cv::Mat& result_re, cv::Mat& result_im)
{
    cv::Mat img = Mat_<float>(padded);
    result_re = Mat_<float>(padded);
    result_im = Mat_<float>(padded);

    // まず行に沿って1D FFTする
    vector<vector<complex<float>>> one_d_dft_result(img.rows); // 結果格納用

    for (int h = 0; h < img.rows; ++h)
    {
        vector<complex<float>> src;
        for (int w = 0; w < img.cols; ++w)
        {
            src.push_back(img.at<float>(h, w));
        }
        one_d_dft_definition(src, one_d_dft_result[h]);
    }

    // 次に列に沿って1D FFTする
    for (int w = 0; w < img.cols; ++w)
    {
        vector<complex<float>> src;
        for (int h = 0; h < img.rows; ++h)
        {
            src.push_back(one_d_dft_result[h][w]);
        }
        vector<complex<float>> dst;
        one_d_dft_definition(src, dst);

        for (int h = 0; h < img.rows; ++h)
        {
            result_re.at<float>(h, w) = dst[h].real();
            result_im.at<float>(h, w) = dst[h].imag();
        }
    }

    return;
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

    // サンプルによるfft
    cv::Mat result_sample;
    two_d_fft(padded, result_sample);
    vector<Mat> splitted;
    split(result_sample, splitted);

    cout << "[correct fft result]" << endl;
    cout << result_sample(cv::Rect(0, 0, 5, 5)) << endl;
    cout << "[correct fft result(Re)]" << endl;
    cout << splitted[0](cv::Rect(0, 0, 5, 5)) << endl;
    cout << "[correct fft result(Im)]" << endl;
    cout << splitted[1](cv::Rect(0, 0, 5, 5)) << endl;

    // 定義によるfft
    cv::Mat result_re;
    cv::Mat result_im;
    two_d_dft_difinition(padded, result_re, result_im);

    cout << "[dft result by definition(Re)]" << endl;
    cout << result_re(cv::Rect(0, 0, 5, 5)) << endl;
    cout << "[dft result by definition(Im)]" << endl;
    cout << result_im(cv::Rect(0, 0, 5, 5)) << endl;

    // 1D fftを繰り返して2D fft
    two_d_dft_difinition_fast(padded, result_re, result_im);

    cout << "[fast 2d dft(Re)]" << endl;
    cout << result_re(cv::Rect(0, 0, 5, 5)) << endl;
    cout << "[fast 2d dft(Im)]" << endl;
    cout << result_im(cv::Rect(0, 0, 5, 5)) << endl;

    return 0;
}
void dftSample(void)
{
    test();

    opencv_fft_sample();
}