#include "MessageSensorStatus.h"

namespace smart_home {
MessageSensorStatus::MessageSensorStatus(std::string status) : status_(status) {};

SensorStatus MessageSensorStatus::GetStatus() {
    if (status_ == "Off") {
        return SensorStatus::Off;
    }
    else if (status_ == "Active") {
        return SensorStatus::Active;
    }
    else if (status_ == "Standby") {
        return SensorStatus::Standby;
    }
    else if (status_ == "Error") {
        return SensorStatus::Error;
    }
    else {
        return SensorStatus::Undefined;
    }
};
} // namespace smart_home
