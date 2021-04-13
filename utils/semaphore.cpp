#include "semaphore.hpp"

tcp2serial::semaphore::semaphore (bool count): _count(count) {
}

void tcp2serial::semaphore::notify() {
    std::unique_lock<std::mutex> lock(_mtx);
    _count = true;
    _cv.notify_one();
}

void tcp2serial::semaphore::wait() {
    std::unique_lock<std::mutex> lock(_mtx);
    while(_count == false) {
        _cv.wait(lock);
    }
    _count = false;
}
