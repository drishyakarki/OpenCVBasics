cmake_minimum_required(VERSION 3.10)

project(affinetransform VERSION 1.0)

#setting c++ standard to be c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#to locate opencv library
find_package(OpenCV REQUIRED)

#including necessary directories for opencv as well as my project's include directory
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#adding subdirectories for both "include" and "src"
add_subdirectory(include)
add_subdirectory(src)

#to gather list of source files from src directory
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# executable file
add_executable(app
    main.cpp
    src/affinetransformation.cpp  
    src/hough.cpp                 
    src/canny.cpp
    src/stitching.cpp
)
target_link_libraries(app ${OpenCV_LIBS})

# adding the binary and source directories  for including headers without specifying full paths
target_include_directories(app PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/include")
