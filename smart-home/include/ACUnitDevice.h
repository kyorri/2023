#ifndef SH_ACUNITDEVICE_INCLUDE_H_
#define SH_ACUNITDEVICE_INCLUDE_H_

#include "Device.h"
#include "ACHeatingStatus.h"

namespace smart_home {
class ACUnitDevice : public Device {
    public:
        ACUnitDevice();

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

        ACHeatingStatus GetHeatingStatus();
        void StartHeating();
        void StopHeating();
        void StartCooling();
        void StopCooling();

    private:
        DeviceStatus status_;
        std::vector<std::shared_ptr<Sensor>> sensors_;
        DeviceType device_type_;
        ACHeatingStatus heating_status_;
};
} // namespace smart_home
#endif  // SH_ACUNITDEVICE_INCLUDE_H_