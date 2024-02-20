#include "ACUnitDevicePrinter.h"
#include "DeviceStatusMessage.h"
#include "ACHeatingStatus.h"

namespace smart_home {
void ACUnitDevicePrinter::Print(Device* device) {
    ACUnitDevice* ac = dynamic_cast<ACUnitDevice*>(device);
    DeviceStatusMessage dsm(ac->GetStatus());
    std::string heating_message;
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
        std::cout << "This AC Unit is in the " << dsm.GetStatus() << " state and is " << heating_message << " up the room!" << std::endl;
        if (ac->GetSensors().size() == 0) {
            std::cout << "> This unit has no sensors attached to it!" << std::endl;
        }
        else {
            std::cout<< "> This Air Conditioning unit has " << ac->GetSensors().size() << " sensor(s):" << std::endl;
            for (auto s : ac->GetSensors()) {
                std::cout << " -";
                s->Interact();
            }
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
};
} // namespace smart_home
