#include "ThermostatDevice.h"
#include "TemperatureSensor.h"
#include "DeviceStatusMessage.h"

#include <iostream>
#include <algorithm>

namespace smart_home {
ThermostatDevice::ThermostatDevice() : status_(DeviceStatus::Off), temperature_(0.0), target_temp_(18.5), device_type_(DeviceType::Thermostat)  {
    sensors_.clear();
};

ThermostatDevice::ThermostatDevice(TemperatureSensor ts) : status_(DeviceStatus::Off), temperature_(ts.GetReading()), target_temp_(18.5), device_type_(DeviceType::Thermostat)  {
    sensors_.clear();
};

void ThermostatDevice::Interact() {
    try {
        switch (status_) {
            case DeviceStatus::Off:
                std::cout << "This thermostat is turned off!" << std::endl;
                break;

            case DeviceStatus::Active:
                if (target_temp_ > temperature_) {
                    std::cout << "This thermostat is heating up to " << target_temp_ << " degrees Celsius, and the current temperature is " << temperature_ << " degrees Celsius!" << std::endl;
                }
                else {
                    std::cout << "This thermostat is indicating a temperature of " << temperature_ << " degrees Celsius, and the target temperature is " << target_temp_ << " degrees Celsius!" << std::endl;
                }
                break;

            case DeviceStatus::Standby:
                std::cout << "This thermostat is standing-by!" << std::endl;
                break;

            case DeviceStatus::Error:
                std::cout << "Unexpected error, the thermostat will shut down!" << std::endl;
                TurnOff();
                break;

            default:
                throw std::logic_error("Thermostat device is in wrong state to be interacted with! (It should be at least active/turned off/standby...)");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
};

void ThermostatDevice::Wait() {
    try {
        switch (status_) {
            case DeviceStatus::Standby:
                // do nothing, we still are in standby
                break;
                
            case DeviceStatus::Active:
                SetStatus(DeviceStatus::Standby);
                break;

            default:
                DeviceStatusMessage dvm(status_);
                std::string message = dvm.GetStatus();
                throw std::logic_error("This thermostat cannot wait because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
};

void ThermostatDevice::Continue() {
    try {
        switch (status_) {
            case (DeviceStatus::Active):
                // do nothing, we still are active
                break;

            case (DeviceStatus::Standby):
                SetStatus(DeviceStatus::Active);
                break;
                
            default:
                DeviceStatusMessage dvm(status_);
                std::string message = dvm.GetStatus();
                throw std::logic_error("This thermostat cannot continue because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void ThermostatDevice::TurnOn() {
    try {
        switch (status_) {
            case DeviceStatus::Off:
                SetStatus(DeviceStatus::Active);
                break;
                
            default:
                throw std::logic_error("Cannot turn on the thermostat! (have you tried to turn it off and on?)");
                break;
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void ThermostatDevice::TurnOff() {
    this->status_ = DeviceStatus::Off;
};

DeviceStatus ThermostatDevice::GetStatus() {
    return status_;
};

void ThermostatDevice::SetStatus(DeviceStatus new_status) {
    status_ = new_status;
};

std::vector<Sensor*> ThermostatDevice::GetSensors() {
    std::vector<Sensor*> sensors;
    for (const auto& d : sensors_) {
        sensors.push_back(d.get());
    }
    return sensors;
};

void ThermostatDevice::AddSensor(antoniaptr::unique_ptr<Sensor> p) {
    sensors_.push_back(std::move(p));
};

void ThermostatDevice::RemoveSensor(int index) {
    try {
        if (index > sensors_.size() || index < 0) {
            throw std::runtime_error("This index is not present in the sensors of this AC Unit.");
        }
        else {
            sensors_.erase(sensors_.begin() + index);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        SetStatus(DeviceStatus::Error);
    }
};

double ThermostatDevice::GetTargetTemperature() {
    return target_temp_;
};

double ThermostatDevice::GetTemperature() {
    return temperature_;
};

void ThermostatDevice::SetTargetTemperature(double new_target_temp) {
    target_temp_ = new_target_temp;
};

void ThermostatDevice::SetTemperature(double new_temperature) {
    temperature_ = new_temperature;
};

DeviceType ThermostatDevice::GetDeviceType() {
    return device_type_;
}
} // namespace smart_home
