#include "DistanceSensor.h"

namespace smart_home_app {

    std::string DistanceSensor::GetInfo() {
        std::string message = std::string();
        message += "This Distance Sensor is reading a distance of " + std::to_string(GetReading()) + " " + GetUnits() + "%!\n";
        return message;
    }; 


    void DistanceSensor::SetReading(double new_reading) {
        reading_ = new_reading;
    };


    double DistanceSensor::GetReading() {
        return reading_;
    };


    std::string DistanceSensor::GetUnits() {
        return units_;
    }


    void DistanceSensor::SetUnits(std::string new_units) {
        units_ = new_units;
    }

} // namespace smart_home_app
