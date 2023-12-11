#ifndef SHA_SENSOR_H_
#define SHA_SENSOR_H_

#include <string>

class Sensor {
    public:
        Sensor(std::string, double);

        void setSensorName(std::string);
        std::string getSensorName();

        void setReading(double);
        double getReading();
    private:
        std::string sensor_name;
        double reading_value;
};
#endif // SHA_SENSOR_H_