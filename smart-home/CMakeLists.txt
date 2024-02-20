cmake_minimum_required(VERSION 3.10)


project(smart-home-application)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/pugixml
)

add_library(pugixml STATIC
    pugixml/pugixml.cpp
    )

add_executable(exec.out
    src/main.cpp

    src/App.cpp
    src/Room.cpp

    src/ACUnitDevice.cpp
    src/DoorbellDevice.cpp
    src/LightDevice.cpp

    src/TemperatureSensor.cpp
    src/HumiditySensor.cpp
    src/DistanceSensor.cpp
    
    src/SensorPrinter.cpp
    src/DevicePrinter.cpp

    src/XMLReader.cpp

    src/XMLWriter.cpp
    )

target_link_libraries(exec.out PRIVATE pugixml)
