/*
 * Di Zhang
 * Jan 25, 2023
 * CS5330 - Computer Vision
 */
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "filter.h"

int greyscale(cv::Mat &src, cv::Mat &dst){
    cv::Mat differentChannels[3];
    cv::split(src, differentChannels);
    cv::Mat b = differentChannels[0];
    cv::Mat g = differentChannels[1];
    cv::Mat r = differentChannels[2];
    differentChannels[1] = differentChannels[0];
    differentChannels[2] = differentChannels[0];
    cv::merge(differentChannels, 3, dst);
    return (0);
}

int blur5x5(cv::Mat &src, cv::Mat &dst) {

    //cv::GaussianBlur(src, dst, cv::Size(5, 5), 0);

    // allocate temp space
    cv::Mat temp;
    temp = cv::Mat::zeros(src.size(), CV_8UC3);
    
    // allocate destination space
    dst = cv::Mat::zeros(src.size(), CV_8UC3);

    // loop through src and apply vertical filter
    // go through rows
    for (int i = 2; i < src.rows-2; i++) {
        
        // source row pointer
        cv::Vec3b *rowptr1 = src.ptr<cv::Vec3b>(i-2);
        cv::Vec3b *rowptr2 = src.ptr<cv::Vec3b>(i-1);
        cv::Vec3b *rowptr3 = src.ptr<cv::Vec3b>(i);
        cv::Vec3b *rowptr4 = src.ptr<cv::Vec3b>(i+1);
        cv::Vec3b *rowptr5 = src.ptr<cv::Vec3b>(i+2);
    
        // destination pointer
        cv::Vec3b *tempptr = temp.ptr<cv::Vec3b>(i);

        // go through columes
        for (int j = 0; j < src.cols; j++) {
    
            // go though each color channels
            for (int k = 0; k < 3; k++) {
                tempptr[j][k] = (1 * rowptr1[j][k] + 2 * rowptr2[j][k] + 4 * rowptr3[j][k] +
                                2 * rowptr4[j][k] + 1 * rowptr5[j][k])/10;
            }
        } 
        
    }

    // loop through temp and apply horizontal filter
    // go through cols
    for (int i = 0; i < temp.rows; i++) {
        
        // temp col pointer
        //cv::Vec3b *rowptr1 = temp.ptr<cv::Vec3b>(i-2);
        //cv::Vec3b *rowptr2 = temp.ptr<cv::Vec3b>(i-1);
        cv::Vec3b *rowptr = temp.ptr<cv::Vec3b>(i);
        //cv::Vec3b *rowptr4 = temp.ptr<cv::Vec3b>(i+1);
        //cv::Vec3b *rowptr5 = temp.ptr<cv::Vec3b>(i+2);
    
        // destination pointer
        cv::Vec3b *destptr = dst.ptr<cv::Vec3b>(i);

        // go through rows
        for (int j = 2; j < temp.cols-2; j++) {
    
            // go though each color channels
            for (int k = 0; k < 3; k++) {
                destptr[j][k] = (1 * rowptr[j-2][k] + 2 * rowptr[j-1][k] + 4 * rowptr[j][k] +
                                2 * rowptr[j+1][k] + 1 * rowptr[j+2][k])/10;
            }
        } 
    }

    return 0;
}

int sobelX3x3( cv::Mat &src, cv::Mat &dst ) {
    return 0;
}

int sobelY3x3( cv::Mat &src, cv::Mat &dst ) {
    return 0;
}

int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ) {
    return 0;
}

int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels ) {
    return 0;
}

int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold ) {
    return 0;
}