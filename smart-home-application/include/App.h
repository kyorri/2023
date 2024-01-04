#ifndef SHA_APP_H_
#define SHA_APP_H_

#include "pugixml.hpp"

#include "Room.h"
#include "Device.h"
#include "Sensor.h"

#include <string>
#include <vector>

namespace smart_home_app {
class App {
    public:
        App(std::string);

        void Save();
        void Load();

        void AddRoom(Room&);
        void RemoveRoom(Room&);

        void AddSensorToDevice(Device&, Sensor&);
        void AddDeviceToRoom(Room&, Device&);
        
        void RemoveSensorFromDevice(Device&, Sensor&);
        void RemoveDeviceFromRoom(Room&, Device&);

        std::vector<Room>& GetRooms();
    private:
        std::string filename_;
        std::vector<Room> rooms_;
};
} // namespace smart_home_app

#endif // SHA_APP_H_