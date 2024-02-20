#include "DeviceFactory.h"

namespace smart_home {
Device* DeviceFactory::Build(DeviceType device_type) {
    switch (device_type) {
        case DeviceType::ACUnit:
            return new ACUnitDevice();
            break;

        case DeviceType::Speaker:
            return new SpeakerDevice();
            break;

        case DeviceType::Thermostat:
            return new ThermostatDevice();
            break;
    };
    return nullptr;
};
} // namespace smart_home
