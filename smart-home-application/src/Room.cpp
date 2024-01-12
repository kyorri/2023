#include "Room.h"

#include <vector>
#include <algorithm>

namespace smart_home_app {
    Room::Room(std::string room_name) : room_name_(room_name) {};

    Room::~Room() {
        for (Device* d : devices_) {
            delete d;
        }
        devices_.clear();
    };

    Room::Room(const Room& other) : room_name_(other.room_name_), devices_(other.devices_) {};

    Room& Room::operator=(const Room& other) {
        Room tmp(other);
        std::swap(room_name_, tmp.room_name_);
        std::swap(devices_, tmp.devices_);
        return *this;
    };
    
    Room::Room(Room&& other) : room_name_(std::move(other.room_name_)), devices_(std::move(other.devices_)) {};

    Room& Room::operator=(Room&& other) {
        if (!(other == *this)) {
            room_name_ = std::move(other.room_name_);
            devices_ = std::move(other.devices_);
        }
        return *this;
    };

    void Room::SetRoomName(std::string room_name) {
        room_name_ = room_name;
    };

    std::string Room::GetRoomName() {
        return room_name_;
    };

    void Room::AddDevice(Device* new_device) {
        devices_.push_back(new_device);
    };

    void Room::RemoveDevice(Device* rem_device) {
        auto it = std::find(devices_.begin(), devices_.end(), rem_device);
        devices_.erase(it);
    };

    bool Room::operator==(const Room& other) {
        return ((this->devices_ == other.devices_) && (this->room_name_ == other.room_name_));
    }

    std::vector<Device*> Room::GetDevices() {
        return devices_;
    };
    
} // namespace smart_home_app
