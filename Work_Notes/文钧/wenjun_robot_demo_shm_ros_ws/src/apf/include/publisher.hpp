#ifndef _PUBLISHER_HPP_
#define _PUBLISHER_HPP_

#include <atomic>
#include <memory>
#include <string>
#include <vector>

#include "type.hpp"

namespace gos {

template <typename MessageType>
class Publisher {
public:
    Publisher(const std::string& node_name, const std::string& topic_name,
              const std::string& publisher_name,
              const std::vector<std::string>& subscriber_nodes,
              const std::vector<std::string>& subscriber_names)
            : node_name_(node_name),
              topic_name_(topic_name),
              publisher_name_(publisher_name),
              subscriber_nodes_(subscriber_nodes),
              subscriber_names_(subscriber_names),
              message_sequence_(0) {}
    ~Publisher() {}

    void Publish(const MessageType& message) {
        std::string serialized_message;
        message.SerializeToString(&serialized_message);
        std::string message_sequence_str = std::to_string(message_sequence_);
        ++message_sequence_;

        MessageReference message_reference;
        memset(message_reference.pool_name, 0, kPoolNameMaxLen);
        memset(message_reference.message_sequence, 0, kMessageSequenceMaxLen);

        memcpy(message_reference.message_sequence, message_sequence_str.c_str(),
               message_sequence_str.length());

        if (pools_.empty()) {
            AppendNewPool();
        }

        boost::interprocess::managed_shared_memory pool;
        MessageStorage* message_storage = nullptr;

        for (size_t i = 0; i < pools_.size(); ++i) {
            std::string& pool_name = pools_[i];
            pool = boost::interprocess::managed_shared_memory(
                    boost::interprocess::open_or_create, pool_name.c_str(),
                    kPoolSize);

            if (pool.get_free_memory() < serialized_message.length() + 256) {
                if (i == pools_.size() - 1) {
                    AppendNewPool();
                }
                continue;
            }

            CharAllocator char_allocator(pool.get_segment_manager());
            message_storage = pool.construct<MessageStorage>(
                    message_sequence_str.c_str())(serialized_message,
                                                  char_allocator);
            message_storage->reference_counter = subscriber_names_.size();

            memcpy(message_reference.pool_name, pool_name.c_str(),
                   pool_name.length());
            break;
        }

        for (auto& subscriber_name : subscriber_names_) {
            boost::interprocess::managed_shared_memory subscriber_queue_segment(
                    boost::interprocess::open_or_create,
                    subscriber_name.c_str(), kSubscriberQueueSegmentSize);
            auto subscriber_queue_ret =
                    subscriber_queue_segment.find<SubscriberQueue>("queue");
            SubscriberQueue* subscriber_queue = subscriber_queue_ret.first;
            if (!subscriber_queue) {
                --(message_storage->reference_counter);
                if (message_storage->reference_counter <= 0) {
                    pool.destroy<MessageStorage>(
                            message_reference.message_sequence);
                }
                continue;
            }
            while (!subscriber_queue->push(message_reference)) {
                MessageReference last_message_reference;
                subscriber_queue->pop(last_message_reference);
                std::string last_message_reference_pool_name(
                        last_message_reference.pool_name);
                std::string last_message_reference_message_sequence(
                        last_message_reference.message_sequence);

                boost::interprocess::managed_shared_memory pool(
                        boost::interprocess::open_or_create,
                        last_message_reference_pool_name.c_str(), kPoolSize);
                CharAllocator char_allocator(pool.get_segment_manager());
                auto last_message_storage_ret = pool.find<MessageStorage>(
                        last_message_reference_message_sequence.c_str());
                MessageStorage* last_message_storage =
                        last_message_storage_ret.first;

                if (last_message_storage) {
                    --(last_message_storage->reference_counter);
                    if (last_message_storage->reference_counter <= 0) {
                        pool.destroy<MessageStorage>(
                                last_message_reference_message_sequence
                                        .c_str());
                    }
                }
            }
        }

        for (auto& subscriber_node : subscriber_nodes_) {
            // TODO: notify subscriber node
        }
    }

private:
    std::string GeneratePoolName(size_t pool_id) {
        return "gos.pool." + node_name_ + "." + publisher_name_ + "." +
               std::to_string(pool_id);
    }

    void CreatePool(const std::string& pool_name) {
        boost::interprocess::managed_shared_memory pool(
                boost::interprocess::open_or_create, pool_name.c_str(),
                kPoolSize);
    }

    void AppendNewPool() {
        auto pool_name = GeneratePoolName(pools_.size());
        CreatePool(pool_name);
        pools_.push_back(pool_name);
    }

private:
    std::string node_name_;
    std::string topic_name_;
    std::string publisher_name_;
    std::vector<std::string> subscriber_nodes_;
    std::vector<std::string> subscriber_names_;
    std::vector<std::string> pools_;
    std::atomic_uint64_t message_sequence_;
};

}  // namespace gos

#endif  // _PUBLISHER_HPP_