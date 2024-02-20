#ifndef SH_SPEAKERDEVICEREADER_INCLUDE_H_
#define SH_SPEAKERDEVICEREADER_INCLUDE_H_

#include "SpeakerDevice.h"
#include "DeviceReader.h"

namespace smart_home {

class SpeakerDeviceReader : public DeviceReader {
    public:
        SpeakerDeviceReader();
        ~SpeakerDeviceReader() = default;
        std::vector<std::pair<std::string, std::string>> ReadInformation(std::string) override;
        DeviceType GetDeviceType() override;
    private:
        DeviceType device_type_;
};

} // smart_home

#endif // SH_SPEAKERDEVICEREADER_INCLUDE_H_