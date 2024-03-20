#ifndef SH_CLIENTAPP_INCLUDE_H_
#define SH_CLIENTAPP_INCLUDE_H_

#include "Socket.h"

namespace smart_home {
class ClientApp {
public:
    ClientApp();
    ClientApp(unsigned short int);

    void Initialize();
    void AttemptConnection();
    void TransferLoop();
private:
    Socket conn_socket_;
    unsigned short int server_port_;
    struct sockaddr_in server_address_;
    const int max_buffer_size_;
};
} // namespace smart_home
#endif // SH_CLIENTAPP_INCLUDE_H_