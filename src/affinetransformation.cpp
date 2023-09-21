#include "../include/affinetransformation.h"
#include <math.h>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

AffineTransformation::AffineTransformation() {}

int* AffineTransformation::multiplication(Mat matrix_1, Mat matrix_2)
{
    static int coordinates[3]; //store and return the result of matrix multiplication across multiple function calls without data being destroyed or reallocated wach time the function is called
    
    int x_ = matrix_1.cols;
    int y_ = matrix_1.rows;
    int k = 0;
    
    for(int i=0; i<y_; i++){
    
        coordinates[k] = 0;
    
        for(int j=0; j<x_; j++){
            coordinates[k] += int(matrix_1.at<float>(i,j)*matrix_2.at<int>(j,0)); //matrix multiplication
        }
    
        k++;
    }
    
    return coordinates;
}


Mat AffineTransformation::applytranslation(Mat image, int x_, int y_) {
    int x = image.cols;
    int y = image.rows;

    // Create a new transparent canvas
    Mat imageclone(y + abs(y_), x + abs(x_), CV_8UC4, Scalar(0, 0, 0, 0));

    Mat mulmatrix = (Mat_<float>(3, 3) << 1, 0, x_, 0, 1, y_, 0, 0, 1); // Translation matrix

    int* coordinates;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            coordinates = multiplication(mulmatrix, (Mat_<int>(3, 1) << j, i, 1)); // Calculate new coordinates after translation

            int new_x = *(coordinates) + x_;
            int new_y = *(coordinates + 1) + y_;

            if (new_x >= 0 && new_x < imageclone.cols && new_y >= 0 && new_y < imageclone.rows) {
                Vec3b pixel = image.at<Vec3b>(i, j);
                imageclone.at<Vec4b>(new_y, new_x) = Vec4b(pixel[0], pixel[1], pixel[2], 255); // Set pixel and full opacity
            }
        }
    }

    return imageclone;
}

int* AffineTransformation::finalwidthheight(int x_, int y_, float angle){
    static int value[2];
    float pi = 2 * acos(0); //acos(0) returns value of pi/2
    float radianangle = pi * angle / 180; //converts degree to radians

    int originx = int(x_/2); //calculates the coordinates of the center point of rectangle
    int originy = int(y_/2);
    
    int centrevaluex, centrevaluey; 
    
    //calculates the x-coordinate of center point after rotation by applying trigonometric functions(cosine and sine) to the original center point and angle
    centrevaluex = int(cos(radianangle) * (0 - originx) - sin(radianangle) * (0 - originy));
    centrevaluex = int(((cos(radianangle) * (x_ - originx) - sin(radianangle) * (0 - originy)) >= centrevaluex) ? (cos(radianangle) * (x_ - originx) - sin(radianangle) * (0 - originy)) : centrevaluex);
    centrevaluex = int(((cos(radianangle) * (x_ - originx) - sin(radianangle) * (y_ - originy)) >= centrevaluex) ? (cos(radianangle) * (x_ - originx) - sin(radianangle) * (y_ - originy)) : centrevaluex);
    centrevaluex = int(((cos(radianangle) * (0 - originx) - sin(radianangle) * (y_ - originy)) >= centrevaluex) ? (cos(radianangle) * (0 - originx) - sin(radianangle) * (y_ - originy)) : centrevaluex);
    
    value[0] = centrevaluex * 2 + 1; //after finding maximum value, it computes the new width by multiplying by 2-to account for both sides and adding 1-for odd number
    
    //similar to x
    centrevaluey = int(sin(radianangle) * (0 - originx) + cos(radianangle) * (0 - originy));
    centrevaluey = int(((sin(radianangle) * (x_ - originx) + cos(radianangle) * (0 - originy)) >= centrevaluey) ? (sin(radianangle) * (x_ - originx) + cos(radianangle) * (0 - originy)) : centrevaluey);
    centrevaluey = int(((sin(radianangle) * (x_ - originx) + cos(radianangle) * (y_- originy)) >= centrevaluey) ? (sin(radianangle) * (x_ - originx) + cos(radianangle) * (y_ - originy)) : centrevaluey);
    centrevaluey = int(((sin(radianangle) * (0 - originx) + cos(radianangle) * (y_ - originy)) >= centrevaluey) ? (sin(radianangle) * (0 - originx) + cos(radianangle) * (y_ - originy)) : centrevaluey);
    
    value[1] = centrevaluey * 2 + 1;
    
    return value; //returns the computed width and height as an array
}

Mat AffineTransformation::applyrotation(Mat image, float angle) {
    int x = image.cols;
    int y = image.rows;

    int originx = int(x / 2);
    int originy = int(y / 2);

    int* finalcoordinates = finalwidthheight(x, y, angle); // Retrieve the calculated width and height of the rotated image and store them as an array

    // Create a new transparent canvas
    Mat imageclone(*(finalcoordinates + 1), *(finalcoordinates), CV_8UC4, Scalar(0, 0, 0, 0));

    float pi = 2 * acos(0);
    float radianangle = pi * angle / 180;

    Mat mulmatrix = (Mat_<float>(3, 3) << cos(radianangle), -sin(radianangle), 0, sin(radianangle), cos(radianangle), 0, 0, 0, 1);

    int* coordinates;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            coordinates = multiplication(mulmatrix, (Mat_<int>(3, 1) << (j - originx), (i - originy), 1)); // New coordinates of the current pixel

            int new_x = *(coordinates) + (*(finalcoordinates) - 1) / 2; // Adjust position to center the rotated image
            int new_y = *(coordinates + 1) + (*(finalcoordinates + 1) - 1) / 2;

            if (new_x >= 0 && new_x < imageclone.cols && new_y >= 0 && new_y < imageclone.rows) {
                Vec3b pixel = image.at<Vec3b>(i, j);
                imageclone.at<Vec4b>(new_y, new_x) = Vec4b(pixel[0], pixel[1], pixel[2], 255); // Set pixel with full opacity
            }
        }
    }

    return imageclone;
}

Mat AffineTransformation::applyshear(Mat image, float x_, float y_) {
    int x = image.cols;
    int y = image.rows;

    // Calculate the dimensions of the sheared image
    int newWidth = x + abs(int(y * x_));
    int newHeight = y + abs(int(x * y_));

    // Create a new transparent canvas
    Mat imageclone(newHeight, newWidth, CV_8UC4, Scalar(0, 0, 0, 0));

    Mat mulmatrix = (Mat_<float>(3, 3) << 1, x_, 0, y_, 1, 0, 0, 0, 1); // 3x3 shear matrix

    int* coordinates;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            coordinates = multiplication(mulmatrix, (Mat_<int>(3, 1) << j, i, 1)); // New coordinates after shear

            int new_x = j + int(y_ * i); // Apply shear to the x-axis
            int new_y = i + int(x_ * j); // Apply shear to the y-axis

            if (new_x >= 0 && new_x < newWidth && new_y >= 0 && new_y < newHeight) {
                Vec3b pixel = image.at<Vec3b>(i, j);
                imageclone.at<Vec4b>(new_y, new_x) = Vec4b(pixel[0], pixel[1], pixel[2], 255); // Set pixel and full opacity
            }
        }
    }

    return imageclone;
}
