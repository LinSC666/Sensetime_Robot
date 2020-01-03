#include <iostream>
#include <sstream>
#include <ctime>
#include <gflags/gflags.h>

#include <ros/ros.h>
#include <am_msgs/DetectionResult.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/cudaarithm.hpp"

#include "lawn_perceptor.hpp"

std::vector<std::vector<cv::Point>> visualizeSegmentation(cv::Mat &im,
                                            cv::Mat seg_mask,
                                            cv::Scalar color) {
    cv::Mat img_draw = im.clone();
    cv::Mat colorboard(im.size(), CV_8UC3, color);
    colorboard.copyTo(img_draw, seg_mask);
    cv::addWeighted(im, 0.5, img_draw, 0.5, 0, im);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(seg_mask, contours, hierarchy, CV_RETR_CCOMP,
                    CV_CHAIN_APPROX_SIMPLE);
    cv::drawContours(im, contours, -1, color, 3);
    return contours;
}

void visualizeDetections(cv::Mat &frame, // NOLINT(runtime/references)
                        const std::vector<Perception::Object> &bboxes,
                        const std::vector<float> &threshes) {
    const int kNumColors = 3;
    int colors[kNumColors]
                [3] = {{145, 205, 222}, {127, 127, 255}, {127, 255, 127}};

    // Appearance
    int r = 0;
    float len_ratio = 0.2f;
    int thickness = 3;
    float alpha = 0.4f;

    for (size_t i = 0; i < bboxes.size(); ++i) {
        int label = bboxes[i].label;
        float score = bboxes[i].confidence;
        // Ignore if score is less than thresh
        float thresh = (threshes.size() == 1) ? threshes.at(0) : threshes.at(label);
        if (score > thresh) {
        float x1 = bboxes[i].bounding_box.x;
        float y1 = bboxes[i].bounding_box.y;
        float x2 = bboxes[i].bounding_box.x + bboxes[i].bounding_box.width;
        float y2 = bboxes[i].bounding_box.y + bboxes[i].bounding_box.height;

        float box_h = y2 - y1 + float(1.0);
        float box_w = x2 - x1 + float(1.0);
        float d = std::min(box_h, box_w) * len_ratio;

        // Draw bounding box
        int red = colors[label % kNumColors][0];
        int green = colors[label % kNumColors][1];
        int blue = colors[label % kNumColors][2];

        cv::Scalar color(blue, green, red);

        // Copy the source image to an overlay
        cv::Mat overlay = frame.clone();

        // Draw a filled rectangle on the overlay copy
        cv::rectangle(overlay, cv::Point(x1 + d * 0.25, y1 + d * 0.25),
                        cv::Point(x2 - d * 0.25, y2 - d * 0.25), color, -1);
        // Blend the overlay with the source image
        cv::addWeighted(overlay, alpha, frame, 1 - alpha, 0, frame);

        // Top left
        cv::line(frame, cv::Point(x1 + r, y1), cv::Point(x1 + r + d, y1), color,
                thickness);
        cv::line(frame, cv::Point(x1, y1 + r), cv::Point(x1, y1 + r + d), color,
                thickness);
        cv::ellipse(frame, cv::Point(x1 + r, y1 + r), cv::Point(r, r), 180, 0, 90,
                    color, thickness);

        // Top right
        cv::line(frame, cv::Point(x2 - r, y1), cv::Point(x2 - r - d, y1), color,
                thickness);
        cv::line(frame, cv::Point(x2, y1 + r), cv::Point(x2, y1 + r + d), color,
                thickness);
        cv::ellipse(frame, cv::Point(x2 - r, y1 + r), cv::Point(r, r), 270, 0, 90,
                    color, thickness);

        // Bottom left
        cv::line(frame, cv::Point(x1 + r, y2), cv::Point(x1 + r + d, y2), color,
                thickness);
        cv::line(frame, cv::Point(x1, y2 - r), cv::Point(x1, y2 - r - d), color,
                thickness);
        cv::ellipse(frame, cv::Point(x1 + r, y2 - r), cv::Point(r, r), 90, 0, 90,
                    color, thickness);

        // Bottom right
        cv::line(frame, cv::Point(x2 - r, y2), cv::Point(x2 - r - d, y2), color,
                thickness);
        cv::line(frame, cv::Point(x2, y2 - r), cv::Point(x2, y2 - r - d), color,
                thickness);
        cv::ellipse(frame, cv::Point(x2 - r, y2 - r), cv::Point(r, r), 0, 0, 90,
                    color, thickness);

        // text
        char text[100];
        sprintf(text, "L:%d|ID:%d|%.2f", label, bboxes[i].object_index, score);
        cv::putText(frame, text, cv::Point(x1, y1 - 10),
                    cv::FONT_HERSHEY_COMPLEX_SMALL, 0.6, color);
        sprintf(text, "X:%.2f|Y:%.2f", bboxes[i].distance[0].x,
                bboxes[i].distance[0].y);
        cv::putText(frame, text, cv::Point(x1, y2 - 10),
                    cv::FONT_HERSHEY_COMPLEX_SMALL, 0.6, color);
        }
    }
}

