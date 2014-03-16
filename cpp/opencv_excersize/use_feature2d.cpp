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

using namespace cv;
using namespace std;


void findAllSurfKeypoints()
{
    Mat img = imread("..\\img\\baboon200.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    // しきい値関係なくすべての点を抽出
    int minHessian = 0;
    SurfFeatureDetector detector(0);
    std::vector<KeyPoint> keypoints;
    detector.detect(img, keypoints);

    if (keypoints.empty()) return;

    // スコアの最小値と最大値を取得
    float minRespone = keypoints[0].response;
    float maxRespone = keypoints[0].response;
    for (auto p : keypoints){
        minRespone = min(minRespone, p.response);
        maxRespone = max(maxRespone, p.response);
    }

    Mat dstImg;

    // keypointを描画
    // all(-1)にすると色が自動で選択される
    drawKeypoints(img, keypoints, dstImg, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imshow("Keypoints", dstImg);
    waitKey(0);

    return;
}

void useFeature2d(){

    Mat img_1 = imread("..\\img\\baboon200.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img_2 = imread("..\\img\\baboon200_rotated.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    if (!img_1.data || !img_2.data)
    {
        return;
    }

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;

    SurfFeatureDetector detector(minHessian);

    std::vector<KeyPoint> keypoints_1, keypoints_2;

    detector.detect(img_1, keypoints_1);
    detector.detect(img_2, keypoints_2);

    //-- Step 2: Calculate descriptors (feature vectors)
    SurfDescriptorExtractor extractor;

    Mat descriptors_1, descriptors_2;

    extractor.compute(img_1, keypoints_1, descriptors_1);
    extractor.compute(img_2, keypoints_2, descriptors_2);

    //-- Step 3: Matching descriptor vectors with a brute force matcher
    BFMatcher matcher(NORM_L2);
    std::vector< DMatch > matches;
    matcher.match(descriptors_1, descriptors_2, matches);

    //-- Draw matches
    Mat img_matches;
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_matches);

    //-- Show detected matches
    imshow("Matches", img_matches);

    waitKey(0);

}