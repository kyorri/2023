#include "SensorPrinter.h"

#include <iostream>
#include <algorithm>

namespace smart_home_app {
    
    void SensorPrinter::Print() {
        for(Sensor* d : sensors_) {
            std::cout << d->GetInfo() << std::endl;
        }
    }


    void SensorPrinter::AddSensor(Sensor* new_sensor) {
        sensors_.push_back(new_sensor);
    }


    void SensorPrinter::RemoveSensor(Sensor* rem_sensor) {
        auto it = std::find(sensors_.begin(), sensors_.end(), rem_sensor);
        sensors_.erase(it);
    }

} // namespace smart_home_app
