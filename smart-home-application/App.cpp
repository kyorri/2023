#include "App.h"

#include <iostream>

App::App(std::string filename) : filename(filename){};

void App::load()
{
    std::cout << "File has been read!" << std::endl;
    std::cout << "\t-" << this->filename << std::endl;
    //
    //
};

void App::save()
{
    std::cout << "File " << this->filename << " saved!" << std::endl;
    //
    //
};

std::vector<Room> App::getRooms()
{
    return this->rooms;
};

void App::addSensor(Device &dev, std::string sensor_name, double reading_value)
{
    dev.getSensors().emplace_back(sensor_name, reading_value);
};

void App::addDevice(Room &room, std::string device_name, bool status){
    room.getDevices().emplace_back(device_name, status);
};

void App::newRoom(std::string room_name){
    this->getRooms().emplace_back(room_name);
};
