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

    std::stringstream RoomAdd(std::stringstream&);
    std::stringstream DeviceAdd(std::stringstream&);
    std::stringstream SensorAdd(std::stringstream&);


    std::stringstream Remove(std::stringstream&);

    std::stringstream RoomRemove(std::stringstream&, int);
    std::stringstream DeviceRemove(std::stringstream&, int, int);
    std::stringstream SensorRemove(std::stringstream&, int, int, int);

    std::stringstream Print(std::stringstream&);

    std::stringstream HomePrint(std::stringstream&);
    std::stringstream RoomPrint(std::stringstream&, int);
    std::stringstream DevicePrint(std::stringstream&, int, int);
    std::stringstream SensorPrint(std::stringstream&, int, int, int);


    std::stringstream List(std::stringstream&);

    std::stringstream RoomPoolList(std::stringstream&);
    std::stringstream DevicePoolList(std::stringstream&);
    std::stringstream SensorPoolList(std::stringstream&);
    std::stringstream RoomList(std::stringstream&);
    std::stringstream DeviceList(std::stringstream&);
    std::stringstream SensorList(std::stringstream&);

    
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