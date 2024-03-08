#include "DeviceStatusMessage.h"

namespace smart_home {
    DeviceStatusMessage::DeviceStatusMessage(const DeviceStatus status) : status_(status) {};

    std::string DeviceStatusMessage::GetStatus() {
        switch (status_) {
            case DeviceStatus::Undefined:
                return "Undefined";
                break;

            case DeviceStatus::Off:
                return "Off";
                break;

            case DeviceStatus::Active:
                return "Active";
                break;

            case DeviceStatus::Standby:
                return "Standby";
                break;

            case DeviceStatus::Error:
                return "Error";
                break;
                
            default:
                return std::string();
                break;
        }
    }
} // namespace smart_home
