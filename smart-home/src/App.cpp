#include "App.h"

#include <cstring>

namespace smart_home {
App::App(const int& argc, const char* const* argv) {
    if (argc == 1) {
        throw std::invalid_argument("Wrong usage of application! (please enter client/server after executable!)");
    }
    else {
        if (strcmp(argv[1], "client") == 0) {
            unsigned short int port = 44445; // we can have 65536 ports (16-bit unsigned int)
            if (argc == 3) {
                port = atoi(argv[2]);
            }
            ClientApp app(port);
        } 
        else if (strcmp(argv[1], "server") == 0) {
            unsigned short int port = 44445; // we can have 65536 ports (16-bit unsigned int)
            if (argc == 3) {
                port = atoi(argv[2]);
            }
            ServerApp app(port, 10);
        }
        else {
            throw std::invalid_argument("Wrong application specifier! (client/server)");
        }
    }
}
} // namespace smart_home