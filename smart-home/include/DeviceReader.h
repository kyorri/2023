#ifndef SH_DEVICEREADER_INCLUDE_H_
#define SH_DEVICEREADER_INCLUDE_H_

#include "Device.h"
#include "DeviceType.h"

namespace smart_home {

class DeviceReader {
    public:
        virtual std::vector<std::pair<std::string, std::string>> ReadInformation(std::string) = 0;
        virtual DeviceType GetDeviceType() = 0;
};

} // smart_home

#endif // SH_DEVICEREADER_INCLUDE_H_