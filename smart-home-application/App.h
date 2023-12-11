#ifndef SHA_APP_H_
#define SHA_APP_H_

#include "Room.h"
#include <string>
#include <vector>

class App {
    public:
        App(std::string);
        void save();
        void load();
        void addSensor(Device&, std::string, double);
        void addDevice(Room&, std::string, bool);
        void newRoom(std::string);
        std::vector<Room> getRooms();
    private:
        std::string filename;
        std::vector<Room> rooms;
};

#endif // SHA_APP_H_