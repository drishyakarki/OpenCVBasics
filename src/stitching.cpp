#include "../include/stitching.h"
#include <opencv2/stitching.hpp>

using namespace cv;
using namespace std;

ImageStitching::ImageStitching() {}

Mat ImageStitching::stitchImages(const vector<Mat>& images) {
    Mat result;
    Ptr<Stitcher> stitcher = Stitcher::create();
    Stitcher::Status status = stitcher->stitch(images, result);

    if (status != Stitcher::OK) {
        return Mat();
    }

    return result;
}
