#include "MessageDeviceType.h"

namespace smart_home {
MessageDeviceType::MessageDeviceType(std::string type) : type_(type) {};

DeviceType MessageDeviceType::GetType() {
    if (type_ == "ACUnit") {
        return DeviceType::ACUnit;
    }
    else if (type_ == "Speaker") {
        return DeviceType::Speaker;
    }
    else if (type_ == "Thermostat") {
        return DeviceType::Thermostat;
    }
    else {
        return DeviceType::Undefined;
    }
};
} // namespace smart_home
