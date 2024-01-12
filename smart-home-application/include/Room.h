#ifndef SHA_ROOM_H_
#define SHA_ROOM_H_

#include "Device.h"

#include <vector>
#include <string>

namespace smart_home_app {
class Room {
    public:
        Room(std::string);
        ~Room();

        Room(const Room&);
        Room& operator=(const Room&);
        
        Room(Room&&);
        Room& operator=(Room&&);

        void SetRoomName(std::string);
        std::string GetRoomName();

        void AddDevice(Device*);
        void RemoveDevice(Device*);

        bool operator==(const Room&);

        std::vector<Device*> GetDevices();
    private:
        std::string room_name_;
        std::vector<Device*> devices_;
};
} // namespace smart_home_app

#endif // SHA_ROOM_H_