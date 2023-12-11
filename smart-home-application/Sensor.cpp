#include "Sensor.h"

Sensor::Sensor(std::string sensor_name, double reading_value)
    : sensor_name(sensor_name), reading_value(reading_value){};

void Sensor::setSensorName(std::string sensor_name)
{
    this->sensor_name = sensor_name;
};
std::string Sensor::getSensorName()
{
    return this->sensor_name;
};

void Sensor::setReading(double reading_value)
{
    this->reading_value = reading_value;
};
double Sensor::getReading()
{
    return this->reading_value;
};