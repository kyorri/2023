#ifndef SH_ROOM_INCLUDE_H_
#define SH_ROOM_INCLUDE_H_

#include "Sensor.h"
#include "Device.h"
#include "unique_ptr.h"

#include <vector>
#include <memory>

namespace smart_home {
class Room {
    public:
        Room(std::string);
        ~Room();

        Room(const Room&) = delete;
        Room& operator=(const Room&) = delete;
        
        Room(Room&&);
        Room& operator=(Room&&);

        void SetName(std::string);
        std::string GetName() const;

        void AddDevice(antoniaptr::unique_ptr<Device>);
        void RemoveDevice(int);

        bool operator==(const Room&);

        std::vector<Device*> GetDevices() const;
    private:
        std::vector<antoniaptr::unique_ptr<Device>> devices_;
        std::string name_;
};
} // namespace smart_home

#endif  // SH_ROOM_INCLUDE_H_