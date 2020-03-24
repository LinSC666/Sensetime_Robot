#ifndef VISUALIZATION_H_
#define VISUALIZATION_H_

#include <string>

#include <grid_map_cv/grid_map_cv.hpp>
#include <grid_map_ros/grid_map_ros.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat RenderGridMap(const grid_map::GridMap& grid_map,
                      const std::string& layer);

#endif  // VISUALIZATION_H_