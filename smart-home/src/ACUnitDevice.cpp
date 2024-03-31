#include "ACUnitDevice.h"
#include "DeviceStatusMessage.h"

#include <iostream>
#include <algorithm>

namespace smart_home {
ACUnitDevice::ACUnitDevice() : status_(DeviceStatus::Off), heating_status_(ACHeatingStatus::Standby), device_type_(DeviceType::ACUnit) {
    sensors_.clear();
};

std::stringstream ACUnitDevice::Interact() {
    std::stringstream device_stream;
    try {
        switch (status_) {
            case DeviceStatus::Off:
                device_stream << "This Air Conditioning unit is turned off!" << std::endl;
                break;

            case DeviceStatus::Active:
                try {
                    switch (heating_status_) {
                        case ACHeatingStatus::Standby:
                            device_stream << "This Air Conditioning unit is neither cooling nor heating up the room!" << std::endl;
                            break;

                        case ACHeatingStatus::Cooling:
                            device_stream << "This Air Conditioning unit is cooling up the room!" << std::endl;
                            break;

                        case ACHeatingStatus::Heating:
                            device_stream << "This Air Conditioning unit is heating up the room!" << std::endl;
                            break;

                        default:
                            throw std::logic_error("Error in getting the state of the heating/cooling of this AC unit!");
                            break;
                    }
                }
                catch(std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;

            case DeviceStatus::Standby:
                device_stream << "This Air Conditioning unit is standing-by!" << std::endl;
                break;

            case DeviceStatus::Error:
                device_stream << "Unexpected error, the Air Conditioning unit will shut down!" << std::endl;
                TurnOff();
                break;

            default:
                throw std::logic_error("AC unit device is in wrong state to be interacted with! (It should be at least active/turned off/standby...)");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return device_stream;
};

void ACUnitDevice::Wait() {
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
                throw std::logic_error("This AC Unit cannot wait because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void ACUnitDevice::Continue() {
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
                throw std::logic_error("This AC Unit cannot continue because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
};

void ACUnitDevice::TurnOn() {
    try {
        switch (status_) {
            case DeviceStatus::Off:
                SetStatus(DeviceStatus::Active);
                break;
                
            default:
                throw std::logic_error("Cannot turn on the AC unit! (have you tried to turn it off and on?)");
                break;
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void ACUnitDevice::TurnOff() {
    status_ = DeviceStatus::Off;
};

DeviceStatus ACUnitDevice::GetStatus() {
    return status_;
};

void ACUnitDevice::SetStatus(DeviceStatus new_status) {
    status_ = new_status;
};

std::vector<Sensor*> ACUnitDevice::GetSensors() {
    std::vector<Sensor*> sensors;
    for (const auto& d : sensors_) {
        sensors.push_back(d.get());
    }
    return sensors;
};

void ACUnitDevice::AddSensor(antoniaptr::unique_ptr<Sensor> p) {
    sensors_.push_back(std::move(p));
};

void ACUnitDevice::RemoveSensor(int index) {
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

void ACUnitDevice::StartHeating() {
    heating_status_ = ACHeatingStatus::Heating;
};

void ACUnitDevice::StopHeating() {
    heating_status_ = ACHeatingStatus::Standby;
};

void ACUnitDevice::StartCooling() {
    heating_status_ = ACHeatingStatus::Cooling;
};

void ACUnitDevice::StopCooling() {
    heating_status_ = ACHeatingStatus::Standby;
}

ACHeatingStatus ACUnitDevice::GetHeatingStatus() {
    return heating_status_;
};

void ACUnitDevice::SetHeatingStatus(const ACHeatingStatus& achs) {
    heating_status_ = achs;
};

DeviceType ACUnitDevice::GetDeviceType() {
    return device_type_;
}
} // namespace smart_home
