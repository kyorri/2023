#include "Sensor.h"

namespace smart_home_app {
Sensor::Sensor(std::string sensor_type, double reading_value)
    : sensor_type_(sensor_type), reading_value_(reading_value){};

bool Sensor::operator==(Sensor& rhs) {
    return this->sensor_type_ == rhs.sensor_type_;
};

void Sensor::SetSensorType(std::string sensor_type)
{
    this->sensor_type_ = sensor_type;
};
std::string Sensor::GetSensorType()
{
    return this->sensor_type_;
};

void Sensor::SetReading(double reading_value)
{
    this->reading_value_ = reading_value;
};
double Sensor::GetReading()
{
    return this->reading_value_;
};
} // namespace smart_home_app