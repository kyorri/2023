#include "XMLWriter.h"

#include "ACUnitDevice.h"
#include "DoorbellDevice.h"
#include "LightDevice.h"

#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "DistanceSensor.h"

#include <algorithm>


namespace smart_home_app {
void XMLWriter::Write(std::string filename) {
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("Root");

    for (Room r : rooms_) {
        pugi::xml_node room_root = root.append_child("Room");
        room_root.append_attribute("name").set_value(r.GetRoomName().c_str());

        for (Device* d : r.GetDevices()) {
            pugi::xml_node device_root = room_root.append_child("Device");
            device_root.append_attribute("type").set_value(d->GetType().c_str());
            device_root.append_attribute("status").set_value(d->GetStatus().c_str());

            std::string device_type = d->GetType();
            if (device_type == "acunit") {
                // Handle acunit device type if needed
            }
            else if (device_type == "doorbell") {
                device_root.append_attribute("visitors").set_value(dynamic_cast<DoorbellDevice*>(d)->GetVisitors());
            }
            else if (device_type == "lights") {
                device_root.append_attribute("brightness").set_value(dynamic_cast<LightDevice*>(d)->GetBrightness());
            }

            for (Sensor* s : d->GetSensors()) {
                pugi::xml_node sensor_root = device_root.append_child("Sensor");
                sensor_root.append_attribute("type").set_value(s->GetType().c_str());
                sensor_root.append_attribute("reading").set_value(s->GetReading());

                std::string sensor_type = s->GetType();
                if (sensor_type == "temp") {
                    sensor_root.append_attribute("scale").set_value((dynamic_cast<TemperatureSensor*>(s)->GetScale()).c_str());
                }
                else if (sensor_type == "hum") {
                    // Handle hum sensor type if needed
                }
                else if (sensor_type == "dist") {
                    sensor_root.append_attribute("unit").set_value((dynamic_cast<DistanceSensor*>(s)->GetUnits()).c_str());
                }
            }
        }
    }
    doc.save_file(filename.c_str());
};

    void XMLWriter::AddRoom(Room new_room) {
        rooms_.push_back(new_room);
    };

    void XMLWriter::RemoveRoom(Room rem_room) {
        auto it = find(rooms_.begin(), rooms_.end(), rem_room);
        rooms_.erase(it);
    };
} // namespace smart_home_app
