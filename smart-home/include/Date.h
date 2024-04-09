#ifndef SH_DATE_H_
#define SH_DATE_H_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <string>
#include <ctime>

namespace smart_home {
class Date {
    public:
        Date(std::time_t);
        Date(std::string);
        Date() = delete;

        std::string GetDate();
        void SetDate(std::string);
        void SetDate(std::time_t);
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &a, const unsigned version) {
            a & date_;
        }
        std::string date_;
};
} // namespace smart_home

#endif // SH_DATE_H_