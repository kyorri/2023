#ifndef SH_MESSAGEDEVICETYPE_INCLUDE_H_
#define SH_MESSAGEDEVICETYPE_INCLUDE_H_

#include "DeviceType.h"

#include <string>

namespace smart_home {
class MessageDeviceType {
    public:
        MessageDeviceType(std::string);
        ~MessageDeviceType() = default;
        
        DeviceType GetType();
    private:
        std::string type_;
};
} // namespace smart_home

#endif  // SH_MESSAGEDEVICETYPE_INCLUDE_H_