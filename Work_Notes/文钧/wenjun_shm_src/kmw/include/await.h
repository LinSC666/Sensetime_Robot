#ifndef _AWAIT_H_
#define _AWAIT_H_

#include <functional>

namespace kmw {

class Await {};

using Function = std::function<void(const Await&)>;

class Task {
public:
    explicit Task(Function task);
};
}  // namespace kmw

#endif  // _AWAIT_H_