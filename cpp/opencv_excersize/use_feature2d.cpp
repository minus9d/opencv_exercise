/**
* @file use_feature2d
* @brief modification of samples\cpp\tutorial_code\features2D\SURF_descriptor.cpp
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

void drawSurfKeypoints()
{
    cv::Mat img = cv::imread("..\\img\\baboon200.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    int minHessian = 400;
    cv::SurfFeatureDetector detector(0);
    std::vector<cv::KeyPoint> keypoints;
    detector.detect(img, keypoints);

    if (keypoints.empty()) return;

    // keypoint��`��
    cv::Mat dstImg;
    drawKeypoints(
        img, // ���͉摜
        keypoints, // �����_
        dstImg, // �o�͉摜
        cv::Scalar::all(-1), // �F  -1�̏ꍇ�̓����_��?
        cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS // �`��̃I�v�V����  DRAW_RICH_KEYPOINTS��I�񂾏ꍇ�́A�L�[�|�C���g�̃T�C�Y�ƕ������`�悳���
        );
    imshow("Keypoints", dstImg);

    // ���͂�keypoint��`��
    cv::Mat dstImgMine;
    cvtColor(img, dstImgMine, CV_GRAY2BGR);
    for (auto k : keypoints){
        circle(dstImgMine, k.pt, 3, cv::Scalar(255, 0, 0));
    }
    imshow("KeypointsMine", dstImgMine);

    cv::waitKey(0);

    return;
}

void useFeature2d(){

    cv::Mat img_1 = cv::imread("..\\img\\baboon200.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat img_2 = cv::imread("..\\img\\baboon200_rotated.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    if (!img_1.data || !img_2.data)
    {
        return;
    }

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;

    cv::SurfFeatureDetector detector(minHessian);

    std::vector<cv::KeyPoint> keypoints_1, keypoints_2;

    detector.detect(img_1, keypoints_1);
    detector.detect(img_2, keypoints_2);

    //-- Step 2: Calculate descriptors (feature vectors)
    cv::SurfDescriptorExtractor extractor;

    cv::Mat descriptors_1, descriptors_2;

    extractor.compute(img_1, keypoints_1, descriptors_1);
    extractor.compute(img_2, keypoints_2, descriptors_2);

    //-- Step 3: Matching descriptor vectors with a brute force matcher
    cv::BFMatcher matcher(cv::NORM_L2);
    std::vector< cv::DMatch > matches;
    matcher.match(descriptors_1, descriptors_2, matches);

    //-- Draw matches
    cv::Mat img_matches;
    cv::drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_matches);

    //-- Show detected matches
    cv::imshow("Matches", img_matches);

    cv::waitKey(0);

}