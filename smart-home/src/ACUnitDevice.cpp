#include "ACUnitDevice.h"
#include "DeviceStatusMessage.h"

#include <iostream>
#include <algorithm>

namespace smart_home {
ACUnitDevice::ACUnitDevice() : status_(DeviceStatus::Off), heating_status_(ACHeatingStatus::Standby), device_type_(DeviceType::ACUnit) {
    sensors_.clear();
};

void ACUnitDevice::Interact() {
    try {
        switch (status_) {
            case DeviceStatus::Off:
                std::cout << "This Air Conditioning unit is turned off!" << std::endl;
                break;

            case DeviceStatus::Active:
                try {
                    switch (heating_status_) {
                        case ACHeatingStatus::Standby:
                            std::cout << "This Air Conditioning unit is neither cooling nor heating up the room!" << std::endl;
                            break;

                        case ACHeatingStatus::Cooling:
                            std::cout << "This Air Conditioning unit is cooling up the room!" << std::endl;
                            break;

                        case ACHeatingStatus::Heating:
                            std::cout << "This Air Conditioning unit is heating up the room!" << std::endl;
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
                std::cout << "This Air Conditioning unit is standing-by!" << std::endl;
                break;

            case DeviceStatus::Error:
                std::cout << "Unexpected error, the Air Conditioning unit will shut down!" << std::endl;
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

std::vector<std::shared_ptr<Sensor>> ACUnitDevice::GetSensors() {
    return sensors_;
};

void ACUnitDevice::AddSensor(std::shared_ptr<Sensor> p) {
    try {
        auto it = std::find_if(sensors_.begin(), sensors_.end(),
                [&p](const std::shared_ptr<Sensor>& sensor) {
                    return sensor.get() == p.get();
                });
        if (it == sensors_.end()) {
            sensors_.push_back(p);
        }
        else {
            throw std::runtime_error("This sensor is already assigned to this AC unit!");
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        SetStatus(DeviceStatus::Error);
    }
};

void ACUnitDevice::RemoveSensor(std::shared_ptr<Sensor> p) {
    try {
        auto it = std::find_if(sensors_.begin(), sensors_.end(),
                [&p](const std::shared_ptr<Sensor>& sensor) {
                    return sensor.get() == p.get();
                });
        if (it == sensors_.end()) {
            throw std::runtime_error("This sensor is not assigned to this AC unit!");
        }
        else {
            sensors_.erase(it);
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
} // namespace smart_home
