#include "Date.h"

#include <sstream>
#include <iomanip>

namespace smart_home {
    
Date::Date(std::time_t epoch_time) {
    SetDate(epoch_time);
};

Date::Date(std::string timestamp) {
    SetDate(timestamp);
};

std::string Date::GetDate() {
    return date_;
};

void Date::SetDate(std::time_t epoch_time) {
    std::tm* tm = std::localtime(&epoch_time);
    std::stringstream new_date_stream;

    new_date_stream << std::put_time(tm, "%Y-%m-%d");
    std::string new_date = new_date_stream.str();

    date_ = new_date;
};

void Date::SetDate(std::string new_date) {
    std::tm* tm{};
    std::stringstream new_date_stream(new_date);

    new_date_stream >> std::get_time(tm, "%Y-%m-%d");

    if (new_date_stream.fail()) {
        throw std::runtime_error("Could not convert the date using the specified date format!");
    }
    std::time_t epoch_time = std::mktime(tm);
    SetDate(epoch_time);
};


} // namespace smart_home
