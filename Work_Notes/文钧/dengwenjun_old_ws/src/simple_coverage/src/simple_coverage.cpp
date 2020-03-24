#include <cmath>

#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <nav_msgs/GetMap.h>
#include <ros/ros.h>
#include <tf/tf.h>
#include <grid_map_cv/grid_map_cv.hpp>
#include <grid_map_ros/grid_map_ros.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat global_costmap_color;

grid_map::GridMap gridmap;

void PrintGridInfo(const nav_msgs::OccupancyGrid& grid) {
    std_msgs::Header header = grid.header;
    nav_msgs::MapMetaData info = grid.info;
    std::vector<int8_t> data = grid.data;

    ROS_INFO("header.frame_id = %s", header.frame_id.c_str());
    ROS_INFO("header.seq = %u", header.seq);
    ROS_INFO("header.stamp = %f", header.stamp.toSec());

    ROS_INFO("info.width = %u", info.width);
    ROS_INFO("info.height = %u", info.height);
    ROS_INFO("info.map_load_time = %f", info.map_load_time.toSec());
    ROS_INFO("info.origin.position = (%f,%f,%f)", info.origin.position.x,
             info.origin.position.y, info.origin.position.z);
    ROS_INFO("info.origin.orientation = (%f,%f,%f,%f)",
             info.origin.orientation.x, info.origin.orientation.y,
             info.origin.orientation.z, info.origin.orientation.w);
    ROS_INFO("info.resolution = %f", info.resolution);

    ROS_INFO("data size = %zd", data.size());
}

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

void CalculateConnectedDomain(grid_map::GridMap& grid_map,
                              const std::string& input_layer,
                              grid_map::Position position,
                              const std::string& output_layer) {
    gridmap.add(output_layer);
    grid_map::Index origin_index;
    gridmap.getIndex(position, origin_index);

    grid_map::Matrix& input_layer_data = gridmap[input_layer];
    grid_map::Matrix& output_layer_data = gridmap[output_layer];

    size_t gridmap_width = gridmap.getSize()(1);
    size_t gridmap_heigh = gridmap.getSize()(0);

    float value = input_layer_data(origin_index(0), origin_index(1));

    std::deque<grid_map::Index> index_queue;
    output_layer_data(origin_index(0), origin_index(1)) = value;
    index_queue.push_back(origin_index);

    std::vector<grid_map::Index> near_indexs(4);

    while (!index_queue.empty()) {
        grid_map::Index index = index_queue.front();
        index_queue.pop_front();

        near_indexs[0](0) = index(0) - 1;
        near_indexs[0](1) = index(1);
        near_indexs[1](0) = index(0) + 1;
        near_indexs[1](1) = index(1);
        near_indexs[2](0) = index(0);
        near_indexs[2](1) = index(1) - 1;
        near_indexs[3](0) = index(0);
        near_indexs[3](1) = index(1) + 1;
        for (size_t i = 0; i < near_indexs.size(); ++i) {
            if (near_indexs[i](0) >= 0 && near_indexs[i](0) < gridmap_heigh &&
                near_indexs[i](1) >= 0 && near_indexs[i](1) < gridmap_width) {
                if (input_layer_data(near_indexs[i](0), near_indexs[i](1)) ==
                            value &&
                    output_layer_data(near_indexs[i](0), near_indexs[i](1)) !=
                            value) {
                    output_layer_data(near_indexs[i](0), near_indexs[i](1)) =
                            value;
                    index_queue.push_back(near_indexs[i]);
                }
            }
        }
    }
}

bool IsFreeInCircle(grid_map::GridMap& grid_map, const std::string& layer,
                    const grid_map::Index& index, double radius) {
    bool is_free = true;
    grid_map::Matrix& layer_data = grid_map[layer];
    grid_map::Position center;
    grid_map.getPosition(index, center);
    for (grid_map::CircleIterator iterator(grid_map, center, radius);
         !iterator.isPastEnd(); ++iterator) {
        const grid_map::Index index(*iterator);
        if (std::isnan(layer_data(index(0), index(1)))) {
            is_free = false;
            break;
        }
    }
    return is_free;
}

