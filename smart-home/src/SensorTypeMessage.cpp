#include "SensorTypeMessage.h"

namespace smart_home {
SensorTypeMessage::SensorTypeMessage(SensorType type) : type_(type) {};

std::string SensorTypeMessage::GetType() {
    switch (type_) {
        case SensorType::Temperature:
            return "Temperature";
            break;

        case SensorType::Humidity:
            return "Humidity";
            break;

        case SensorType::AirQualityLevel:
            return "AirQualityLevel";
            break;

        default:
            return std::string();
            break;
    }
};
} // namespace smart_home
