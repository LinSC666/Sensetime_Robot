#include <chrono>
#include <thread>

#include "node.hpp"

#include "msg/vel.pb.h"

int main() {
    gos::Node node("node_pub", "/home/linsc/SenseTime_robot/Sensetime_Robot/Work_Notes/文钧/shm_ws/gos-refactor/test/config/config.json");
    std::shared_ptr<gos::Publisher<gos_test::vel>> publisher =
            node.CreatePublisher<gos_test::vel>("vel", "pub1");

    gos_test::vel vel;
    vel.set_linear_x(1.12f);
    vel.set_angular_z(2.15f);
    while (true) {
        publisher->Publish(vel);
    }
    return 0;
}