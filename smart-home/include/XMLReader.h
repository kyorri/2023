#ifndef SH_XMLREADER_INCLUDE_H_
#define SH_XMLREADER_INCLUDE_H_

#include "Room.h"
#include "unique_ptr.h"

#include <string>

namespace smart_home {

class XMLReader {
    public:
        XMLReader() = delete;
        XMLReader(std::string);
        std::vector<antoniaptr::unique_ptr<Room>> Read();
    private:
        std::string filename_;
};

} // namespace smart_home

#endif // SH_XMLREADER_INCLUDE_H_