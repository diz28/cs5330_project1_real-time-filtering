
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
    char recording;

    // create video writer object
    cv::VideoWriter record("record.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 5, cv::Size(refS.width, refS.height));

    int noarg = argc;
    for (;;)
    {
        if (noarg > 1) {
            frame = cv::imread(argv[1]);
        } else {
            *capdev >> frame; // get a new frame from the camera, treat as a stream
        }

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

            cv::Mat gusFrame;
            blur5x5(frame, gusFrame);
            frame = gusFrame;
            checker = 'b';
            
        }

        // Q6    
        if (key == 'x' || checker == 'x') {
            cv::Mat displayFrameX;
            cv::Mat sobelxFrame;
            sobelX3x3(frame, sobelxFrame);
            cv::convertScaleAbs(sobelxFrame, displayFrameX);
            frame = displayFrameX;
            checker = 'x';
        }

        if (key == 'y' || checker == 'y') {
            cv::Mat displayFrameY;
            cv::Mat sobelyFrame;
            sobelY3x3(frame, sobelyFrame);
            cv::convertScaleAbs(sobelyFrame, displayFrameY);
            frame = displayFrameY;
            checker = 'y';
        }

        // Q7
        if (key == 'm' || checker == 'm') {

            cv::Mat magFrame;
            cv::Mat displayFrame;
            cv::Mat sobelX;
            cv::Mat sobelY;
            sobelX3x3(frame, sobelX);
            sobelY3x3(frame, sobelY);
            magnitude(sobelX, sobelY, magFrame);       
            cv::convertScaleAbs(magFrame, displayFrame);
            frame = displayFrame;
            checker = 'm';
            
        }

        // Q8
        if (key == 'l' || checker == 'l') {
            cv::Mat quanFrame;
            blurQuantize(frame, quanFrame, 10);
            frame = quanFrame;
            checker = 'l';            
        }

        // Q9
        if (key == 'c' || checker == 'c') {
            cv::Mat cartoonFrame;
            cv::Mat displayFrame;

            // cartoon(src, dest, levels, magThreadhold);
            cartoon(frame, cartoonFrame, 10, 25);
            frame = cartoonFrame;
            checker = 'c';
            
        }

        // Q10
        // display a negative image
        if (key == 'o' || checker == 'o') {
            
            cv::Mat negFrame;
            negative(frame, negFrame);
            frame = negFrame;
            checker = 'o';
        }

        // extensions
        // start recording
        if (key == 'r' || recording == 'r') {
            record.write(frame);
            recording = 'r';
        }

        // stop recording
        if (key == 'z') {
            record.release();
            recording = '\0';
            std::string filename;
            std::string avi = ".avi";
            while (true) {
                std::cout << "Enter recording name: ";
                std::getline(std::cin, filename);
                int result = rename("record.avi", (filename + avi).c_str());
                if (result == 0) {
                    break;
                }
            }
        }    
        
        // Q2
        // save the frame at the moment when pressing the 's' key
        if (key == 's') {
            cv::imwrite("capture.png", frame);

            std::string filename;
            std::string png = ".png";
            while (true) {
                std::cout << "Enter image name: ";
                std::getline(std::cin, filename);
                int result = rename("capture.png", (filename + png).c_str());
                if (result == 0) {
                    break;
                }
            }
        }

        // undo filters back to normal
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
