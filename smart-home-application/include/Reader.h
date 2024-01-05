#ifndef SHA_READER_H_
#define SHA_READER_H_

#include "Room.h"

namespace smart_home_app {

class Reader {
    public:
        virtual void Read(std::string) = 0;
};

} // smart_home_app

#endif // SHA_READER_H_