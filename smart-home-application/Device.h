#ifndef SHA_DEVICE_H_
#define SHA_DEVICE_H_

#include <vector>
#include <string>
#include "Sensor.h"

class Device {
    public:
        Device(std::string, bool);

        void setDeviceName(std::string);
        std::string getDeviceName();

        void setStatus(bool);
        bool getStatus();

        std::vector<Sensor> getSensors();
    private:
        std::string device_name;
        bool status;
        std::vector<Sensor> sensors;
};

#endif // SHA_DEVICE_H_