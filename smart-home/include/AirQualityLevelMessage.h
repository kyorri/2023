#ifndef SH_AIRQUALITYLEVELMESSAGE_INCLUDE_H_
#define SH_AIRQUALITYLEVELMESSAGE_INCLUDE_H_

#include "AirQualityLevel.h"

#include <string>

namespace smart_home {
class AirQualityLevelMessage {
    public:
        AirQualityLevelMessage(AirQualityLevel);
        ~AirQualityLevelMessage() = default;
        
        std::string GetStatus();
    private:
        AirQualityLevel status_;
};
} // namespace smart_home
#endif  // SH_AIRQUALITYLEVELMESSAGE_INCLUDE_H_