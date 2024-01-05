#ifndef SHA_WRITER_H_
#define SHA_WRITER_H_

#include "Room.h"

namespace smart_home_app {

class Writer {
    public:
        virtual void Write(std::string) = 0;
        virtual void AddRoom(Room) = 0;
        virtual void RemoveRoom(Room) = 0;
};

} // smart_home_app

#endif // SHA_WRITER_H_