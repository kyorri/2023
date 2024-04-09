#ifndef SH_THREADPOOL_INCLUDE_H_
#define SH_THREADPOOL_INCLUDE_H_

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>

namespace smart_home {
    // std::function<void()> t;
class ThreadPool{
    using Task = std::function<void()>;

    public:
        ThreadPool() = delete;
        ThreadPool(int);

        ~ThreadPool();
        
        void enqueue(Task);
        
    private:
        std::vector<std::thread> threads_;
        std::queue<Task> tasks_;
        std::mutex pool_mutex_;
        std::atomic<bool> stop_;
        std::condition_variable condition_;
    
};
} // namespace smart_home

#endif // SH_THREADPOOL_INCLUDE_H_