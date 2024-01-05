
#include "Room.h"
#include "Device.h"
#include "Sensor.h"

#include "DevicePrinter.h"
#include "SensorPrinter.h"

#include "ACUnitDevice.h"
#include "DoorbellDevice.h"

#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "DistanceSensor.h"

#include "XMLReader.h"
#include "XMLWriter.h"

#include <iostream>
#include <vector>

int main()
{
    smart_home_app::Device* d1; // AC Unit
    smart_home_app::Device* d2; // Smart Doorbell
    smart_home_app::Sensor* s1; // Temp Sensor
    smart_home_app::Sensor* s2; // Distance Sensor
    smart_home_app::Sensor* s3; // Humidity Sensor

    s1 = new smart_home_app::TemperatureSensor;
    smart_home_app::TemperatureSensor* ts = dynamic_cast<smart_home_app::TemperatureSensor*>(s1);
    ts->SetScale('f');
    ts->SetReading(78.23);
    ts->SetScaleTo('k');

    s2 = new smart_home_app::HumiditySensor;
    smart_home_app::HumiditySensor* hs = dynamic_cast<smart_home_app::HumiditySensor*>(s2);
    hs->SetReading(0.57);

    s3 = new smart_home_app::DistanceSensor;
    smart_home_app::DistanceSensor* ds = dynamic_cast<smart_home_app::DistanceSensor*>(s3);
    ds->SetReading(0.32);
    ds->SetUnits("meter(s)");

    d1 = new smart_home_app::ACUnitDevice;
    smart_home_app::ACUnitDevice* ac = dynamic_cast<smart_home_app::ACUnitDevice*>(d1);
    ac->TurnOn();
    ac->AddSensor(s1);
    ac->AddSensor(s2);

    d2 = new smart_home_app::DoorbellDevice;
    smart_home_app::DoorbellDevice* db = dynamic_cast<smart_home_app::DoorbellDevice*>(d2);
    db->SetVisitors(3);
    db->AddSensor(s1);
    db->AddSensor(s3);

    smart_home_app::DevicePrinter dp;
    dp.AddDevice(d1);
    dp.AddDevice(d2);
    //dp.Print();
    
    s2->SetReading(0.23);
    
    smart_home_app::SensorPrinter sp;
    sp.AddSensor(s1);
    sp.AddSensor(s2);
    sp.AddSensor(s3);
    // sp.Print();

    smart_home_app::XMLWriter xmlw;

    smart_home_app::Room r("kitchen");
    r.AddDevice(d1);
    r.AddDevice(d2);
    xmlw.AddRoom(r);
    xmlw.Write("test.xml");

    delete ts;
    delete hs;
    delete ds;
    delete ac;
    delete db;

    return 0;
}
