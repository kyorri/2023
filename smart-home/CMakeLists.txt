cmake_minimum_required(VERSION 3.12)
project(SmartHome LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/pugixml
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

                        src/DeviceStatusMessage.cpp
                        src/SensorStatusMessage.cpp
                        src/AirQualityLevelMessage.cpp

                        # Printers for status of devices
                        src/ACUnitDevicePrinter.cpp

                        # Readers
                        src/ACUnitDeviceReader.cpp
                        src/SpeakerDeviceReader.cpp
                        src/ThermostatDeviceReader.cpp

                        # Writers

                        )

target_link_libraries(exec.out PRIVATE pugixml)