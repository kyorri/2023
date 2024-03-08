#include "MessageSensorType.h"

namespace smart_home {
MessageSensorType::MessageSensorType(std::string type) : type_(type) {};

SensorType MessageSensorType::GetType() {
    if (type_ == "Temperature") {
        return SensorType::Temperature;
    }
    else if (type_ == "Humidity") {
        return SensorType::Humidity;
    }
    else if (type_ == "AirQualityLevel") {
        return SensorType::AirQualityLevel;
    }
    else {
        return SensorType::Undefined;
    }
};
} // namespace smart_home
