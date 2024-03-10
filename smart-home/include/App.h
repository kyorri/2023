#ifndef SH_APP_INCLUDE_H_
#define SH_APP_INCLUDE_H_

#include "unique_ptr.h"

#include "Room.h"
#include "Device.h"
#include "Sensor.h"

#include "DeviceFactory.h"
#include "SensorFactory.h"

#include "ACUnitDevice.h"
#include "SpeakerDevice.h"
#include "ThermostatDevice.h"

#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "AirQualitySensor.h"

#include "DevicePrinter.h"
#include "ACUnitDevicePrinter.h"
#include "SpeakerDevicePrinter.h"
#include "ThermostatDevicePrinter.h"

#include "XMLReader.h"
#include "XMLWriter.h"
#include "RoomPrinter.h"
#include "ThreadedPrintingService.h"

#include "pugixml.hpp"


namespace smart_home {
class App {
    public:
        App();
};
} // namespace smart_home
#endif  // SH_APP_INCLUDE_H_