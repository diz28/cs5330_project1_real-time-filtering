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
        cv::Vec3b *rowptr = temp.ptr<cv::Vec3b>(i);
    
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

// sobelX filter
// [-1, 0, 1]                 [1]
// [-2, 0, 2] = [-1, 0, 1] x  [2]
// [-1, 0, 1]                 [1]
int sobelX3x3( cv::Mat &src, cv::Mat &dst ) {

    // allocate temp space
    cv::Mat temp;
    temp = cv::Mat::zeros(src.size(), CV_16SC3);
    
    // allocate destination space
    dst = cv::Mat::zeros(src.size(), CV_16SC3);

    // loop through src and apply vertical filter
    // go through rows
    for (int i = 1; i < src.rows-1; i++) {
        
        // source row pointer
        cv::Vec3b *rowptr1 = src.ptr<cv::Vec3b>(i-1);
        cv::Vec3b *rowptr2 = src.ptr<cv::Vec3b>(i);
        cv::Vec3b *rowptr3 = src.ptr<cv::Vec3b>(i+1);
    
        // destination pointer
        cv::Vec3s *tempptr = temp.ptr<cv::Vec3s>(i);

        // go through columes
        for (int j = 0; j < src.cols; j++) {
            
            // go though each color channels
            for (int k = 0; k < 3; k++) {
                tempptr[j][k] = (1 * rowptr1[j][k] + 2 * rowptr2[j][k] + 1 * rowptr3[j][k])/4;
            }
        }
    }

    // loop through temp and apply horizontal filter
    // go through rows
    for (int i = 0; i < temp.rows; i++) {

        // temp col pointer
        cv::Vec3s *rowptr = temp.ptr<cv::Vec3s>(i);

        // destination pointer
        cv::Vec3s *destptr = dst.ptr<cv::Vec3s>(i);
        
        // go through rows
        for (int j = 1; j < temp.cols-1; j++) {
            // go though each color channels
            for (int k = 0; k < 3; k++) {
                destptr[j][k] = -1 * rowptr[j-1][k] + 1 * rowptr[j+1][k];
            }
        } 
    }
    
    return 0;
}

// sobelY filter
// [ 1, 2, 1]                [ 1]
// [ 0, 0, 0] = [1, 2, 1] x  [ 0]
// [-1,-2,-1]                [-1]
int sobelY3x3( cv::Mat &src, cv::Mat &dst ) {
     // allocate temp space
    cv::Mat temp;
    temp = cv::Mat::zeros(src.size(), CV_16SC3);
    
    // allocate destination space
    dst = cv::Mat::zeros(src.size(), CV_16SC3);

    // loop through src and apply vertical filter
    // go through rows
    for (int i = 1; i < src.rows-1; i++) {
        
        // source row pointer
        cv::Vec3b *rowptr1 = src.ptr<cv::Vec3b>(i-1);
        cv::Vec3b *rowptr2 = src.ptr<cv::Vec3b>(i);
        cv::Vec3b *rowptr3 = src.ptr<cv::Vec3b>(i+1);
    
        // destination pointer
        cv::Vec3s *tempptr = temp.ptr<cv::Vec3s>(i);

        // go through columes
        for (int j = 0; j < src.cols; j++) {
            
            // go though each color channels
            for (int k = 0; k < 3; k++) {
                tempptr[j][k] = -1 * rowptr1[j][k] + 1 * rowptr3[j][k];
            }
        }
    }

    // loop through temp and apply horizontal filter
    // go through rows
    for (int i = 0; i < temp.rows; i++) {

        // temp col pointer
        cv::Vec3s *rowptr = temp.ptr<cv::Vec3s>(i);

        // destination pointer
        cv::Vec3s *destptr = dst.ptr<cv::Vec3s>(i);
        
        // go through rows
        for (int j = 1; j < temp.cols-1; j++) {
            // go though each color channels
            for (int k = 0; k < 3; k++) {
                destptr[j][k] = (1 * rowptr[j-1][k] + 2 * rowptr[j][k] + 1 * rowptr[j+1][k])/4;
            }
        } 
    }
    
    return 0;
}

