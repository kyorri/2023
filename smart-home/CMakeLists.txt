cmake_minimum_required(VERSION 3.12)
project(SmartHome LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS YES) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.74.0 COMPONENTS serialization) 

file(GLOB APPLICATION_SOURCES "src/*.cpp")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src

        ${PROJECT_SOURCE_DIR}/unique-ptr
        
        ${PROJECT_SOURCE_DIR}/pugixml
)

add_executable(exec.out ${APPLICATION_SOURCES})

add_library(pugixml STATIC pugixml/pugixml.cpp)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(exec.out ${Boost_LIBRARIES} pugixml)
endif()