#include "HumiditySensor.h"

namespace smart_home_app {

    std::string HumiditySensor::GetInfo() {
        std::string message = std::string();
        message += "This Humidity Sensor is reading a humidity level of " + std::to_string(GetPercent()) + "%!\n";
        return message;
    };


    void HumiditySensor::SetReading(double new_reading) {
        if (new_reading > 1.0) {
            reading_ = 1.0;
        }
        else if (new_reading < 0.0) {
            reading_ = 0.0;
        }
        else {
            reading_ = new_reading;
        }
    };


    double HumiditySensor::GetReading() {
        return reading_;
    };


    uint32_t HumiditySensor::GetPercent() {
        return (uint32_t)(reading_ * 100);
    };

} // namespace smart_home_app
