# Install script for directory: /home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/hq_decision_making_parser

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/build/hq_decision_making_parser/catkin_generated/installspace/hq_decision_making_parser.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hq_decision_making_parser/cmake" TYPE FILE FILES "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/build/hq_decision_making_parser/catkin_generated/installspace/hq_decision_making_parser-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hq_decision_making_parser/cmake" TYPE FILE FILES
    "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/build/hq_decision_making_parser/catkin_generated/installspace/hq_decision_making_parserConfig.cmake"
    "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/build/hq_decision_making_parser/catkin_generated/installspace/hq_decision_making_parserConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hq_decision_making_parser" TYPE FILE FILES "/home/linsc/ROS_Project/Sensetime_ws/dengwenjun_old_ws/src/hq_decision_making_parser/package.xml")
endif()