class PerceptionNode {
public:
    PerceptionNode():
        node_("~"),
        perception_sdk_dir_("/root/gophield/ros_ws/src/perception/"),
        config_file_("/root/gophield/ros_ws/src/common/config/perception.json"),
        lawn_perceptor_(config_file_.c_str()),
        source_image_subscriber_(node_.subscribe("/image_source/image_raw", 1, &PerceptionNode::sourceImageCallback, this)),
        detection_result_publisher_(
            node_.advertise<am_msgs::DetectionResult>("detection_result", 5)),
        segmentation_result_publisher_(
            node_.advertise<sensor_msgs::Image>("segmentation_result", 5)),
        undistort_image_publisher_(
                node_.advertise<sensor_msgs::Image>("undistort_image", 5)){}
    
    void run_perception_sample() {
        std::string img_file = perception_sdk_dir_ + "test/images/lawn_det.jpg";
        Perception::ObjectResults results;
        cv::Mat im;
        im = cv::imread(img_file);

        lawn_perceptor_.Process(&im, &results);
        std::cout << results.seg_width << " " << results.seg_height << std::endl;
        for (auto p : results.cones) {
            std::cout << p.bounding_box.x << " " << p.bounding_box.y << " "
                    << p.bounding_box.width << " " << p.bounding_box.height
                    << std::endl;
        }

        // get seg score
        cv::Mat seg_score(results.seg_height, results.seg_width, CV_32F);
        for (int row = 0; row < results.seg_height; row++) {
            for (int col = 0; col < results.seg_width; col++) {
                float val =
                    static_cast<float>(
                        results.seg.get()[row * results.seg_width + col]);
                seg_score.at<float>(row, col) = val;
            }
        }

        // get seg mask
        cv::resize(seg_score, seg_score, im.size());
        cv::threshold(seg_score, seg_score, 0.5, 255, cv::THRESH_BINARY);
        cv::Mat seg_mask;
        seg_score.convertTo(seg_mask, CV_8U);
        // save
        cv::imwrite("seg.png", seg_mask);

        // vis seg mask
        std::vector<std::vector<cv::Point>> contours;
        contours = visualizeSegmentation(im, seg_mask, cv::Scalar(128, 128, 240));

        // vis 2d det
        std::vector<Perception::Object> bboxes;
        bboxes.insert(bboxes.end(), results.cones.begin(), results.cones.end());
        bboxes.insert(bboxes.end(), results.pedestrians.begin(),
                        results.pedestrians.end());
        bboxes.insert(bboxes.end(), results.golfs.begin(), results.golfs.end());
        std::vector<float> score_thresh;
        score_thresh.push_back(0.5);
        visualizeDetections(im, bboxes, score_thresh);
        // save
        cv::imwrite("res_show.png", im);
    }

    void Init() {
        std::cout << "config file: " << config_file_ << std::endl;
        ROS_INFO("Started initializing perceptor...");
        lawn_perceptor_.Init();
        ROS_INFO("Finished initializing perceptor.");

        //run_perception_sample();
    }

