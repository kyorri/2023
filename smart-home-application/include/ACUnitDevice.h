#ifndef SHA_ACUNITDEVICE_H_
#define SHA_ACUNITDEVICE_H_

#include "Device.h"

#include <vector>
#include <string>

namespace smart_home_app {
    class ACUnitDevice : public Device {
        public:
            std::string GetType() override;
            std::string GetInfo() override;
            void TurnOff() override;
            void TurnOn() override;
            void AddSensor(Sensor*) override;
            void RemoveSensor(Sensor*) override;
            std::vector<Sensor*> GetSensors() override;
            std::string GetStatus() override;

        private:
            bool status_;
            std::vector<Sensor*> sensors_;

    };
} // namespace smart_home_app

#endif // SHA_ACUNITDEVICE_H_
