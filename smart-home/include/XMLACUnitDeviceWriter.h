#ifndef SH_XMLACUNITDEVICEWRITER_INCLUDE_H_
#define SH_XMLACUNITDEVICEWRITER_INCLUDE_H_

#include "ACUnitDevice.h"
#include "DeviceType.h"
#include "XMLDeviceWriter.h"

namespace smart_home {

class XMLACUnitDeviceWriter : public XMLDeviceWriter {
    public:
        pugi::xml_node Write(Device*) override;
        DeviceType GetDeviceType() override;
};

} // namespace smart_home

#endif // SH_XMLACUNITDEVICEWRITER_INCLUDE_H_