#include "get_image.h"

MynteyeLeftCamera::MynteyeLeftCamera()
{
  std::cout << "MynteyeLeftCamera Construction!" << std::endl;

  if (!util::select(cam_, &dev_info_)) {
    std::cout << "error" << std::endl;
    // return 1;
  }
  util::print_stream_infos(cam_, dev_info_.index);
  std::cout << "we open device: " << dev_info_.index << ", "
            << dev_info_.name << std::endl << std::endl;
  

  params_ = OpenParams(dev_info_.index);
  {
    // Framerate: 10(default usb3.0) 5(default usb2.0), [0,60], [30](STREAM_2560x720)
    params_.framerate = 10;

    // Device mode, default DEVICE_ALL
    //   DEVICE_COLOR: IMAGE_LEFT_COLOR ✓ IMAGE_RIGHT_COLOR ? IMAGE_DEPTH x
    //   DEVICE_DEPTH: IMAGE_LEFT_COLOR x IMAGE_RIGHT_COLOR x IMAGE_DEPTH ✓
    //   DEVICE_ALL:   IMAGE_LEFT_COLOR ✓ IMAGE_RIGHT_COLOR ? IMAGE_DEPTH ✓
    // Note: ✓: available, x: unavailable, ?: depends on #stream_mode
    // params_.dev_mode = DeviceMode::DEVICE_ALL;

    // Color mode: raw(default), rectified
    // params_.color_mode = ColorMode::COLOR_RECTIFIED;

    // Stream mode: left color only
    // params_.stream_mode = StreamMode::STREAM_640x480;  // vga
    params_.stream_mode = StreamMode::STREAM_1280x720;  // hd
    // Stream mode: left+right color
    // params_.stream_mode = StreamMode::STREAM_1280x480;  // vga
    // params_.stream_mode = StreamMode::STREAM_2560x720;  // hd

    // Auto-exposure: true(default), false
    // params_.state_ae = false;

    // Auto-white balance: true(default), false
    // params_.state_awb = false;

    // IR Depth Only: true, false(default)
    // Note: IR Depth Only mode support frame rate between 15fps and 30fps.
    //     When dev_mode != DeviceMode::DEVICE_ALL,
    //       IR Depth Only mode not be supported.
    //     When stream_mode == StreamMode::STREAM_2560x720,
    //       frame rate only be 15fps in this mode.
    //     When frame rate less than 15fps or greater than 30fps,
    //       IR Depth Only mode will be not available.
    // params_.ir_depth_only = true;

    // Infrared intensity: 0(default), [0,10]
    params_.ir_intensity = 4;

    // Colour depth image, default 5000. [0, 16384]
    params_.colour_depth_value = 5000;
  }

  // Enable what process logics
  // cam_.EnableProcessMode(ProcessMode::PROC_IMU_ALL);

  // Enable image infos
  cam_.EnableImageInfo(true);

  cam_.Open(params_);

  std::cout << std::endl;
  if (!cam_.IsOpened()) {
    std::cerr << "Error: Open camera failed" << std::endl;
    // return 1;
  }
  std::cout << "Open device success" << std::endl << std::endl;

  std::cout << "Press ESC/Q on Windows to terminate" << std::endl;

  is_left_ok_ = cam_.IsStreamDataEnabled(ImageType::IMAGE_LEFT_COLOR);

  // if (is_left_ok_) cv::namedWindow("left color");
  
  counter_ = util::Counter(params_.framerate);
  allow_count_ = false;

  // for (int i;;i++) {
  //   cam_.WaitForStream();
  //   char key = static_cast<char>(cv::waitKey(1));

  //   if (is_left_ok_) {
  //     auto left_color = cam_.GetStreamData(ImageType::IMAGE_LEFT_COLOR);
  //     if (left_color.img) {
  //       allow_count_ = true;
  //       cv::Mat left = left_color.img->To(ImageFormat::COLOR_BGR)->ToMat();
  //       painter_.DrawSize(left, CVPainter::TOP_LEFT);
  //       painter_.DrawStreamData(left, left_color, CVPainter::TOP_RIGHT);
  //       painter_.DrawInformation(left, util::to_string(counter_.fps()),
  //           CVPainter::BOTTOM_RIGHT);
  //       cv::imshow("left color", left);
        
        
  //     }
  //   }

  //   if (allow_count_ == true) {
  //     counter_.Update();
  //   }
    
    
  //   if (key == 27 || key == 'q' || key == 'Q') {  // ESC/Q
  //     break;
  //   }
    
  // }


  camera_matrix_ = ReadMatFromTxt("/home/gophield/youlian/github/youlian_ws/src/detection/camera_para/intrinsic.txt",3,3);
  dist_coeffs_ = ReadMatFromTxt("/home/gophield/youlian/github/youlian_ws/src/detection/camera_para/distortion.txt",1,5);

  
}


