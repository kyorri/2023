#ifndef SH_THERMOSTATDEVICE_INCLUDE_H_
#define SH_THERMOSTATDEVICE_INCLUDE_H_

#include "Device.h"
#include "TemperatureSensor.h"

namespace smart_home {
class ThermostatDevice : public Device {
    public:
        ThermostatDevice();
        ThermostatDevice(const TemperatureSensor);

        void Interact() override;

        void Wait() override;
        void Continue() override;
        void TurnOn() override;
        void TurnOff() override;

        DeviceStatus GetStatus() override;
        void SetStatus(DeviceStatus) override;

        std::vector<Sensor*> GetSensors() override;
        void AddSensor(antoniaptr::unique_ptr<Sensor>) override;
        void RemoveSensor(int) override;

        double GetTargetTemperature();
        double GetTemperature();
        void SetTargetTemperature(double);
        void SetTemperature(double);

        DeviceType GetDeviceType();
    private:
        DeviceStatus status_;
        std::vector<antoniaptr::unique_ptr<Sensor>> sensors_;
        DeviceType device_type_;
        double target_temp_;
        double temperature_;
};
} // namespace smart_home
#endif  // SH_THERMOSTATDEVICE_INCLUDE_H_