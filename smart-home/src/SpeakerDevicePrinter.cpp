#include "SpeakerDevicePrinter.h"
#include "DeviceStatusMessage.h"

namespace smart_home {
std::stringstream SpeakerDevicePrinter::Print(Device* device) {
    SpeakerDevice* sp = dynamic_cast<SpeakerDevice*>(device);
    DeviceStatusMessage dsm(sp->GetStatus());
    std::stringstream device_stream;
    device_stream << "This Speaker is in the " << dsm.GetStatus() << " state and is has volume set to " << sp->GetVolume() * 100 << " percent!" << std::endl;
    if (sp->GetSensors().size() == 0) {
        device_stream << "> This unit has no sensors attached to it!" << std::endl;
    }
    else {
        device_stream << "> This Speaker has " << sp->GetSensors().size() << " sensor(s):" << std::endl;
        for (const auto& s : sp->GetSensors()) {
            device_stream << " -";
            device_stream << (s->Interact()).rdbuf();
        }
    }
    return device_stream;
};
} // namespace smart_home
