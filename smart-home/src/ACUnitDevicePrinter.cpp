#include "ACUnitDevicePrinter.h"
#include "DeviceStatusMessage.h"
#include "ACHeatingStatus.h"

namespace smart_home {
std::stringstream ACUnitDevicePrinter::Print(Device* device) {
    ACUnitDevice* ac = dynamic_cast<ACUnitDevice*>(device);
    DeviceStatusMessage dsm(ac->GetStatus());
    std::string heating_message;
    std::stringstream device_stream;
    try {
        switch (ac->GetHeatingStatus()) {
        case ACHeatingStatus::Cooling:
            heating_message = "cooling";
            break;
        
        case ACHeatingStatus::Heating:
            heating_message = "heating";
            break;

        case ACHeatingStatus::Standby:
            heating_message = "neither cooling nor heating";
            break;

        default:
            throw std::logic_error("This AC Unit is not in a right state of heating/cooling/neither!");
            break;
        }
        device_stream << "This AC Unit is in the " << dsm.GetStatus() << " state and is " << heating_message << " up the room!" << std::endl;
        if (ac->GetSensors().size() == 0) {
            device_stream << "> This unit has no sensors attached to it!" << std::endl;
        }
        else {
            device_stream << "> This Air Conditioning unit has " << ac->GetSensors().size() << " sensor(s):" << std::endl;
            for (const auto& s : ac->GetSensors()) {
                device_stream << " -";
                device_stream << (s->Interact()).rdbuf();
            }
        }
        return device_stream;
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return device_stream;
};
} // namespace smart_home
