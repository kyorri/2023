#include "ThreadPool.h"

namespace smart_home {

ThreadPool::ThreadPool(int thread_num) : stop_(false)  {
    for (int i = 0; i < thread_num; i++) {
        threads_.emplace_back(
            [this](){
                while (true) {
                    Task t;
                    {
                        std::unique_lock<std::mutex> lock(pool_mutex_);
                        condition_.wait(lock, 
                            [this] () {
                                return !tasks_.empty() || stop_;
                            });
                        if (stop_ && tasks_.empty()) {
                            return;
                        }
                        t = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    t();
                }
            });
    }
};

ThreadPool::~ThreadPool() {
    stop_ = true;
    condition_.notify_all();
    for (std::thread& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }

};

void ThreadPool::enqueue(Task new_task) { 
    { 
        std::unique_lock<std::mutex> lock(pool_mutex_); 
        tasks_.emplace(std::move(new_task)); 
    } 
    condition_.notify_one(); 
} 

} // namespace smart_home