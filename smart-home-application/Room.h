#ifndef SHA_ROOM_H_
#define SHA_ROOM_H_

#include <vector>
#include <string>
#include "Device.h"

class Room {
    public:
        Room(std::string);

        void setRoomName(std::string);
        std::string getRoomName();

        std::vector<Device> getDevices();
    private:
        std::string room_name;
        std::vector<Device> devices;
};

#endif // SHA_ROOM_H_