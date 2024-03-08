#ifndef SH_MESSAGESENSORTATUS_INCLUDE_H_
#define SH_MESSAGESENSORTATUS_INCLUDE_H_

#include "SensorStatus.h"

#include <string>

namespace smart_home {
class MessageSensorStatus {
    public:
        MessageSensorStatus(std::string);
        ~MessageSensorStatus() = default;
        
        SensorStatus GetStatus();
    private:
        std::string status_;
};
} // namespace smart_home

#endif  // SH_MESSAGESENSORTATUS_INCLUDE_H_