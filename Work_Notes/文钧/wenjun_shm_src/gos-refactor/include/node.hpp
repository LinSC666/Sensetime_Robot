#ifndef _NODE_HPP_
#define _NODE_HPP_

#include <memory>
#include <string>
#include <deque>

#include "nlohmann/json.hpp"

#include "publisher.hpp"
#include "subscriber.hpp"

namespace gos {

class Node {
public:
    Node(const std::string& node_name, const std::string& config_file);
    std::string GetName() const;

    template <typename MessageType>
    std::shared_ptr<Publisher<MessageType>> CreatePublisher(
            const std::string& topic_name, const std::string& publisher_name) {
        if (config_json_.find(topic_name) == config_json_.end()) {
            throw std::runtime_error(
                    "Create Publisher failed. Can not find "
                    "configuration of topic: " +
                    topic_name);
        }
        auto topic_obj = config_json_[topic_name];

        auto nodes_obj = topic_obj["nodes"];
        std::vector<std::string> subscriber_nodes;
        for (size_t i = 0; i < nodes_obj.size(); ++i) {
            subscriber_nodes.push_back(nodes_obj[i].get<std::string>());
        }

        auto sub_obj = topic_obj["sub"];
        std::vector<std::string> subscriber_names;
        for (size_t i = 0; i < sub_obj.size(); ++i) {
            subscriber_names.push_back(sub_obj[i].get<std::string>());
        }

        return std::make_shared<Publisher<MessageType>>(
                node_name_, topic_name, publisher_name, subscriber_nodes,
                subscriber_names);
    }

    template <typename MessageType>
    std::shared_ptr<Subscriber<MessageType>> CreateSubscriber(
            const std::string& topic_name, const std::string& subscriber_name,
            size_t queue_size,
            std::function<void(const MessageType&)> callback) {
        if(config_json_.find(topic_name) == config_json_.end()){
            throw std::runtime_error(
                    "Create Subscriber failed. Can not find "
                    "configuration of topic: " +
                    topic_name);
        }

        std::string whole_subscriber_name = "gos.sub." + node_name_ + "." +
                                            topic_name + "." + subscriber_name;

        auto topic_obj = config_json_[topic_name];

        auto sub_obj = topic_obj["sub"];
        for (size_t i = 0; i < sub_obj.size(); ++i) {
            if (sub_obj[i].get<std::string>() == whole_subscriber_name) 
            {
                std::shared_ptr<Subscriber<MessageType>> subscriber =
                std::make_shared<Subscriber<MessageType>>(node_name_, topic_name, subscriber_name,queue_size, callback);
                std::weak_ptr<Subscriber<MessageType>> subscriber_weak_ptr =
                        subscriber;
                subscribers_.push_back(subscriber_weak_ptr);
                return subscriber;
            }
        }

        throw std::runtime_error(
                "Create Subscriber failed. Can not find subscriber name : " +
                whole_subscriber_name + " in config file");
    }

    void Spin();
    bool SpinOnce();
    void Wait();

private:
    std::string node_name_;
    std::string config_file_;
    nlohmann::json config_json_;

    std::deque<std::weak_ptr<SubscriberBase>> subscribers_;
};

}  // namespace gos

#endif  // _NODE_HPP_