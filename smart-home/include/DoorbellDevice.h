#ifndef SHA_DOORBELLDEVICE_H_
#define SHA_DOORBELLDEVICE_H_

#include "Device.h"

namespace smart_home_app {
class DoorbellDevice : public Device {
    public:
        std::string GetType() override;
        std::string GetInfo() override;
        void TurnOff() override;
        void TurnOn() override;
        void AddSensor(Sensor*) override;
        void RemoveSensor(Sensor*) override;
        std::vector<Sensor*> GetSensors() override;
        std::string GetStatus() override;

        void SetVisitors(uint32_t);
        uint32_t GetVisitors();
    private:
        bool status_;
        uint32_t visitors_;
        std::vector<Sensor*> sensors_;
};
} // namespace smart_home_app

#endif // SHA_DOORBELLDEVICE_H_