#ifndef SHA_DEVICEPRINTER_H_
#define SHA_DEVICEPRINTER_H_

#include "Printer.h"
#include "Device.h"

namespace smart_home_app {
class DevicePrinter : public Printer {
    public:
        void Print() override;
        void AddDevice(Device*);
        void RemoveDevice(Device*);
    private:
        std::vector<Device*> devices_;
};
} // smart_home_app

#endif // SHA_DEVICEPRINTER_H_