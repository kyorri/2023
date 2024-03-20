#include "SpeakerDevice.h"
#include "DeviceStatusMessage.h"

#include <iostream>
#include <algorithm>

namespace smart_home {

SpeakerDevice::SpeakerDevice() : status_(DeviceStatus::Off), device_type_(DeviceType::Speaker) {
    sensors_.clear();
};

std::stringstream SpeakerDevice::Interact() {
    std::stringstream device_stream;
    try {
        switch (status_) {
            case DeviceStatus::Off:
                device_stream << "This speaker is turned off!" << std::endl;
                break;

            case DeviceStatus::Active:
                device_stream << "This speaker is playing your favourite songs at " << static_cast<int>(volume_ * 100) << "\% volume!" << std::endl;
                break;

            case DeviceStatus::Standby:
                device_stream << "This speaker is standing-by!" << std::endl;
                break;

            case DeviceStatus::Error:
                device_stream << "Unexpected error, speaker will shut down!" << std::endl;
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
    return device_stream;
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

std::vector<Sensor*> SpeakerDevice::GetSensors() {
    std::vector<Sensor*> sensors;
    for (const auto& d : sensors_) {
        sensors.push_back(d.get());
    }
    return sensors;
};

void SpeakerDevice::AddSensor(antoniaptr::unique_ptr<Sensor> p) {
    sensors_.push_back(std::move(p));
};

void SpeakerDevice::RemoveSensor(int index) {
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

double SpeakerDevice::GetVolume() {
    return volume_;
};

void SpeakerDevice::SetVolume(double new_volume) {
    volume_ = new_volume;
};

DeviceType SpeakerDevice::GetDeviceType() {
    return device_type_;
}

} // namespace smart_home
