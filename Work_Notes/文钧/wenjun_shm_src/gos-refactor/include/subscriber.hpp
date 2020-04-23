#ifndef _SUBSCRIBER_HPP_
#define _SUBSCRIBER_HPP_

#include <functional>
#include <memory>
#include <string>

#include "type.hpp"

namespace gos {

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
        boost::interprocess::managed_shared_memory subscriber_queue_segment(
                boost::interprocess::open_or_create,
                whole_subscriber_name_.c_str(), kSubscriberQueueSegmentSize);
        SubscriberQueue* sub_queue =
                subscriber_queue_segment.find_or_construct<SubscriberQueue>(
                        "queue")();
    }
    virtual ~Subscriber() {}

    bool Spin() override {
        boost::interprocess::managed_shared_memory subscriber_queue_segment(
                boost::interprocess::open_or_create,
                whole_subscriber_name_.c_str(), kSubscriberQueueSegmentSize);
        auto sub_queue_ret =
                subscriber_queue_segment.find<SubscriberQueue>("queue");
        SubscriberQueue* sub_queue = sub_queue_ret.first;
        if (!sub_queue) {
            SubscriberQueue* sub_queue =
                    subscriber_queue_segment.find_or_construct<SubscriberQueue>(
                            "queue")();
        }
        MessageReference message_reference;
        if (!sub_queue->pop(message_reference)) {
            return false;
        }

        boost::interprocess::managed_shared_memory pool(
                boost::interprocess::open_or_create,
                message_reference.pool_name, kPoolSize);
        auto message_storage_ret =
                pool.find<MessageStorage>(message_reference.message_sequence);
        MessageStorage* message_storage = message_storage_ret.first;
        if (!message_storage) {
            return false;
        }

        std::string content(message_storage->content.cbegin(),
                            message_storage->content.cend());
        --(message_storage->reference_counter);
        if (message_storage->reference_counter <= 0) {
            pool.destroy<MessageStorage>(message_reference.message_sequence);
        }

        MessageType message;
        message.ParseFromString(content);
        callback_(message);
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
}  // namespace gos

#endif  // _SUBSCRIBER_HPP_