#ifndef SH_MESSAGESENSORTYPE_INCLUDE_H_
#define SH_MESSAGESENSORTYPE_INCLUDE_H_

#include "SensorType.h"

#include <string>

namespace smart_home {
class MessageSensorType {
    public:
        MessageSensorType(std::string);
        ~MessageSensorType() = default;
        
        SensorType GetType();
    private:
        std::string type_;
};
} // namespace smart_home

#endif  // SH_MESSAGESENSORTYPE_INCLUDE_H_