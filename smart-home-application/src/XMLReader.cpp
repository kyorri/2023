#include "XMLReader.h"

#include "Room.h"
#include "Device.h"
#include "Sensor.h"

#include "ACUnitDevice.h"
#include "DoorbellDevice.h"
#include "LightDevice.h"

#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "DistanceSensor.h"

namespace smart_home_app {

    void XMLReader::Read(std::string filename) {
        pugi::xml_document doc;
        doc.load_file(filename.c_str());
        pugi::xml_node root_node = doc.child("Root");

        for (pugi::xml_node room_node = root_node.child("Room"); room_node; room_node = room_node.next_sibling("Room")) {
            Room* r = new Room(room_node.attribute("name").value());

            for (pugi::xml_node device_node = room_node.child("Device"); device_node; device_node = device_node.next_sibling("Device")) {
                Device* d = nullptr;

                std::string device_type = device_node.attribute("type").value();
                std::string device_status = device_node.attribute("status").value();

                if (device_type == "acunit") {

                }
                else if (device_type == "doorbell") {
                    std::string visitors = device_node.attribute("visitors").value();
                    dynamic_cast<DoorbellDevice*>(d)->SetVisitors(std::stoi(visitors));
                }
                else if (device_type == "lights") {
                    std::string brightness = device_node.attribute("brightness").value();
                    dynamic_cast<LightDevice*>(d)->SetBrightness(std::stoi(brightness));
                }

                for (pugi::xml_node sensor_node = device_node.child("Sensor"); sensor_node; sensor_node = sensor_node.next_sibling("Sensor")) {
                    Sensor* s = nullptr;

                    std::string sensor_type = sensor_node.attribute("type").value();
                    std::string reading = sensor_node.attribute("reading").value();

                    if (sensor_type == "temp") {
                        std::string scale = sensor_node.attribute("scale").value();
                        TemperatureSensor* ts = dynamic_cast<TemperatureSensor*>(s);
                        ts->SetScale(*scale.c_str());
                    }
                    else if (sensor_type == "hum") {

                    }
                    else if (sensor_type == "dist") {
                        std::string unit = sensor_node.attribute("unit").value();
                        DistanceSensor* ds = dynamic_cast<DistanceSensor*>(s);
                        ds->SetUnits(unit);
                    }

                    d->AddSensor(s);
                }
                r->AddDevice(d);
            }
            rooms_.push_back(*r);
            delete r;
        }
    };

    std::vector<Room> XMLReader::GetRooms() {
        return rooms_;
    }
} // namespace smart_home_app
