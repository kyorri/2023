#include "XMLSpeakerDeviceWriter.h"

#include "DeviceStatusMessage.h"
#include "DeviceTypeMessage.h"
#include "SensorTypeMessage.h"
#include "SensorStatusMessage.h"

namespace smart_home {
pugi::xml_node XMLSpeakerDeviceWriter::Write(Device* device) {
    SpeakerDevice* sp = dynamic_cast<SpeakerDevice*>(device);
    DeviceStatusMessage dsm(sp->GetStatus());
    pugi::xml_document doc;
    pugi::xml_node device_node = doc.append_child("Device");
    DeviceTypeMessage dtm(sp->GetDeviceType());
    device_node.append_attribute("Type").set_value(dtm.GetType().c_str());
    device_node.append_attribute("Status").set_value(dsm.GetStatus().c_str());
    device_node.append_attribute("Volume").set_value(sp->GetVolume());

    if (sp->GetSensors().size() == 0) {
        return device_node;
    }
    
    for (auto s : sp->GetSensors()) {
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

DeviceType XMLSpeakerDeviceWriter::GetDeviceType() {
    return DeviceType::Speaker;
};

} // namespace smart_home