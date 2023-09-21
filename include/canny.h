#include <opencv4/opencv2/core.hpp>

using namespace cv;

class CannyDetection {

    public:
        CannyDetection();
        Mat applyCannyDetection(const Mat& img);

};