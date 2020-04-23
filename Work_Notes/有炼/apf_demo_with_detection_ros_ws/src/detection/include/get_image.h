#ifndef GET_IMAGE_H
#define GET_IMAGE_H

#include<iostream>
#include <fstream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "mynteyed/camera.h"
#include "mynteyed/utils.h"

#include "util/cam_utils.h"
#include "util/counter.h"
#include "util/cv_painter.h"

MYNTEYE_USE_NAMESPACE

class MynteyeLeftCamera {
public:
    MynteyeLeftCamera();
    ~MynteyeLeftCamera(){};
    
    void displayImage(cv::Mat& image);
    bool getOriginalImage(cv::Mat& image);
    bool getUndistortedImage(cv::Mat& image);
    void wattForStream() { cam_.WaitForStream(); };
private:
    Camera cam_;
    DeviceInfo dev_info_;
    CVPainter painter_;
    OpenParams params_;
    bool is_left_ok_;
    util::Counter counter_;
    bool allow_count_;

    cv::Mat camera_matrix_;
    cv::Mat dist_coeffs_;

    cv::Mat ReadMatFromTxt(const std::string& filename, int rows,int cols);
    void getImageUndistort(cv::Mat& img_in, const cv::Mat& camera_matrix, const cv::Mat& dist_coeffs);
    
};


#endif
