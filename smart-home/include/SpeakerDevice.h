#ifndef SH_SPEAKERDEVICE_INCLUDE_H__
#define SH_SPEAKERDEVICE_INCLUDE_H__

#include "Device.h"

namespace smart_home {
class SpeakerDevice : public Device {
    public:
        SpeakerDevice();

        void Interact() override;

        void Wait() override;
        void Continue() override;
        void TurnOn() override;
        void TurnOff() override;

        DeviceStatus GetStatus() override;
        void SetStatus(DeviceStatus) override;

        std::vector<std::shared_ptr<Sensor>> GetSensors() override;
        void AddSensor(std::shared_ptr<Sensor>) override;
        void RemoveSensor(std::shared_ptr<Sensor>) override;

        double GetVolume();
        void SetVolume(double);
    private:
        DeviceStatus status_;
        std::vector<std::shared_ptr<Sensor>> sensors_;
        DeviceType device_type_;
        double volume_;
};
} // namespace smart_home
#endif  // SH_SPEAKERDEVICE_INCLUDE_H__