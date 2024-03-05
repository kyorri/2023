#ifndef SH_XMLSPEAKERDEVICEWRITER_INCLUDE_H_
#define SH_XMLSPEAKERDEVICEWRITER_INCLUDE_H_

#include "SpeakerDevice.h"
#include "DeviceType.h"
#include "XMLDeviceWriter.h"

namespace smart_home {

class XMLSpeakerDeviceWriter : public XMLDeviceWriter {
    public:
        pugi::xml_node Write(Device*) override;
        DeviceType GetDeviceType() override;
};

} // namespace smart_home

#endif // SH_XMLSPEAKERDEVICEWRITER_INCLUDE_H_