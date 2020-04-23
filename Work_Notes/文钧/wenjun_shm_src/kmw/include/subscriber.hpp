#ifndef _SUBSCRIBER_HPP_
#define _SUBSCRIBER_HPP_

#include <functional>
#include <memory>
#include <string>

#include <iostream>

#include "type.hpp"

namespace kmw {

class SubscriberBase {
public:
    SubscriberBase() {}
    virtual ~SubscriberBase() {}
    virtual bool Spin() = 0;
};

template <typename MessageType>
class Subscriber : public SubscriberBase {
public:
    Subscriber(const std::string& node_name, const std::string& topic_name,
               const std::string& subscriber_name, size_t queue_size,
               std::function<void(const MessageType&)> callback)
            : node_name_(node_name),
              topic_name_(topic_name),
              subscriber_name_(subscriber_name),
              whole_subscriber_name_("gos.sub." + node_name_ + "." +
                                     topic_name + "." + subscriber_name),
              queue_size_(queue_size),
              callback_(callback) {
        std::unique_ptr<boost::interprocess::message_queue> mq;
        try {
            boost::interprocess::message_queue::remove(
                    whole_subscriber_name_.c_str());
            mq = std::make_unique<boost::interprocess::message_queue>(
                    boost::interprocess::create_only,
                    whole_subscriber_name_.c_str(), queue_size, 1024 * 1024);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    virtual ~Subscriber() {}

    bool Spin() override {
        std::unique_ptr<boost::interprocess::message_queue> mq;
        try {
            mq = std::make_unique<boost::interprocess::message_queue>(
                    boost::interprocess::open_only,
                    whole_subscriber_name_.c_str());
            std::string buffer(mq->get_max_msg_size(), 0);
            size_t recv_size;
            unsigned int recv_priority;
            if (!mq->try_receive((void*) (buffer.data()), buffer.length(),
                                 recv_size, recv_priority)) {
                return false;
            }
            buffer.resize(recv_size);
            MessageType message;
            message.ParseFromString(buffer);
            if (callback_) {
                callback_(message);
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            return false;
        }
        return true;
    }

private:
    std::string node_name_;
    std::string topic_name_;
    std::string subscriber_name_;
    std::string whole_subscriber_name_;
    size_t queue_size_;
    std::function<void(const MessageType&)> callback_;
};
}  // namespace kmw

#endif  // _SUBSCRIBER_HPP_