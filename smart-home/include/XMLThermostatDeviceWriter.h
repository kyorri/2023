#ifndef SH_XMLTHERMOSTATDEVICEWRITER_INCLUDE_H_
#define SH_XMLTHERMOSTATDEVICEWRITER_INCLUDE_H_

#include "ThermostatDevice.h"
#include "DeviceType.h"
#include "XMLDeviceWriter.h"

namespace smart_home {

class XMLThermostatDeviceWriter : public XMLDeviceWriter {
    public:
        pugi::xml_node Write(Device*) override;
        DeviceType GetDeviceType() override;
};

} // namespace smart_home

#endif // SH_XMLTHERMOSTATDEVICEWRITER_INCLUDE_H_