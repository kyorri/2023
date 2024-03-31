#include "ThermostatDevicePrinter.h"
#include "DeviceStatusMessage.h"

namespace smart_home {
std::stringstream ThermostatDevicePrinter::Print(Device* device) {
    ThermostatDevice* thm = dynamic_cast<ThermostatDevice*>(device);
    DeviceStatusMessage dsm(thm->GetStatus());
    std::stringstream device_stream;
    device_stream << "This Thermostat is in the "
            << dsm.GetStatus()
            << " state and the temperature of the room is "
            << thm->GetTemperature()
            << " degrees Celsius, with the target temperature of "
            << thm->GetTargetTemperature()
            << " degrees Celsius!" << std::endl;
    if (thm->GetSensors().size() == 0) {
        device_stream << "> This unit has no sensors attached to it!" << std::endl;
    }
    else {
        device_stream << "> This Thermostat has " << thm->GetSensors().size() << " sensor(s):" << std::endl;
        for (const auto& s : thm->GetSensors()) {
            device_stream << " -";
            device_stream << (s->Interact()).rdbuf();
        }
    }
    return device_stream;
};
} // namespace smart_home
