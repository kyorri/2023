#ifndef SH_DEVICEPRINTER_INCLUDE_H_
#define SH_DEVICEPRINTER_INCLUDE_H_

#include "Device.h"

#include <sstream>

namespace smart_home {
class DevicePrinter {
    public:
        virtual std::stringstream Print(Device*) = 0;
};
} // namespace smart_home
#endif  // SH_DEVICEPRINTER_INCLUDE_H_