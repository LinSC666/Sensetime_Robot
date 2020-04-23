cmake_minimum_required(VERSION 2.8)
project(kmw)

add_compile_options(-std=c++14)

include_directories(include)

add_library(kmw SHARED src/node.cpp)

add_library(vel SHARED test/msg/vel.pb.cc)

add_executable(publisher_test test/publisher_test.cpp)
target_link_libraries(publisher_test kmw vel protobuf rt pthread)

add_executable(subscriber_test test/subscriber_test.cpp)
target_link_libraries(subscriber_test kmw vel protobuf rt pthread)



