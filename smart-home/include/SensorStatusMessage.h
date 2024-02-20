#ifndef SH_SENSORSTATUSMESSAGE_INCLUDE_H_
#define SH_SENSORSTATUSMESSAGE_INCLUDE_H_

#include "SensorStatus.h"

#include <string>

namespace smart_home {
class SensorStatusMessage {
    public:
        SensorStatusMessage(SensorStatus);
        ~SensorStatusMessage() = default;
        
        std::string GetStatus();
    private:
        SensorStatus status_;
};
} // namespace smart_home

#endif  // SH_SENSORSTATUSMESSAGE_INCLUDE_H_