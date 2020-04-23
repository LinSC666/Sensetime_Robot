#include <chrono>
#include <iostream>
#include <thread>

#include "node.hpp"

#include "msg/vel.pb.h"

int main() {
    size_t count = 0;
    gos::Node node("node_sub", "/home/linsc/SenseTime_robot/Sensetime_Robot/Work_Notes/文钧/shm_ws/gos-refactor/test/config/config.json");
    std::shared_ptr<gos::Subscriber<gos_test::vel>> subscriber =
            node.CreateSubscriber<gos_test::vel>("vel", "sub1", 100, [&](const gos_test::vel& vel)
             {
                        ++count;
                        std::cout << count << std::endl;
                        std::cout << vel.linear_x() << std::endl;
                        std::cout << vel.angular_z() << std::endl;
            });

    node.Spin();
    return 0;
}