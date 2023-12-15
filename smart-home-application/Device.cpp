#include "Device.h"

#include <iostream>
#include <vector>
#include <algorithm>

namespace smart_home_app {
Device::Device(std::string device_name, bool status) : device_name_(device_name), status_(status) {};

Device::~Device() {};

Device::Device(const Device& other) : device_name_(other.device_name_), status_(other.status_) {};

Device::Device(Device&& other) = default;

Device& Device::operator=(const Device& rhs) {
    Device temp(rhs.device_name_, rhs.status_);
    for (Sensor s : rhs.sensors_) {
        this->sensors_.push_back(s);
    }
    std::swap(device_name_, temp.device_name_);
    std::swap(status_, temp.status_);
    std::swap(sensors_, temp.sensors_);
    return *this;
};

Device& Device::operator=(Device&& rhs) = default;

void Device::SetDeviceName(std::string device_name){
    this->device_name_ = device_name;
};

std::string Device::GetDeviceName(){
    return this->device_name_;
};

void Device::SetStatus(bool status) {
    this->status_ = status;
};

bool Device::GetStatus() {
    return this->status_;
};

void Device::AddSensor(Sensor sensor) {
    this->GetSensors().push_back(sensor);
};

void Device::RemoveSensor(Sensor sensor) {
    size_t i = 0;
    for (auto s : this->sensors_) {
        if (s.GetSensorType() == sensor.GetSensorType()) {
            this->sensors_.erase(this->sensors_.begin() + i);
            break;
        }
        i++;
    }
};

std::vector<Sensor>& Device::GetSensors() {
    return this->sensors_;
};
} // namespace smart_home_app