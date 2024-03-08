#include "MessageDeviceStatus.h"

namespace smart_home {
MessageDeviceStatus::MessageDeviceStatus(std::string status) : status_(status) {};

DeviceStatus MessageDeviceStatus::GetStatus() {
    if (status_ == "Off") {
        return DeviceStatus::Off;
    }
    else if (status_ == "Active") {
        return DeviceStatus::Active;
    }
    else if (status_ == "Standby") {
        return DeviceStatus::Standby;
    }
    else if (status_ == "Error") {
        return DeviceStatus::Error;
    }
    else {
        return DeviceStatus::Undefined;
    }
};
} // namespace smart_home
