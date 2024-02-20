#ifndef SH_THERMOSTATDEVICEREADER_INCLUDE_H_
#define SH_THERMOSTATDEVICEREADER_INCLUDE_H_

#include "ThermostatDevice.h"
#include "DeviceReader.h"

namespace smart_home {

class ThermostatDeviceReader : public DeviceReader {
    public:
        ThermostatDeviceReader();
        ~ThermostatDeviceReader() = default;
        std::vector<std::pair<std::string, std::string>> ReadInformation(std::string) override;
        DeviceType GetDeviceType() override;
    private:
        DeviceType device_type_;
};

} // smart_home

#endif // SH_THERMOSTATDEVICEREADER_INCLUDE_H_