#include "ACUnitDevice.h"

#include <iostream>
#include <vector>
#include <algorithm>

namespace smart_home_app {

    std::string ACUnitDevice::GetType() {
        return "acunit";
    }

    std::string ACUnitDevice::GetInfo() {
        std::string message = std::string();
        message += "This AC Unit is " + GetStatus() + " and has these sensors attached:\n";
        for (auto s : sensors_) {
            message += "\t-" + s->GetInfo();
        }
        return message;
    };


    std::string ACUnitDevice::GetStatus() {
        if (status_) {
            return "on";
        }
        return "off";
    };


    void ACUnitDevice::TurnOff() {
        status_ = false;
    };


    void ACUnitDevice::TurnOn() {
        status_ = true;
    };


    void ACUnitDevice::AddSensor(Sensor* new_sensor) {
        sensors_.push_back(new_sensor);
    };


    void ACUnitDevice::RemoveSensor(Sensor* rem_sensor) {
        auto it = std::find(sensors_.begin(), sensors_.end(), rem_sensor);
        sensors_.erase(it);
    };


    std::vector<Sensor*> ACUnitDevice::GetSensors() {
        return sensors_;
    };

} // namespace smart_home_app