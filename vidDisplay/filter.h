/*
 * Di Zhang
 * Jan 25, 2023
 * CS5330 - Computer Vision
 */

// headers - make vidDisplay.cpp and filter.cpp talk to each other
#include <opencv2/opencv.hpp>

int greyscale(cv::Mat &src, cv::Mat &dst);

int blur5x5( cv::Mat &src, cv::Mat &dst );

int sobelX3x3( cv::Mat &src, cv::Mat &dst );

int sobelY3x3( cv::Mat &src, cv::Mat &dst );

int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst );

int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels );

int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold );

int negative(cv::Mat &src, cv::Mat &dst);

int laplacian(cv::Mat &src, cv::Mat &dst);
