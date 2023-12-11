#include "Device.h"

#include <vector>

Device::Device(std::string device_name, bool status) : device_name(device_name), status(status) {};

void Device::setDeviceName(std::string device_name){
    this->device_name = device_name;
};

std::string Device::getDeviceName(){
    return this->device_name;
};

void Device::setStatus(bool status) {
    this->status = status;
};

bool Device::getStatus() {
    return this->status;
};

std::vector<Sensor> Device::getSensors() {
    return this->sensors;
};