    void get_object(am_msgs::DetectionResult& message, const Perception::Object& detect_object, std::uint8_t label) {
        am_msgs::Object am_object;
        am_object.object_index = detect_object.object_index;
        am_object.confidence = detect_object.confidence;
        am_object.bounding_box_cv.x = detect_object.bounding_box.x;
        am_object.bounding_box_cv.y = detect_object.bounding_box.y;
        am_object.bounding_box_cv.width = detect_object.bounding_box.width;
        am_object.bounding_box_cv.height = detect_object.bounding_box.height;
        for(auto const& point : detect_object.distance) {
            geometry_msgs::Point geometry_pt;
            geometry_pt.x = point.x;
            geometry_pt.y = point.y;
            am_object.location_bv.push_back(geometry_pt);
        }
        am_object.label = label;
        message.objects.push_back(am_object);
    }

    void get_detection_results(am_msgs::DetectionResult& message, const Perception::ObjectResults& results) {
        for (auto detect_object : results.pedestrians) {
            get_object(message, detect_object, am_msgs::Object::LABEL_PEDESTRIAN);
        }
        for (auto detect_object : results.cones) {
            get_object(message, detect_object, am_msgs::Object::LABEL_CONE);
        }
        for (auto detect_object : results.golfs) {
            get_object(message, detect_object, am_msgs::Object::LABEL_GOLF);
        }
        for (auto detect_object : results.sprinklers) {
            get_object(message, detect_object, am_msgs::Object::LABEL_SPRINKLER);
        }
    }

    void sourceImageCallback(const sensor_msgs::Image::ConstPtr& image) {
        auto start = std::chrono::high_resolution_clock::now();
        // copy sensor_msgs::Image to cv::Mat
        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(image, sensor_msgs::image_encodings::BGR8);
        } catch (cv_bridge::Exception& e) {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
    
        auto perception_start = std::chrono::high_resolution_clock::now();
        Perception::ObjectResults results;
        lawn_perceptor_.Process(&(cv_ptr->image), &results);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::microseconds>( end - perception_start ).count() / 1000.0;
        ROS_DEBUG("Finished perception process in %f ms", duration_ms);
        {
            am_msgs::DetectionResult message;
            message.header = image->header;
            get_detection_results(message, results);
            detection_result_publisher_.publish(message);
        }
        {
            cv::Mat seg_score(results.seg_height, results.seg_width, CV_32F);
            for (int row = 0; row < results.seg_height; row++) {
                for (int col = 0; col < results.seg_width; col++) {
                    float val =
                        static_cast<float>(
                            results.seg.get()[row * results.seg_width + col]);
                    seg_score.at<float>(row, col) = val;
                }
            }
            cv_bridge::CvImage out_msg;
            out_msg.header   = image->header;
            out_msg.image    = seg_score;
            out_msg.encoding = "32FC1";
            segmentation_result_publisher_.publish(out_msg.toImageMsg());
        }
        {
            cv_bridge::CvImage out_camera_msg;
            out_camera_msg.header = image->header;
            out_camera_msg.image = cv_ptr->image;
            out_camera_msg.encoding = "bgr8";
            undistort_image_publisher_.publish(out_camera_msg.toImageMsg());
        }
        end = std::chrono::high_resolution_clock::now();
        duration_ms = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count() / 1000.0;
        ROS_DEBUG("Finished function %s for frame %s in %f ms", __func__, image->header.frame_id.c_str(), duration_ms);
    }

private:
    ros::NodeHandle node_;
    std::string perception_sdk_dir_;
    std::string config_file_;
    Perception::LawnPerceptor lawn_perceptor_;
    ros::Subscriber source_image_subscriber_;
    ros::Publisher detection_result_publisher_;
    ros::Publisher segmentation_result_publisher_;
    ros::Publisher undistort_image_publisher_;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "perception_node");

    PerceptionNode node;
    node.Init();

    ros::spin();
}
