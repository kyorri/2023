#include "ServerApp.h"
#include "DeviceFactory.h"
#include "SensorFactory.h"
#include "RoomPrinter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#include <stdexcept>

namespace smart_home {
ServerApp::ServerApp() : max_buffer_size_(0), max_connections_(0) {
    throw std::invalid_argument("Please enter a port number for the server!");
};

ServerApp::ServerApp(int server_port) : server_socket_(), server_port_(server_port), max_buffer_size_(8192), max_connections_(10) {
    Initialize();
    MainLoop();
};

ServerApp::ServerApp(int server_port, int backlog) : server_socket_(), max_connections_(backlog), server_port_(server_port), max_buffer_size_(8192) {
    Initialize();
    MainLoop();
};

void ServerApp::Initialize() {
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port_);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket_(), (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        throw std::runtime_error("Error at bind for the server!");
    }

    if (listen(server_socket_(), max_connections_) == -1) {
        throw std::runtime_error("Listening failed for the server!");
    }

    std::cout << "Server is listening at port number " << server_port_ << "!" << std::endl;
};

void ServerApp::MainLoop() {
    ThreadPool tp(std::thread::hardware_concurrency());

    while (true) {
        sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);
        Socket new_client_socket = std::move(accept(server_socket_(), (struct sockaddr *)&client_address, &client_addr_len));
        if (new_client_socket() == -1) {
            throw std::runtime_error("Accepting the client connection failed! Possible invalid socket file descriptor!");
        }
        
        std::cout << "Client connected!" << std::endl;

        ServerConnection new_conn(new_client_socket, client_address, client_addr_len);

        tp.enqueue([this, &new_conn](){
            AuthenticateClient(std::move(new_conn));
        });

        tp.enqueue([this, &new_conn](){
            HandleClient(std::move(new_conn));
        });
        
        clients_connected_.push_back(std::move(new_conn));
    }
    
};

void ServerApp::AuthenticateClient(ServerConnection conn) {
    const int client_name_max_length = 64;

    std::string authentication_message = "Please enter your username (Type *nothing* to exit): ";
    char buffer_recv[client_name_max_length] = {};

    Socket& client_socket = conn.GetSocket();

    int bytes_sent = send(client_socket(), authentication_message.c_str(), authentication_message.size(), 0);
    if (bytes_sent == -1) {
        throw std::runtime_error("There was a problem prompting a user for their username!");
    }
    
    int bytes_received = recv(client_socket(), buffer_recv, client_name_max_length, 0);
    if (bytes_received == 0) {
        throw std::runtime_error("The client chose to exit the authentication process!");
    }
    if (bytes_received == -1) {
        throw std::runtime_error("There was an error fetching the client's name!");
    }

    std::string client_name = buffer_recv;
    conn.SetClientName(client_name);
};

void ServerApp::HandleClient(ServerConnection conn) {
    int bytes_received;
    int bytes_sent;

    char buffer_recv[max_buffer_size_] = {0};
    char buffer_send[max_buffer_size_] = {0};

    Socket& client_socket = conn.GetSocket();

    // action type src
    char menu[] = "-- Smart Home application --\n"
        "- Please select one of the following operations to do..\n"
        "- add [room_pool#/device_pool#/sensor_pool#] [-/room_pool#/device_pool#]\n"
        "- remove [room#/device#/sensor#] [-/room#/(room#//device#)]\n"
        "- print [room#/device#/sensor#]\n"
        "- list [rooms/devices/sensors/room_pool/device_pool/sensor_pool] [-/room#/device#/sensor#]\n"
        "- create [room/device_*/sensor_*]\n";
    
    bytes_sent = send(client_socket(), menu, strlen(menu), 0);
    do {
        bytes_received = recv(client_socket(), buffer_recv, sizeof(buffer_recv), 0);
        if (bytes_received == -1) {
            throw std::runtime_error("Failed receiving data from client!");
        }
        if (bytes_received == 0) { // '\0'
            throw std::runtime_error("Connection closed by the client!");
        }
        buffer_recv[bytes_received] = '\0';

        std::string client_response = buffer_recv;
        Message client_message;
        std::stringstream iss(client_response);
        {
            boost::archive::text_iarchive in_archive(iss);
            in_archive >> client_message;
        }
        LogMessage(client_message);

        std::string client_request = buffer_recv;
        std::stringstream client_stream(client_request);
        std::string action;
        client_stream >> action;

        std::stringstream response_stream;
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
        } else {
            throw std::invalid_argument("Wrong input from client instance!");
        }
        client_request.clear();
        action.clear();

        std::string response = response_stream.str() + std::string(menu);
        strcpy(buffer_send, response.c_str());

        bytes_sent = send(client_socket(), buffer_send, strlen(buffer_send), 0);
        int send_tries = 2;
        while (bytes_sent == -1 && send_tries > 0) {
            throw std::runtime_error("Error sending back data to client! Trying again...");
            bytes_sent = send(client_socket(), buffer_send, strlen(buffer_send), 0);
            send_tries--;
        }

    } while (bytes_received > 0);
};

