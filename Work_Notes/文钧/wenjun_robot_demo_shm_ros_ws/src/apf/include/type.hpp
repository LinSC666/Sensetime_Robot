#ifndef _TYPE_HPP_
#define _TYPE_HPP_

#include <boost/atomic.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/lockfree/queue.hpp>

namespace gos {

const size_t kPoolNameMaxLen = 32;
const size_t kMessageSequenceMaxLen = 32;
const size_t kPoolSize = 1024 * 1024;
const size_t kSubscriberQueueSegmentSize = 1024 * 1024;

using CharAllocator = boost::interprocess::allocator<
        char, boost::interprocess::managed_shared_memory::segment_manager>;
using SharedString =
        boost::interprocess::basic_string<char, std::char_traits<char>,
                                          CharAllocator>;

struct MessageReference {
    char pool_name[kPoolNameMaxLen];
    char message_sequence[kMessageSequenceMaxLen];
};

struct MessageStorage {
    explicit MessageStorage(const CharAllocator& char_allocator)
            : content(char_allocator) {}
    MessageStorage(const std::string& message_content,
                   const CharAllocator& char_allocator)
            : content(message_content.cbegin(), message_content.cend(),
                      char_allocator) {}

    boost::atomic_uint32_t reference_counter;
    SharedString content;
};

// using SubscriberQueue =
//         boost::lockfree::queue<MessageReference,
//                                boost::lockfree::fixed_sized<true>>;

using SubscriberQueue = boost::lockfree::queue<MessageReference,
                                               boost::lockfree::capacity<1>>;

}  // namespace gos

#endif  // _TYPE_HPP_