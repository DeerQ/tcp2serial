#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP
#include <mutex>
#include <condition_variable>
namespace tcp2serial {
class semaphore {
    public:
        semaphore (bool count = false);
        void notify();
        void wait();

    private:
        std::mutex _mtx;
        std::condition_variable _cv;
        bool _count;
};
}
#endif