void ServerApp::LogMessage(Message& message) {
    std::ofstream file_log(log_file_name_, std::ios::app);
    if (!file_log.is_open()) {
        throw std::runtime_error("Error while appending to the log file!");
    }
    file_log << message.GetServerLogFormat();
};


std::map<std::string, int> ParseToken(std::string token) {
    std::map<std::string, int> parse_result;
    if (token.empty()) {
        return parse_result;
    }
    auto room_it = token.find("room#");
    auto device_it = token.find("device#");
    auto sensor_it = token.find("sensor#");

    auto room_pool_it = token.find("room_pool#");
    auto device_pool_it = token.find("device_pool#");
    auto sensor_pool_it = token.find("sensor_pool#");

    std::size_t room_num_it_start, room_num_it_end;
    if (device_it != std::string::npos) {
        room_num_it_start = token.find("room#") + std::string("room#").size();
        room_num_it_end = token.find("/", room_num_it_start + 1);
    } else {
        room_num_it_start = token.find("room#") + std::string("room#").size();
        room_num_it_end = std::string::npos;
    }

    std::size_t device_num_it_start, device_num_it_end;
    if (sensor_it != std::string::npos) {
        device_num_it_start = token.find("device#") + std::string("device#").size();
        device_num_it_end = token.find("/", device_num_it_start + 1);
    } else {
        device_num_it_start = token.find("device#") + std::string("device#").size();
        device_num_it_end = std::string::npos;
    }

    std::size_t sensor_num_it_start, sensor_num_it_end;
    sensor_num_it_start = token.find("sensor#") + std::string("sensor#").size();
    sensor_num_it_end = std::string::npos;

    std::string room_num_string = token.substr(room_num_it_start, room_num_it_end - room_num_it_start);
    std::string device_num_string = token.substr(device_num_it_start, device_num_it_end - device_num_it_start);
    std::string sensor_num_string = token.substr(sensor_num_it_start, sensor_num_it_end - sensor_num_it_start);

    std::size_t room_pool_num_it_start, room_pool_num_it_end;
    if (device_pool_it != std::string::npos) {
        room_pool_num_it_start = token.find("room_pool#") + std::string("room_pool#").size();
        room_pool_num_it_end = token.find("/", room_pool_num_it_start + 1);
    } else {
        room_pool_num_it_start = token.find("room_pool#") + std::string("room_pool#").size();
        room_pool_num_it_end = std::string::npos;
    }

    std::size_t device_pool_num_it_start, device_pool_num_it_end;
    if (sensor_pool_it != std::string::npos) {
        device_pool_num_it_start = token.find("device_pool#") + std::string("device_pool#").size();
        device_pool_num_it_end = token.find("/", device_pool_num_it_start + 1);
    } else {
        device_pool_num_it_start = token.find("device_pool#") + std::string("device_pool#").size();
        device_pool_num_it_end = std::string::npos;
    }

    std::size_t sensor_pool_num_it_start, sensor_pool_num_it_end;
    sensor_pool_num_it_start = token.find("sensor_pool#") + std::string("sensor_pool#").size();
    sensor_pool_num_it_end = std::string::npos;

    std::string room_pool_num_string = token.substr(room_pool_num_it_start, room_pool_num_it_end - room_pool_num_it_start);
    std::string device_pool_num_string = token.substr(device_pool_num_it_start, device_pool_num_it_end - device_pool_num_it_start);
    std::string sensor_pool_num_string = token.substr(sensor_pool_num_it_start, sensor_pool_num_it_end - sensor_pool_num_it_start);


    int room_value, device_value, sensor_value, room_pool_value, device_pool_value, sensor_pool_value;

    room_value = atoi(room_num_string.c_str());
    device_value = atoi(device_num_string.c_str());
    sensor_value = atoi(sensor_num_string.c_str());

    room_pool_value = atoi(room_pool_num_string.c_str());
    device_pool_value = atoi(device_pool_num_string.c_str());
    sensor_pool_value = atoi(sensor_pool_num_string.c_str());
    // std::cout << "room#" << room_value << " / device#" << device_value << " / sensor#" << sensor_value << std::endl;
    // std::cout << "room_pool#" << room_pool_value << " / device_pool#" << device_pool_value << " / sensor_pool#" << sensor_pool_value << std::endl;


    if (room_it != std::string::npos) {
        parse_result["room"] = room_value;
    }
    else {
        parse_result["room"] = -1;
    }

    if (device_it != std::string::npos) {
        parse_result["device"] = device_value;
    }
    else {
        parse_result["device"] = -1;
    }

    if (sensor_it != std::string::npos) {
        parse_result["sensor"] = sensor_value;
    }
    else {
        parse_result["sensor"] = -1;
    }

    if (room_pool_it != std::string::npos) {
        parse_result["room_pool"] = room_pool_value;
    }
    else {
        parse_result["room_pool"] = -1;
    }

    if (device_pool_it != std::string::npos) {
        parse_result["device_pool"] = device_pool_value;
    }
    else {
        parse_result["device_pool"] = -1;
    }

    if (sensor_pool_it != std::string::npos) {
        parse_result["sensor_pool"] = sensor_pool_value;
    }
    else {
        parse_result["sensor_pool"] = -1;
    }
    // std::cout << "Room: " << parse_result["room"] << "| Device: " << parse_result["device"] << "| Sensor: " << parse_result["sensor"] << " /" << std::endl;
    // std::cout << "Room_pool: " << parse_result["room_pool"] << "| Device_pool: " << parse_result["device_pool"] << "| Sensor_pool: " << parse_result["sensor_pool"] << " /" << std::endl;

    return parse_result;
};

