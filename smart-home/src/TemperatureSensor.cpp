#include "TemperatureSensor.h"
#include "SensorStatusMessage.h"

namespace smart_home {
TemperatureSensor::TemperatureSensor() : status_(SensorStatus::Off), reading_(0.0) {};

TemperatureSensor::TemperatureSensor(double reading) : status_(SensorStatus::Off), reading_(reading) {};

void TemperatureSensor::Interact() {
    SensorStatusMessage ssm(status_);
    std::cout << "This Temperature sensor is in the state of " << ssm.GetStatus() << ", and is indicating a temperature of " << reading_ << " degrees Celsius!" << std::endl;
};

SensorStatus TemperatureSensor::GetStatus() {
    return status_;
};

void TemperatureSensor::SetStatus(SensorStatus new_status) {
    status_ = new_status;
};

double TemperatureSensor::GetReading() {
    return reading_;
};

void TemperatureSensor::SetReading(double new_reading) {
    reading_ = new_reading;
};

void TemperatureSensor::Wait() {
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
                throw std::logic_error("This Temperature sensor cannot wait because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void TemperatureSensor::Continue() {
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
                throw std::logic_error("This Temperature sensor cannot continue because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void TemperatureSensor::TurnOn() {
    try {
        switch (status_) {
            case SensorStatus::Off:
                SetStatus(SensorStatus::Active);
                break;
                
            default:
                throw std::logic_error("Cannot turn on the Temperature sensor! (have you tried to turn it off and on?)");
                break;
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void TemperatureSensor::TurnOff() {
    status_ = SensorStatus::Off;
};
} // namespace smart_home
