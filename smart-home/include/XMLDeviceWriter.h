#ifndef SH_XMLDEVICEWRITER_INCLUDE_H_
#define SH_XMLDEVICEWRITER_INCLUDE_H_

#include "Device.h"
#include "DeviceType.h"

#include "pugixml.hpp"

namespace smart_home {

class XMLDeviceWriter {
    public:
        virtual pugi::xml_node Write(Device*) = 0;
        virtual DeviceType GetDeviceType() = 0;
};

} // namespace smart_home

#endif // SH_XMLDEVICEWRITER_INCLUDE_H_