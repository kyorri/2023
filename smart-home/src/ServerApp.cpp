#include "ServerApp.h"
#include "DeviceFactory.h"
#include "SensorFactory.h"
#include "RoomPrinter.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stdexcept>

namespace smart_home {
ServerApp::ServerApp() : max_buffer_size_(0) {
    throw std::invalid_argument("Please enter a port number for the server!");
};

ServerApp::ServerApp(int server_port) : server_socket_(), server_port_(server_port), max_buffer_size_(8192) {

    // RoomPrinter rp;
    // // rp.Print(room1.get());
    // rp.Print(house_rooms_[0].get());
    antoniaptr::unique_ptr<Room> room1(new Room("Kitchen"));

    DeviceFactory df;
    antoniaptr::unique_ptr<Device> dev1 = df.Build(DeviceType::Thermostat);
    antoniaptr::unique_ptr<Device> dev2 = df.Build(DeviceType::ACUnit);
    dev2->TurnOff();

    room1->AddDevice(std::move(dev1));

    SensorFactory sf;
    antoniaptr::unique_ptr<Sensor> sen1 = sf.Build(SensorType::Temperature);

    house_rooms_.push_back(std::move(room1));
    device_pool_.push_back(std::move(dev2));
    sensor_pool_.push_back(std::move(sen1));

    InitializeAndListen();
    AcceptConnection();
    TransferLoop();
};

void ServerApp::InitializeAndListen() {
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port_);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket_(), (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        throw std::runtime_error("Error at bind for the server!");
    }

    if (listen(server_socket_(), 1) == -1) {
        throw std::runtime_error("Listening failed for the server!");
    }
    std::cout << "Server is listening at port number " << server_port_ << "!" << std::endl;
};

void ServerApp::AcceptConnection() {
    sockaddr_in client_address;
    socklen_t client_addr_len = sizeof(client_address);
    client_socket_ = std::move(accept(server_socket_(), (struct sockaddr *)&client_address, &client_addr_len));

    if (client_socket_() == -1) {
        throw std::runtime_error("Accepting the client connection failed! Possible invalid socket file descriptor!");
    }
    std::cout << "Client connected!" << std::endl;
};

void ServerApp::TransferLoop() {
    int bytes_received;
    int bytes_sent;

    char buffer_recv[max_buffer_size_] = {0};
    char buffer_send[max_buffer_size_] = {0};

    // action type src
    char menu[] = "-- Smart Home application --\n"
        "- Please select one of the following operations to do..\n"
        "- add [room#/device#/sensor#] [-/room#/(room#//device#)]\n"
        "- remove [room#/device#/sensor#] [-/room#/(room#//device#)]\n"
        "- print [room#/device#/sensor#] [-/room#/(room#//device#)]\n"
        "- list [rooms/devices/sensors/room_pool/device_pool/sensor_pool] [-/room#/(room#//device#)]\n"
        "- create [room/device_*/sensor_*]\n";
    
    bytes_sent = send(client_socket_(), menu, strlen(menu), 0);
    do {
        bytes_received = recv(client_socket_(), buffer_recv, sizeof(buffer_recv), 0);
        if (bytes_received == -1) {
            throw std::runtime_error("Failed receiving data from client!");
        }
        if (bytes_received == 0) { // '\0'
            throw std::runtime_error("Connection closed by the client!");
        }
        buffer_recv[bytes_received] = '\0';

        std::string action;
        std::string client_request = buffer_recv;
        std::stringstream client_stream(client_request);
        client_stream >> action;
        std::vector<std::string> actions {"add", "remove", "print", "list", "create"};
        std::stringstream response_stream;
        auto it = std::find(actions.begin(), actions.end(), action);
        if (it == actions.end()) {
            throw std::invalid_argument("Wrong input from client instance!");
        }
        if (action == "add") {
            response_stream = Add(client_stream);
        } else if (action == "remove") {
            response_stream = Remove(client_stream);
        } else if (action == "print") {
            response_stream = Print(client_stream);
        } else if (action == "list") {
            response_stream = List(client_stream);
        } else if (action == "create") {
            response_stream = Create(client_stream);
        }
        client_request.clear();
        action.clear();

        std::string response = response_stream.str() + std::string(menu);
        strcpy(buffer_send, response.c_str());

        bytes_sent = send(client_socket_(), buffer_send, strlen(buffer_send), 0);
        int send_tries = 2;
        while (bytes_sent == -1 && send_tries > 0) {
            throw std::runtime_error("Error sending back data to client! Trying again...");
            bytes_sent = send(client_socket_(), buffer_send, strlen(buffer_send), 0);
            send_tries--;
        }

        // 
        std::cerr << " >--< -- Client sent the message -- " << std::endl << buffer_recv << std::endl;
        // i ll use cerr for debug purposes, hopefully i won t forget about this

    } while (bytes_received > 0);
};

