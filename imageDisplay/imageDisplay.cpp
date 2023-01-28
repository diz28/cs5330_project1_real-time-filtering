/*
 * Di Zhang
 * Jan 25, 2023
 * CS5330 - Computer Vision
 */
#include <opencv2/highgui.hpp>
#include <iostream>
int main( int argc, char** argv )
{
    cv::Mat image;
    image = cv::imread("Lena.jpg",cv::IMREAD_ANYCOLOR);
    if(image.empty()) {
        std::cout<<"Could not open file" << std::endl;
        return -1;
    }
    cv::namedWindow("puppy image", cv::WINDOW_NORMAL);
    cv::resizeWindow("puppy image", 500, 500),
    cv::imshow("puppy image", image);

    while (true) {
        int k =  cv::waitKey(0);
        if (k == 'q') {
            break;
        } else if (k == 'Q') {
            break;
        }
    }
    return 0;
}
