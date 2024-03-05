#include "Room.h"

#include <vector>
#include <algorithm>

namespace smart_home {
    Room::Room(std::string room_name) : name_(room_name) {};

    Room::~Room() {
        devices_.clear();
    };

    // Room::Room(const Room& other) : name_(other.name_) {
    //     std::for_each(other.devices_.begin(), other.devices_.end(), [&devices_] (const auto& d) {
    //         devices_.push_back(std::move(d));
    //     });
    // };

    // Room& Room::operator=(const Room& other) {
    //     Room tmp(other);
    //     std::swap(name_, tmp.name_);
    //     std::swap(devices_, tmp.devices_);
    //     return *this;
    // };
    
    Room::Room(Room&& other) : name_(std::move(other.name_)), devices_(std::move(other.devices_)) {};

    Room& Room::operator=(Room&& other) {
        if (!(other == *this)) {
            name_ = std::move(other.name_);
            devices_ = std::move(other.devices_);
        }
        return *this;
    };

    std::vector<Device*> Room::GetDevices() const {
        std::vector<Device*> devices;
        for (const auto& d : devices_) {
            devices.push_back(d.get());
        }
        return devices;
    };

    void Room::AddDevice(antoniaptr::unique_ptr<Device> p) {
        devices_.push_back(std::move(p));
    };

    void Room::RemoveDevice(int index) {
        try {
            if (index > devices_.size() || index < 0) {
                throw std::runtime_error("This index is not present in the sensors of this AC Unit.");
            }
            else {
                devices_.erase(devices_.begin() + index);
            }
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    };

    bool Room::operator==(const Room& other) {
        return (this->name_ == other.name_);
    }

    void Room::SetName(std::string room_name) {
        name_ = room_name;
    };

    std::string Room::GetName() const {
        return name_;
    };
} // namespace smart_home_app