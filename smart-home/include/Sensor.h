#ifndef SH_SENSOR_INCLUDE_H_
#define SH_SENSOR_INCLUDE_H_

#include "SensorStatus.h"
#include "SensorType.h"

#include <iostream>
#include <vector>
#include <memory>

namespace smart_home {
class Sensor {
    public:
        virtual void Interact() = 0;

        virtual void Wait() = 0;
        virtual void Continue() = 0;
        virtual void TurnOn() = 0;
        virtual void TurnOff() = 0;

        virtual SensorStatus GetStatus() = 0;
        virtual void SetStatus(SensorStatus) = 0;

        virtual double GetReading() = 0;
        virtual void SetReading(double) = 0;

        virtual SensorType GetSensorType() = 0;
    // protected:
    //     SensorStatus status_;
    //     double reading_;
};
} // namespace smart_home

#endif  // SH_SENSOR_INCLUDE_H_