#ifndef SHA_LIGHTDEVICE_H_
#define SHA_LIGHTDEVICE_H_

#include "Device.h"

namespace smart_home_app {
class LightDevice : public Device {
    public:
        std::string GetType() override;
        std::string GetInfo() override;
        void TurnOff() override;
        void TurnOn() override;
        void AddSensor(Sensor*) override;
        void RemoveSensor(Sensor*) override;
        std::vector<Sensor*> GetSensors() override;
        std::string GetStatus() override;

        uint32_t GetBrightness();
        void SetBrightness(uint32_t);
    private:
        bool status_;
        uint32_t brightness_;
        std::vector<Sensor*> sensors_;
};
} // namespace smart_home_app

#endif // SHA_LIGHTDEVICE_H_