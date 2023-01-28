
/*
 * Di Zhang
 * Jan 25, 2023
 * CS5330 - Computer Vision
 */

#include <iostream>
#include <opencv2/opencv.hpp>

#include "filter.h"

int main(int argc, char *argv[])
{
    cv::VideoCapture *capdev;

    // open the video device
    capdev = new cv::VideoCapture(0);
    if (!capdev->isOpened())
    {
        printf("Unable to open video device\n");
        return (-1);
    }

    // get some properties of the image
    cv::Size refS((int)capdev->get(cv::CAP_PROP_FRAME_WIDTH),
                  (int)capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1); // identifies a window
    cv::Mat frame;
    char checker;
    for (;;)
    {
        *capdev >> frame; // get a new frame from the camera, treat as a stream

        if (frame.empty())
        {
            printf("frame is empty\n");
            break;
        }
        
        // see if there is a waiting keystroke
        char key = cv::waitKey(10);
        if (key == 'q') {
            break;
        }

        // Q3
        // change video to grayscale
        if (key == 'g' || checker == 'g') {
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
            checker = 'g';
        }

        // Q2
        // save the frame at the moment when pressing the 's' key
        if (key == 's') {
            cv::imwrite("capture.png", frame);
        }

        // Q4
        if (key == 'h' || checker == 'h') {
            // allocated new image space for greyscale image
            cv::Mat greyFrame(frame.rows, frame.cols, CV_8UC3);
            // call greyscale function in filter source file
            greyscale(frame, greyFrame);
            frame = greyFrame;
            checker = 'h';
        }

        // Q5
        if (key == 'b' || checker == 'b') {

            //cv::Mat img = cv::imread("lena.png");
            
            cv::Mat gusFrame;
            cv::Mat displayFrame;
            //cv::namedWindow("gusFrame", 1);
            blur5x5(frame, gusFrame);
            
            //cv::convertScaleAbs(gusFrame, displayFrame);
            //cv::imshow("gusFrame", gusFrame);
            //cv::waitKey(0);
            //cv::destroyWindow("gusFrame");
            frame = gusFrame;
            //checker = 'b';
            
        }

        // Q6
        
        if (key == 'x') {
            
        }

        if (key == 'y') {

        }

        // Q7
        if (key == 'm') {

        }

        // Q8
        if (key == 'l') {

        }

        // Q9
        if (key == 'c') {
            
        }
        // change grayscale back to color
        if (key == 'n') {
            checker = '\0';
        }
        cv::imshow("Video", frame);
    }

    delete capdev;
    return (0);
}
/*


*/
