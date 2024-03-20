#ifndef SH_TEMPERATURESENSOR_INCLUDE_H_
#define SH_TEMPERATURESENSOR_INCLUDE_H_

#include "Sensor.h"

namespace smart_home {
class TemperatureSensor : public Sensor {
    public:
        TemperatureSensor();
        TemperatureSensor(double);

        std::stringstream Interact() override;

        void Wait() override;
        void Continue() override;
        void TurnOn() override;
        void TurnOff() override;

        SensorStatus GetStatus() override;
        void SetStatus(SensorStatus) override;

        double GetReading() override;
        void SetReading(double) override;

        SensorType GetSensorType();
    private:
        SensorStatus status_;
        SensorType sensor_type_;
        double reading_;

};
} // namespace smart_home

#endif  // SH_TEMPERATURESENSOR_INCLUDE_H_