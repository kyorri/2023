#include "XMLThermostatDeviceReader.h"

#include "DeviceFactory.h"
#include "SensorFactory.h"
#include "MessageDeviceStatus.h"
#include "MessageSensorStatus.h"
#include "MessageSensorType.h"

namespace smart_home {
antoniaptr::unique_ptr<Device> XMLThermostatDeviceReader::Read(pugi::xml_node device_node) {
    DeviceFactory df;
    antoniaptr::unique_ptr<Device> device = df.Build(DeviceType::ACUnit);

    MessageDeviceStatus mds(device_node.attribute("Status").value());
    device->SetStatus(mds.GetStatus());

    double temp = atof(device_node.attribute("Temperature").value());
    double target_temp = atof(device_node.attribute("TargetTemperature").value());

    ThermostatDevice* speaker = dynamic_cast<ThermostatDevice*>(device.get());
    speaker->SetTemperature(temp);
    speaker->SetTargetTemperature(target_temp);

    SensorFactory sf;
    for (pugi::xml_node sensor_node : device_node.children("Sensor")) {
        std::string sensor_type_message = sensor_node.attribute("Type").value();
        MessageSensorType mst(sensor_type_message);
        
        std::string sensor_status_message = sensor_node.attribute("Status").value();
        MessageSensorStatus mss(sensor_status_message);
        SensorStatus sensor_status = mss.GetStatus();
        
        antoniaptr::unique_ptr<Sensor> sensor = sf.Build(mst.GetType());

        double reading = atof(sensor_node.attribute("Reading").value());
        sensor->SetStatus(sensor_status);
        sensor->SetReading(reading);
        device->AddSensor(std::move(sensor));
    }
    return std::move(device);
};

} // namespace smart_home