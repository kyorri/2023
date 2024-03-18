#include "App.h"

namespace smart_home {
App::App() {
    DeviceFactory df;
    SensorFactory sf;
    antoniaptr::unique_ptr<Room> room(new Room("Living Room"));
    ThreadedPrintingService tps(room.get(), 6);
    tps.StartPrintingService();
    antoniaptr::unique_ptr<Device> ac = df.Build(DeviceType::ACUnit);

    antoniaptr::unique_ptr<Sensor> sensor1 = sf.Build(SensorType::Humidity);
    antoniaptr::unique_ptr<Sensor> sensor2 = sf.Build(SensorType::Temperature);
    antoniaptr::unique_ptr<Sensor> sensor3 = sf.Build(SensorType::AirQualityLevel);

    ac->AddSensor(std::move(sensor1));
    ac->AddSensor(std::move(sensor2));
    ac->AddSensor(std::move(sensor3));

    ac->TurnOn();
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    room->AddDevice(std::move(ac));
    std::this_thread::sleep_for(std::chrono::seconds(5));

    antoniaptr::unique_ptr<Device> speaker = df.Build(DeviceType::Speaker);
    antoniaptr::unique_ptr<Sensor> sensor4 = sf.Build(SensorType::Humidity);
    antoniaptr::unique_ptr<Sensor> sensor5 = sf.Build(SensorType::Temperature);

    speaker->TurnOn();
    speaker->Wait();

    speaker->AddSensor(std::move(sensor4));
    speaker->AddSensor(std::move(sensor5));

    std::this_thread::sleep_for(std::chrono::seconds(5));
    room->AddDevice(std::move(speaker));
    std::this_thread::sleep_for(std::chrono::seconds(5));

    tps.StopPrintingService();
}
} // namespace smart_home