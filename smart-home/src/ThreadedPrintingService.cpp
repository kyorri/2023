#include "ThreadedPrintingService.h"
#include "RoomPrinter.h"
#include <iostream> // for std::cerr

namespace smart_home {
    ThreadedPrintingService::ThreadedPrintingService(Room* room) : room_(room), period_(30), stop_(false) {}

    ThreadedPrintingService::ThreadedPrintingService(Room* room, int period) : room_(room), period_(period), stop_(false) {}

    void ThreadedPrintingService::StartPrintingService() {
        printing_thread_ = std::thread(&ThreadedPrintingService::PrintingTask, this);
    }

    void ThreadedPrintingService::StopPrintingService() {
        stop_ = true;
        if (printing_thread_.joinable()) {
            printing_thread_.join();
        }
    }

    void ThreadedPrintingService::PrintingTask() {
        RoomPrinter rp;
        try {
            while (!stop_) {
                if (room_ != nullptr) {
                    std::lock_guard<std::mutex> lock(print_mutex_);
                    rp.Print(room_);
                    std::this_thread::sleep_for(std::chrono::seconds(period_));
                } else {
                    throw std::runtime_error("Room address is nullptr, cannot print to the screen details!");
                }
            }
        } catch (std::exception& e) {
            std::lock_guard<std::mutex> lock(print_mutex_);
            std::cerr << e.what() << std::endl;
        }
    }
} // namespace smart_home
