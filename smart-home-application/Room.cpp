#include "Room.h"

#include <vector>

Room::Room(std::string room_name) : room_name(room_name){};

void Room::setRoomName(std::string room_name)
{
    this->room_name = room_name;
};
std::string Room::getRoomName()
{
    return this->room_name;
};

std::vector<Device> Room::getDevices()
{
    return this->devices;
};