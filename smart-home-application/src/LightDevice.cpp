#include "LightDevice.h"

#include <algorithm>

namespace smart_home_app
{

    std::string LightDevice::GetInfo() {
        std::string message = std::string();
        message += "These Lights are " + GetStatus() + ", have " + std::to_string(GetBrightness()) + " lumens, and has these sensors attached:\n";
        for (auto s : sensors_) {
            message += "\t-" + s->GetInfo();
        }
        return message;
    };


    std::string LightDevice::GetStatus() {
        if (status_) {
            return "on";
        }
        return "off";
    };


    void LightDevice::TurnOff() {
        status_ = false;
    };


    void LightDevice::TurnOn() {
        status_ = true;
    };


    void LightDevice::AddSensor(Sensor* new_sensor) {
        sensors_.push_back(new_sensor);
    };


    void LightDevice::RemoveSensor(Sensor* rem_sensor) {
        auto it = std::find(sensors_.begin(), sensors_.end(), rem_sensor);
        sensors_.erase(it);
    };


    std::vector<Sensor*> LightDevice::GetSensors() {
        return sensors_;
    };


    uint32_t LightDevice::GetBrightness() {
        return brightness_;
    }


    void LightDevice::SetBrightness(uint32_t new_brightness) {
        brightness_ = new_brightness;
    }

} // namespace smart_home_app
