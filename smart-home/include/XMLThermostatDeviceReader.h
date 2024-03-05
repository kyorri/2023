#ifndef SH_XMLTHERMOSTATDEVICEREADER_INCLUDE_H_
#define SH_XMLTHERMOSTATDEVICEREADER_INCLUDE_H_

#include "ThermostatDevice.h"
#include "XMLDeviceReader.h"

namespace smart_home {

class XMLThermostatDeviceReader : public XMLDeviceReader {
    public:
        XMLThermostatDeviceReader() = default;
        ~XMLThermostatDeviceReader() = default;
        antoniaptr::unique_ptr<Device> Read(pugi::xml_node);
};

} // smart_home

#endif // SH_XMLTHERMOSTATDEVICEREADER_INCLUDE_H_