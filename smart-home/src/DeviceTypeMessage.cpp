#include "DeviceTypeMessage.h"

namespace smart_home {
DeviceTypeMessage::DeviceTypeMessage(DeviceType type) : type_(type) {};

std::string DeviceTypeMessage::GetType() {
    switch (type_) {
        case DeviceType::ACUnit:
            return "ACUnit";
            break;

        case DeviceType::Speaker:
            return "Speaker";
            break;

        case DeviceType::Thermostat:
            return "Thermostat";
            break;

        default:
            return std::string();
            break;
    }
};
} // namespace smart_home