std::deque<std::pair<grid_map::Index, grid_map::Index>> CalculateCoveragePaths(
        grid_map::GridMap& grid_map, const std::string& layer,
        double robot_width) {
    double resolution = gridmap.getResolution();
    double cell_step = robot_width / resolution;
    grid_map::Matrix& layer_data = gridmap[layer];
    std::deque<std::pair<grid_map::Index, grid_map::Index>> coverage_paths;

    for (double row_index = 0; row_index < gridmap.getSize()(0);
         row_index += cell_step) {
        size_t row_index_u = static_cast<size_t>(row_index);

        bool is_covering = false;
        grid_map::Index begin_index;
        grid_map::Index end_index;

        size_t col_index = 0;
        for (col_index = 0; col_index < gridmap.getSize()(1); ++col_index) {
            grid_map::Index index(row_index, col_index);
            bool is_free = IsFreeInCircle(grid_map, layer, index, 0.6);
            if (!is_covering && is_free) {
                begin_index(0) = row_index;
                begin_index(1) = col_index;
                is_covering = true;
            }

            if (is_covering && !is_free) {
                end_index(0) = row_index;
                end_index(1) = col_index;
                is_covering = false;
                coverage_paths.push_back(
                        std::make_pair(begin_index, end_index));
            }
        }
        if (is_covering) {
            end_index(0) = row_index;
            end_index(1) = col_index;
            is_covering = false;
            coverage_paths.push_back(std::make_pair(begin_index, end_index));
        }
    }
    return coverage_paths;
}

void RenderCoveragePaths(
        grid_map::GridMap& grid_map,
        const std::deque<std::pair<grid_map::Index, grid_map::Index>>& paths,
        const std::string& input_layer, const std::string& output_layer) {
    grid_map.add(output_layer);
    grid_map[output_layer] = grid_map[input_layer];
    grid_map::Matrix& output_layer_data = gridmap[output_layer];
    for (const std::pair<grid_map::Index, grid_map::Index>& path : paths) {
        for (grid_map::LineIterator iterator(gridmap, path.first, path.second);
             !iterator.isPastEnd(); ++iterator) {
            const grid_map::Index index(*iterator);
            output_layer_data(index(0), index(1)) = 200;
        }
    }
}

double GetDistance(const grid_map::Index& index1,
                   const grid_map::Index& index2) {
    auto x_diff = index1(1) - index2(1);
    auto y_diff = index1(0) - index2(0);
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

std::vector<grid_map::Index> ConnectPaths(
        std::deque<std::pair<grid_map::Index, grid_map::Index>> paths) {
    std::vector<grid_map::Index> path;
    path.push_back(paths.front().first);
    path.push_back(paths.front().second);
    paths.pop_front();
    while (!paths.empty()) {
        auto last_index = path.back();
        double min_distance = GetDistance(last_index, paths.front().first);
        auto near_iter = paths.begin();
        bool is_first_index = true;
        for (auto iter = paths.begin(); iter != paths.end(); ++iter) {
            double distance = GetDistance(last_index, iter->first);
            if (distance < min_distance) {
                min_distance = distance;
                near_iter = iter;
                is_first_index = true;
            }
            distance = GetDistance(last_index, iter->second);
            if (distance < min_distance) {
                min_distance = distance;
                near_iter = iter;
                is_first_index = false;
            }
        }
        if (is_first_index) {
            path.push_back(near_iter->first);
            path.push_back(near_iter->second);
        } else {
            path.push_back(near_iter->second);
            path.push_back(near_iter->first);
        }
        paths.erase(near_iter);
    }
    return path;
}

void RenderWholePath(grid_map::GridMap& grid_map,
                     const std::vector<grid_map::Index>& path,
                     const std::string& input_layer,
                     const std::string& output_layer) {
    grid_map.add(output_layer);
    grid_map[output_layer] = grid_map[input_layer];
    grid_map::Matrix& output_layer_data = gridmap[output_layer];
    for (size_t i = 0; i < path.size() - 1; ++i) {
        for (grid_map::LineIterator iterator(gridmap, path[i], path[i + 1]);
             !iterator.isPastEnd(); ++iterator) {
            const grid_map::Index index(*iterator);
            output_layer_data(index(0), index(1)) = 200;
        }
    }
}

void GlobalCostMapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg) {
    ROS_INFO("Get global_costmap");

    PrintGridInfo(*msg);

    grid_map::GridMapRosConverter::fromOccupancyGrid(*msg, "global_costmap",
                                                     gridmap);
}

