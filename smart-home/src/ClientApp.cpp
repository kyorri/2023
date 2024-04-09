#include "ClientApp.h"

#include <boost/archive/text_oarchive.hpp>

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <sstream>

namespace smart_home {
ClientApp::ClientApp() : max_buffer_size_(0) {
    throw std::invalid_argument("Wrong usage of client application! Please supply the port of the server application to connect!");
};

ClientApp::ClientApp(unsigned short int server_port) : conn_socket_(), server_port_(server_port), max_buffer_size_(8192) {
    Initialize();
    AttemptConnection();
    RespondAuthentication();
    TransferLoop();
};

void ClientApp::Initialize() {
    if (conn_socket_() == -1) {
        std::runtime_error("Error while creating a socket for the client!");
    }

    server_address_.sin_port = htons(server_port_);
    server_address_.sin_family = AF_INET;

    if (inet_pton(AF_INET, "127.0.0.1", &server_address_.sin_addr) <= 0) {
        std::runtime_error("Invalid server address! You could check if the port number is correct!");
    }
};
    
void ClientApp::AttemptConnection() {
    if (connect(conn_socket_(), (sockaddr*)&server_address_, sizeof(server_address_)) == -1) {
        std::runtime_error("Connection to the server failed!");
    }
};

void ClientApp::RespondAuthentication() {
    const int server_message_max_length = 64;

    char buffer_recv[server_message_max_length] = {};

    Socket& server_socket = conn_socket_;

    int bytes_received = recv(server_socket(), buffer_recv, server_message_max_length, 0);

    if (bytes_received == -1) {
        throw std::runtime_error("Could not receive the data from the server for the authentication process!");
    }

    std::string client_name;
    std::getline(std::cin, client_name);

    int bytes_sent = send(server_socket(), client_name.c_str(), client_name.size(), 0);
    if (bytes_sent == -1) {
        throw std::runtime_error("There was a problem sending the client name information to the server instance!");
    }

};


void ClientApp::TransferLoop() {
    char buffer_recv[max_buffer_size_] = {0};
    char buffer_send[max_buffer_size_] = {0};

    int bytes_received;
    int bytes_sent;
    while (true) {
        bytes_received = recv(conn_socket_(), buffer_recv, sizeof(buffer_recv), 0);
        if (bytes_received <= 0) {
            throw std::runtime_error("There was a problem at receiving data from the server instance!");
        }
        buffer_recv[bytes_received] = '\0';
        std::cout << "----------------------------" << std::endl;
        std::cout << buffer_recv << std::endl;
        
        // we get data from client and check if we exit, we ll use an exception to stop the client instance
        std::cout << "Enter message for the server (enter *nothing* to close):\n >>> ";
        std::string client_input;
        std::getline(std::cin, client_input);

        Message message(client_input, client_name_);

        std::stringstream ss;
        boost::archive::text_oarchive out_archive(ss);
        out_archive << message;

        std::string serialized_message = ss.str();

        std::string token;
        std::stringstream exit_check(client_input);
        exit_check >> token;
        if (token.size() == 0) {
            throw std::runtime_error("Ending connection to server instance!");
        }
        token.clear();

        bytes_sent = send(conn_socket_(), serialized_message.c_str(), serialized_message.size(), 0);
        if (bytes_sent == -1) {
            throw std::runtime_error("There was an error sending data to the server!");
        }
    }
};
} // namespace smart_home
