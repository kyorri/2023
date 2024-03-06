cmake_minimum_required(VERSION 3.12)
project(SmartHome LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/pugixml
        ${PROJECT_SOURCE_DIR}/unique-ptr
)

add_library(pugixml STATIC pugixml/pugixml.cpp)

add_executable(exec.out src/_main.cpp
                        src/App.cpp
                        src/Room.cpp

                        # Devices
                        src/ACUnitDevice.cpp
                        src/SpeakerDevice.cpp
                        src/ThermostatDevice.cpp

                        # Sensors
                        src/TemperatureSensor.cpp
                        src/HumiditySensor.cpp
                        src/AirQualitySensor.cpp

                        # Utility classes
                        src/DeviceFactory.cpp
                        src/SensorFactory.cpp

                        src/MessageDeviceStatus.cpp
                        src/DeviceStatusMessage.cpp
                        src/MessageSensorStatus.cpp
                        src/SensorStatusMessage.cpp
                        src/MessageDeviceType.cpp
                        src/DeviceTypeMessage.cpp
                        src/MessageSensorType.cpp
                        src/SensorTypeMessage.cpp
                        src/AirQualityLevelMessage.cpp

                        # Printers for status of devices
                        src/ACUnitDevicePrinter.cpp
                        src/SpeakerDevicePrinter.cpp
                        src/ThermostatDevicePrinter.cpp
                        
                        # Printing service
                        src/ThreadedPrintingService.cpp
                        src/RoomPrinter.cpp

                        # Readers
                        src/XMLReader.cpp
                        src/XMLRoomReader.cpp
                        src/XMLACUnitDeviceReader.cpp
                        src/XMLSpeakerDeviceReader.cpp
                        src/XMLThermostatDeviceReader.cpp

                        # Writers
                        src/XMLWriter.cpp
                        src/XMLRoomWriter.cpp
                        src/XMLACUnitDeviceWriter.cpp
                        src/XMLSpeakerDeviceWriter.cpp
                        src/XMLThermostatDeviceWriter.cpp
                        )

target_link_libraries(exec.out PRIVATE pugixml)