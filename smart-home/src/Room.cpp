#include "Room.h"

#include <vector>
#include <algorithm>

namespace smart_home {
    Room::Room(std::string room_name) : name_(room_name) {};

    Room::~Room() {
        devices_.clear();
    };

    Room::Room(const Room& other) : name_(other.name_), devices_(other.devices_) {};

    Room& Room::operator=(const Room& other) {
        Room tmp(other);
        std::swap(name_, tmp.name_);
        std::swap(devices_, tmp.devices_);
        return *this;
    };
    
    Room::Room(Room&& other) : name_(std::move(other.name_)), devices_(std::move(other.devices_)) {};

    Room& Room::operator=(Room&& other) {
        if (!(other == *this)) {
            name_ = std::move(other.name_);
            devices_ = std::move(other.devices_);
        }
        return *this;
    };

    void Room::AddDevice(std::shared_ptr<Device>& p) {
        try {
            auto it = std::find_if(devices_.begin(), devices_.end(), 
                [&p](const std::shared_ptr<Device>& device) {
                    return device.get() == p.get();
                });
            if (it == devices_.end()) {
                devices_.emplace_back(std::move(p));
            }
            else {
                throw std::runtime_error("This sensor is already assigned to this speaker!");
            }
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    };

    void Room::RemoveDevice(std::shared_ptr<Device>& p) {
        devices_.erase(
            std::remove_if(devices_.begin(), devices_.end(),
                [&p](const std::shared_ptr<Device>& device) {
                    return device.get() == p.get();
                }),
            devices_.end()
        );
    };

    bool Room::operator==(const Room& other) {
        return ((this->devices_ == other.devices_) && (this->name_ == other.name_));
    }

    void Room::SetName(std::string room_name) {
        name_ = room_name;
    };

    std::string Room::GetName() {
        return name_;
    };

    std::vector<std::shared_ptr<Device>> Room::GetDevices() {
        return devices_;
    };
    
} // namespace smart_home_app