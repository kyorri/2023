#include "DevicePrinter.h"

#include <iostream>
#include <algorithm>

namespace smart_home_app {

void DevicePrinter::Print() {
    for(Device* d : devices_) {
        std::cout << d->GetInfo() << std::endl;
    }
}


void DevicePrinter::AddDevice(Device* new_device) {
    devices_.push_back(new_device);
}


void DevicePrinter::RemoveDevice(Device* rem_device) {
    auto it = std::find(devices_.begin(), devices_.end(), rem_device);
    devices_.erase(it);
}

} // smart_home_app