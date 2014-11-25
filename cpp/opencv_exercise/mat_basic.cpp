#include "mat_basic.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

void matBasic(void)
{
    cv::Mat img = cv::imread("..\\img\\board.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // http://book.mycom.co.jp/support/pc/opencv2/c3/opencv_mat.html#mat-various-properties

    // �s��
    std::cout << "rows: " << img.rows << std::endl;
    // ��
    std::cout << "cols: " << img.cols << std::endl;


    // �������i�摜�Ȃ̂ŏc�E����2�����j
    std::cout << "dims: " << img.dims << std::endl;
    // �T�C�Y�i2�����̏ꍇ�j
    std::cout << "size[]: " << img.size().width << "," << img.size().height << std::endl;
    // �r�b�g�[�xID
    std::cout << "depth (ID): " << img.depth() << "(=" << CV_8U << ")" << std::endl;
    // �`�����l����
    std::cout << "channels: " << img.channels() << std::endl;
    // �i�����`�����l�����琬��j1�v�f�̃T�C�Y [�o�C�g�P��]
    std::cout << "elemSize: " << img.elemSize() << "[byte]" << std::endl;
    // 1�v�f����1�`�����l�����̃T�C�Y [�o�C�g�P��]
    std::cout << "elemSize1 (elemSize/channels): " << img.elemSize1() << "[byte]" << std::endl;
    // �^�C�v
    std::cout << "type (ID): " << img.type() << "(=" << CV_8UC3 << ")" << std::endl;
    // �v�f�̑���
    std::cout << "total: " << img.total() << std::endl;
    // �X�e�b�v�� [�o�C�g�P��]
    std::cout << "step: " << img.step << "[byte]" << std::endl;
    // 1�X�e�b�v���̃`�����l������
    std::cout << "step1 (step/elemSize1): " << img.step1() << std::endl;
    // �f�[�^�͘A�����H
    std::cout << "isContinuous: " << (img.isContinuous() ? "true" : "false") << std::endl;
    // �����s�񂩁H
    std::cout << "isSubmatrix: " << (img.isSubmatrix() ? "true" : "false") << std::endl;
    // �f�[�^�͋󂩁H
    std::cout << "empty: " << (img.empty() ? "true" : "false") << std::endl;

}
