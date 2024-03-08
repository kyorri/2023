#ifndef SH_MESSAGEDEVICESTATUS_INCLUDE_H_
#define SH_MESSAGEDEVICESTATUS_INCLUDE_H_

#include "DeviceStatus.h"

#include <string>

namespace smart_home {
class MessageDeviceStatus {
    public:
        MessageDeviceStatus(std::string);
        ~MessageDeviceStatus() = default;
        
        DeviceStatus GetStatus();
    private:
        std::string status_;
};
} // namespace smart_home

#endif  // SH_MESSAGEDEVICESTATUS_INCLUDE_H_