#include "App.h"

namespace smart_home {
App::App() {
    smart_home::DeviceFactory df;
    smart_home::Device* d1 = df.Build(smart_home::DeviceType::Speaker);
    smart_home::SpeakerDevice* sdev1 = dynamic_cast<smart_home::SpeakerDevice*>(d1);
    sdev1->TurnOn();
    sdev1->SetVolume(0.5);
    // sdev1->Interact();

    smart_home::Device* d2 = df.Build(smart_home::DeviceType::ACUnit);
    smart_home::ACUnitDevice* acdev1 = dynamic_cast<smart_home::ACUnitDevice*>(d2);
    std::shared_ptr<smart_home::AirQualitySensor> s1 = std::make_shared<smart_home::AirQualitySensor>(123);
    acdev1->TurnOn();
    acdev1->StartHeating();
    acdev1->AddSensor(s1);
    acdev1->AddSensor(s1);
    acdev1->RemoveSensor(s1);
    s1->TurnOn();
    s1->Wait();
    s1->SetReading(50);
    acdev1->AddSensor(s1);
    acdev1->TurnOff();
    acdev1->TurnOn();
    smart_home::DevicePrinter* dev_prnt = new smart_home::ACUnitDevicePrinter;
    dev_prnt->Print(acdev1);
}
} // namespace smart_home