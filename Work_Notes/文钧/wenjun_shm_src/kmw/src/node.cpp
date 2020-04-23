#include "node.hpp"

#include <fstream>

#include <boost/interprocess/managed_shared_memory.hpp>

#include <iostream>

namespace kmw {

Node::Node(const std::string& node_name, const std::string& config_file)
        : node_name_(node_name),
          config_file_(config_file),
          whole_node_name_("gos.node." + node_name) {
    std::fstream config_file_stream(config_file);
    config_json_ = nlohmann::json::parse(config_file_stream);
}

std::string Node::GetName() const {
    return node_name_;
}

void Node::Spin() {
    while (true) {
        if (!SpinOnce()) {
            Wait();
        }
    }
}

bool Node::SpinOnce() {
    bool is_all_queue_empty = true;
    for (auto subscriber_iter = subscribers_.begin();
         subscriber_iter != subscribers_.end(); ++subscriber_iter) {
        if (auto subscriber = subscriber_iter->lock()) {
            if (subscriber->Spin()) {
                is_all_queue_empty = false;
            }
        } else {
            subscriber_iter = subscribers_.erase(subscriber_iter);
        }
    }
    return !is_all_queue_empty;
}

void Node::Wait() {}

}  // namespace kmw