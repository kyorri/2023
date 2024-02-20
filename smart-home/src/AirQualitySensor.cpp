#include "AirQualitySensor.h"
#include "SensorStatusMessage.h"
#include "AirQualityLevelMessage.h"

namespace smart_home {
AirQualitySensor::AirQualitySensor() : status_(SensorStatus::Off), reading_(0.0), air_quality_lvl_(AirQualityLevel::Good) {};

AirQualitySensor::AirQualitySensor(double reading) : status_(SensorStatus::Off), reading_(reading) {
    if (reading >= 0 && reading <= 50) {
        air_quality_lvl_ = AirQualityLevel::Good;
    }
    else if (reading >= 51 && reading <= 100) {
        air_quality_lvl_ = AirQualityLevel::Moderate;
    }
    else if (reading >= 101 && reading <= 150) {
        air_quality_lvl_ = AirQualityLevel::Unhealty_For_Sensitive_Groups;
    }
    else if (reading >= 151 && reading <= 200) {
        air_quality_lvl_ = AirQualityLevel::Unhealthy;
    }
    else if (reading >= 201 && reading <= 250) {
        air_quality_lvl_ = AirQualityLevel::Very_Unhealthy;
    }
    else {
        if (reading < 0.0) {
            air_quality_lvl_ = AirQualityLevel::Good;
            reading_ = 0.0;
        }
        else if (reading > 250) {
            air_quality_lvl_ = AirQualityLevel::Very_Unhealthy;
            reading_ = 250.0;
        }
    }
};

void AirQualitySensor::Interact() {
    SensorStatusMessage ssm(status_);
    AirQualityLevelMessage aqlm(air_quality_lvl_);
    std::cout << "This Air Quality sensor is in the state of " << ssm.GetStatus() << ", and is indicating a reading of " << reading_ << " Air Quality Index, in the air quality level of " << aqlm.GetStatus() << "!" << std::endl;
};

SensorStatus AirQualitySensor::GetStatus() {
    return status_;
};

void AirQualitySensor::SetStatus(SensorStatus new_status) {
    status_ = new_status;
};

double AirQualitySensor::GetReading() {
    return reading_;
};

void AirQualitySensor::SetReading(double new_reading) {
    reading_ = new_reading;
    if (new_reading >= 0 && new_reading <= 50) {
        air_quality_lvl_ = AirQualityLevel::Good;
    }
    else if (new_reading >= 51 && new_reading <= 100) {
        air_quality_lvl_ = AirQualityLevel::Moderate;
    }
    else if (new_reading >= 101 && new_reading <= 150) {
        air_quality_lvl_ = AirQualityLevel::Unhealty_For_Sensitive_Groups;
    }
    else if (new_reading >= 151 && new_reading <= 200) {
        air_quality_lvl_ = AirQualityLevel::Unhealthy;
    }
    else if (new_reading >= 201 && new_reading <= 250) {
        air_quality_lvl_ = AirQualityLevel::Very_Unhealthy;
    }
    else {
        if (new_reading < 0.0) {
            air_quality_lvl_ = AirQualityLevel::Good;
            reading_ = 0.0;
        }
        else if (new_reading > 250) {
            air_quality_lvl_ = AirQualityLevel::Very_Unhealthy;
            reading_ = 250.0;
        }
    }
};

AirQualityLevel AirQualitySensor::GetAirQualityLevel() {
    return air_quality_lvl_;
};

void AirQualitySensor::Wait() {
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
                throw std::logic_error("This Air Quality sensor cannot wait because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void AirQualitySensor::Continue() {
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
                throw std::logic_error("This Air Quality sensor cannot continue because we are in the \"" + message + "\" state!");
                break;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void AirQualitySensor::TurnOn() {
    try {
        switch (status_) {
            case SensorStatus::Off:
                SetStatus(SensorStatus::Active);
                break;
                
            default:
                throw std::logic_error("Cannot turn on the Air Quality sensor! (have you tried to turn it off and on?)");
                break;
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};

void AirQualitySensor::TurnOff() {
    status_ = SensorStatus::Off;
};
} // namespace smart_home