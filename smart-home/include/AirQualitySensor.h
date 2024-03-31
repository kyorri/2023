#ifndef SH_AIRQUALITYSENSOR_INCLUDE_H_
#define SH_AIRQUALITYSENSOR_INCLUDE_H_

#include "Sensor.h"
#include "AirQualityLevel.h"
#include "AirQualityLevelMessage.h"

namespace smart_home {
class AirQualitySensor : public Sensor {
    public:
        AirQualitySensor();
        AirQualitySensor(double);

        std::stringstream Interact() override;
        
        void Wait() override;
        void Continue() override;
        void TurnOn() override;
        void TurnOff() override;

        SensorStatus GetStatus() override;
        void SetStatus(SensorStatus) override;

        double GetReading() override;
        void SetReading(double) override;

        AirQualityLevel GetAirQualityLevel();
        
        SensorType GetSensorType();
    private:
        SensorStatus status_;
        double reading_;
        SensorType sensor_type_;
        AirQualityLevel air_quality_lvl_;

};
} // namespace smart_home

#endif  // SH_AIRQUALITYSENSOR_INCLUDE_H_