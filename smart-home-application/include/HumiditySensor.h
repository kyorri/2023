#ifndef SHA_HUMIDITYSENSOR_H_
#define SHA_HUMIDITYSENSOR_H_

#include "Sensor.h"

#include <string>

namespace smart_home_app {
class HumiditySensor : public Sensor {
    public:
        std::string GetInfo() override;
        void SetReading(double) override;
        double GetReading() override;

        uint32_t GetPercent();
    private:
        double reading_;
};
} // namespace smart_home_app

#endif // SHA_HUMIDITYSENSOR_H_