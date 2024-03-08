#ifndef SH_XMLROOMREADER_INCLUDE_H_
#define SH_XMLROOMREADER_INCLUDE_H_

#include "Room.h"

#include "pugixml.hpp"

namespace smart_home {

class XMLRoomReader {
    public:
        antoniaptr::unique_ptr<Room> Read(pugi::xml_node);
};

} // namespace smart_home

#endif // SH_XMLROOMREADER_INCLUDE_H_