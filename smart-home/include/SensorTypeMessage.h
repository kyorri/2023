#ifndef SH_SENSORTYPEMESSAGE_INCLUDE_H_
#define SH_SENSORTYPEMESSAGE_INCLUDE_H_

#include "SensorType.h"

#include <string>

namespace smart_home {
class SensorTypeMessage {
    public:
        SensorTypeMessage(SensorType);
        ~SensorTypeMessage() = default;
        
        std::string GetType();
    private:
        SensorType type_;
};
} // namespace smart_home

#endif  // SH_SENSORTYPEMESSAGE_INCLUDE_H_