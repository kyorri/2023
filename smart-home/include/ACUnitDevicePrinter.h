#ifndef SH_ACUNITDEVICEPRINTER_INCLUDE_H_
#define SH_ACUNITDEVICEPRINTER_INCLUDE_H_

#include "DevicePrinter.h"
#include "ACUnitDevice.h"

namespace smart_home {
class ACUnitDevicePrinter : public DevicePrinter {
    public:
        std::stringstream Print(Device*);
};
} // namespace smart_home
#endif  // SH_ACUNITDEVICEPRINTER_INCLUDE_H_