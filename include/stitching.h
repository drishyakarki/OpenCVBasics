#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

class ImageStitching {
public:
    ImageStitching();

    Mat stitchImages(const vector<Mat>& images);
};
