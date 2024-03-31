#ifndef SH_ACUNITDEVICE_INCLUDE_H_
#define SH_ACUNITDEVICE_INCLUDE_H_

#include "Device.h"
#include "ACHeatingStatus.h"

namespace smart_home {
class ACUnitDevice : public Device {
    public:
        ACUnitDevice();

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

        ACHeatingStatus GetHeatingStatus();
        void SetHeatingStatus(const ACHeatingStatus&);

        void StartHeating();
        void StopHeating();
        void StartCooling();
        void StopCooling();

        DeviceType GetDeviceType();
    private:
        DeviceStatus status_;
        std::vector<antoniaptr::unique_ptr<Sensor>> sensors_;
        DeviceType device_type_;
        ACHeatingStatus heating_status_;
};
} // namespace smart_home
#endif  // SH_ACUNITDEVICE_INCLUDE_H_