int main(int argc, char** argv) {
    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>
            MoveBaseClient;

    ros::init(argc, argv, "simple_coverage");
    ros::NodeHandle node;

    ros::Subscriber global_costmap_subscriber = node.subscribe(
            "/move_base/global_costmap/costmap", 1000, GlobalCostMapCallback);

    while (1) {
        ros::spinOnce();
        if (gridmap.exists("global_costmap")) {
            break;
        }
    }

    CalculateConnectedDomain(gridmap, "global_costmap",
                             grid_map::Position(0, 0), "connected_domain");

    auto coverage_paths =
            CalculateCoveragePaths(gridmap, "connected_domain", 0.5);

    auto path = ConnectPaths(coverage_paths);

    RenderCoveragePaths(gridmap, coverage_paths, "connected_domain",
                        "coverage_paths");
    RenderWholePath(gridmap, path, "connected_domain", "path");

    global_costmap_color = RenderGridMap(gridmap, "global_costmap");
    cv::Mat connected_domain_image = RenderGridMap(gridmap, "connected_domain");
    cv::Mat coverage_paths_image = RenderGridMap(gridmap, "coverage_paths");
    cv::Mat path_image = RenderGridMap(gridmap, "path");

    // cv::imshow("global_costmap_color", global_costmap_color);
    // cv::imshow("connected_domain", connected_domain_image);
    // cv::imshow("coverage_paths", coverage_paths_image);
    // cv::imshow("path", path_image);

    // while (ros::ok()) {
    //     cv::waitKey(10);
    // }

    cv::imwrite("global_costmap_color.jpg", global_costmap_color);
    cv::imwrite("connected_domain.jpg", connected_domain_image);
    cv::imwrite("coverage_paths.jpg", coverage_paths_image);
    cv::imwrite("path.jpg", path_image);

    MoveBaseClient action_client("move_base", true);

    while (!action_client.waitForServer(ros::Duration(5.0))) {
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;

    for (size_t i = 0; i < path.size(); ++i) {
        auto& index = path[i];

        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        grid_map::Position position;
        gridmap.getPosition(index, position);
        goal.target_pose.pose.position.x = position.x();
        goal.target_pose.pose.position.y = position.y();

        double x_diff = 0.0;
        double y_diff = 0.0;
        if (i == 0) {
            grid_map::Position next_position;
            gridmap.getPosition(path[i + 1], next_position);
            x_diff = next_position.x() - position.x();
            y_diff = next_position.y() - position.y();
        } else {
            grid_map::Position last_position;
            gridmap.getPosition(path[i - 1], last_position);
            x_diff = position.x() - last_position.x();
            y_diff = position.y() - last_position.y();
        }

        auto quat = tf::createQuaternionFromYaw(std::atan2(y_diff, x_diff));
        goal.target_pose.pose.orientation.x = quat.x();
        goal.target_pose.pose.orientation.y = quat.y();
        goal.target_pose.pose.orientation.z = quat.z();
        goal.target_pose.pose.orientation.w = quat.w();

        ROS_INFO("Sending goal: (%f,%f)", position.x(), position.y());
        action_client.sendGoal(goal);

        action_client.waitForResult();

        if (action_client.getState() ==
            actionlib::SimpleClientGoalState::SUCCEEDED)
            ROS_INFO("Hooray, the base moved");
        else
            ROS_INFO("The base failed to move");
    }

    return 0;
}