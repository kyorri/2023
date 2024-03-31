#ifndef SH_SOCKET_INCLUDE_H_
#define SH_SOCKET_INCLUDE_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

namespace smart_home {
class Socket {
public:
    Socket();
    Socket(int);
    ~Socket();

    Socket(Socket&) = delete;
    Socket& operator=(Socket&) = delete;

    Socket(Socket&&);
    Socket& operator=(Socket&&);

    const int& operator()();
private:
    int socket_fd_;
};
} // namespace smart_home
#endif // SH_SOCKET_INCLUDE_H_