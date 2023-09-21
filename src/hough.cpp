#include "../include/hough.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

HoughTransformation::HoughTransformation() {}


std::pair<Mat, Mat> HoughTransformation::applyHoughTransformation(const Mat& img) {
    Mat edges;
    Canny(img, edges, 50, 150, 3);

    vector<Vec2f> lines;
    HoughLines(edges, lines, 1, CV_PI / 180, 150, 0, 0);

    Mat cdst;
    cvtColor(edges, cdst, COLOR_GRAY2BGR);

    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
    }

    vector<Vec4i> linesP;
    HoughLinesP(edges, linesP, 1, CV_PI / 180, 50, 50, 10);

    Mat cdstP;
    cvtColor(edges, cdstP, COLOR_GRAY2BGR);

    for (size_t i = 0; i < linesP.size(); i++) {
        Vec4i l = linesP[i];
        line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
    }

    return std::make_pair(cdst, cdstP);
}

