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

    int* p = new int(5); 
    int* p1 = new int(7);
    int* p2 = new int(9);
    up::UniquePointer<int> u_ptr = std::move(p);
    std::cout << *u_ptr.Get() << std::endl;
    std::cout << p << '\t' << u_ptr.Release() << std::endl;
    u_ptr = std::move(p1);
    u_ptr.Reset();
    // std::cout << "u_ptr is storing some other pointer? " << ((u_ptr)? "true" : "false") << std::endl;
    up::UniquePointer<int> u_ptr2(p2);
    u_ptr = std::move(u_ptr2);
    std::cout << "u_ptr is storing some other pointer? " << ((u_ptr)? "true" : "false") << std::endl;

    return 0;
}
