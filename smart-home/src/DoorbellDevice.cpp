#include "DoorbellDevice.h"

#include <iostream>
#include <vector>
#include <algorithm>

namespace smart_home_app {

    std::string DoorbellDevice::GetType() {
        return "doorbell";
    }

    std::string DoorbellDevice::GetInfo() {
        std::string message = std::string();
        message += "This Doorbell is " + GetStatus() + ", had " + std::to_string(GetVisitors()) + " today, and has these sensors attached:\n";
        for (auto s : sensors_) {
            message += "\t-" + s->GetInfo();
        }
        return message;
    };


    std::string DoorbellDevice::GetStatus() {
        if (status_) {
            return "on";
        }
        return "off";
    };


    void DoorbellDevice::TurnOff() {
        status_ = false;
    };


    void DoorbellDevice::TurnOn() {
        status_ = true;
    };


    void DoorbellDevice::AddSensor(Sensor* new_sensor) {
        sensors_.push_back(new_sensor);
    };


    void DoorbellDevice::RemoveSensor(Sensor* rem_sensor) {
        auto it = std::find(sensors_.begin(), sensors_.end(), rem_sensor);
        sensors_.erase(it);
    };


    std::vector<Sensor*> DoorbellDevice::GetSensors() {
        return sensors_;
    };


    void DoorbellDevice::SetVisitors(uint32_t new_visitors) {
        visitors_ = new_visitors;
    };


    uint32_t DoorbellDevice::GetVisitors() {
        return visitors_;
    };
} // namespace smart_home_app