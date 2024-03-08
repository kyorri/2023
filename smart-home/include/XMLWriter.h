#ifndef SH_XMLWRITER_INCLUDE_H_
#define SH_XMLWRITER_INCLUDE_H_

#include "XMLRoomWriter.h"

#include <string>

namespace smart_home {

class XMLWriter {
    public:
        XMLWriter() = delete;
        XMLWriter(std::string);
        void Write();
        void AddRoom(antoniaptr::unique_ptr<Room>);
        void RemoveRoom(std::string);
    private:
        std::string filename_;
        std::vector<antoniaptr::unique_ptr<Room>> rooms_;
};

} // namespace smart_home

#endif // SH_XMLWRITER_INCLUDE_H_