std::stringstream ServerApp::Add(std::stringstream& client_stream) {
    std::stringstream server_response("-- Add operation --");
    std::string type_specifier;
    client_stream >> type_specifier;
    if (type_specifier.find("device") != std::string::npos) {
        
    } else if (type_specifier.find("device") != std::string::npos) {

    } else if (type_specifier.find("device") != std::string::npos) {
        
    } else if (type_specifier.find("device") != std::string::npos) {
        
    }
    server_response << std::endl;
    return server_response;
};

std::stringstream ServerApp::Remove(std::stringstream& client_stream) {
    std::stringstream server_response("-- Remove operation --");
    std::string type_specifier;
    client_stream >> type_specifier;
    if (type_specifier.find("room_pool#") != std::string::npos) {

    } else if (type_specifier.find("device_pool#") != std::string::npos) {

    } else if (type_specifier.find("sensor_pool#") != std::string::npos) {
        
    } else if (type_specifier.find("room#") != std::string::npos) {
        
    } else if (type_specifier.find("device#") != std::string::npos) {
        
    } else if (type_specifier.find("sensor#") != std::string::npos) {
        
    }

    server_response << std::endl;
    return server_response;
};

std::stringstream ServerApp::Print(std::stringstream& client_stream) {
    std::stringstream server_response("-- Printing operation --");
    
    server_response << std::endl;
    return server_response;
};

std::stringstream ServerApp::List(std::stringstream& client_stream) {
    std::stringstream server_response;
    std::string type_specifier;
    client_stream >> type_specifier;
    
    server_response << "-- Listing operation --" << std::endl;
    if (type_specifier == "rooms") {
        server_response << "Rooms listing" << std::endl;
        if (house_rooms_.size() > 0) {
            int i = 0;
            std::for_each(house_rooms_.begin(), house_rooms_.end(), 
                [&i, &server_response] (const antoniaptr::unique_ptr<Room>& room) {
                    server_response << "(" << i << ") " << room->GetName() << std::endl;
                    i++;
                });
        }
        else {
            server_response << ">There are no rooms available!" << std::endl;
        }
    } else if (type_specifier == "devices") {
        std::string room_index_token;
        client_stream >> room_index_token;
        std::string index = room_index_token.substr(room_index_token.find("room#") + std::string("room#").size());
        int room_index = stoi(index);

        // std::cout << index << std::endl;
        // std::cout << house_rooms_.size() << std::endl;
        // std::cout << house_rooms_[room_index]->GetDevices().size() << std::endl;

        if (room_index < house_rooms_.size()) {
            if (house_rooms_[room_index]->GetDevices().size() > 0) {
                int i = 0;
                std::vector<Device*> devices = house_rooms_[room_index]->GetDevices();
                std::for_each(devices.begin(), devices.end(), 
                    [&i, &server_response] (Device* device) {
                        server_response << "(" << i << ") " << (device->Interact()).rdbuf() << std::endl;
                        i++;
                    });
            } else {
                server_response << "There are no devices installed in the room \"" << house_rooms_[room_index]->GetName() << "\"!" << std::endl;
            }
        }
        else {
            throw std::runtime_error("Client instance supplied a wrong index for an existing room (or there are no existing rooms)!\nEnding the connection!");
        }
    } else if (type_specifier == "sensors") {
        std::string room_index_token;
        client_stream >> room_index_token;
        std::string index = room_index_token.substr(room_index_token.find("room#") + std::string("room#").size());
        int room_index = stoi(index);
        std::string device_index_token;


    } else if (type_specifier == "room_pool") {
        server_response << "-- Room pool objects waiting --" << std::endl;
        if (room_pool_.size() > 0) {
            int i = 0;
            std::for_each(room_pool_.begin(), room_pool_.end(), 
                    [&i, &server_response] (antoniaptr::unique_ptr<Room>& room) {
                        server_response << "(" << i << ") " << room.get()->GetName() << std::endl;
                        i++;
                    });
        }
        else {
            server_response << "There are no rooms waiting in the room pool!" << std::endl;
        }
    } else if (type_specifier == "device_pool") {
        server_response << "-- Device pool objects waiting --" << std::endl;
        if (device_pool_.size() > 0) {
            int i = 0;
            std::for_each(device_pool_.begin(), device_pool_.end(), 
                    [&i, &server_response] (antoniaptr::unique_ptr<Device>& device) {
                        server_response << "(" << i << ") " << (device.get()->Interact()).rdbuf() << std::endl;
                        i++;
                    });
        }
        else {
            server_response << "There are no devices waiting in the device pool!" << std::endl;
        }
    } else if (type_specifier == "sensor_pool") {
        server_response << "-- Sensor pool objects waiting --" << std::endl;
        if (sensor_pool_.size() > 0) {
            int i = 0;
            std::for_each(sensor_pool_.begin(), sensor_pool_.end(), 
                    [&i, &server_response] (antoniaptr::unique_ptr<Sensor>& sensor) {
                        server_response << "(" << i << ") " << (sensor.get()->Interact()).rdbuf() << std::endl;
                        i++;
                    });
        }
        else {
            server_response << "There are no sensors waiting in the sensor pool!" << std::endl;
        }
    } else {
        server_response << "Wrong type specifier for the list operation!" << std::endl;
    }

    server_response << std::endl;
    return server_response;
};

