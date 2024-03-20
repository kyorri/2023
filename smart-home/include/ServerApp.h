#ifndef SH_SERVERAPP_INCLUDE_H_
#define SH_SERVERAPP_INCLUDE_H_

#include "Socket.h"
#include "Room.h"
#include "Device.h"
#include "Sensor.h"
#include "XMLWriter.h"
#include "unique_ptr.h"

#include <vector>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace smart_home {
class ServerApp {
public:
    ServerApp();
    ServerApp(int);
    
    void InitializeAndListen();
    void AcceptConnection();
    void TransferLoop();

    std::stringstream Add(std::stringstream&);
    std::stringstream Remove(std::stringstream&);
    std::stringstream Print(std::stringstream&);
    std::stringstream List(std::stringstream&);
    std::stringstream Create(std::stringstream&);

private:
    std::string file_name;
    std::vector<antoniaptr::unique_ptr<Room>> house_rooms_;
    std::vector<antoniaptr::unique_ptr<Room>> room_pool_;
    std::vector<antoniaptr::unique_ptr<Device>> device_pool_;
    std::vector<antoniaptr::unique_ptr<Sensor>> sensor_pool_;
    Socket server_socket_;
    Socket client_socket_;
    int server_port_;
    const int max_buffer_size_;
};
} // namespace smart_home
#endif // SH_SERVERAPP_INCLUDE_H_