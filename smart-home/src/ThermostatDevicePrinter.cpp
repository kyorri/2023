#include "ThermostatDevicePrinter.h"
#include "DeviceStatusMessage.h"

namespace smart_home {
void ThermostatDevicePrinter::Print(Device* device) {
    ThermostatDevice* thm = dynamic_cast<ThermostatDevice*>(device);
    DeviceStatusMessage dsm(thm->GetStatus());
    std::cout << "This Thermostat is in the "
            << dsm.GetStatus()
            << " state and the temperature of the room is "
            << thm->GetTemperature()
            << " degrees Celsius, with the target temperature of "
            << thm->GetTargetTemperature()
            << " degrees Celsius!" << std::endl;
    if (thm->GetSensors().size() == 0) {
        std::cout << "> This unit has no sensors attached to it!" << std::endl;
    }
    else {
        std::cout<< "> This Thermostat has " << thm->GetSensors().size() << " sensor(s):" << std::endl;
        for (const auto& s : thm->GetSensors()) {
            std::cout << " -";
            s->Interact();
        }
    }
};
} // namespace smart_home
