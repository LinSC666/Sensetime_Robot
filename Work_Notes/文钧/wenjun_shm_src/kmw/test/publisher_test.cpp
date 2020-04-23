#include <chrono>
#include <thread>

#include "node.hpp"

#include "msg/vel.pb.h"

int main() {
    kmw::Node node("node_pub", "config.json");
    std::shared_ptr<kmw::Publisher<gos_test::vel>> publisher =
            node.CreatePublisher<gos_test::vel>("vel", "pub1");

    gos_test::vel vel;
    vel.set_linear_x(1.0f);
    vel.set_angular_z(2.0f);
    while (true) {
        publisher->Publish(vel);
    }
    return 0;
}