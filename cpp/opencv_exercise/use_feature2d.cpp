/**
* @file use_feature2d
* @brief modification of samples\cpp\tutorial_code\features2D\SURF_descriptor.cpp
*/

#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

/**
@brief SURF�Ō��o���������_���摜�ɏd�􂵂ĕ\��
*/
void drawSurfKeypoints()
{
    cv::Mat img = cv::imread("..\\img\\baboon200.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // �����_�����o
    int minHessian = 400;
    cv::SurfFeatureDetector detector(minHessian);
    std::vector<cv::KeyPoint> keypoints;
    detector.detect(img, keypoints);

    if (keypoints.empty()) return;

    // response�l�̍ŏ��E�ő���擾
    double response_min = (keypoints.end() - 1)->response;
    double response_max = keypoints[0].response;

    // Window��Trackbar�𐶐�
    const std::string window_name = "Keypoints";
    cv::namedWindow(window_name, CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);
    int trackbar_value = response_min;
    cv::createTrackbar("res.", window_name, &trackbar_value, response_max + 1);

    while (1)
    {
        int more_than_trackbar_value_index = -1;
        for (int i = 0; i < keypoints.size(); ++i)
        {
            if (keypoints[i].response >= trackbar_value) {
                more_than_trackbar_value_index = i;
            }
        }

        // keypoint��`��
        cv::Mat dstImg = img.clone();

        if (more_than_trackbar_value_index != -1)
        {
            // ���݂�Trackbar�̒l�ȏ�̓����_�݂̂�\��
            cv::drawKeypoints(
                img, // ���͉摜
                std::vector<cv::KeyPoint>(
                    keypoints.begin(),
                    keypoints.begin() + more_than_trackbar_value_index + 1), // �����_
                dstImg, // �o�͉摜
                cv::Scalar(0, 0, 255), // �F
                cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS // �`��̃I�v�V����  DRAW_RICH_KEYPOINTS��I�񂾏ꍇ�́A�L�[�|�C���g�̃T�C�Y�ƕ������`�悳���
                );
        }

        cv::imshow(window_name, dstImg);

        // Esc�ŏI��
        if (cv::waitKey(15) == 27)
            break;
    }


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