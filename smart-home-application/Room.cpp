#include "Room.h"

#include <vector>
#include <algorithm>

namespace smart_home_app {
Room::Room(std::string room_name) : room_name_(room_name){};

void Room::SetRoomName(std::string room_name)
{
    this->room_name_ = room_name;
};
std::string Room::GetRoomName()
{
    return this->room_name_;
};

void Room::AddDevice(Device& device) {
    this->devices_.push_back(device);
};

void Room::RemoveDevice(Device& device) {
    size_t i = 0;
    for (auto d : this->devices_) {
        if (d.GetDeviceName() == device.GetDeviceName()) {
            this->devices_.erase(this->devices_.begin() + i);
            break;
        }
        i++;
    }
};

std::vector<Device>& Room::GetDevices()
{
    return this->devices_;
};
} // namespace smart_home_app
