#include "TemperatureSensor.h"

#include <ctype.h>

namespace smart_home_app {

    std::string TemperatureSensor::GetInfo() {
        std::string message = std::string();
        message += "This Temperature Sensor is reading " + std::to_string(GetReading()) + " degrees " + GetScale() + "!\n";
        return message;
    };


    void TemperatureSensor::SetReading(double new_reading) {
        reading_ = new_reading;
    };


    double TemperatureSensor::GetReading() {
        return reading_;
    };

    void TemperatureSensor::SetScale(char scale) {
        scale_ = tolower(scale);
    }

    void TemperatureSensor::SetScaleTo(char initial_scale, char final_scale) {
        double celsius_value;
        double final_value;
        switch (initial_scale) {
            case 'c':
                celsius_value = GetReading();
                break;
            case 'f':
                celsius_value = (GetReading() - 32.0) / 1.8;
                break;
            case 'k':
                celsius_value = GetReading() - 273.15;
                break;
        }
        switch (final_scale) {
            case 'c':
                final_value = celsius_value;
                break;
            case 'f':
                final_value = celsius_value * 1.8 + 32.0;
                break;
            case 'k':
                final_value = celsius_value + 273.15;
                break;
        }
        SetReading(final_value);
    };


    void TemperatureSensor::SetScaleTo(char new_scale) {
        SetScaleTo(scale_, new_scale);
    };


    std::string TemperatureSensor::GetScale() {
        char scale = tolower(scale_);
        if (scale == 'c') {
            return "Celsius";
        }
        else if (scale == 'k') {
            return "Kelvin";
        }
        else if (scale == 'f') {
            return "Fahrenheit";
        }
        return ""; 
    };

} // namespace smart_home_app
