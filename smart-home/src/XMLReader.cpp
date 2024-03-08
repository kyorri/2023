#include "XMLReader.h"

#include "XMLRoomReader.h"
#include "pugixml.hpp"

namespace smart_home {
XMLReader::XMLReader(std::string filename) : filename_(filename) {};
std::vector<antoniaptr::unique_ptr<Room>> XMLReader::Read() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename_.c_str());

    std::vector<antoniaptr::unique_ptr<Room>> rooms;

    try {
        if (!result) {
            throw std::runtime_error("There was an error loading the XML file!");
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    XMLRoomReader xmlrrd;
    pugi::xml_node root = doc.child("Root");
    for (pugi::xml_node room : root.children("Room")) {
        rooms.push_back(std::move(xmlrrd.Read(room)));
    }

    return std::move(rooms);
};
} // namespace smart_home