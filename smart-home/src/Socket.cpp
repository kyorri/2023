#include "Socket.h"

#include <iostream>

namespace smart_home {
Socket::Socket() : socket_fd_(-1) {
    socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
};

Socket::Socket(int socket_fd) : socket_fd_(socket_fd) {};

Socket::Socket(Socket&& other) : socket_fd_(other.socket_fd_) {
    other.socket_fd_ = -1;
}

Socket& Socket::operator=(Socket && other) {
    if (this != &other) {
        if (socket_fd_ != -1) {
            close(socket_fd_);
        }
        socket_fd_ = other.socket_fd_;
        other.socket_fd_ = -1;
    }
    return *this;
}


const int &Socket::operator()() {
    if (socket_fd_ == -1) {
        throw std::runtime_error("Error for the socket!");
    }
    return socket_fd_;
};

Socket::~Socket() {
    if (socket_fd_ != -1) {
        close(socket_fd_);
    }
}
} // namespace smart_home
