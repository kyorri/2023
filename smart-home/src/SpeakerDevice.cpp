#include "SpeakerDevice.h"
#include "DeviceStatusMessage.h"

#include <iostream>
#include <algorithm>

namespace smart_home {

SpeakerDevice::SpeakerDevice() : status_(DeviceStatus::Off), device_type_(DeviceType::Speaker) {
    sensors_.clear();
};

void SpeakerDevice::Interact() {
    try {
        switch (status_) {
            case DeviceStatus::Off:
                std::cout << "This speaker is turned off!" << std::endl;
                break;

            case DeviceStatus::Active:
                std::cout << "This speaker is playing your favourite songs at " << static_cast<int>(volume_ * 100) << "\% volume!" << std::endl;
                break;

            case DeviceStatus::Standby:
                std::cout << "This speaker is standing-by!" << std::endl;
                break;

            case DeviceStatus::Error:
                std::cout << "Unexpected error, speaker will shut down!" << std::endl;
                TurnOff();
                break;

            default:
                throw std::logic_error("Speaker device is in wrong state to be interacted with! (It should be at least active/turned off/standby...)");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
};

void SpeakerDevice::Wait() {
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
                throw std::logic_error("This speaker cannot wait because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
};

void SpeakerDevice::Continue() {
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
                throw std::logic_error("This speaker cannot continue because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void SpeakerDevice::TurnOn() {
    try {
        switch (status_) {
            case DeviceStatus::Off:
                SetStatus(DeviceStatus::Active);
                break;
                
            default:
                throw std::logic_error("Cannot turn on the speaker! (have you tried to turn it off and on?)");
                break;
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void SpeakerDevice::TurnOff() {
    this->status_ = DeviceStatus::Off;
};

DeviceStatus SpeakerDevice::GetStatus() {
    return status_;
};

void SpeakerDevice::SetStatus(DeviceStatus new_status) {
    status_ = new_status;
};

std::vector<std::shared_ptr<Sensor>> SpeakerDevice::GetSensors() {
    return sensors_;
};

void SpeakerDevice::AddSensor(std::shared_ptr<Sensor> p) {
    try {
        auto it = std::find_if(sensors_.begin(), sensors_.end(),
                [&p](const std::shared_ptr<Sensor>& sensor) {
                    return sensor.get() == p.get();
                });
        if (it == sensors_.end()) {
            sensors_.push_back(p);
        }
        else {
            throw std::runtime_error("This sensor is already assigned to this speaker!");
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        SetStatus(DeviceStatus::Error);
    }
};

void SpeakerDevice::RemoveSensor(std::shared_ptr<Sensor> p) {
    try {
        auto it = std::find_if(sensors_.begin(), sensors_.end(),
                [&p](const std::shared_ptr<Sensor>& sensor) {
                    return sensor.get() == p.get();
                });
        if (it == sensors_.end()) {
            throw std::runtime_error("This sensor is not assigned to this speaker!");
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

double SpeakerDevice::GetVolume() {
    return volume_;
};

void SpeakerDevice::SetVolume(double new_volume) {
    volume_ = new_volume;
};
} // namespace smart_home
