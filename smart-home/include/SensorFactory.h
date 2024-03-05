#ifndef SH_SENSORFACTORY_INCLUDE_H_
#define SH_SENSORFACTORY_INCLUDE_H_

#include "Sensor.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "AirQualitySensor.h"
#include "unique_ptr.h"

namespace smart_home {
class SensorFactory {
    public:
        antoniaptr::unique_ptr<Sensor> Build(SensorType);
};
} // namespace smart_home
#endif  // SH_SENSORFACTORY_INCLUDE_H_