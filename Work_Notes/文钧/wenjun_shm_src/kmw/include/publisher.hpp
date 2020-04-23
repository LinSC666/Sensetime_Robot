#ifndef _PUBLISHER_HPP_
#define _PUBLISHER_HPP_

#include <atomic>
#include <memory>
#include <string>
#include <vector>

#include <iostream>

#include "type.hpp"

namespace kmw {

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
              subscriber_names_(subscriber_names) {}
    ~Publisher() {}

    void Publish(const MessageType& message) {
        std::string serialized_message;
        message.SerializeToString(&serialized_message);

        for (auto& subscriber_name : subscriber_names_) {
            std::unique_ptr<boost::interprocess::message_queue> mq;
            try {
                mq = std::make_unique<boost::interprocess::message_queue>(
                        boost::interprocess::open_only,
                        subscriber_name.c_str());
            } catch (const boost::interprocess::interprocess_exception& e) {
                // message queue was not previously created.
                continue;
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }

            try {
                while (!mq->try_send(serialized_message.c_str(),
                                     serialized_message.length(), 0)) {
                    std::vector<uint8_t> temp_buffer(mq->get_max_msg_size());
                    size_t temp_buffer_recv_size;
                    unsigned int temp_buffer_recv_priority;
                    mq->try_receive(temp_buffer.data(), temp_buffer.size(),
                                    temp_buffer_recv_size,
                                    temp_buffer_recv_priority);
                }
            } catch (const boost::interprocess::interprocess_exception& e) {
                // message queue send on error.
                continue;
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }

        for (auto& subscriber_node : subscriber_nodes_) {
            // TODO: notify subscriber node
        }
    }

private:
private:
    std::string node_name_;
    std::string topic_name_;
    std::string publisher_name_;
    std::vector<std::string> subscriber_nodes_;
    std::vector<std::string> subscriber_names_;
};

}  // namespace kmw

#endif  // _PUBLISHER_HPP_