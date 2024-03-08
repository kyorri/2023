#include "XMLACUnitDeviceWriter.h"

#include "DeviceStatusMessage.h"
#include "DeviceTypeMessage.h"
#include "SensorTypeMessage.h"
#include "SensorStatusMessage.h"

namespace smart_home {
pugi::xml_node XMLACUnitDeviceWriter::Write(Device* device) {
    DeviceStatusMessage dsm(device->GetStatus());
    ACUnitDevice* ac = dynamic_cast<ACUnitDevice*>(device);
    std::string heating_message;
    switch (ac->GetHeatingStatus()) {
        case ACHeatingStatus::Cooling:
            heating_message = "Cooling";
            break;

        case ACHeatingStatus::Heating:
            heating_message = "Heating";
            break;

        case ACHeatingStatus::Standby:
            heating_message = "Standby";
            break;

        default:
            break;
    }
    pugi::xml_document doc;
    pugi::xml_node device_node = doc.append_child("Device");
    DeviceTypeMessage dtm(ac->GetDeviceType());
    device_node.append_attribute("Type").set_value(dtm.GetType().c_str());
    device_node.append_attribute("Status").set_value(dsm.GetStatus().c_str());
    device_node.append_attribute("HeatingStatus").set_value(heating_message.c_str());

    if (ac->GetSensors().size() == 0) {
        return device_node;
    }
    
    for (auto s : ac->GetSensors()) {
        if (s == nullptr) {
            continue;
        }
        else {
            SensorTypeMessage stm(s->GetSensorType());
            SensorStatusMessage ssm(s->GetStatus());
            pugi::xml_node sensor_node = device_node.append_child("Sensor");
            sensor_node.append_attribute("Type").set_value(stm.GetType().c_str());
            sensor_node.append_attribute("Status").set_value(ssm.GetStatus().c_str());
            sensor_node.append_attribute("Reading").set_value(s->GetReading());
        }
    }
    return device_node;
};

DeviceType XMLACUnitDeviceWriter::GetDeviceType() {
    return DeviceType::ACUnit;
};

} // namespace smart_home