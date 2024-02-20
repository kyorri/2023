#ifndef SH_AIRQUALITYLEVEL_INCLUDE_H_
#define SH_AIRQUALITYLEVEL_INCLUDE_H_

namespace smart_home {
// https://www.deq.nc.gov/documents/pdf/ioa-2-1-act-aqi-051415/download
enum class AirQualityLevel {
                                   // AQI - Air Quality Index
    Good,                          // 0 - 50 AQI
    Moderate,                      // 51 - 100 AQI
    Unhealty_For_Sensitive_Groups, // 101 - 150 AQI
    Unhealthy,                     // 151 - 200 AQI
    Very_Unhealthy                 // 201 - 250 AQI
};
} // namespace smart_home

#endif  // SH_AIRQUALITYLEVEL_INCLUDE_H_