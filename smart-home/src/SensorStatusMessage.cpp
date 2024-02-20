#include "SensorStatusMessage.h"

namespace smart_home {
SensorStatusMessage::SensorStatusMessage(SensorStatus status) : status_(status) {};

std::string SensorStatusMessage::GetStatus() {
    switch (status_) {
        case SensorStatus::Undefined:
            return "Undefined";
            break;
        case SensorStatus::Off:
            return "Off";
            break;
        case SensorStatus::Active:
            return "Active";
            break;
        case SensorStatus::Standby:
            return "Standby";
            break;
        case SensorStatus::Error:
            return "Error";
            break;
        default:
            break;
    }
};
} // namespace smart_home
