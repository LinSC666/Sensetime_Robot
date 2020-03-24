#ifndef SIMPLE_COVERAGE_GLOBAL_PLANNER_H_
#define SIMPLE_COVERAGE_GLOBAL_PLANNER_H_

#include <angles/angles.h>
#include <base_local_planner/costmap_model.h>
#include <base_local_planner/world_model.h>
#include <costmap_2d/costmap_2d.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_core/base_global_planner.h>
#include <ros/ros.h>
#include <tf/tf.h>

#include <atomic>
#include <deque>
#include <grid_map_cv/grid_map_cv.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "expander.h"
#include "orientation_filter.h"
#include "potential_calculator.h"
#include "traceback.h"

namespace simple_coverage_global_planner {

class SimpleCoverageGlobalPlanner : public nav_core::BaseGlobalPlanner {
public:
    SimpleCoverageGlobalPlanner();
    SimpleCoverageGlobalPlanner(std::string name,
                                costmap_2d::Costmap2DROS* costmap_ros);
    ~SimpleCoverageGlobalPlanner() override;

    void initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros);
    void initialize(std::string name, costmap_2d::Costmap2D* costmap,
                    std::string frame_id);
    bool makePlan(const geometry_msgs::PoseStamped& start,
                  const geometry_msgs::PoseStamped& goal,
                  std::vector<geometry_msgs::PoseStamped>& plan);

private:
    void StartGoalCheckerThread();

    geometry_msgs::PoseStamped GetRobotPose();

    void ClearRobotCell(unsigned int mx, unsigned int my);
    void UpdateGlobalCostmap();

    void CalculateConnectedDomain(grid_map::GridMap& gridmap,
                                  const std::string& input_layer,
                                  grid_map::Position position,
                                  const std::string& output_layer);

    std::deque<std::pair<grid_map::Index, grid_map::Index>>
    CalculateCoveragePaths(grid_map::GridMap& gridmap, const std::string& layer,
                           double robot_width);

    std::vector<grid_map::Index> ConnectPaths(
            std::deque<std::pair<grid_map::Index, grid_map::Index>> paths);

    std::vector<geometry_msgs::PoseStamped> LineToPlan(
            const grid_map::Index& start, const grid_map::Index& goal);

    bool GetPlanFromPotential(double start_x, double start_y, double goal_x,
                              double goal_y,
                              std::vector<geometry_msgs::PoseStamped>& plan);

    void SubdivisonPath();

    void PublishPlan(const std::vector<geometry_msgs::PoseStamped>& path);

    void MapToWorld(double mx, double my, double& wx, double& wy);
    bool WorldToMap(double wx, double wy, double& mx, double& my);

    double GetDistance(const geometry_msgs::PoseStamped& pose1,
                       const geometry_msgs::PoseStamped& pose2);
    double GetDistance(const grid_map::Index& index1,
                       const grid_map::Index& index2);

    bool IsFreeInCircle(grid_map::GridMap& gridmap, const std::string& layer,
                        const grid_map::Index& index, double radius);

    void OutlineMap(unsigned char* costarr, int nx, int ny,
                    unsigned char value);

private:
    void ReadPlan(const std::string& filename,
                  std::deque<grid_map::Index>& waypoints,
                  std::deque<std::vector<geometry_msgs::PoseStamped>>& paths);
    void WritePlan(
            const std::string& filename,
            const std::deque<grid_map::Index>& waypoints,
            const std::deque<std::vector<geometry_msgs::PoseStamped>>& paths);

private:
    cv::Mat RenderGridMap(const grid_map::GridMap& gridmap,
                          const std::string& layer);
    void RenderCoveragePaths(
            grid_map::GridMap& gridmap,
            const std::deque<std::pair<grid_map::Index, grid_map::Index>>&
                    paths,
            const std::string& input_layer, const std::string& output_layer);

    void RenderWholePath(grid_map::GridMap& gridmap,
                         const std::vector<grid_map::Index>& path,
                         const std::string& input_layer,
                         const std::string& output_layer);

private:
    costmap_2d::Costmap2DROS* costmap_ros_;
    costmap_2d::Costmap2D* costmap_;
    std::string frame_id_;

    std::unique_ptr<global_planner::PotentialCalculator> p_calc_;
    std::unique_ptr<global_planner::Expander> planner_;
    std::unique_ptr<global_planner::Traceback> path_maker_;
    std::unique_ptr<global_planner::OrientationFilter> orientation_filter_;

    std::vector<float> potential_array_;

    ros::Publisher plan_pub_;

    std::thread goal_checker_thread_;
    std::atomic_bool goal_checker_thread_stop_flag_;

    bool initialized_;

    bool is_running_;

    grid_map::GridMap gridmap_;

    std::deque<grid_map::Index> waypoints_;
    std::deque<std::vector<geometry_msgs::PoseStamped>> paths_;
    geometry_msgs::PoseStamped current_goal_;

    std::deque<grid_map::Index> waypoints_backup_;
    std::deque<std::vector<geometry_msgs::PoseStamped>> paths_backup_;

    std::mutex mutex_;
};
}  // namespace simple_coverage_global_planner

#endif  // SIMPLE_COVERAGE_GLOBAL_PLANNER_H_