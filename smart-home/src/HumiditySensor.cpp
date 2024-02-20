#include "HumiditySensor.h"
#include "SensorStatusMessage.h"

namespace smart_home {
HumiditySensor::HumiditySensor() : status_(SensorStatus::Off), reading_(0.0) {};

HumiditySensor::HumiditySensor(double reading) : status_(SensorStatus::Off) {
    SetReading(reading);
};

void HumiditySensor::Interact() {
    SensorStatusMessage ssm(status_);
    std::cout << "This Humidity sensor is in the state of " << ssm.GetStatus() << ", and is indicating a humidity level of " << GetPercent() << "%!" << std::endl;
};

SensorStatus HumiditySensor::GetStatus() {
    return status_;
};

void HumiditySensor::SetStatus(SensorStatus new_status) {
    status_ = new_status;
};

double HumiditySensor::GetReading() {
    return reading_;
};

void HumiditySensor::SetReading(double new_reading) {
    if (new_reading > 1.0) {
        reading_ = 1.0;
    }
    else if (new_reading < 0.0) {
        reading_ = 0.0;
    }
    else {
        reading_ = new_reading;
    }
};

int HumiditySensor::GetPercent() {
    return reading_ * 100;
}

void HumiditySensor::Wait() {
    try {
        switch (status_) {
            case SensorStatus::Standby:
                // do nothing, we still are in standby
                break;

            case SensorStatus::Active:
                SetStatus(SensorStatus::Standby);
                break;

            default:
                SensorStatusMessage dvm(status_);
                std::string message = dvm.GetStatus();
                throw std::logic_error("This Humidity sensor cannot wait because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void HumiditySensor::Continue() {
    try {
        switch (status_) {
            case (SensorStatus::Active):
                // do nothing, we still are active
                break;

            case (SensorStatus::Standby):
                SetStatus(SensorStatus::Active);
                break;
                
            default:
                SensorStatusMessage dvm(status_);
                std::string message = dvm.GetStatus();
                throw std::logic_error("This Humidity sensor cannot continue because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void HumiditySensor::TurnOn() {
    try {
        switch (status_) {
            case SensorStatus::Off:
                SetStatus(SensorStatus::Active);
                break;
                
            default:
                throw std::logic_error("Cannot turn on the Humidity sensor! (have you tried to turn it off and on?)");
                break;
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void HumiditySensor::TurnOff() {
    status_ = SensorStatus::Off;
};
} // namespace smart_home
