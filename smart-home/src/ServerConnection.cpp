#include "ServerConnection.h"

namespace smart_home {

ServerConnection::ServerConnection(Socket& socket, sockaddr_in socket_address, socklen_t socket_length) 
    : socket_(std::move(socket)), client_address_(socket_address), client_addr_len_(socket_length) {};


ServerConnection::ServerConnection(Socket& socket, sockaddr_in socket_address, socklen_t socket_length, std::string client_name) 
    : socket_(std::move(socket)), client_address_(socket_address), client_addr_len_(socket_length), client_name_(client_name) {};

ServerConnection::ServerConnection(ServerConnection&& other)
    : socket_(std::move(other.socket_)), client_name_(std::move(other.client_name_)),
        client_address_(other.client_address_), client_addr_len_(other.client_addr_len_) {

    other.client_address_ = {};
    other.client_addr_len_ = 0;
}

ServerConnection& ServerConnection::operator=(ServerConnection&& other) {
    if (this != &other) {
        socket_ = std::move(other.socket_);
        client_name_ = std::move(other.client_name_);
        client_address_ = other.client_address_;
        client_addr_len_ = other.client_addr_len_;

        other.client_address_ = {};
        other.client_addr_len_ = 0;
    }
    return *this;
};

Socket& ServerConnection::GetSocket() {
    return socket_;
};

std::string ServerConnection::GetClientName() {
    return client_name_;
};

sockaddr_in& ServerConnection::GetClientAddress() {
    return client_address_;
};

socklen_t& ServerConnection::GetClientAddressLength() {
    return client_addr_len_;
};

void ServerConnection::SetClientName(std::string new_client_name) {
    client_name_ = new_client_name;
};

void ServerConnection::SetClientAddress(sockaddr_in& new_client_address) {
    client_address_ = new_client_address;
};

void ServerConnection::SetClientAddressLength(socklen_t& new_client_address_length) {
    client_addr_len_ = new_client_address_length;
};
} // namespace smart_home
