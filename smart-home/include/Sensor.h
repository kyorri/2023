#ifndef SHA_SENSOR_H_
#define SHA_SENSOR_H_

#include <string>

namespace smart_home_app {
class Sensor {
    public:
        virtual std::string GetType() = 0;
        virtual std::string GetInfo() = 0;
        virtual void SetReading(double) = 0;
        virtual double GetReading() = 0;
};
} // namespace smart_home_app

#endif // SHA_SENSOR_H_