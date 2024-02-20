#include "ACUnitDeviceReader.h"

namespace smart_home {
ACUnitDeviceReader::ACUnitDeviceReader() : device_type_(DeviceType::ACUnit) {};

DeviceType ACUnitDeviceReader::GetDeviceType() {
    return device_type_;
};

std::vector<std::pair<std::string, std::string>> ACUnitDeviceReader::ReadInformation(std::string filename) {
    return std::vector<std::pair<std::string, std::string>>();
};

} // namespace smart_home
