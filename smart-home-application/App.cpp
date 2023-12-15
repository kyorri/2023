#include "pugixml.hpp"

#include "App.h"
#include "Room.h"
#include "Device.h"
#include "Sensor.h"

#include <iostream>
#include <algorithm>

namespace smart_home_app {
App::App(std::string filename) : filename_(filename) {};

void App::Load() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(this->filename_.c_str());

    if (!result)
    {
        std::cout << "pugiXML parsing failed - " << result.description() << "." << std::endl;
        return;
    }

    pugi::xml_node roomsNode = doc.child("Configuration").child("Rooms");

    for (pugi::xml_node roomNode = roomsNode.child("Room"); roomNode; roomNode = roomNode.next_sibling("Room"))
    {
        std::string roomName = roomNode.attribute("name").as_string();
        Room room(roomName);

        for (pugi::xml_node deviceNode = roomNode.child("Devices").child("Device"); deviceNode; deviceNode = deviceNode.next_sibling("Device"))
        {
            std::string deviceName = deviceNode.attribute("name").as_string();
            bool deviceStatus = deviceNode.attribute("status").as_bool();
            Device device(deviceName, deviceStatus);

            for (pugi::xml_node sensorNode = deviceNode.child("Sensors").child("Sensor"); sensorNode; sensorNode = sensorNode.next_sibling("Sensor"))
            {
                std::string sensorType = sensorNode.attribute("type").as_string();
                double sensorReading = sensorNode.attribute("reading").as_double();
                Sensor sensor(sensorType, sensorReading);

                device.AddSensor(sensor);
            }

            room.AddDevice(device);
        }

        this->rooms_.push_back(room);
    }

    std::cout << "Configuration data loaded successfully from " << this->filename_ << "!" << std::endl;
};

void App::Save() {
    pugi::xml_document doc;

    pugi::xml_node root = doc.append_child("Configuration");
    pugi::xml_node rooms_node = root.append_child("Rooms");

    for (auto &room : rooms_)
    {
        pugi::xml_node room_node = rooms_node.append_child("Room");
        room_node.append_attribute("name").set_value(room.GetRoomName().c_str());
        pugi::xml_node devices_node = room_node.append_child("Devices");
        for (auto &device : room.GetDevices()) {
            pugi::xml_node device_node = devices_node.append_child("Device");
            device_node.append_attribute("name").set_value(device.GetDeviceName().c_str());
            device_node.append_attribute("status").set_value(device.GetStatus());
            pugi::xml_node t = device_node.append_child("Sensors");
            for (auto sensor : device.GetSensors()) {
                pugi::xml_node sensor_node = t.append_child("Sensor");
                sensor_node.append_attribute("type").set_value(sensor.GetSensorType().c_str());
                sensor_node.append_attribute("reading").set_value(sensor.GetReading());
            }
        }
    }
    bool saveResult = doc.save_file(this->filename_.c_str());
    if (saveResult) {
        std::cout << "Configuration saved succesfully to " << filename_ << "!" << std::endl;
    } else {
        std::cout << "Problem with saving to " << filename_ << "!" << std::endl;
    }
    // for (Room room : this->GetRooms()) {
    //     std::cout << "Room - " << room.GetRoomName() << std::endl;
    //     std::vector<Device> v1 = room.GetDevices();
    //     for (Device d : v1) {
    //         std::cout << "\tDevice - " << d.GetDeviceName() << " - " << ((d.GetStatus() == true) ? "on" : "off") << std::endl;

    //         std::vector<Sensor> v2 = d.GetSensors();
    //         for (Sensor s : v2) {
    //             std::cout << "\t\tSensor - " << s.GetSensorType() << " -> " << s.GetReading() << std::endl;
    //         }
    // }

};

void App::AddRoom(Room& room) {
    this->GetRooms().push_back(room);
};

void App::RemoveRoom(Room& room) {
    size_t i = 0;
    for (auto r : this->GetRooms()) {
        if (r.GetRoomName() == room.GetRoomName()) {
            this->rooms_.erase(this->rooms_.begin() + i);
            break;
        }
        i++;
    }
};

void App::AddSensorToDevice(Device &device, Sensor& sensor) {
    device.AddSensor(sensor);
};

void App::AddDeviceToRoom(Room &room, Device &device) {
    room.AddDevice(device);
};

void App::RemoveSensorFromDevice(Device &device, Sensor& sensor) {
    device.RemoveSensor(sensor);
}

void App::RemoveDeviceFromRoom(Room &room, Device& device) {
    room.RemoveDevice(device);
}

std::vector<Room>& App::GetRooms() {
    return this->rooms_;
};
} // namespace smart_home_app