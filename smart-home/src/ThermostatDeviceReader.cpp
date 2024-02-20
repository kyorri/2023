#include "ThermostatDeviceReader.h"

namespace smart_home {
ThermostatDeviceReader::ThermostatDeviceReader() : device_type_(DeviceType::Thermostat) {};

DeviceType ThermostatDeviceReader::GetDeviceType() {
    return device_type_;
};

std::vector<std::pair<std::string, std::string>> ThermostatDeviceReader::ReadInformation(std::string filename) {
    return std::vector<std::pair<std::string, std::string>>();
};

} // namespace smart_home
