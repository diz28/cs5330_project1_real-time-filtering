/*
* name: Di Zhang
* date: Jan 25, 2023
* course: CS5330 - Computer Vision
*/
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
int main(int argc, char *argv[]) {
        cv::VideoCapture *capdev;

        // open the video device
        capdev = new cv::VideoCapture(0);
        if( !capdev->isOpened() ) {
                printf("Unable to open video device\n");
                return(-1);
        }

        // get some properties of the image
        cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                       (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
        printf("Expected size: %d %d\n", refS.width, refS.height);

        cv::namedWindow("Video", 1); // identifies a window
        cv::Mat frame;
        cv::Mat gray;

        for(;;) {
                *capdev >> frame; // get a new frame from the camera, treat as a stream
                if( frame.empty() ) {
                  printf("frame is empty\n");
                  break;
                }                
                cv::imshow("Video", frame);

                // see if there is a waiting keystroke
                char key = cv::waitKey(10);
                if( key == 'q') {
                    break;
                }
                if (key == 's') {
                    cv::imwrite("capture.png", frame);       
                }
                if (key == 'g') {
                    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
                    cv::imshow("Gray", gray);
                    cv::imwrite("gray.png", gray);
                }
        }

        delete capdev;
        return(0);
}