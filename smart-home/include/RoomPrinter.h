#ifndef SH_ROOMPRINTER_INCLUDE_H_
#define SH_ROOMPRINTER_INCLUDE_H_

#include "Room.h"

namespace smart_home {
class RoomPrinter {
    public:
        std::stringstream Print(Room*);
};
} // namespace smart_home
#endif  // SH_ROOMPRINTER_INCLUDE_H_