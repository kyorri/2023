#ifndef SH_DEVICEFACTORY_INCLUDE_H_
#define SH_DEVICEFACTORY_INCLUDE_H_

#include "Device.h"
#include "ACUnitDevice.h"
#include "SpeakerDevice.h"
#include "ThermostatDevice.h"

namespace smart_home {
class DeviceFactory {
    public:
        antoniaptr::unique_ptr<Device> Build(DeviceType);
};
} // namespace smart_home
#endif  // SH_DEVICEFACTORY_INCLUDE_H_