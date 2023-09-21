#include <opencv4/opencv2/core.hpp>

using namespace cv;

class HoughTransformation {

    public:
        HoughTransformation();
        std::pair<Mat, Mat> applyHoughTransformation(const Mat& img);
};