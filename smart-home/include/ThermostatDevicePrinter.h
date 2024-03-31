#ifndef SH_THERMOSTATDEVICEPRINTER_INCLUDE_H_
#define SH_THERMOSTATDEVICEPRINTER_INCLUDE_H_

#include "DevicePrinter.h"
#include "ThermostatDevice.h"

namespace smart_home {
class ThermostatDevicePrinter : public DevicePrinter {
    public:
        std::stringstream Print(Device*);
};
} // namespace smart_home
#endif  // SH_THERMOSTATDEVICEPRINTER_INCLUDE_H_