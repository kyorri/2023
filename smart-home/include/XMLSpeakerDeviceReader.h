#ifndef SH_XMLSPEAKERDEVICEREADER_INCLUDE_H_
#define SH_XMLSPEAKERDEVICEREADER_INCLUDE_H_

#include "SpeakerDevice.h"
#include "XMLDeviceReader.h"

namespace smart_home {

class XMLSpeakerDeviceReader : public XMLDeviceReader {
    public:
        XMLSpeakerDeviceReader() = default;
        ~XMLSpeakerDeviceReader() = default;
        antoniaptr::unique_ptr<Device> Read(pugi::xml_node);
};

} // smart_home

#endif // SH_XMLSPEAKERDEVICEREADER_INCLUDE_H_