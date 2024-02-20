#ifndef SH_SENSORSTATUS_INCLUDE_H_
#define SH_SENSORSTATUS_INCLUDE_H_

namespace smart_home {
enum class SensorStatus {
    Undefined,
    Off,
    Ready,
    Active,
    Standby,
    Error
};
} // namespace smart_home

#endif  // SH_SENSORSTATUS_INCLUDE_H_