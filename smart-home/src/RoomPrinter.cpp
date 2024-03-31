#include "RoomPrinter.h"

#include "DevicePrinter.h"
#include "ACUnitDevicePrinter.h"
#include "SpeakerDevicePrinter.h"
#include "ThermostatDevicePrinter.h"

namespace smart_home {
std::stringstream RoomPrinter::Print(Room* room) {
    std::stringstream room_stream;
    try {
        if (room != nullptr) {

            if (room->GetDevices().size() > 0) {
                room_stream << room->GetName() << " has " << room->GetDevices().size() << " device(s) inside." << std::endl;
                for (const auto& device : room->GetDevices()) {
                    if (device != nullptr) {
                        DevicePrinter* dev_printer;
                        switch (device->GetDeviceType()) {
                            case DeviceType::ACUnit:
                                dev_printer = new ACUnitDevicePrinter();
                                break;
                            
                            case DeviceType::Speaker:
                                dev_printer = new SpeakerDevicePrinter();
                                break;

                            case DeviceType::Thermostat:
                                dev_printer = new ACUnitDevicePrinter();
                                break;

                            default:
                                throw std::runtime_error("There was a problem fetching the Device type.");
                                break;
                        }
                        room_stream << (dev_printer->Print(device)).rdbuf();
                    }
                    else {
                        throw std::runtime_error("Cannot print a Device with a nullptr address.");
                    }
                }
            } 
            else {
                std::cout << room->GetName() << " has no devices." << std::endl;
            } 
        }
        else {
            throw std::runtime_error("Cannot print a Room with a nulllptr address.");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl; 
    }
    return room_stream;
};
} // namespace smart_home