#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"  // cv::calcHist

// �Q�l
// http://laconsigna.wordpress.com/2011/04/29/1d-histogram-on-opencv/
// http://opencv.jp/cookbook/opencv_img.html


// �q�X�g�O�����f�[�^��\���p�̉摜�ɕϊ�
void make_histogram_image(cv::MatND& hist, cv::Mat& hist_img, int nbins)
{
    // histogram��`�悷�邽�߂̉摜�̈���m��
    int img_width = 512;
    int img_height = 512;
    hist_img = cv::Mat(cv::Size(img_width, img_height), CV_8UC3);

    // �q�X�g�O�����̃X�P�[�����O
    // �q�X�g�O������bin�̒��ŁA�p�x���ő��bin�̍������A���傤�ǉ摜�̏c���Ɠ����l�ɂȂ�悤�ɂ���
    double max_val = 0.0;
    cv::minMaxLoc(hist, 0, &max_val);
    hist = hist * (max_val ? img_height / max_val : 0.0);

    // �q�X�g�O������bin�̐�������`������
    for (int j = 0; j < nbins; ++j){
        // saturate_cast�́A���S�Ɍ^�ϊ����邽�߂̊֐��B�����ӂ��h�~
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

    // �q�X�g�O�����𐶐����邽�߂ɕK�v�ȃf�[�^
    int nbins = 64; // �q�X�g�O�����̃r���̐�
    int hsize[] = { nbins }; // �����1�����̃q�X�g�O���������̂ŗv�f���͈��
    float range[] = { 0, 255 };  // �����f�[�^�̍ŏ��l�A�ő�l�@����͋P�x�f�[�^�Ȃ̂Œl���[0, 255]
    const float *ranges[] = { range }; // �����1�����̃q�X�g�O���������̂ŗv�f���͈��
    int chnls[] = { 0 }; // cv::Mat�̉��Ԗڂ̃`���l�����g�����@����͔����摜�Ȃ̂�0�Ԗڂ̃`���l���ȊO�I�����Ȃ�

    // �����摜����P�x�̃q�X�g�O�����f�[�^�i���ebin���Ƃ̏o���񐔂��J�E���g�������́j�𐶐�
    cv::MatND hist;
    cv::calcHist(&img, 1, chnls, cv::Mat(), hist, 1, hsize, ranges);

    // �e�L�X�g�`���Ńq�X�g�O�����f�[�^���m�F
    std::cout << hist << std::endl;

    // �q�X�g�O�����f�[�^��\���p�̉摜�ɕϊ�
    // OpenCV�ł͊֐����p�ӂ���Ă��Ȃ��̂Ŏ��O�ŗp�ӂ���K�v������
    cv::Mat hist_img;
    make_histogram_image(hist, hist_img, nbins);
    cv::imshow("histogram image", hist_img);

    // �摜�\���̂��߂�wait
    cv::waitKey(-1);
}