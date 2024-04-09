#include "Message.h"

#include <ctime>

namespace smart_home {

Message::Message() : text_message_(""), date_(""), sender_name_("") {};

Message::Message(std::string message_contents) : text_message_(message_contents), date_(std::time(nullptr)), sender_name_(std::string_view("user_placeholder")) {};

Message::Message(std::string message_contents, std::string sender_name) : text_message_(message_contents), sender_name_(sender_name), date_(std::time(nullptr)) {};

Message::Message(std::string message_contents, std::string sender_name, std::string date) : text_message_(message_contents), sender_name_(sender_name), date_(date) {};

std::string Message::GetServerLogFormat() {
    std::stringstream output;
    output << "[" << date_.GetDate() << " / " << sender_name_ << "]" << std::endl;
    output << text_message_ << std::endl;
    return output.str();
};

std::string Message::GetMessageContents() {
    return text_message_;
};

} // namespace smart_home