std::stringstream ServerApp::Add(std::stringstream& client_stream) {
    std::stringstream server_response("-- Add operation --");
    std::string add_object;
    client_stream >> add_object;

    auto obj_locator = ParseToken(add_object);
    int room_pool_index = obj_locator["room_pool"];
    int device_pool_index = obj_locator["device_pool"];
    int sensor_pool_index = obj_locator["sensor_pool"];

    std::string destination;
    client_stream >> destination;
    auto obj_destination = ParseToken(destination);

    if (room_pool_index != -1) {

        if (room_pool_.size() > 0 && room_pool_index < room_pool_.size()) {
            std::string room_name = room_pool_[room_pool_index]->GetName();
            house_rooms_.push_back(std::move(room_pool_[room_pool_index]));
            // house_rooms_.erase(house_rooms_.begin() + room_pool_index);
            server_response << "Added the room \"" << room_name << "\"from the pool to the smart home!";
        } else {
            server_response << "Wrong index for the room pool object to be added to the rooms in the smart home!";
        }
    } else if (device_pool_index != -1) {

        if (device_pool_.size() > 0 && device_pool_index < device_pool_.size()) {
            int room_pool_index_dest = obj_destination["room_pool"];

            if (room_pool_.size() > 0 && room_pool_index_dest < room_pool_.size()) {
                room_pool_[room_pool_index_dest]->AddDevice(std::move(device_pool_[device_pool_index]));
                // device_pool_.erase(device_pool_.begin() + device_pool_index);
                server_response << "Added the device from the pool to the room#" << room_pool_index_dest << " from the room pool!";
            } else {
                server_response << "Wrong index for the destination of the device that should be added!";
            }
        } else {
            server_response << "Wrong index for the device selected from the pool!";
        }
    } else if (sensor_pool_index != -1) {

        if (sensor_pool_.size() > 0 && sensor_pool_index < sensor_pool_.size()) {
            int device_pool_index_dest = obj_destination["device_pool"];

            if (device_pool_.size() > 0 && device_pool_index_dest < device_pool_.size()) {
                device_pool_[device_pool_index_dest]->AddSensor(std::move(sensor_pool_[sensor_pool_index]));
                // sensor_pool_.erase(sensor_pool_.begin() + sensor_pool_index);
                server_response << "Added the sensor from the pool to the device#" << device_pool_index_dest << " from the device pool!";
            } else {
                server_response << "Wrong index for the destination of the sensor that should be added!";
            }
        } else {
            server_response << "Wrong index for the sensor selected from the pool!";
        }
    }
    
    server_response << std::endl;
    return server_response;
};

