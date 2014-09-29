/**
 * CSE 665/463 Computer Vision HW1
 * 
 * Program get a frame from the web cam and apply binary
 * thresholding to the image, continue doing this until
 * user enters ESC.
 * 
 * Created by Samet Sait Talayhan - 101044044
 */

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
int threshold_value = 0;
int threshold_type = 0;		// Binary Threshold

int const max_value = 255;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
const char* window_name = "Computer Vision HW01";
const char* trackbar_value = "Value";


/**
 * @function main
 */
int main(int argc, char** argv) {
    
    VideoCapture capture;
    
    if (argc == 2) {
        capture.open(atoi(argv[1])); // open the external camera.
    }else{
        capture.open(0); // open the default camera.
    }

    
    if (!capture.isOpened()) { // check camera
        return -1;
    }

    /// Create a window to display results
    namedWindow(window_name, CV_WINDOW_AUTOSIZE);

    /// Create Trackbar to choose type of Threshold
    createTrackbar(trackbar_value,
            window_name, &threshold_value,
            max_value);



    while (true) {
        capture >> src; // get a new frame from camera

        /// Convert the image to Gray
        cvtColor(src, src_gray, CV_RGB2GRAY);

        /// Call the function to threshold process
        threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
	    if (!dst.empty())
	    {
	    	imshow(window_name, dst);
	    }

        /// Wait until user finishes program
        int c;
        c = waitKey(20);
        if ((char) c == 27) {
            break;
        }
    }

}