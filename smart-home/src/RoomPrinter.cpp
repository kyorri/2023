#include "RoomPrinter.h"

#include "DevicePrinter.h"
#include "ACUnitDevicePrinter.h"
#include "SpeakerDevicePrinter.h"
#include "ThermostatDevicePrinter.h"

namespace smart_home {
void RoomPrinter::Print(Room* room) {
    DevicePrinter* dev_printer;
    try {
        if (room != nullptr) {
            for (const auto& device : room->GetDevices()) {
                if (device != nullptr) {
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
                    dev_printer->Print(device);
                }
                else {
                    throw std::runtime_error("Cannot print a Device with a nullptr address.");
                }
            }
            
        }
        else {
            throw std::runtime_error("Cannot print a Room with a nulllptr address.");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl; 
    }
};
} // namespace smart_home
