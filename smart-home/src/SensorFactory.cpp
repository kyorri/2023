#include "SensorFactory.h"

namespace smart_home {
antoniaptr::unique_ptr<Sensor> SensorFactory::Build(SensorType sensor_type) {

    switch (sensor_type) {
        case SensorType::Temperature:
            return std::move(antoniaptr::unique_ptr<Sensor>(new TemperatureSensor()));
            break;

        case SensorType::Humidity:
            return std::move(antoniaptr::unique_ptr<Sensor>(new HumiditySensor()));
            break;

        case SensorType::AirQualityLevel:
            return std::move(antoniaptr::unique_ptr<Sensor>(new AirQualitySensor()));
            break;
        
        default:
            return std::move(antoniaptr::unique_ptr<Sensor>(nullptr));
    };
};
} // namespace smart_home
