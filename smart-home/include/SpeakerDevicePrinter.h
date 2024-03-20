#ifndef SH_SPEAKERDEVICEPRINTER_INCLUDE_H_
#define SH_SPEAKERDEVICEPRINTER_INCLUDE_H_

#include "DevicePrinter.h"
#include "SpeakerDevice.h"

namespace smart_home {
class SpeakerDevicePrinter : public DevicePrinter {
    public:
        std::stringstream Print(Device*);
};
} // namespace smart_home
#endif  // SH_SPEAKERDEVICEPRINTER_INCLUDE_H_