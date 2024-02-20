#include "SpeakerDeviceReader.h"

namespace smart_home {
SpeakerDeviceReader::SpeakerDeviceReader() : device_type_(DeviceType::Speaker) {};

DeviceType SpeakerDeviceReader::GetDeviceType() {
    return device_type_;
};

std::vector<std::pair<std::string, std::string>> SpeakerDeviceReader::ReadInformation(std::string filename) {
    return std::vector<std::pair<std::string, std::string>>();
};

} // namespace smart_home
