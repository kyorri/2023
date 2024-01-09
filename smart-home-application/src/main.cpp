
#include "Room.h"
#include "Device.h"
#include "Sensor.h"

#include "DevicePrinter.h"
#include "SensorPrinter.h"

#include "ACUnitDevice.h"
#include "DoorbellDevice.h"

#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "DistanceSensor.h"

#include "XMLReader.h"
#include "XMLWriter.h"

#include <iostream>
#include <vector>

#include "UniquePointer.h"

int main() {
    int* p;
    up::UniquePointer<int> u_ptr;
    u_ptr.Acquire(p);
    u_ptr.Release();

    return 0;
}
