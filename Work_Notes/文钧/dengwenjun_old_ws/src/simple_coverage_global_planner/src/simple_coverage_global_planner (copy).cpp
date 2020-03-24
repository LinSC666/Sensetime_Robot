#include "simple_coverage_global_planner.h"

#include <thread>
#include <fstream>

#include <pluginlib/class_list_macros.h>

#include <grid_map_costmap_2d/Costmap2DConverter.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "dijkstra.h"
#include "gradient_path.h"
#include "json.hpp"
#include "visualization.h"
#include "geometry_msgs/PoseStamped.h"

#define MELODIC

PLUGINLIB_EXPORT_CLASS(
        simple_coverage_global_planner::SimpleCoverageGlobalPlanner,
        nav_core::BaseGlobalPlanner)

namespace simple_coverage_global_planner {

const double kRobotWidh = 0.2;
const double kMarginSize = 0.4;
const double kGoalTolerance = 0.8;
const size_t kSubdivisionSize = 20;
const float kConvertOffset = 0.5f;

grid_map::Costmap2DConverter<grid_map::GridMap> gCostmap2dConverter;

SimpleCoverageGlobalPlanner::SimpleCoverageGlobalPlanner()
        : costmap_(nullptr), initialized_(false), is_running_(false) {}

SimpleCoverageGlobalPlanner::SimpleCoverageGlobalPlanner(
        std::string name, costmap_2d::Costmap2DROS* costmap_ros)
        : costmap_(nullptr), initialized_(false), is_running_(false) {
    initialize(name, costmap_ros);
}

SimpleCoverageGlobalPlanner::~SimpleCoverageGlobalPlanner() {
    goal_checker_thread_stop_flag_ = true;
    goal_checker_thread_.join();
}

void SimpleCoverageGlobalPlanner::initialize(
        std::string name, costmap_2d::Costmap2DROS* costmap_ros) {
    costmap_ros_ = costmap_ros;

    //　使用Costmap2DROS初始化GridMap
    gCostmap2dConverter.initializeFromCostmap2D(*costmap_ros, gridmap_);

    initialize(name, costmap_ros->getCostmap(),
               costmap_ros->getGlobalFrameID());

    StartGoalCheckerThread();
}

void SimpleCoverageGlobalPlanner::initialize(std::string name,
                                             costmap_2d::Costmap2D* costmap,
                                             std::string frame_id) {
    ROS_INFO("[Simple Coverage Global Planner] initialize");
    if (initialized_) {
        ROS_WARN(
                "[Simple Coverage Global Planner] This planner has already "
                "been initialized, doing nothing");
        return;
    }

    ros::NodeHandle private_nh("~/" + name);

    costmap_ = costmap;
    frame_id_ = frame_id;

    unsigned int cx = costmap->getSizeInCellsX();
    unsigned int cy = costmap->getSizeInCellsY();

    p_calc_ = std::make_unique<global_planner::PotentialCalculator>(cx, cy);
    auto expansion = std::make_unique<global_planner::DijkstraExpansion>(
            p_calc_.get(), cx, cy);
    expansion->setPreciseStart(true);
    planner_ = std::move(expansion);
    path_maker_ = std::make_unique<global_planner::GradientPath>(p_calc_.get());
    orientation_filter_ = std::make_unique<global_planner::OrientationFilter>();

    plan_pub_ = private_nh.advertise<nav_msgs::Path>("plan", 1);

    initialized_ = true;

    // 添加初始的全局costmap层
    gCostmap2dConverter.addLayerFromCostmap2D(
            *costmap_, "initial_global_costmap", gridmap_);

    auto start = GetRobotPose();
    // start.pose.position.x = -1.2;
    // start.pose.position.y = -3.8;

    std::cout << "start : " << start.pose.position.x << " "
              << start.pose.position.y << std::endl;

    unsigned int start_x_i, start_y_i;
    if (!costmap_->worldToMap(start.pose.position.x, start.pose.position.y,
                              start_x_i, start_y_i)) {
        ROS_WARN(
                "The robot's start position is off the global costmap. "
                "Planning will always fail.");
    }

    ClearRobotCell(start_x_i, start_y_i);

    CalculateConnectedDomain(
            gridmap_, "initial_global_costmap",
            grid_map::Position(start.pose.position.x, start.pose.position.y),
            "connected_domain");

    auto coverage_paths =
            CalculateCoveragePaths(gridmap_, "connected_domain", kRobotWidh);

    auto path = ConnectPaths(coverage_paths);
    waypoints_.assign(path.begin(), path.end());
    ///////////////////////////////////////////////////////////////
    RenderCoveragePaths(gridmap_, coverage_paths, "connected_domain",
                        "coverage_paths");
    RenderWholePath(gridmap_, path, "connected_domain", "path");
    cv::Mat coverage_paths_image = RenderGridMap(gridmap_, "coverage_paths");
    cv::Mat path_image = RenderGridMap(gridmap_, "path");
    cv::imwrite("/home/nvidia/Projects/dengwenjun-workspace/coverage_paths.jpg",
                coverage_paths_image);
    cv::imwrite("/home/nvidia/Projects/dengwenjun-workspace/path.jpg",
                path_image);
    /////////////////////////////////////////////////////////////////
    grid_map::Index start_index;
    gridmap_.getIndex(
            grid_map::Position(start.pose.position.x, start.pose.position.y),
            start_index);

    for (size_t i = 0; i < waypoints_.size(); ++i) {
        grid_map::Index pre_index = i == 0 ? start_index : waypoints_[i - 1];
        grid_map::Index current_index = waypoints_[i];
        paths_.push_back(LineToPlan(pre_index, current_index));
    }

    WritePlan("plan", waypoints_, paths_);

    SubdivisonPath();

    waypoints_backup_ = waypoints_;
    paths_backup_ = paths_;

    std::cout << "initialize finish" << std::endl;
}

bool SimpleCoverageGlobalPlanner::makePlan(
        const geometry_msgs::PoseStamped& start,
        const geometry_msgs::PoseStamped& goal,
        std::vector<geometry_msgs::PoseStamped>& plan) {
    ROS_INFO("[Simple Coverage Global Planner] makePlan");

    std::lock_guard<std::mutex> lock(mutex_);

    if (!initialized_) {
        ROS_ERROR(
                "[Simple Coverage Global Planner] This planner has not been "
                "initialized yet, please call initialize() before use");
        return false;
    }

    std::string global_frame = frame_id_;

    if (start.header.frame_id != global_frame) {
        ROS_ERROR(
                "The start pose passed to this planner must be in the %s "
                "frame.  It is instead in the %s frame.",
                global_frame.c_str(), start.header.frame_id.c_str());
        return false;
    }

    unsigned int start_x_i, start_y_i;
    if (!costmap_->worldToMap(start.pose.position.x, start.pose.position.y,
                              start_x_i, start_y_i)) {
        ROS_WARN(
                "The robot's start position is off the global costmap. "
                "Planning will always fail.");
    }

    if (!is_running_) {
        waypoints_ = waypoints_backup_;
        paths_ = paths_backup_;
        ROS_INFO("Start new coverage");
        is_running_ = true;
    }

    ClearRobotCell(start_x_i, start_y_i);
    UpdateGlobalCostmap();

    std::cout << "current position : " << start.pose.position.x << " "
              << start.pose.position.y << std::endl;

    if (waypoints_.empty()) {
        ROS_INFO("Coverage finished.");
        is_running_ = false;
        return false;
    }

    plan.clear();

    geometry_msgs::PoseStamped current_path_goal;
    bool goal_found = false;
    while (!goal_found && !paths_.empty()) {
        for (size_t i = paths_[0].size() - 1; i >= 0; ++i) {
            current_path_goal = paths_[0][i];
            if (gridmap_.atPosition(
                        "global_costmap",
                        grid_map::Position(
                                current_path_goal.pose.position.x,
                                current_path_goal.pose.position.y)) == 0) {
                goal_found = true;
                break;
            }
        }
        if (!goal_found) {
            paths_.pop_front();
            waypoints_.pop_front();
        }
    }

    if (!goal_found) {
        return false;
    }

    current_goal_ = current_path_goal;

    grid_map::Index start_index, current_goal_index;
    gridmap_.getIndex(
            grid_map::Position(start.pose.position.x, start.pose.position.y),
            start_index);
    gridmap_.getIndex(grid_map::Position(current_path_goal.pose.position.x,
                                         current_path_goal.pose.position.y),
                      current_goal_index);
    auto start_plan = LineToPlan(start_index, current_goal_index);

    plan = start_plan;

    for (size_t i = 1; i < paths_.size(); ++i) {
        for (auto& pose : paths_[i]) {
            plan.push_back(pose);
        }
    }

    orientation_filter_->processPath(start, plan);

    PublishPlan(plan);

    std::cout << "plan size : " << plan.size() << std::endl;

    return !plan.empty();
}

void SimpleCoverageGlobalPlanner::StartGoalCheckerThread() {
    goal_checker_thread_stop_flag_ = false;
    goal_checker_thread_ = std::thread([this]() {
        ros::NodeHandle node;
        ros::Rate rate(10.0);
        while (node.ok() && !goal_checker_thread_stop_flag_) {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                geometry_msgs::PoseStamped current_pose = GetRobotPose();
                if (GetDistance(current_pose, current_goal_) > kGoalTolerance) {
                    continue;
                }

                if (paths_.empty()) {
                    continue;
                }

                paths_.pop_front();
                waypoints_.pop_front();

                if (!paths_.empty()) {
                    current_goal_ = paths_.front().back();
                }
            }
            rate.sleep();
        }
    });
}

