#ifndef SHA_DISTANCESENSOR_H
#define SHA_DISTANCESENSOR_H

#include "Sensor.h"

namespace smart_home_app
{
class DistanceSensor : public Sensor {
    public:
        std::string GetType() override;
        std::string GetInfo() override;
        void SetReading(double) override;
        double GetReading() override;

        std::string GetUnits();
        void SetUnits(std::string);
    private:
        std::string units_;
        double reading_;
};
} // namespace smart_home_app


#endif // SHA_DISTANCESENSOR_H
