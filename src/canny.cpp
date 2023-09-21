#include "../include/canny.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

CannyDetection::CannyDetection() {}

Mat CannyDetection::applyCannyDetection(const Mat& img) {

        Mat blurredImg;
        GaussianBlur(img, blurredImg, Size(5, 5), 1.5, 1.5);

        Mat edges;
        Canny(blurredImg, edges, 50, 150);

        Mat dilatedEdg, erodedEdg;
        dilate(edges, dilatedEdg, Mat(), Point(-1, -1), 2);
        erode(dilatedEdg, erodedEdg, Mat(), Point(-1, -1), 2);

        imshow("Canny Edge Detection", erodedEdg);
        waitKey(0);

        return erodedEdg;
}
