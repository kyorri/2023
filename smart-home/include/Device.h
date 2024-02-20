#ifndef SH_DEVICE_INCLUDE_H_
#define SH_DEVICE_INCLUDE_H_

#include "Sensor.h"
#include "DeviceStatus.h"
#include "DeviceType.h"

#include <iostream>
#include <vector>
#include <memory>

namespace smart_home {
class Device {
    public:
        virtual void Interact() = 0;

        virtual void Wait() = 0;
        virtual void Continue() = 0;
        virtual void TurnOn() = 0;
        virtual void TurnOff() = 0;

        virtual DeviceStatus GetStatus() = 0;
        virtual void SetStatus(DeviceStatus) = 0;

        virtual std::vector<std::shared_ptr<Sensor>> GetSensors() = 0;
        virtual void AddSensor(std::shared_ptr<Sensor>) = 0;
        virtual void RemoveSensor(std::shared_ptr<Sensor>) = 0;
    // protected:
    //     DeviceStatus status_;
    //     std::vector<std::shared_ptr<Sensor>> sensors_;
};
} // namespace smart_home
#endif  // SH_DEVICE_INCLUDE_H_