std::stringstream RoomAdd(std::stringstream&);
std::stringstream DeviceAdd(std::stringstream&);
std::stringstream SensorAdd(std::stringstream&);

std::stringstream ServerApp::Remove(std::stringstream& client_stream) {
    std::stringstream server_response("-- Removing operation --");
    std::string print_object;
    client_stream >> print_object;
    
    auto obj_locator = ParseToken(print_object);
    int room_index = obj_locator["room"];
    int device_index = obj_locator["device"];
    int sensor_index = obj_locator["sensor"];


    if (sensor_index == -1) {
        if (device_index == -1) {
            // room @
            server_response << RoomRemove(client_stream, room_index).rdbuf();

        }
        else {
            // device @
            server_response << DeviceRemove(client_stream, room_index, device_index).rdbuf();
        }
    }
    else {
        // sensor @
        server_response << SensorRemove(client_stream, room_index, device_index, sensor_index).rdbuf();
    }
    server_response << std::endl;
    return server_response;
};


std::stringstream ServerApp::RoomRemove(std::stringstream& client_stream, int room_index) {
    std::stringstream server_response;

    if (house_rooms_.size() > 0 && room_index < house_rooms_.size()) {
        std::string room_name = house_rooms_[room_index]->GetName();
        house_rooms_.erase(house_rooms_.begin() + room_index);
        server_response << "Room \"" << room_name << "\" was removed from the smart home!" << std::endl;
    } else {
        server_response << "Index out of bounds for the rooms in the smart home!";
    }
    return server_response;
};

std::stringstream ServerApp::DeviceRemove(std::stringstream&, int room_index, int device_index) {
    std::stringstream server_response;
    if (house_rooms_.size() > 0 && room_index < house_rooms_.size()) {
        antoniaptr::unique_ptr<Room>& room = house_rooms_[room_index];
        std::vector<Device*> devices = room->GetDevices();
        std::string room_name = room->GetName();

        if (devices.size() > 0 && device_index < devices.size()) {
            house_rooms_[room_index]->RemoveDevice(device_index);
            server_response << "Device #" << device_index << " was removed from \"" << room_name << "\" was removed from the smart home!" << std::endl;

        } else {
            server_response << "Index out of bounds for the device in the \"" << room_name << "\"!";
        }

    } else {
        server_response << "Index out of bounds for the rooms in the smart home!";
    }
    return server_response;
};

std::stringstream ServerApp::SensorRemove(std::stringstream&, int room_index, int device_index, int sensor_index) {
    std::stringstream server_response;
    if (house_rooms_.size() > 0 && room_index < house_rooms_.size()) {
        antoniaptr::unique_ptr<Room>& room = house_rooms_[room_index];
        std::vector<Device*> devices = room->GetDevices();
        std::string room_name = room->GetName();

        if (devices.size() > 0 && device_index < devices.size()) {
            Device* device = devices[device_index];
            std::vector<Sensor*> sensors = devices[device_index]->GetSensors();
    
            if (sensors.size() > 0 && sensor_index < sensors.size()) {
                device->RemoveSensor(sensor_index);
                server_response << "Device #" << device_index << " was removed from \"" << room_name << "\" was removed from the smart home!" << std::endl;

            }
            else {
                server_response << "Index out of bounds for the selected sensor!";
                
            }

        } else {
            server_response << "Index out of bounds for the device in the \"" << room_name << "\"!";
        }

    } else {
        server_response << "Index out of bounds for the rooms in the smart home!";
    }
    return server_response;
};


