#ifndef SH_XMLDEVICEREADER_INCLUDE_H_
#define SH_XMLDEVICEREADER_INCLUDE_H_

#include "Device.h"
#include "DeviceType.h"

#include "pugixml.hpp"

namespace smart_home {

class XMLDeviceReader {
    public:
        virtual antoniaptr::unique_ptr<Device> Read(pugi::xml_node) = 0;
};

} // smart_home

#endif // SH_XMLDEVICEREADER_INCLUDE_H_