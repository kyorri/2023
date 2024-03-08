#ifndef SH_DEVICETYPEMESSAGE_INCLUDE_H_
#define SH_DEVICETYPEMESSAGE_INCLUDE_H_

#include "DeviceType.h"

#include <string>

namespace smart_home {
class DeviceTypeMessage {
    public:
        DeviceTypeMessage(DeviceType);
        ~DeviceTypeMessage() = default;
        
        std::string GetType();
    private:
        DeviceType type_;
};
} // namespace smart_home

#endif  // SH_DEVICETYPEMESSAGE_INCLUDE_H_