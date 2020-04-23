cmake_minimum_required(VERSION 2.8.3)
set(PROJECT_NAME detection)
project(${PROJECT_NAME})

# mynteye part
########################################################################################################
include(./cmake/Common.cmake)
# options
option(DEBUG "Enable Debug Log" OFF)
option(TIMECOST "Enable Time Cost" OFF)
add_definitions(-DLOG_TAG=MYNTEYE)
if(DEBUG)
  add_definitions(-DDEBUG)
  message(STATUS "Using macro DEBUG")
endif()
if(TIMECOST)
  add_definitions(-DTIME_COST)
  message(STATUS "Using macro TIME_COST")
endif()
# flags
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
include(./cmake/DetectCXX11.cmake)
# packages
LIST(APPEND CMAKE_MODULE_PATH ./cmake)
LIST(APPEND CMAKE_PREFIX_PATH ./_install/lib/cmake)
find_package(mynteyed REQUIRED)
message(STATUS "Found mynteye: ${mynteyed_VERSION}")
if(NOT mynteyed_WITH_OPENCV)
  message(FATAL_ERROR "Please install OpenCV, then rebuild mynteye with it."
      " Because these samples use OpenCV to show images.")
endif()
include(./cmake/DetectOpenCV.cmake)
########################################################################################################


# model part
########################################################################################################
set (CMAKE_CXX_STANDARD 11)

# OpenCV
find_package(OpenCV REQUIRED)

find_package(CUDA)
message("-- OpenCV version: ${OpenCV_VERSION}")
message("-- CUDA version: ${CUDA_VERSION}")
message("-- CUDA_NVCC_FLAGS: ${CUDA_NVCC_FLAGS}")

set(
	CUDA_NVCC_FLAGS
	${CUDA_NVCC_FLAGS}; 
    -O3 
	-gencode arch=compute_53,code=sm_53
)

if(CUDA_VERSION_MAJOR GREATER 9)
	message("-- CUDA ${CUDA_VERSION_MAJOR} detected, enabling SM_72")

	set(
		CUDA_NVCC_FLAGS
		${CUDA_NVCC_FLAGS}; 
		-gencode arch=compute_72,code=sm_72
	)

endif()
message("-- CUDA_NVCC_FLAGS: ${CUDA_NVCC_FLAGS}")

# tensorRT
message("CUDA_TOOLKIT_ROOT_DIR = ${CUDA_TOOLKIT_ROOT_DIR}")

find_path(TENSORRT_INCLUDE_DIR NvInfer.h
  HINTS ${TENSORRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR} /usr/include
  PATH_SUFFIXES include)
find_path(TENSORRT_INCLUDE_DIR NvInferPlugin.h
  HINTS ${TENSORRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR}
  PATH_SUFFIXES include)
MESSAGE(STATUS "Found TensorRT headers at ${TENSORRT_INCLUDE_DIR}")

find_library(TENSORRT_LIBRARY_INFER nvinfer
  HINTS ${TENSORRT_ROOT} ${TENSORRT_BUILD} ${CUDA_TOOLKIT_ROOT_DIR}
  PATH_SUFFIXES lib lib64 lib/x64 lib/aarch64-linux-gnu)
find_library(TENSORRT_LIBRARY_INFER_PLUGIN nvinfer_plugin
  HINTS  ${TENSORRT_ROOT} ${TENSORRT_BUILD} ${CUDA_TOOLKIT_ROOT_DIR}
  PATH_SUFFIXES lib lib64 lib/x64 lib/aarch64-linux-gnu)
find_library(TENSORRT_LIBRARY_PARSER nvparsers
  HINTS  ${TENSORRT_ROOT} ${TENSORRT_BUILD} ${CUDA_TOOLKIT_ROOT_DIR}
  PATH_SUFFIXES lib lib64 lib/x64 lib/aarch64-linux-gnu)
find_library(TENSORRT_LIBRARY_ONNXPARSER nvonnxparser
  HINTS  ${TENSORRT_ROOT} ${TENSORRT_BUILD} ${CUDA_TOOLKIT_ROOT_DIR}
  PATH_SUFFIXES lib lib64 lib/x64 lib/aarch64-linux-gnu)
set(TENSORRT_LIBRARY ${TENSORRT_LIBRARY_INFER} ${TENSORRT_LIBRARY_INFER_PLUGIN} ${TENSORRT_LIBRARY_PARSER} ${TENSORRT_LIBRARY_ONNXPARSER})
message(STATUS "Find TensorRT libs at ${TENSORRT_LIBRARY}")
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  TENSORRT DEFAULT_MSG TENSORRT_INCLUDE_DIR TENSORRT_LIBRARY)
if(NOT TENSORRT_FOUND)
  message(ERROR
    "Cannot find TensorRT library.")
endif()
########################################################################################################



# ROS part
########################################################################################################
find_package(catkin REQUIRED COMPONENTS
  am_msgs
  geometry_msgs
  roscpp
  rospy
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS am_msgs geometry_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
########################################################################################################




# common part
########################################################################################################
include_directories(./include )

AUX_SOURCE_DIRECTORY(./src DIR_SRCS)
message("DIR_SRCS = ${DIR_SRCS}")
AUX_SOURCE_DIRECTORY(./src/util DIR_SRC_UTILS)
message("DIR_SRC_UTILS = ${DIR_SRC_UTILS}")
set(DEPENDENCY ${DIR_SRCS} ${DIR_SRC_UTILS})
message("DEPENDENCY = ${DEPENDENCY}")

cuda_add_executable(
  ${PROJECT_NAME} 
  ${DEPENDENCY} 
)

target_link_libraries(${PROJECT_NAME} 
  mynteye_depth
  ${TENSORRT_LIBRARY}
  ${OpenCV_LIBS}
  ${catkin_LIBRARIES}
)


