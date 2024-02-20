#include "AirQualityLevelMessage.h"

namespace smart_home {
AirQualityLevelMessage::AirQualityLevelMessage(AirQualityLevel air_quality_lvl) : status_(air_quality_lvl) {};

std::string AirQualityLevelMessage::GetStatus() {
    switch (status_) {
        case AirQualityLevel::Good:
            return "Good";
            break;

        case AirQualityLevel::Moderate:
            return "Moderate";
            break;

        case AirQualityLevel::Unhealty_For_Sensitive_Groups:
            return "Unhealthy for sensitive groups";
            break;

        case AirQualityLevel::Unhealthy:
            return "Unhealthy";
            break;

        case AirQualityLevel::Very_Unhealthy:
            return "Very unhealthy";
            break;

        default:
            return std::string();
            break;
    };
};
} // namespace smart_home
