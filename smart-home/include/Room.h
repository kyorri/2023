#ifndef SH_ROOM_INCLUDE_H_
#define SH_ROOM_INCLUDE_H_

#include "Sensor.h"
#include "Device.h"

#include <vector>
#include <memory>

namespace smart_home {
class Room {
    public:
        Room(std::string);
        ~Room();

        Room(const Room&);
        Room& operator=(const Room&);
        
        Room(Room&&);
        Room& operator=(Room&&);

        void SetName(std::string);
        std::string GetName();

        void AddDevice(std::shared_ptr<Device>&);
        void RemoveDevice(std::shared_ptr<Device>&);

        bool operator==(const Room&);

        std::vector<std::shared_ptr<Device>> GetDevices();
    private:
        std::vector<std::shared_ptr<Device>> devices_;
        std::string name_;
};
} // namespace smart_home

#endif  // SH_ROOM_INCLUDE_H_