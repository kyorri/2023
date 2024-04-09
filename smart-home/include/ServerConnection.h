#ifndef SH_SERVERCONNECTION_INCLUDE_H_
#define SH_SERVERCONNECTION_INCLUDE_H_

#include "Socket.h"

#include <string>

namespace smart_home {
class ServerConnection {
public:
    ServerConnection(Socket&, sockaddr_in, socklen_t);
    ServerConnection(Socket&, sockaddr_in, socklen_t, std::string);
    ~ServerConnection() = default;
    
    ServerConnection(ServerConnection&) = delete;
    ServerConnection& operator=(ServerConnection&) = delete;

    ServerConnection(ServerConnection&&);
    ServerConnection& operator=(ServerConnection&&);

    Socket& GetSocket();
    std::string GetClientName();
    sockaddr_in& GetClientAddress();
    socklen_t& GetClientAddressLength();

    void SetClientName(std::string);
    void SetClientAddress(sockaddr_in&);
    void SetClientAddressLength(socklen_t&);

private:
    Socket socket_;
    std::string client_name_;
    sockaddr_in client_address_;
    socklen_t client_addr_len_;
};
} // namespace smart_home
#endif // SH_SERVERCONNECTION_INCLUDE_H_