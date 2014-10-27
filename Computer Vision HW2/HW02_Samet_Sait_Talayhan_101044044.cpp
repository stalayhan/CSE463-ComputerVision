/**
 * CSE 665/463 Computer Vision HW2
 *
 * 1-) Binarization of the input image. Using a skin color filter, then
 *     thresholding techniques.
 *
 * 2-) Find the contours in the binary image.
 *
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
#include <iostream>

using namespace cv;
using namespace std;

/// Global variables
int threshold_value = 0;
int threshold_type = 0;		// Binary Threshold

int thresh = 100;
int max_thresh = 255;

int const max_value = 255;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
const char* window_name = "Computer Vision HW01";
const char* trackbar_value = "Value";


RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

/**
 * @function main
 */
int main(int argc, char** argv)
{
    /*
    VideoCapture capture;

    if (argc == 2) {
        capture.open(atoi(argv[1])); // open the external camera.
    }else{
        capture.open(0); // open the default camera.
    }


    if (!capture.isOpened()) { // check camera
        return -1;
    }
    */

    if(argc != 2)
    {
      printf("[-]Resmin yolunu göster hacı.\n");
      return 0;
    }

    /// Load an image
    src = imread( argv[1], CV_LOAD_IMAGE_COLOR );

    // Convert image to gray and blur it.
    cvtColor(src, src_gray, CV_RGB2GRAY);
    blur( src_gray, src_gray, Size(3,3) );

    /// Create a window to display results
    namedWindow(window_name, CV_WINDOW_AUTOSIZE);

    /// Create Trackbar to choose type of Threshold
    /* createTrackbar(trackbar_value,
            window_name, &threshold_value,
            max_value);
    */

    createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );

    imshow(window_name, src);  //show our image inside it.

  /*

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
    */

    waitKey(0);
    return 0;
}

/** @function thresh_callback */
void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< (int)contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}