std::stringstream ServerApp::Create(std::stringstream& client_stream) {
    std::stringstream server_response;
    std::string type_specifier;
    client_stream >> type_specifier;
    server_response << "-- Create operation --" << std::endl;
    if (type_specifier.find("room") != std::string::npos) {
        std::string room_name;
        std::string temp_name;
        while(client_stream >> temp_name) {
            room_name += " " + temp_name;
        }
        std::cout << room_name << std::endl;
        antoniaptr::unique_ptr<Room> new_room(new Room(room_name));
        room_pool_.push_back(std::move(new_room));
        server_response << "Created a new Room named\"" << room_name << "\" to the pool!" << std::endl;
    } else if (type_specifier.find("device") != std::string::npos) {
        DeviceFactory df;
        if (type_specifier == "device_acunit") {
            antoniaptr::unique_ptr<Device> dev = df.Build(DeviceType::ACUnit);
            device_pool_.push_back(std::move(dev));
            server_response << "Created a new Air Conditioning Unit to the pool!" << std::endl;
        } 
        else if (type_specifier == "device_thermostat") {
            antoniaptr::unique_ptr<Device> dev = df.Build(DeviceType::Thermostat);
            device_pool_.push_back(std::move(dev));
            server_response << "Created a new Thermostat Unit to the pool!" << std::endl;
        } 
        else if (type_specifier == "device_speaker") {
            antoniaptr::unique_ptr<Device> dev = df.Build(DeviceType::Speaker);
            device_pool_.push_back(std::move(dev));
            server_response << "Created a new Speaker device to the pool!" << std::endl;
        } 
        else {
            server_response << "Wrong device type!" << std::endl;
        }
    } else if (type_specifier.find("sensor") != std::string::npos) {
        SensorFactory sf;
        if (type_specifier == "sensor_temperature") {
            antoniaptr::unique_ptr<Sensor> sen = sf.Build(SensorType::Temperature);
            sensor_pool_.push_back(std::move(sen));
            server_response << "Created a new Temperature sensor to the pool!" << std::endl;
        } 
        else if (type_specifier == "sensor_humidity") {
            antoniaptr::unique_ptr<Sensor> sen = sf.Build(SensorType::Humidity);
            sensor_pool_.push_back(std::move(sen));
            server_response << "Created a new Humidity sensor to the pool!" << std::endl;
        } 
        else if (type_specifier == "sensor_airquality") {
            antoniaptr::unique_ptr<Sensor> sen = sf.Build(SensorType::AirQualityLevel);
            sensor_pool_.push_back(std::move(sen));
            server_response << "Created a new Air Quality Level sensor to the pool!" << std::endl;
        } 
        else {
            server_response << "Wrong device type!" << std::endl;
        }
    } else {
        server_response << "Wrong create type specifier!" << std::endl;
    }
    server_response << std::endl;
    return server_response;
};

} // namespace smart_home
