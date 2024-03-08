#include "XMLRoomReader.h"

#include "DeviceTypeMessage.h"
#include "MessageDeviceType.h"
#include "DeviceType.h"
#include "XMLDeviceReader.h"
#include "XMLACUnitDeviceReader.h"
#include "XMLSpeakerDeviceReader.h"
#include "XMLThermostatDeviceReader.h"

namespace smart_home {
antoniaptr::unique_ptr<Room> XMLRoomReader::Read(pugi::xml_node room_node) {
    antoniaptr::unique_ptr<Room> room;

    try {
        if (room_node) {
            room->SetName(room_node.attribute("Name").value());
            
            for (pugi::xml_node device_node : room_node.children("Device")) {
                std::string device_type_message = device_node.attribute("Type").value();
                MessageDeviceType mdt(device_type_message);
                DeviceType device_type = mdt.GetType();
                
                antoniaptr::unique_ptr<Device> device;
                XMLDeviceReader* xmldr;
                switch (device_type) {
                    case DeviceType::ACUnit:
                        xmldr = new XMLACUnitDeviceReader();
                        break;

                    case DeviceType::Speaker:
                        xmldr = new XMLSpeakerDeviceReader();
                        break;

                    case DeviceType::Thermostat:
                        xmldr = new XMLThermostatDeviceReader();
                        break;
                    
                    default:
                        throw std::runtime_error("Error while fetching XML Device Reader!");

                }
                device = std::move(xmldr->Read(device_node));
                room->AddDevice(std::move(device));
            }
        } else {
            throw std::runtime_error("");
        }

    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return antoniaptr::unique_ptr<Room>(nullptr);
    }
    return room;
};
} // namespace smart_home
