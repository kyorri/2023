#ifndef SH_MESSAGE_INCLUDE_H_
#define SH_MESSAGE_INCLUDE_H_

#include "Date.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <string>

namespace smart_home {
class Message {
public:
    Message();
    Message(std::string);
    Message(std::string, std::string);
    Message(std::string, std::string, std::string);

    ~Message() = default;
    
    std::string GetMessageContents();
    std::string GetServerLogFormat();
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &a, const unsigned version) {
        a & sender_name_;
        a & date_;
        a & text_message_;
    }
    std::string text_message_, sender_name_;
    Date date_;
};
} // namespace smart_home

#endif  // SH_MESSAGE_INCLUDE_H_