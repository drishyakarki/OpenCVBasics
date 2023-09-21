# OpenCV Basics
---
## Description
---
In this exercise, I have completed the following tasks:
- installation of opencv
- 2D transformation on images from scratch using matrix multiplication [Rotation, Translation, Shearing] adaptive canvas
- Canny Edge Detection [Gaussian Blur, Dilate, Erode]
- Hough Transformation for Line Detection
- Image Stitching

*All of the affine transformations are implemented from scratch in C++ using openCV*

**Also the transformed images have the background as transparent**

*The project is implemented using OOP concept*

## Affine Transformation
### Translation
Translation involves moving each point of the image by a specified distance in a specific direction. The matrix used for the translation along the x-axis and y-axis by certain distance tx and ty respectively is:

                        [ 1 0 tx ]
                        [ 0 1 ty ]
                        [ 0 0  1 ]
                    

### Rotation
Rotation involves rotating the image by a certain angle θ. The matrix used for counter-clockwise rotation through angle θ is:

                        [ cos(θ) -sin(θ) 0 ]
                        [ sin(θ) cos(θ)  0 ]
                        [ 0          0   1 ]


### Shearing
Shearing is the transformation in which the shape of an object is distorted along one axis while keeping the other axis unchanged. There are two types of shearing: horizontal (along the x-axis) and vertical (along the y-axis). It is described using shearing factors Shx and Shy.

                        [ 1 Shx 0 ]
                        [ Shy 1 0 ]
                        [ 0   0 1 ]

## Canny Edge Detection
Canny edge detection is a widely used image processing technique that aims to identify the edges within an image. Edges in an image represent significant changes in intensity or color and often correspond to object boundaries, making them crucial for various computer vision tasks such as object recognition and image segmentation.

## Hough Transformation
The Hough Transform is a mathematical technique for detecting shapes like lines and circles in images by representing them as parametric equations. It uses an accumulator array to identify patterns, making it a valuable tool in computer vision for tasks such as object detection and image analysis.

## Image Stitching
Image stitching is a computer vision technique that combines multiple images into a larger, seamless panorama or composite image. It aligns and blends overlapping parts of the input images to create a single, coherent output, often used in photography, virtual tours, and panoramic mapping.

## Project Structure
``````
.
├── CMakeLists.txt
├── data
│   ├── a1.png
│   ├── a2.png
│   ├── a3.png
│   ├── check.png
│   └── soduko.png
├── include
│   ├── affinetransformation.h
│   ├── canny.h
│   ├── CMakeLists.txt
│   ├── hough.h
│   └── stitching.h
├── main.cpp
├── README.md
└── src
    ├── affinetransformation.cpp
    ├── canny.cpp
    ├── CMakeLists.txt
    ├── hough.cpp
    └── stitching.cpp
``````

## Prerequisites

To run this project, you'll need to have the following prerequisites installed:

1. **OpenCV**: OpenCV is required for this project. If you haven't installed it yet, you can follow the instructions below:

- Open a terminal window.

- Update the package list to ensure you have the latest information about available packages:
   ```
   sudo apt update
- Install the opencv package:
```
sudo apt install libopencv-dev
```
- After the installation is complete, you can verify the installed OpenCV version with the following command:
```
pkg-config --modversion opencv
```
This command should display the installed OpenCV version.

2. **CMake**: CMake is also required. If it's not already installed on your device, you can install it using the following command:
```
sudo apt-get install cmake
```

---
## How to Run the Project

Follow these steps to run the project:

1. **Download the Code**: Download the project code from the Git repository.

2. **Open the Folder**: Navigate to the folder you just downloaded using the terminal. This folder contains various subfolders and files.

3. **Create build directory**: Run the following command 
```
mkdir build
```
Navigate to the build directory
```
cd build
```

4. **CMake Configuration**: Run the following command to configure CMake for your project:
```
cmake ..
```

5. **Compile the Project**: After configuring CMake, run the `make` command to compile the project. This will generate the executable.

6. **Executable Creation**: The executable named `app` has now been created.

7. **Run the Project**: To check the project's output, run the following command in the terminal:

```
./app
```


7. **Specific Image Processing Mode**: If you want to apply an affine transformation to a specific image, you should provide the path to the image along with the image's name and extension as follows:

```
./app <mode> <image_path1> <image_path2> ... (where <mode> is 'affine', 'hough', 'canny', or 'stitch')
```

8. **Close Windows**: To close all the open windows generated by the project, press the 'esc' key on your keyboard.

---

## Input & Output

The input images are in the data directory

## Follow for more such projects
Drishya Karki# OpenCVBasics
