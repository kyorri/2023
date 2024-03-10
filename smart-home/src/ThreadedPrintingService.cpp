#include "ThreadedPrintingService.h"

#include "RoomPrinter.h"

namespace smart_home {
ThreadedPrintingService::ThreadedPrintingService(Room* room) : room_(room), period_(30) {};

ThreadedPrintingService::ThreadedPrintingService(Room* room, int period) : room_(room), period_(period) {

};

void ThreadedPrintingService::StartPrintingService() {
    printing_thread_ = std::thread(&smart_home::ThreadedPrintingService::PrintingTask, this);
    printing_thread_.detach();
};

void ThreadedPrintingService::StopPrintingService() {
    if (printing_thread_.joinable()) {
        printing_thread_.join();
    }
};

void ThreadedPrintingService::PrintingTask() {
    RoomPrinter rp;
    try {
        while (true) {
            std::lock_guard<std::mutex> lock(print_mutex_);

            if (room_ != nullptr) {
                rp.Print(room_);

                std::this_thread::sleep_for(std::chrono::seconds(period_));
            }
            else {
                throw std::runtime_error("Room address is nullptr, cannot print to the screen details!");
            }
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};
} // namespace smart_home