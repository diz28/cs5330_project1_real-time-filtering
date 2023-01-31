
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
    // capture live cam video stream
    cv::VideoCapture *capdev;

    // open the video device
    capdev = new cv::VideoCapture(0);
    
    // error checking
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
    
    // frame - live stream frame or image fream
    cv::Mat frame;
    // flag - help to keep the filter alive
    char checker;
    // flag - help to keep the recording running
    char recording;

    // create video writer object
    cv::VideoWriter record("record.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 5, cv::Size(refS.width, refS.height));

    // no. of command line parameters
    int noarg = argc;
    for (;;)
    {
        // checking if user want to use live cam stream or image
        if (noarg > 1) {
            frame = cv::imread(argv[1]);
        } else {
            *capdev >> frame; // get a new frame from the camera, treat as a stream
        }

        // error check
        if (frame.empty()) {
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
            // use opencv function to change img to greyscale
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
            checker = 'g';
        }

        // Q4
        if (key == 'h' || checker == 'h') {
            // initilize parameters
            cv::Mat greyFrame;
            // call greyscale function in filter source file
            greyscale(frame, greyFrame);
            // shallow copy converted frame back to 'frame'
            frame = greyFrame;
            checker = 'h';
        }

        // Q5
        if (key == 'b' || checker == 'b') {
            // initilize parameters
            cv::Mat gusFrame;
            // convert frame to greyscale using function built from scrach
            blur5x5(frame, gusFrame);
            // shallow copy converted frame back to 'frame'm
            frame = gusFrame;
            checker = 'b';
            
        }

        // Q6    
        if (key == 'x' || checker == 'x') {
            // initilize parameters
            cv::Mat displayFrameX;
            cv::Mat sobelxFrame;
            // filter function
            sobelX3x3(frame, sobelxFrame);
            cv::convertScaleAbs(sobelxFrame, displayFrameX);
            frame = displayFrameX;
            checker = 'x';
        }

        if (key == 'y' || checker == 'y') {
            // initilize parameters
            cv::Mat displayFrameY;
            cv::Mat sobelyFrame;
            // filter function
            sobelY3x3(frame, sobelyFrame);
            // convert negative values to positive for display purposes
            cv::convertScaleAbs(sobelyFrame, displayFrameY);
            frame = displayFrameY;
            checker = 'y';
        }

        // Q7
        if (key == 'm' || checker == 'm') {
            // initilize parameters
            cv::Mat magFrame;
            cv::Mat displayFrame;
            cv::Mat sobelX;
            cv::Mat sobelY;
            // use previous functions to calculate maginitude
            sobelX3x3(frame, sobelX);
            sobelY3x3(frame, sobelY);
            // call mag function to filter image
            magnitude(sobelX, sobelY, magFrame);
            // convert negative values to positive for display purposes
            cv::convertScaleAbs(magFrame, displayFrame);
            frame = displayFrame;
            checker = 'm';
            
        }

        // Q8
        if (key == 'l' || checker == 'l') {
            // initilize parameters
            cv::Mat quanFrame;
            // call blurQuantize function to filter image
            blurQuantize(frame, quanFrame, 10);
            frame = quanFrame;
            checker = 'l';            
        }

        // Q9
        if (key == 'c' || checker == 'c') {
            // initilize parameters
            cv::Mat cartoonFrame;
            cv::Mat displayFrame;

            // cartoon(src, dest, levels, magThreadhold);
            // call cartoon function to filter image
            cartoon(frame, cartoonFrame, 10, 25);
            frame = cartoonFrame;
            checker = 'c';
            
        }

        // Q10
        // display a negative image
        if (key == 'o' || checker == 'o') {
            
            // initilize parameters
            cv::Mat negFrame;
            // call negative function to filter image
            negative(frame, negFrame);
            frame = negFrame;
            checker = 'o';
        }

        // extensions

        // laplacian filter
        // another edge detecter filer
        if (key == 'p' || checker == 'p') {
            // initilize parameters
            cv::Mat lapFrame;
            cv::Mat displayFrame;
            // call lapFunction
            laplacian(frame, lapFrame);
            // convert negtive to positives
            cv::convertScaleAbs(lapFrame, displayFrame);
            frame = displayFrame;
            checker = 'p';
        }

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
        
        // undo filters back to normal
        if (key == 'n') {
            checker = '\0';
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
        // show image in window
        cv::imshow("Video", frame);
    }
    delete capdev;
    return (0);
}
/*


*/
