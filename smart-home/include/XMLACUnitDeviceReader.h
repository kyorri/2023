#ifndef SH_XMLACUNITDEVICEREADER_INCLUDE_H_
#define SH_XMLACUNITDEVICEREADER_INCLUDE_H_

#include "ACUnitDevice.h"
#include "XMLDeviceReader.h"

namespace smart_home {

class XMLACUnitDeviceReader : public XMLDeviceReader {
    public:
        XMLACUnitDeviceReader() = default;
        ~XMLACUnitDeviceReader() = default;
        antoniaptr::unique_ptr<Device> Read(pugi::xml_node);
};

} // smart_home

#endif // SH_XMLACUNITDEVICEREADER_INCLUDE_H_