std::stringstream ServerApp::Print(std::stringstream& client_stream) {
    std::stringstream server_response("-- Printing operation --");
    std::string print_object;
    client_stream >> print_object;
    
    if (print_object.compare("home") == 0) {
        server_response << HomePrint(client_stream).rdbuf();
    }
    else {
        auto obj_locator = ParseToken(print_object);
        int room_index = obj_locator["room"];
        int device_index = obj_locator["device"];
        int sensor_index = obj_locator["sensor"];


        if (sensor_index == -1) {
            if (device_index == -1) {
                // room @
                server_response << RoomPrint(client_stream, room_index).rdbuf();

            }
            else {
                // device @
                server_response << DevicePrint(client_stream, room_index, device_index).rdbuf();
            }
        }
        else {
            // sensor @
            server_response << SensorPrint(client_stream, room_index, device_index, sensor_index).rdbuf();
        }
    }

    server_response << std::endl;
    return server_response;
};

std::stringstream ServerApp::HomePrint(std::stringstream& client_stream) {
    std::stringstream server_response;
    RoomPrinter* rp = new RoomPrinter();

    std::for_each(house_rooms_.begin(), house_rooms_.end(), 
        [&rp, &server_response] (antoniaptr::unique_ptr<Room>& room) {
            server_response << rp->Print(room.get()).rdbuf() << std::endl;
        });
    return server_response;
};

std::stringstream ServerApp::RoomPrint(std::stringstream& client_stream, int room_index) {
    std::stringstream server_response;
    RoomPrinter* rp = new RoomPrinter();

    if (house_rooms_.size() > 0 && room_index < house_rooms_.size()) {
        Room* room = house_rooms_[room_index].get();
        std::stringstream response = rp->Print(room);
        server_response << response.rdbuf();

    } else {
        server_response << "Index out of bounds for the rooms in the smart home!";
    }
    return server_response;
};

std::stringstream ServerApp::DevicePrint(std::stringstream& client_stream, int room_index, int device_index) {
    std::stringstream server_response;
    RoomPrinter* rp = new RoomPrinter();
    if (house_rooms_.size() > 0 && room_index < house_rooms_.size()) {
        auto devices = house_rooms_[room_index]->GetDevices();

        if (devices.size() > 0 && device_index < devices.size()) {
            auto device = devices[device_index];
            std::stringstream response = device->Interact();
            server_response << response.rdbuf();

        } else {
            server_response << "Index out of bounds for the device in the room#" << room_index << "!";
        }

    } else {
        server_response << "Index out of bounds for the rooms in the smart home!";
    }
    return server_response;
};

std::stringstream ServerApp::SensorPrint(std::stringstream& client_stream, int room_index, int device_index, int sensor_index) {
    std::stringstream server_response;
    RoomPrinter* rp = new RoomPrinter();
    if (house_rooms_.size() > 0 && room_index < house_rooms_.size()) {
        std::vector<Device*> devices = house_rooms_[room_index]->GetDevices();

        if (devices.size() > 0 && device_index < devices.size()) {
            std::vector<Sensor*> sensors = devices[device_index]->GetSensors(); 

            if (sensors.size() > 0 && sensor_index < sensors.size()) {
                Sensor* sensor = sensors[sensor_index];
                std::stringstream response = sensor->Interact();
                server_response << response.rdbuf();

            } else {
                server_response << "Index out of bounds for the sensor in the room#" << room_index << "/device#" << device_index << "!";
            }

        } else {
            server_response << "Index out of bounds for the device in the room#" << room_index << "!";
        }

    } else {
        server_response << "Index out of bounds for the rooms in the smart home!";
    }
    return server_response;
};

