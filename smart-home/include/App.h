#ifndef SH_APP_INCLUDE_H_
#define SH_APP_INCLUDE_H_

#include "unique_ptr.h"

#include "ServerApp.h"
#include "ClientApp.h"

#include "Room.h"
#include "Device.h"
#include "Sensor.h"

#include "DeviceFactory.h"
#include "SensorFactory.h"

#include "DevicePrinter.h"

#include "XMLReader.h"
#include "XMLWriter.h"
#include "RoomPrinter.h"
#include "ThreadedPrintingService.h"

namespace smart_home {
class App {
    public:
        App(const int&, const char* const*);
};
} // namespace smart_home
#endif  // SH_APP_INCLUDE_H_