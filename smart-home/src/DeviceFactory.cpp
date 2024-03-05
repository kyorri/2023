#include "DeviceFactory.h"

namespace smart_home {
antoniaptr::unique_ptr<Device> DeviceFactory::Build(DeviceType device_type) {

    switch (device_type) {
        case DeviceType::ACUnit:
            return std::move(antoniaptr::unique_ptr<Device>(new ACUnitDevice()));
            break;

        case DeviceType::Speaker:
            return std::move(antoniaptr::unique_ptr<Device>(new SpeakerDevice()));
            break;

        case DeviceType::Thermostat:
            return std::move(antoniaptr::unique_ptr<Device>(new ThermostatDevice()));
            break;
        
        default:
            return std::move(antoniaptr::unique_ptr<Device>(nullptr));
    };
};
} // namespace smart_home
