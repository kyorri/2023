#ifndef SHA_DEVICE_H_
#define SHA_DEVICE_H_

#include "Sensor.h"

#include <vector>
#include <string>

namespace smart_home_app {
class Device {
    public:
		virtual std::string GetType() = 0;
        virtual std::string GetInfo() = 0;
		virtual void TurnOff() = 0;
		virtual void TurnOn() = 0;
		virtual void AddSensor(Sensor*) = 0;
		virtual void RemoveSensor(Sensor*) = 0;
		virtual std::vector<Sensor*> GetSensors() = 0;
		virtual std::string GetStatus() = 0;
};
} // namespace smart_home_app

#endif // SHA_DEVICE_H_
