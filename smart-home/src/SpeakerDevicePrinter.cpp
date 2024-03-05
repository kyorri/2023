#include "SpeakerDevicePrinter.h"
#include "DeviceStatusMessage.h"

namespace smart_home {
void SpeakerDevicePrinter::Print(Device* device) {
    SpeakerDevice* sp = dynamic_cast<SpeakerDevice*>(device);
    DeviceStatusMessage dsm(sp->GetStatus());
    std::cout << "This Speaker is in the " << dsm.GetStatus() << " state and is has volume set to " << sp->GetVolume() * 100 << " percent!" << std::endl;
    if (sp->GetSensors().size() == 0) {
        std::cout << "> This unit has no sensors attached to it!" << std::endl;
    }
    else {
        std::cout<< "> This Speaker has " << sp->GetSensors().size() << " sensor(s):" << std::endl;
        for (const auto& s : sp->GetSensors()) {
            std::cout << " -";
            s->Interact();
        }
    }
};
} // namespace smart_home
