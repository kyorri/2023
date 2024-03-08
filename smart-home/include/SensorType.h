#ifndef SH_SENSORTYPE_INCLUDE_H_ 
#define SH_SENSORTYPE_INCLUDE_H_

namespace smart_home {
enum class SensorType {
    Temperature,
    Humidity,
    AirQualityLevel,
    Undefined
};
}; // namespace smart_home

#endif // SH_SENSORTYPE_INCLUDE_H_