std::stringstream ServerApp::RoomPoolList(std::stringstream& client_stream) {
    std::stringstream server_response;
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
    return server_response;
}

std::stringstream ServerApp::DevicePoolList(std::stringstream& client_stream) {
    std::stringstream server_response;
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
    return server_response;
}

std::stringstream ServerApp::SensorPoolList(std::stringstream& client_stream) {
    std::stringstream server_response;
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
    return server_response;
}

std::stringstream ServerApp::RoomList(std::stringstream& client_stream) {
    std::stringstream server_response;
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
    return server_response;
}

std::stringstream ServerApp::DeviceList(std::stringstream& client_stream) {
    std::stringstream server_response;
    std::string device_locator;
    client_stream >> device_locator;
    if (device_locator.empty()) {
        server_response << "Please input the locator for the devices you want to list! (In this case the room#)";
        return server_response;
    }

    std::map<std::string, int> locators = ParseToken(device_locator);
    int room_number = locators["room"];

    if (house_rooms_.size() > 0 && (room_number < house_rooms_.size())) {
        auto devices = house_rooms_[room_number]->GetDevices();

        int i = 0;
        std::for_each(devices.begin(), devices.end(), 
            [&i, &server_response] (Device* dev) {
                server_response << "(" << i << ") " << dev->Interact().rdbuf() << std::endl;
                i++;
            });
    } else {
        server_response << "Wrong room number!" << std::endl;
    }
    return server_response;
}

std::stringstream ServerApp::SensorList(std::stringstream& client_stream) {
    std::stringstream server_response;
    std::string sensor_locator;
    client_stream >> sensor_locator;
    if (sensor_locator.empty()) {
        server_response << "Please input the locator for the sensors you want to list! (In this case the room# and device#)";
        return server_response;
    }

    std::map<std::string, int> locators = ParseToken(sensor_locator);
    int room_number = locators["room"];
    int device_number = locators["device"];

    if (house_rooms_.size() > 0 && (room_number < house_rooms_.size())) {
        auto devices = house_rooms_[room_number]->GetDevices();

        if (devices.size() > 0 && (device_number < devices.size())) {
            auto sensors = devices[device_number]->GetSensors();

            int i = 0;
            std::for_each(sensors.begin(), sensors.end(), 
                [&i, &server_response] (Sensor* sen) {
                    server_response << "(" << i << ") " << sen->Interact().rdbuf() << std::endl;
                    i++;
                });
        } else {
            server_response << "Wrong device number!" << std::endl;
        }
    } else {
        server_response << "Wrong room number!" << std::endl;
    }

    return server_response;
}

std::stringstream ServerApp::List(std::stringstream& client_stream) {
    std::stringstream server_response;
    std::string list_type_specifier;
    client_stream >> list_type_specifier;
    
    server_response << "-- Listing operation --" << std::endl;
    if (list_type_specifier == "room_pool") {
        server_response << RoomPoolList(client_stream).rdbuf();

    } else if (list_type_specifier == "device_pool") {
        server_response << DevicePoolList(client_stream).rdbuf();

    } else if (list_type_specifier == "sensor_pool") {
        server_response << SensorPoolList(client_stream).rdbuf();

    } else if (list_type_specifier == "rooms") {
        server_response << RoomList(client_stream).rdbuf();

    } else if (list_type_specifier == "devices") {
        server_response << DeviceList(client_stream).rdbuf();
        
    } else if (list_type_specifier == "sensors") {
        server_response << SensorList(client_stream).rdbuf();

    } else {
        server_response << "Wrong type specifier for the list operation!";
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

        if (room_name.empty()) {
            server_response << "Cannot create an unnamed room! Please input the new room name!" << std::endl;
        }
        else {
            room_name.erase(room_name.begin()); // erase the first " " character
            antoniaptr::unique_ptr<Room> new_room(new Room(room_name));
            room_pool_.push_back(std::move(new_room));
            server_response << "Created a new Room named \"" << room_name << "\" to the pool!" << std::endl;
        }

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
