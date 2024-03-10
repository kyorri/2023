#include "App.h"

namespace smart_home {
App::App() {
    XMLWriter xmlwr("test.xml");
    antoniaptr::unique_ptr<Device> ac(new ACUnitDevice());
    antoniaptr::unique_ptr<Sensor> s1(new TemperatureSensor());
    antoniaptr::unique_ptr<Sensor> s2(new HumiditySensor());
    antoniaptr::unique_ptr<Sensor> s3(new TemperatureSensor());

    DeviceFactory df;
    SensorFactory sf;

    antoniaptr::unique_ptr<Device> speaker = df.Build(DeviceType::Speaker);
    ac->TurnOn();
    s1->TurnOn();
    s1->Wait();
    s2->TurnOn();

    antoniaptr::unique_ptr<Sensor> s4 = sf.Build(SensorType::AirQualityLevel); 

    s4->SetReading(156);
    ac->AddSensor(std::move(s1));
    ac->AddSensor(std::move(s2));
    ac->AddSensor(std::move(s4));

    antoniaptr::unique_ptr<Room> room1(new Room("Living Room"));


    room1->AddDevice(std::move(ac));
    speaker->AddSensor(std::move(s3));
    room1->AddDevice(std::move(speaker));

    // RoomPrinter room_pr;

    // room_pr.Print(room1.get());
    // xmlwr.AddRoom(std::move(room1));

    antoniaptr::unique_ptr<Room> room2(new Room("Kitchen"));
    antoniaptr::unique_ptr<Sensor> s5 = sf.Build(SensorType::Temperature);
    s5->SetReading(22.53);
    s5->TurnOn();
    s5->Wait();

    antoniaptr::unique_ptr<Device> d_room2 = df.Build(DeviceType::Thermostat);
    d_room2->TurnOn();
    d_room2->Wait();
    d_room2->TurnOn();
    std::cout << std::endl;
    d_room2->AddSensor(std::move(s5));

    // DevicePrinter* dp = new ThermostatDevicePrinter();
    // Device* dev = d_room2.get();
    // dp->Print(dev);

    room2->AddDevice(std::move(d_room2));

    ThreadedPrintingService tps(room1.get(), 4);
    tps.StartPrintingService();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    tps.StopPrintingService();

    // xmlwr.AddRoom(std::move(room2));
    xmlwr.Write();

}
} // namespace smart_home