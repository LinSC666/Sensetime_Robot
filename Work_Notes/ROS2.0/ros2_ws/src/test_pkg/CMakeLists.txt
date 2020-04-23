cmake_minimum_required(VERSION 3.5)
project(test_pkg)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -pg")

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
#find_package(rclcpp_components REQUIRED)

add_executable(my_node src/my_node.cpp)
add_executable(talker src/talker.cpp)
add_executable(listener src/listener.cpp)
add_executable(talker2 src/talker2.cpp)
add_executable(listener2 src/listener2.cpp)
add_executable(service src/service.cpp)
add_executable(client src/client.cpp)
add_executable(L1 src/L1.cpp)
add_executable(L3 src/L3.cpp)
add_executable(D2cpp src/D2cpp.cpp)
add_executable(D3cpp src/D3cpp.cpp)

target_include_directories(my_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(talker PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(listener PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(talker2 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(listener2 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(service PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(client PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(L1 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(L3 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(D2cpp PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_include_directories(D3cpp PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

ament_target_dependencies(talker rclcpp std_msgs)
ament_target_dependencies(listener rclcpp std_msgs)
ament_target_dependencies(talker2 rclcpp std_msgs)
ament_target_dependencies(listener2 rclcpp std_msgs)
ament_target_dependencies(my_node rclcpp std_msgs)
ament_target_dependencies(service rclcpp std_msgs example_interfaces)
ament_target_dependencies(client rclcpp std_msgs example_interfaces)
ament_target_dependencies(L1 rclcpp std_msgs)
ament_target_dependencies(L3 rclcpp std_msgs)
ament_target_dependencies(D2cpp rclcpp std_msgs sensor_msgs example_interfaces)
ament_target_dependencies(D3cpp rclcpp std_msgs)


install(TARGETS my_node
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS talker
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS listener
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS talker2
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS listener2
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS service
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})
install(TARGETS client
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS L1
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS L3
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS D2cpp
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS D3cpp
  EXPORT export_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
