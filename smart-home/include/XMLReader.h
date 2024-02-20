#ifndef SHA_XMLREADER_H_
#define SHA_XMLREADER_H_

#include "pugixml.hpp"
#include "Reader.h"
#include "Room.h"

#include <vector>
#include <string>

namespace smart_home_app {

class XMLReader : Reader{
    public:
        void Read(std::string) override;
        std::vector<Room> GetRooms();
    private:
        std::vector<Room> rooms_;
};

} // smart_home_app

#endif // SHA_XMLREADER_H_