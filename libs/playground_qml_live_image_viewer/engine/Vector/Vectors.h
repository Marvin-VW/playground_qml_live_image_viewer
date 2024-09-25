// Copyright (C) 2024 Marvin-VW
#include "../Shape/Shape.h"

#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>
#include <set>

class Vectors {

public:
    cv::Mat vector(const cv::Mat& point1, const cv::Mat& point2);
    std::tuple<cv::Mat, cv::Mat> normal(triangle& tri, float scale = 0.5f);

};
