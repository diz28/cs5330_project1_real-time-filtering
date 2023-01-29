
/*
 * Di Zhang
 * Jan 25, 2023
 * CS5330 - Computer Vision
 */

#include <iostream>
#include <opencv2/opencv.hpp>

#include "filter.h"

using namespace std;

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

    cv::Mat square = cv::imread("square.png"); 
    cv::Mat lena = cv::imread("lena.png");

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
            
            blur5x5(frame, gusFrame);
            
            //cv::convertScaleAbs(gusFrame, displayFrame);
            //cv::imshow("gusFrame", gusFrame);
            //cv::waitKey(0);
            //cv::destroyWindow("gusFrame");
            frame = gusFrame;
            checker = 'b';
            
        }

        // Q6    
        if (key == 'x' || checker == 'x') {
            cv::Mat displayFrameX;
            cv::Mat sobelxFrame;
            cv::namedWindow("sobelxFrame", 1);
            sobelX3x3(square, sobelxFrame);
            cv::convertScaleAbs(sobelxFrame, displayFrameX);

            cv::imshow("sobelxFrame", displayFrameX);
            //displayFrameX.copyTo(frameXCopy);
            //frame = displayFrameX;
            checker = 'x';
        }

        if (key == 'y' || checker == 'y') {
            cv::Mat displayFrameY;
            cv::Mat sobelyFrame;
            cv::namedWindow("sobelyFrame", 1);
            sobelY3x3(square, sobelyFrame);
            cv::convertScaleAbs(sobelyFrame, displayFrameY);
            cv::imshow("sobelyFrame", displayFrameY);
            //frame = displayFrameY;
            checker = 'y';
        }

        // Q7
        if (key == 'm' || checker == 'm') {

            cv::Mat magFrame;
            cv::Mat displayFrame;
            cv::Mat sobelX;
            cv::Mat sobelY;
            sobelX3x3(square, sobelX);
            sobelY3x3(square, sobelY);

            cv::namedWindow("magWindows", 1);
            magnitude(sobelX, sobelY, magFrame);       
            cv::convertScaleAbs(magFrame, displayFrame);
            cv:imshow("magWindows", displayFrame);
            checker = 'm';
            
        }

        // Q8
        if (key == 'l' || checker == 'l') {
            cv::Mat quanFrame;
            cv::Mat displayFrame;
            cv::Mat blurLena;

            cv::Size sizel = lena.size();
            cout << "lean height " << sizel.height << endl;

            cv::namedWindow("quanWindows", 1);
            blur5x5(lena, blurLena);

            cv::Size sizeb = blurLena.size();
            cout << "blurLena height " << sizeb.height << endl;

            blurQuantize(blurLena, quanFrame, 15);

            cv::Size sizeq = quanFrame.size();
            cout << "quanFranme height " << sizeq.height << endl;
            cv::convertScaleAbs(quanFrame, displayFrame);
            cv::imshow("quanWindows", displayFrame);

            checker = 'l';            
        }

        // Q9
        if (key == 'c') {
            
        }

        // Additional taskes
        
        // brightness adjustment
        

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
