#ifndef SH_THREADEDPRINTINGSERVICE_INCLUDE_H_
#define SH_THREADEDPRINTINGSERVICE_INCLUDE_H_

#include "RoomPrinter.h"

#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
<<<<<<< HEAD
#include <condition_variable>
=======
>>>>>>> featureHW8_client_server_impl

namespace smart_home {
class ThreadedPrintingService {
    public:
        ThreadedPrintingService(Room*);
        ThreadedPrintingService(Room*, int);
        
        void StartPrintingService();
        void StopPrintingService();

        void PrintingTask();
    private:
        Room* room_;
        int period_;
        std::atomic<bool> stop_;
        std::thread printing_thread_;
        std::mutex print_mutex_;

};
} // namespace smart_home

#endif  // SH_THREADEDPRINTINGSERVICE_INCLUDE_H_