cmake_minimum_required(VERSION 2.8)
project(shareMemory_test)

add_compile_options(-std=c++11)

add_library(msg.pb SHARED  msg.pb.cc)
add_library(msg_pic.pb SHARED  msg_pic.pb.cc)
########################################################################################
add_library(publish_subscribe_proto_msg_pic_mock_data SHARED  publish_subscribe_proto_msg_pic_mock_data.cpp)
########################################################################################

########################################################################################
add_library(publish_subscribe_proto_msg_pic SHARED  publish_subscribe_proto_msg_pic.cpp)
########################################################################################

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

##########################################################################################################################
add_executable(publish_mock_data publish_mock_data.cpp)
target_link_libraries(publish_mock_data publish_subscribe_proto_msg_pic_mock_data msg.pb protobuf pthread ${OpenCV_LIBS})

add_executable(subscribe_mock_data subscribe_mock_data.cpp)
target_link_libraries(subscribe_mock_data publish_subscribe_proto_msg_pic_mock_data msg.pb protobuf pthread ${OpenCV_LIBS})
##########################################################################################################################

##########################################################################################################################
add_executable(publish publish.cpp)
target_link_libraries(publish publish_subscribe_proto_msg_pic msg.pb protobuf pthread ${OpenCV_LIBS})

add_executable(subscribe1 subscribe1.cpp)
target_link_libraries(subscribe1 publish_subscribe_proto_msg_pic msg.pb protobuf pthread ${OpenCV_LIBS})
##########################################################################################################################


##########################################################################################################################
add_executable(publish_3msg_pic_proto publish_3msg_pic_proto.cpp)
target_link_libraries(publish_3msg_pic_proto  msg_pic.pb protobuf pthread ${OpenCV_LIBS})

add_executable(subscribe_3msg_pic_proto subscribe_3msg_pic_proto.cpp)
target_link_libraries(subscribe_3msg_pic_proto  msg_pic.pb protobuf pthread ${OpenCV_LIBS})
##########################################################################################################################


##########################################################################################################################
add_executable(publish_3msg_pic_proto_delay_test publish_3msg_pic_proto_delay_test.cpp)
target_link_libraries(publish_3msg_pic_proto_delay_test  msg_pic.pb protobuf pthread ${OpenCV_LIBS})

add_executable(subscribe_3msg_pic_proto_delay_test subscribe_3msg_pic_proto_delay_test.cpp)
target_link_libraries(subscribe_3msg_pic_proto_delay_test  msg_pic.pb protobuf pthread ${OpenCV_LIBS})
##########################################################################################################################


add_executable(subscribe_3msg_pic subscribe_3msg_pic.cpp)
target_link_libraries(subscribe_3msg_pic msg.pb protobuf pthread ${OpenCV_LIBS})

add_executable(publish_3msg_pic publish_3msg_pic.cpp)
target_link_libraries(publish_3msg_pic msg.pb protobuf pthread ${OpenCV_LIBS})


add_executable(shm_master shm_master.cpp)
target_link_libraries(shm_master msg.pb protobuf pthread ${OpenCV_LIBS})

add_executable(string_to_char  string_to_char.cpp)
target_link_libraries(string_to_char )


