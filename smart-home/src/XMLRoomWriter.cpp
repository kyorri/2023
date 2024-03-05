#include "XMLRoomWriter.h"

#include "Room.h"
#include "XMLDeviceWriter.h"
#include "XMLACUnitDeviceWriter.h"
#include "XMLSpeakerDeviceWriter.h"
#include "XMLThermostatDeviceWriter.h"

namespace smart_home{
pugi::xml_node XMLRoomWriter::Write(const Room& room) {
    pugi::xml_document doc;
    pugi::xml_node room_node = doc.append_child("Room");
    room_node.append_attribute("Name").set_value(room.GetName().c_str());
    try {
        for (auto d : room.GetDevices()) {
            if (d != nullptr) {
                XMLDeviceWriter* xml;
                switch (d->GetDeviceType()) {
                    case DeviceType::ACUnit:
                        xml = new XMLACUnitDeviceWriter;
                        break;

                    case DeviceType::Speaker:
                        xml = new XMLSpeakerDeviceWriter;
                        break;

                    case DeviceType::Thermostat:
                        xml = new XMLThermostatDeviceWriter;
                        break;

                    default:
                        throw std::logic_error("Non-existing device type for writing to an XML!");
                        break;
                }
                room_node.append_copy(xml->Write(d));
            }
            else {
                throw std::runtime_error("Cannot write to an XML file a device with nullptr address!");
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return room_node;
}
} // namespace smart_home
