#include "visualization.h"

cv::Mat RenderGridMap(const grid_map::GridMap& grid_map,
                      const std::string& layer) {
    cv::Mat gridmap_image(grid_map.getSize()(0), grid_map.getSize()(1), CV_8UC3,
                          cv::Scalar(0, 0, 0));
    const grid_map::Matrix& data = grid_map[layer];
    for (grid_map::GridMapIterator iterator(grid_map); !iterator.isPastEnd();
         ++iterator) {
        const grid_map::Index index(*iterator);

        float value = data(index(0), index(1));
        if (std::isnan(value)) {
            gridmap_image.at<cv::Vec3b>(index(0), index(1))[0] = 255;
        } else if (value == 0) {
            gridmap_image.at<cv::Vec3b>(index(0), index(1))[1] = 255;
        } else if (value == 100) {
            gridmap_image.at<cv::Vec3b>(index(0), index(1))[2] = 255;
        } else if (value == 200) {
            gridmap_image.at<cv::Vec3b>(index(0), index(1))[0] = 255;
            gridmap_image.at<cv::Vec3b>(index(0), index(1))[2] = 255;
        } else {
            gridmap_image.at<cv::Vec3b>(index(0), index(1))[1] = value;
            gridmap_image.at<cv::Vec3b>(index(0), index(1))[2] = value;
        }
    }
    return gridmap_image;
}