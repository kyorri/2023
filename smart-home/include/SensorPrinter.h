#ifndef SHA_SENSORPRINTER_H_
#define SHA_SENSORPRINTER_H_

#include "Printer.h"
#include "Sensor.h"

#include <vector>

namespace smart_home_app {
class SensorPrinter : public Printer {
    public:
        void Print() override;

        void AddSensor(Sensor*);
        void RemoveSensor(Sensor*);
    private:
        std::vector<Sensor*> sensors_;
};
} // namespace smart_home_app
#endif // SHA_SENSORPRINTER_H_