bool MynteyeLeftCamera::getOriginalImage(cv::Mat& image)
{
  if(is_left_ok_){
    auto left_color = cam_.GetStreamData(ImageType::IMAGE_LEFT_COLOR);
    if (left_color.img) {
      image = left_color.img->To(ImageFormat::COLOR_BGR)->ToMat();
      painter_.DrawSize(image, CVPainter::TOP_LEFT);
      painter_.DrawStreamData(image, left_color, CVPainter::TOP_RIGHT);
      painter_.DrawInformation(image, util::to_string(counter_.fps()),
          CVPainter::BOTTOM_RIGHT);

      // cv::imshow("image color", image);
      
      return true;
    }
    else {
      // std::cout << "Can not get stream data from camera." << std::endl;
      return false;
    }
  }
  else {
    // std::cout << "Camera stream sata is disabled!" << std::endl;
    return false;
  }
}

bool MynteyeLeftCamera::getUndistortedImage(cv::Mat& image)
{
  if(is_left_ok_){
    auto left_color = cam_.GetStreamData(ImageType::IMAGE_LEFT_COLOR);
    if (left_color.img) {
      image = left_color.img->To(ImageFormat::COLOR_BGR)->ToMat();
      painter_.DrawSize(image, CVPainter::TOP_LEFT);
      painter_.DrawStreamData(image, left_color, CVPainter::TOP_RIGHT);
      painter_.DrawInformation(image, util::to_string(counter_.fps()),
          CVPainter::BOTTOM_RIGHT);

      getImageUndistort(image, camera_matrix_, dist_coeffs_);
      
      // cv::imshow("image color", image);
      
      return true;
    }
    else {
      // std::cout << "Can not get stream data from camera." << std::endl;
      return false;
    }
  }
  else {
    // std::cout << "Camera stream sata is disabled!" << std::endl;
    return false;
  }
}


void MynteyeLeftCamera::displayImage(cv::Mat& image) {

  for (int i;;i++) {
    cam_.WaitForStream();
    char key = static_cast<char>(cv::waitKey(1));

    if (is_left_ok_) {
      auto left_color = cam_.GetStreamData(ImageType::IMAGE_LEFT_COLOR);
      if (left_color.img) {
        allow_count_ = true;
        // cv::Mat image = left_color.img->To(ImageFormat::COLOR_BGR)->ToMat();
        image = left_color.img->To(ImageFormat::COLOR_BGR)->ToMat();
        painter_.DrawSize(image, CVPainter::TOP_LEFT);
        painter_.DrawStreamData(image, left_color, CVPainter::TOP_RIGHT);
        painter_.DrawInformation(image, util::to_string(counter_.fps()),
            CVPainter::BOTTOM_RIGHT);
        // cv::imshow("image color", image);
        
        
      }
    }

    if (allow_count_ == true) {
      counter_.Update();
    }
    
    
    if (key == 27 || key == 'q' || key == 'Q') {  // ESC/Q
      break;
    }
    
  }
  
}

cv::Mat MynteyeLeftCamera::ReadMatFromTxt(const std::string& filename, int rows,int cols)
{
    double m;
    cv::Mat out = cv::Mat::zeros(rows, cols, CV_64FC1);//Matrix to store values

    std::ifstream fileStream(filename);
    int cnt = 0;//index starts from 0
    while (fileStream >> m)
    {
        int temprow = cnt / cols;
        int tempcol = cnt % cols;
        out.at<double>(temprow, tempcol) = m;
        cnt++;
    }
    return out;
}


void MynteyeLeftCamera::getImageUndistort(cv::Mat& img_in, const cv::Mat& camera_matrix, const cv::Mat& dist_coeffs) {
    int h = img_in.rows;
    int w = img_in.cols;
    cv::Size_<int> img_size(w,h);
    cv::Rect roi;
    cv::Mat img_undistort;
    cv::Mat newCamImage = cv::getOptimalNewCameraMatrix(camera_matrix, dist_coeffs, img_size,1,img_size,&roi);
    cv::undistort(img_in, img_undistort,camera_matrix, dist_coeffs, newCamImage);
	  img_in = cv::Mat(img_undistort,roi);
}
