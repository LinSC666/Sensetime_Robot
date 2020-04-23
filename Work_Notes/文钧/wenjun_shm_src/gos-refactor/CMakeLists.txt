cmake_minimum_required(VERSION 2.8)
project(gos)

add_compile_options(-std=c++11)

include_directories(include)

add_library(gos SHARED src/node.cpp)

add_library(vel SHARED test/msg/vel.pb.cc)

add_executable(publisher_test test/publisher_test.cpp)
target_link_libraries(publisher_test gos vel protobuf rt pthread)

add_executable(subscriber_test test/subscriber_test.cpp)
target_link_libraries(subscriber_test gos vel protobuf rt pthread)



