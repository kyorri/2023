#ifndef SH_DEVICESTATUSMESSAGE_INCLUDE_H_
#define SH_DEVICESTATUSMESSAGE_INCLUDE_H_

#include "DeviceStatus.h"

#include <string>

namespace smart_home {
class DeviceStatusMessage {
    public:
        DeviceStatusMessage(DeviceStatus);
        ~DeviceStatusMessage() = default;
        
        std::string GetStatus();
    private:
        DeviceStatus status_;
};
} // namespace smart_home

#endif  // SH_DEVICESTATUSMESSAGE_INCLUDE_H_