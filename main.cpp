#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "include/affinetransformation.h"
#include "include/hough.h"
#include "include/canny.h"
#include "include/stitching.h"

using namespace std;
using namespace cv;

class ImageProcessor {
public:
    void processImage(const string& mode, const vector<string>& imagePaths) {
        if (mode == "affine") {
            if (imagePaths.empty()) {
                cerr << "No image paths provided." << endl;
                return;
            }
            Mat img = imread(imagePaths[0], IMREAD_GRAYSCALE);
            if (img.empty()) {
                cerr << "Could not open the image" << endl;
                return;
            }
            performAffineTransformation(img);
        } else if (mode == "hough") {
            if (imagePaths.empty()) {
                cerr << "No image paths provided." << endl;
                return;
            }
            Mat img = imread(imagePaths[0], IMREAD_GRAYSCALE);
            if (img.empty()) {
                cerr << "Could not open the image" << endl;
                return;
            }
            performHoughTransformation(img);
        } else if (mode == "canny") {
            if (imagePaths.empty()) {
                cerr << "No image paths provided." << endl;
                return;
            }
            Mat img = imread(imagePaths[0], IMREAD_GRAYSCALE);
            if (img.empty()) {
                cerr << "Could not open the image" << endl;
                return;
            }
            performCannyTransformation(img);
        } else if (mode == "stitch") {
            if (imagePaths.size() < 2) {
                cerr << "Insufficient image paths for stitching. Provide at least two image paths." << endl;
                return;
            }
            performImageStitching(imagePaths);
        } else {
            cerr << "Invalid mode. Use 'affine', 'hough', 'canny', or 'stitch'." << endl;
        }
    }

private:
    const string imagePath_;

    void performAffineTransformation(const Mat& img) {
        AffineTransformation affinetransform;

        Mat rotated_img = affinetransform.applyrotation(img, 45);
        Mat translated_img = affinetransform.applytranslation(img, 100, 100);
        Mat sheared_img = affinetransform.applyshear(img, 0.5, 0.5);

        namedWindow("Rotated Image", WINDOW_NORMAL);
        imshow("Rotated Image", rotated_img);
        waitKey(0);
        destroyWindow("Rotated Image");

        namedWindow("Translated Image", WINDOW_NORMAL);
        imshow("Translated Image", translated_img);
        waitKey(0);
        destroyWindow("Translated Image");

        namedWindow("Sheared Image", WINDOW_NORMAL);
        imshow("Sheared Image", sheared_img);
        waitKey(0);
        destroyWindow("Sheared Image");
    }

    void performHoughTransformation(const Mat& img) {
        HoughTransformation houghtransform;

        pair<Mat, Mat> result = houghtransform.applyHoughTransformation(img);

        imshow("Original image", img);
        imshow("Detected Lines (in red) - Standard Hough Line Transform", result.first);
        imshow("Detected Lines (in red) - Probabilistic Line Transform", result.second);
        waitKey(0);
    }

    void performCannyTransformation(const Mat& img) {
        CannyDetection cannydetection;

        Mat imageT = cannydetection.applyCannyDetection(img);

        imshow("Canny Edge Detection", imageT);

        waitKey(0);
    }

    void performImageStitching(const vector<string>& imagePaths) {
        vector<Mat> images;
        for (const string& imagePath : imagePaths) {
            Mat image = imread(imagePath);
            if (image.empty()) {
                cerr << "Could not open the image: " << imagePath << endl;
                return;
            }
            images.push_back(image);
        }

        ImageStitching stitcher;
        Mat stitchedImage = stitcher.stitchImages(images);

        if (!stitchedImage.empty()) {
            namedWindow("Stitched Image", WINDOW_NORMAL);
            imshow("Stitched Image", stitchedImage);
            waitKey(0);
            destroyWindow("Stitched Image");
        } else {
            cerr << "Image stitching failed." << endl;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./app <mode> <image_path1> <image_path2> ... (where <mode> is 'affine', 'hough', 'canny', or 'stitch')" << endl;
        return -1;
    }

    string mode = argv[1];
    vector<string> imagePaths(argv + 2, argv + argc);

    ImageProcessor imageProcessor;
    imageProcessor.processImage(mode, imagePaths);

    return 0;
}