geometry_msgs::PoseStamped SimpleCoverageGlobalPlanner::GetRobotPose() {
//#ifdef KINETIC
    tf::Stamped<tf::Pose> global_pose_tf;
    costmap_ros_->getRobotPose(global_pose_tf);

    geometry_msgs::PoseStamped global_pose;
    tf::poseStampedTFToMsg(global_pose_tf, global_pose);
//#endif
/*
#ifdef MELODIC
    geometry_msgs::PoseStamped global_pose;
    costmap_ros_->getRobotPose(global_pose);
#endif
*/
    return global_pose;
}

void SimpleCoverageGlobalPlanner::ClearRobotCell(unsigned int mx,
                                                 unsigned int my) {
    if (!initialized_) {
        ROS_ERROR(
                "This planner has not been initialized yet, please call "
                "initialize() before use");
        return;
    }
    costmap_->setCost(mx, my, costmap_2d::FREE_SPACE);
}

void SimpleCoverageGlobalPlanner::UpdateGlobalCostmap() {
    if (gridmap_.exists("global_costmap")) {
        gridmap_.erase("global_costmap");
    }
    gCostmap2dConverter.addLayerFromCostmap2D(*costmap_, "global_costmap",
                                              gridmap_);
}

void SimpleCoverageGlobalPlanner::CalculateConnectedDomain(
        grid_map::GridMap& gridmap, const std::string& input_layer,
        grid_map::Position position, const std::string& output_layer) {
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

std::deque<std::pair<grid_map::Index, grid_map::Index>>
SimpleCoverageGlobalPlanner::CalculateCoveragePaths(grid_map::GridMap& gridmap,
                                                    const std::string& layer,
                                                    double kRobotWidh) {
    double resolution = gridmap.getResolution();
    double cell_step = kRobotWidh / resolution;
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
            bool is_free = IsFreeInCircle(gridmap, layer, index, kMarginSize);
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

std::vector<grid_map::Index> SimpleCoverageGlobalPlanner::ConnectPaths(
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

std::vector<geometry_msgs::PoseStamped> SimpleCoverageGlobalPlanner::LineToPlan(
        const grid_map::Index& start, const grid_map::Index& goal) {
    int nx = costmap_->getSizeInCellsX(), ny = costmap_->getSizeInCellsY();
    p_calc_->setSize(nx, ny);
    planner_->setSize(nx, ny);
    path_maker_->setSize(nx, ny);
    potential_array_.resize(nx * ny);

    OutlineMap(costmap_->getCharMap(), nx, ny, costmap_2d::LETHAL_OBSTACLE);

    grid_map::Position start_pos;
    grid_map::Position goal_pos;

    gridmap_.getPosition(start, start_pos);
    gridmap_.getPosition(goal, goal_pos);

    double start_x, start_y, goal_x, goal_y;

    WorldToMap(start_pos.x(), start_pos.y(), start_x, start_y);
    WorldToMap(goal_pos.x(), goal_pos.y(), goal_x, goal_y);

    bool found_legal = planner_->calculatePotentials(
            costmap_->getCharMap(), start_x, start_y, goal_x, goal_y,
            nx * ny * 2, potential_array_.data());

    planner_->clearEndpoint(costmap_->getCharMap(), potential_array_.data(),
                            goal_x, goal_y, 2);

    std::vector<geometry_msgs::PoseStamped> plan;
    if (found_legal) {
        if (!GetPlanFromPotential(start_x, start_y, goal_x, goal_y, plan)) {
            ROS_ERROR(
                    "Failed to get a plan from potential when a legal "
                    "potential was found. This shouldn't happen.");
        }
    } else {
        ROS_ERROR("Failed to get a plan.");
    }

    return plan;
}

bool SimpleCoverageGlobalPlanner::GetPlanFromPotential(
        double start_x, double start_y, double goal_x, double goal_y,
        std::vector<geometry_msgs::PoseStamped>& plan) {
    if (!initialized_) {
        ROS_ERROR(
                "This planner has not been initialized yet, but it is being "
                "used, please call initialize() before use");
        return false;
    }

    std::string global_frame = frame_id_;

    plan.clear();

    std::vector<std::pair<float, float>> path;

    if (!path_maker_->getPath(potential_array_.data(), start_x, start_y, goal_x,
                              goal_y, path)) {
        ROS_ERROR("NO PATH!");
        return false;
    }

    ros::Time plan_time = ros::Time::now();
    for (int i = path.size() - 1; i >= 0; i--) {
        std::pair<float, float> point = path[i];

        double world_x, world_y;
        MapToWorld(point.first, point.second, world_x, world_y);

        geometry_msgs::PoseStamped pose;
        pose.header.stamp = plan_time;
        pose.header.frame_id = global_frame;
        pose.pose.position.x = world_x;
        pose.pose.position.y = world_y;
        pose.pose.position.z = 0.0;
        pose.pose.orientation.x = 0.0;
        pose.pose.orientation.y = 0.0;
        pose.pose.orientation.z = 0.0;
        pose.pose.orientation.w = 1.0;
        plan.push_back(pose);
    }

    return !plan.empty();
}

void SimpleCoverageGlobalPlanner::SubdivisonPath() {
    std::deque<grid_map::Index> new_waypoints;
    std::deque<std::vector<geometry_msgs::PoseStamped>> new_paths;

    for (size_t i = 0; i < waypoints_.size(); ++i) {
        if (paths_[i].empty()) {
            continue;
        }
        for (size_t j = 0; j < paths_[i].size(); j += kSubdivisionSize) {
            size_t begin_index = j;
            size_t end_index = j + kSubdivisionSize;
            end_index = std::min(paths_[i].size(), end_index);
            geometry_msgs::PoseStamped end_pose = paths_[i][end_index - 1];
            grid_map::Index waypoint;
            gridmap_.getIndex(grid_map::Position(end_pose.pose.position.x,
                                                 end_pose.pose.position.y),
                              waypoint);
            new_waypoints.push_back(waypoint);
            new_paths.push_back(std::vector<geometry_msgs::PoseStamped>(
                    &(paths_[i][begin_index]), &(paths_[i][end_index])));
        }
    }

    waypoints_ = std::move(new_waypoints);
    paths_ = std::move(new_paths);
}

void SimpleCoverageGlobalPlanner::PublishPlan(
        const std::vector<geometry_msgs::PoseStamped>& path) {
    if (!initialized_) {
        ROS_ERROR(
                "This planner has not been initialized yet, but it is being "
                "used, please call initialize() before use");
        return;
    }

    nav_msgs::Path gui_path;
    gui_path.poses.resize(path.size());

    gui_path.header.frame_id = frame_id_;
    gui_path.header.stamp = ros::Time::now();

    for (unsigned int i = 0; i < path.size(); i++) {
        gui_path.poses[i] = path[i];
    }

    plan_pub_.publish(gui_path);
}

void SimpleCoverageGlobalPlanner::MapToWorld(double mx, double my, double& wx,
                                             double& wy) {
    wx = costmap_->getOriginX() +
         (mx + kConvertOffset) * costmap_->getResolution();
    wy = costmap_->getOriginY() +
         (my + kConvertOffset) * costmap_->getResolution();
}

double SimpleCoverageGlobalPlanner::GetDistance(
        const geometry_msgs::PoseStamped& pose1,
        const geometry_msgs::PoseStamped& pose2) {
    auto x_diff = pose1.pose.position.x - pose2.pose.position.x;
    auto y_diff = pose1.pose.position.y - pose2.pose.position.y;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

double SimpleCoverageGlobalPlanner::GetDistance(const grid_map::Index& index1,
                                                const grid_map::Index& index2) {
    auto x_diff = index1(1) - index2(1);
    auto y_diff = index1(0) - index2(0);
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

bool SimpleCoverageGlobalPlanner::WorldToMap(double wx, double wy, double& mx,
                                             double& my) {
    double origin_x = costmap_->getOriginX(), origin_y = costmap_->getOriginY();
    double resolution = costmap_->getResolution();

    if (wx < origin_x || wy < origin_y) {
        return false;
    }

    mx = (wx - origin_x) / resolution - kConvertOffset;
    my = (wy - origin_y) / resolution - kConvertOffset;

    if (mx < costmap_->getSizeInCellsX() && my < costmap_->getSizeInCellsY()) {
        return true;
    }

    return false;
}

bool SimpleCoverageGlobalPlanner::IsFreeInCircle(grid_map::GridMap& gridmap,
                                                 const std::string& layer,
                                                 const grid_map::Index& index,
                                                 double radius) {
    bool is_free = true;
    grid_map::Matrix& layer_data = gridmap[layer];
    grid_map::Position center;
    gridmap.getPosition(index, center);
    for (grid_map::CircleIterator iterator(gridmap, center, radius);
         !iterator.isPastEnd(); ++iterator) {
        const grid_map::Index index(*iterator);
        if (std::isnan(layer_data(index(0), index(1)))) {
            is_free = false;
            break;
        }
    }
    return is_free;
}

void SimpleCoverageGlobalPlanner::OutlineMap(unsigned char* costarr, int nx,
                                             int ny, unsigned char value) {
    unsigned char* pc = costarr;
    for (int i = 0; i < nx; i++) {
        *pc++ = value;
    }
    pc = costarr + (ny - 1) * nx;
    for (int i = 0; i < nx; i++) {
        *pc++ = value;
    }
    pc = costarr;
    for (int i = 0; i < ny; i++, pc += nx) {
        *pc = value;
    }
    pc = costarr + nx - 1;
    for (int i = 0; i < ny; i++, pc += nx) {
        *pc = value;
    }
}

cv::Mat SimpleCoverageGlobalPlanner::RenderGridMap(
        const grid_map::GridMap& gridmap, const std::string& layer) {
    cv::Mat gridmap_image(gridmap.getSize()(0), gridmap.getSize()(1), CV_8UC3,
                          cv::Scalar(0, 0, 0));
    const grid_map::Matrix& data = gridmap[layer];
    for (grid_map::GridMapIterator iterator(gridmap); !iterator.isPastEnd();
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

void SimpleCoverageGlobalPlanner::RenderCoveragePaths(
        grid_map::GridMap& gridmap,
        const std::deque<std::pair<grid_map::Index, grid_map::Index>>& paths,
        const std::string& input_layer, const std::string& output_layer) {
    gridmap.add(output_layer);
    gridmap[output_layer] = gridmap[input_layer];
    grid_map::Matrix& output_layer_data = gridmap[output_layer];
    for (const std::pair<grid_map::Index, grid_map::Index>& path : paths) {
        for (grid_map::LineIterator iterator(gridmap, path.first, path.second);
             !iterator.isPastEnd(); ++iterator) {
            const grid_map::Index index(*iterator);
            output_layer_data(index(0), index(1)) = 200;
        }
    }
}

void SimpleCoverageGlobalPlanner::RenderWholePath(
        grid_map::GridMap& gridmap, const std::vector<grid_map::Index>& path,
        const std::string& input_layer, const std::string& output_layer) {
    gridmap.add(output_layer);
    gridmap[output_layer] = gridmap[input_layer];
    grid_map::Matrix& output_layer_data = gridmap[output_layer];
    for (size_t i = 0; i < path.size() - 1; ++i) {
        for (grid_map::LineIterator iterator(gridmap, path[i], path[i + 1]);
             !iterator.isPastEnd(); ++iterator) {
            const grid_map::Index index(*iterator);
            output_layer_data(index(0), index(1)) = 200;
        }
    }
}

void SimpleCoverageGlobalPlanner::ReadPlan(
        const std::string& filename, std::deque<grid_map::Index>& waypoints,
        std::deque<std::vector<geometry_msgs::PoseStamped>>& paths) {}

void SimpleCoverageGlobalPlanner::WritePlan(
        const std::string& filename,
        const std::deque<grid_map::Index>& waypoints,
        const std::deque<std::vector<geometry_msgs::PoseStamped>>& paths) {
    std::vector<std::map<std::string, int>> waypoints_convert;
    for (auto& waypoint : waypoints) {
        std::map<std::string, int> waypoint_map;
        waypoint_map.clear();
        waypoint_map["0"] = waypoint(0);
        waypoint_map["1"] = waypoint(1);
        waypoints_convert.push_back(waypoint_map);
    }
    nlohmann::json json_obj;
    json_obj["waypoints"] = waypoints_convert;

    std::ofstream json_file(filename);
    json_file << json_obj;
    json_file.close();
}

}  // namespace simple_coverage_global_planner
