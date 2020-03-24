# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "am_driver_safe: 0 messages, 2 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(am_driver_safe_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv" NAME_WE)
add_custom_target(_am_driver_safe_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_driver_safe" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv" ""
)

get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv" NAME_WE)
add_custom_target(_am_driver_safe_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "am_driver_safe" "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(am_driver_safe
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_driver_safe
)
_generate_srv_cpp(am_driver_safe
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_driver_safe
)

### Generating Module File
_generate_module_cpp(am_driver_safe
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_driver_safe
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(am_driver_safe_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(am_driver_safe_generate_messages am_driver_safe_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv" NAME_WE)
add_dependencies(am_driver_safe_generate_messages_cpp _am_driver_safe_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv" NAME_WE)
add_dependencies(am_driver_safe_generate_messages_cpp _am_driver_safe_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(am_driver_safe_gencpp)
add_dependencies(am_driver_safe_gencpp am_driver_safe_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS am_driver_safe_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages

### Generating Services
_generate_srv_eus(am_driver_safe
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_driver_safe
)
_generate_srv_eus(am_driver_safe
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_driver_safe
)

### Generating Module File
_generate_module_eus(am_driver_safe
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_driver_safe
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(am_driver_safe_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(am_driver_safe_generate_messages am_driver_safe_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv" NAME_WE)
add_dependencies(am_driver_safe_generate_messages_eus _am_driver_safe_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv" NAME_WE)
add_dependencies(am_driver_safe_generate_messages_eus _am_driver_safe_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(am_driver_safe_geneus)
add_dependencies(am_driver_safe_geneus am_driver_safe_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS am_driver_safe_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(am_driver_safe
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_driver_safe
)
_generate_srv_lisp(am_driver_safe
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_driver_safe
)

### Generating Module File
_generate_module_lisp(am_driver_safe
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_driver_safe
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(am_driver_safe_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(am_driver_safe_generate_messages am_driver_safe_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv" NAME_WE)
add_dependencies(am_driver_safe_generate_messages_lisp _am_driver_safe_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv" NAME_WE)
add_dependencies(am_driver_safe_generate_messages_lisp _am_driver_safe_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(am_driver_safe_genlisp)
add_dependencies(am_driver_safe_genlisp am_driver_safe_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS am_driver_safe_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages

### Generating Services
_generate_srv_nodejs(am_driver_safe
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_driver_safe
)
_generate_srv_nodejs(am_driver_safe
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_driver_safe
)

### Generating Module File
_generate_module_nodejs(am_driver_safe
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_driver_safe
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(am_driver_safe_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(am_driver_safe_generate_messages am_driver_safe_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv" NAME_WE)
add_dependencies(am_driver_safe_generate_messages_nodejs _am_driver_safe_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv" NAME_WE)
add_dependencies(am_driver_safe_generate_messages_nodejs _am_driver_safe_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(am_driver_safe_gennodejs)
add_dependencies(am_driver_safe_gennodejs am_driver_safe_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS am_driver_safe_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(am_driver_safe
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_driver_safe
)
_generate_srv_py(am_driver_safe
  "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_driver_safe
)

### Generating Module File
_generate_module_py(am_driver_safe
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_driver_safe
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(am_driver_safe_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(am_driver_safe_generate_messages am_driver_safe_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/turnOfLoopCmd.srv" NAME_WE)
add_dependencies(am_driver_safe_generate_messages_py _am_driver_safe_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/am_driver_safe/srv/TifCmd.srv" NAME_WE)
add_dependencies(am_driver_safe_generate_messages_py _am_driver_safe_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(am_driver_safe_genpy)
add_dependencies(am_driver_safe_genpy am_driver_safe_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS am_driver_safe_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_driver_safe)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/am_driver_safe
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(am_driver_safe_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(am_driver_safe_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET am_driver_safe_generate_messages_cpp)
  add_dependencies(am_driver_safe_generate_messages_cpp am_driver_safe_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_driver_safe)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/am_driver_safe
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(am_driver_safe_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(am_driver_safe_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET am_driver_safe_generate_messages_eus)
  add_dependencies(am_driver_safe_generate_messages_eus am_driver_safe_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_driver_safe)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/am_driver_safe
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(am_driver_safe_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(am_driver_safe_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET am_driver_safe_generate_messages_lisp)
  add_dependencies(am_driver_safe_generate_messages_lisp am_driver_safe_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_driver_safe)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/am_driver_safe
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(am_driver_safe_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(am_driver_safe_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET am_driver_safe_generate_messages_nodejs)
  add_dependencies(am_driver_safe_generate_messages_nodejs am_driver_safe_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_driver_safe)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_driver_safe\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/am_driver_safe
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(am_driver_safe_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(am_driver_safe_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET am_driver_safe_generate_messages_py)
  add_dependencies(am_driver_safe_generate_messages_py am_driver_safe_generate_messages_py)
endif()
