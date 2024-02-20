#ifndef SH_DEVICESTATUS_INCLUDE_H_
#define SH_DEVICESTATUS_INCLUDE_H_

namespace smart_home {
enum class DeviceStatus {
    Undefined,
    Off,
    Ready,
    Active,
    Standby,
    Error
};
} // namespace smart_home

#endif  // SH_DEVICESTATUS_INCLUDE_H_