#ifndef SH_ACUNITDEVICEREADER_INCLUDE_H_
#define SH_ACUNITDEVICEREADER_INCLUDE_H_

#include "ACUnitDevice.h"
#include "DeviceReader.h"

namespace smart_home {

class ACUnitDeviceReader : public DeviceReader {
    public:
        ACUnitDeviceReader();
        ~ACUnitDeviceReader() = default;
        std::vector<std::pair<std::string, std::string>> ReadInformation(std::string) override;
        DeviceType GetDeviceType() override;
    private:
        DeviceType device_type_;
};

} // smart_home

#endif // SH_ACUNITDEVICEREADER_INCLUDE_H_