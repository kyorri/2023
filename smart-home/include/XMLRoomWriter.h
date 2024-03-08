#ifndef SH_XMLROOMWRITER_INCLUDE_H_
#define SH_XMLROOMWRITER_INCLUDE_H_

#include "Room.h"

#include "pugixml.hpp"

namespace smart_home {

class XMLRoomWriter {
    public:
        pugi::xml_node Write(const Room&);
};

} // namespace smart_home

#endif // SH_XMLROOMWRITER_INCLUDE_H_