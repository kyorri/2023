#include "XMLWriter.h"

#include "XMLRoomWriter.h"
#include "pugixml.hpp"

#include <algorithm>

namespace smart_home {
XMLWriter::XMLWriter(std::string filename) : filename_(filename) {};

void XMLWriter::Write() {
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("Root");
    XMLRoomWriter xmlrw;
    for (const auto& r : rooms_) {
         root.append_copy(xmlrw.Write(*r));
    }
    doc.save_file(filename_.c_str());
};

void XMLWriter::AddRoom(antoniaptr::unique_ptr<Room> r) {
    try {
        if (r.get() != nullptr) {
            rooms_.push_back(std::move(r));
        }
        else {
            throw std::runtime_error("Unexpected address pointed by the unique pointer while adding to the XMLWriter!");
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    };
};

void XMLWriter::RemoveRoom(std::string filename) {
    rooms_.erase(std::remove_if(rooms_.begin(), rooms_.end(),
      [filename](const antoniaptr::unique_ptr<Room>& r) {
        return r->GetName() == filename;
      }), rooms_.end());
};
} // namespace smart_home
