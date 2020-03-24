# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "am_msgs: 15 messages, 0 services")

set(MSG_I_FLAGS "-Iam_msgs:/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(am_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg" "am_msgs/Rect:geometry_msgs/Point"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg" ""
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg" "am_msgs/MotorFeedback:std_msgs/Header"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg" "am_msgs/Rect:am_msgs/Object:std_msgs/Header:geometry_msgs/Point"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg" ""
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg" "am_msgs/LoopData:std_msgs/Header"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg" NAME_WE)
add_custom_target(_am_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_msgs" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg" "std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg;/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)
_generate_msg_cpp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(am_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(am_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(am_msgs_generate_messages am_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_cpp _am_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(am_msgs_gencpp)
add_dependencies(am_msgs_gencpp am_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS am_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg;/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)
_generate_msg_eus(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
)

### Generating Services

### Generating Module File
_generate_module_eus(am_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(am_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(am_msgs_generate_messages am_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_eus _am_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(am_msgs_geneus)
add_dependencies(am_msgs_geneus am_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS am_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg;/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)
_generate_msg_lisp(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(am_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(am_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(am_msgs_generate_messages am_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_lisp _am_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(am_msgs_genlisp)
add_dependencies(am_msgs_genlisp am_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS am_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg;/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)
_generate_msg_nodejs(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
)

### Generating Services

### Generating Module File
_generate_module_nodejs(am_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(am_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(am_msgs_generate_messages am_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_nodejs _am_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(am_msgs_gennodejs)
add_dependencies(am_msgs_gennodejs am_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS am_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg;/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/kinetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg"
  "${MSG_I_FLAGS}"
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)
_generate_msg_py(am_msgs
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(am_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(am_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(am_msgs_generate_messages am_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/StateInput.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/CurrentStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Object.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Rect.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/BatteryStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedbackDiffDrive.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/DetectionResult.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MowerMovementState.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelEncoder.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/LoopData.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/Loop.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/SensorStatus.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/MotorFeedback.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelPower.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_msgs/msg/WheelCurrent.msg" NAME_WE)
add_dependencies(am_msgs_generate_messages_py _am_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(am_msgs_genpy)
add_dependencies(am_msgs_genpy am_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS am_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(am_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(am_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(am_msgs_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(am_msgs_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(am_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(am_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(am_msgs_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(am_msgs_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(am_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(am_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