int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ) {
    // allocate destination space
    dst = cv::Mat::zeros(sx.size(), CV_16SC3);

    // loop through src and apply vertical filter
    // go through rows
    for (int i = 0; i < sx.rows; i++) {
        
        // source row pointer
        cv::Vec3s *rowptrsx = sx.ptr<cv::Vec3s>(i);
        cv::Vec3s *rowptrsy = sy.ptr<cv::Vec3s>(i);
    
        // destination pointer
        cv::Vec3s *dstptr = dst.ptr<cv::Vec3s>(i);

        // go through columes
        for (int j = 0; j < sx.cols; j++) {
            
            // go though each color channels
            for (int k = 0; k < 3; k++) {
                dstptr[j][k] = sqrt((rowptrsx[j][k] * rowptrsx[j][k]) + (rowptrsy[j][k] * rowptrsy[j][k]));
            }
        }
    }

    return 0;
}

int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels ) {
    cv::Mat blur;
    blur5x5(src, blur);

    // allocates destination space
    dst = cv::Mat::zeros(blur.size(), CV_8UC3);

    // size of buckets
    int bucketSize = 255/levels;

    // loop through blur and apply quantizer
    // go through rows
    for (int i = 0; i < blur.rows; i++) {
        // source pointer
        cv::Vec3b *rowptr = blur.ptr<cv::Vec3b>(i);
        
        // destination pointer
        cv::Vec3b *dstptr = dst.ptr<cv::Vec3b>(i);

        // go through cols
        for (int j = 0; j < blur.cols; j++) {
            for (int k = 0; k < 3; k++) {
                int xt = rowptr[j][k] / bucketSize;
                dstptr[j][k] = xt * bucketSize;
            }
        }
    }
    return 0;
}

int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold ) {

    cv::Mat sobelx;
    cv::Mat sobely;
    cv::Mat mag;
    cv::Mat quantize;

    // get the magnitude image
    sobelX3x3(src, sobelx);
    sobelY3x3(src, sobely);
    magnitude(sobelx, sobely, mag);

    // quantize and blur
    blurQuantize(mag, quantize, levels);

    // allocate destination space
    dst = cv::Mat::zeros(quantize.size(), CV_16SC3);

    for (int i = 0; i < quantize.rows; i++) {
        
        // src pointer
        cv::Vec3b *rowptr = quantize.ptr<cv::Vec3b>(i);

        // destination pointer
        cv::Vec3b *dstptr = dst.ptr<cv::Vec3b>(i);

        for (int j = 0; j < quantize.cols; j++) {
           
            int mmax = std::max(std::max(rowptr[j][0], rowptr[j][1]), rowptr[j][2]);
            if (mmax > magThreshold) {
                dstptr[j][0] = 0;
                dstptr[j][1] = 0;
                dstptr[j][2] = 0;
            } else {
                dstptr[j][0] = rowptr[j][0];
                dstptr[j][1] = rowptr[j][1];
                dstptr[j][2] = rowptr[j][2];
            }
        }

    }
    
    return 0;
}



int negative(cv::Mat &src, cv::Mat &dst) {

    // initilize destination image
    dst = cv::Mat::zeros(src.size(), CV_8UC3);

    for (int i = 0; i < src.rows; i++) {

        // row ptr
        cv::Vec3b *rowptr = src.ptr<cv::Vec3b>(i);
        // destination ptr
        cv::Vec3b *dstptr = dst.ptr<cv::Vec3b>(i);

        for (int j = 0; j < src.cols; j++) {
            dstptr[j][0] = 255 - rowptr[j][0];
            dstptr[j][1] = 255 - rowptr[j][1];
            dstptr[j][2] = 255 - rowptr[j][2];
        }
    }

    

    return 0;
}
