#ifndef SH_ACHEATINGSTATUS_INCLUDE_H_
#define SH_ACHEATINGSTATUS_INCLUDE_H_

namespace smart_home {
enum class ACHeatingStatus {
    Undefined,
    Heating,
    Cooling,
    Standby,
    Error
};
} // namespace smart_home
#endif  // SH_ACHEATINGSTATUS_INCLUDE_H_