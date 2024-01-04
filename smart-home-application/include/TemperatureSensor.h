#ifndef SHA_TEMPERATURESENSOR_H_
#define SHA_TEMPERATURESENSOR_H_

#include "Sensor.h"

#include <string>

namespace smart_home_app {
class TemperatureSensor : public Sensor {
    public:
        std::string GetInfo() override;
        void SetReading(double) override;
        double GetReading() override;

        void SetScale(char);
        std::string GetScale();

        void SetScaleTo(char, char);
        void SetScaleTo(char);
    private:
        char scale_ = '\0';
        double reading_;
};
} // namespace smart_home_app

#endif // SHA_TEMPERATURESENSOR_H_