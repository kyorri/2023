#ifndef SHA_XMLWRITER_H_
#define SHA_XMLWRITER_H_

#include "pugixml.hpp"
#include "Writer.h"
#include "Room.h"

#include <vector>

namespace smart_home_app {

class XMLWriter : public Writer {
    public:
        void Write(std::string) override;
        void AddRoom(Room) override;
        void RemoveRoom(Room) override;
    private:
        std::vector<Room> rooms_;
};

} // smart_home_app

#endif // SHA_XMLWRITER_H_