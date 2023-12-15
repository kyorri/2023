cmake_minimum_required(VERSION 3.10)


project(smart-home-application)


add_executable(exec.out
    main.cpp
    App.cpp
    Device.cpp
    Room.cpp
    Sensor.cpp
    pugixml.cpp
    )