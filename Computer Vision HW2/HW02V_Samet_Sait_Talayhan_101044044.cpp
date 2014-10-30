#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define THRESH_VALUE 40
RNG rng(12345);

int main(int argc, char* argv[])
{
    VideoCapture cap; // open the default camera

    // argument control
    if(argc != 2)
    {
      cout <<"[-]Resmin yolunu göster hacı." <<endl;
      return 0;
    }

    cout << "[+]File path: " << argv[1] << endl;
    if( !cap.open(argv[1]) )  // check if we succeeded
    {
      std::cout << "[-]File doesnt open!\n";
      return -1;
    }
    cout << "[+]Showing the video." << endl;

    Mat edges;
    namedWindow("edges",CV_WINDOW_AUTOSIZE);
    namedWindow("canny",CV_WINDOW_AUTOSIZE);
    namedWindow("Convex Hull",CV_WINDOW_AUTOSIZE);
    for(;;)
    {
        Mat frame;
        Mat canny;
        Mat threshold_output;
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, CV_BGR2GRAY);
        blur( edges, edges, Size(3,3) );

        /// Detect edges using Threshold
        threshold( edges, threshold_output, THRESH_VALUE, 255, THRESH_BINARY );
        Canny(threshold_output, canny, 0, 30, 3);

        /// Find contours
        findContours( canny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);

        /// Find the convex hull object for each contour
        vector<vector<Point> >hull( contours.size() );
        for( int i = 0; i < contours.size(); i++ )
        {  convexHull( Mat(contours[i]), hull[i], false ); }

        /// Draw contours + hull results
        Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
        for( int i = 0; i< contours.size(); i++ )
        {
          Scalar color = Scalar( 0, 255, 0); //rng.uniform(0,255)
          drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
          drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
        }

        /// Show in a window
        imshow("Convex Hull", drawing );
        imshow("canny", canny);
        imshow("edges", threshold_output);
        if(waitKey(30) >= 0) break;
    }

    cout << "[+]Done." << endl;
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
