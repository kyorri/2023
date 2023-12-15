#ifndef SHA_DEVICE_H_
#define SHA_DEVICE_H_

#include "Sensor.h"

#include <vector>
#include <string>

namespace smart_home_app {
class Device {
    public:
        Device(std::string, bool);
        
        ~Device();
        Device(const Device&);
        Device(Device&&);
        Device& operator=(const Device&);
        Device& operator=(Device&&);

        void SetDeviceName(std::string);
        std::string GetDeviceName();

        void SetStatus(bool);
        bool GetStatus();

        void AddSensor(Sensor);
        void RemoveSensor(Sensor);

        std::vector<Sensor>& GetSensors();
    private:
        std::string device_name_;
        bool status_;
        std::vector<Sensor> sensors_;
};
} // namespace smart_home_app

#endif // SHA_DEVICE_H_
