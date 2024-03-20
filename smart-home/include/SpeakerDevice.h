#ifndef SH_SPEAKERDEVICE_INCLUDE_H__
#define SH_SPEAKERDEVICE_INCLUDE_H__

#include "Device.h"

namespace smart_home {
class SpeakerDevice : public Device {
    public:
        SpeakerDevice();

        std::stringstream Interact() override;

        void Wait() override;
        void Continue() override;
        void TurnOn() override;
        void TurnOff() override;

        DeviceStatus GetStatus() override;
        void SetStatus(DeviceStatus) override;

        std::vector<Sensor*> GetSensors() override;
        void AddSensor(antoniaptr::unique_ptr<Sensor>) override;
        void RemoveSensor(int) override;

        double GetVolume();
        void SetVolume(double);

        DeviceType GetDeviceType();
    private:
        DeviceStatus status_;
        std::vector<antoniaptr::unique_ptr<Sensor>> sensors_;
        DeviceType device_type_;
        double volume_;
};
} // namespace smart_home
#endif  // SH_SPEAKERDEVICE_INCLUDE_H__