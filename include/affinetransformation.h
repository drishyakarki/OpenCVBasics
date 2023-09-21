#include <opencv4/opencv2/core.hpp>

using namespace cv;

class AffineTransformation{
    
    public: 
        AffineTransformation();
        Mat applytranslation(Mat image,int x_,int y_);
        Mat applyrotation(Mat image,float angle);
        Mat applyshear(Mat image,float x_,float y_);
        Mat initializeAdaptiveCanvas(const Mat& image);
    
    private: 
        int* multiplication(Mat matrix_1,Mat matrix_2);
        int* finalwidthheight(int x_,int y_,float angle);
};