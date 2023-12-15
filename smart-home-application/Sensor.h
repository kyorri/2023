#ifndef SHA_SENSOR_H_
#define SHA_SENSOR_H_

#include <string>

namespace smart_home_app {
class Sensor {
    public:
        Sensor(std::string, double);

        void SetSensorType(std::string);
        std::string GetSensorType();

        bool operator==(Sensor&);

        void SetReading(double);
        double GetReading();
    private:
        std::string sensor_type_;
        double reading_value_;
};
} // namespace smart_home_app

#endif // SHA_SENSOR_H_