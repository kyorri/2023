#include <iostream>

#include "App.h"
#include "Room.h"
#include "Device.h"
#include "Sensor.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "No filename chosen!" 
                  << std::endl
                  << "Please enter a filename after the executable!"
                  << std::endl;
        return -1;
    }
    std::string filename = argv[1];

    App app(filename);
    app.load();
    // functionality for the app here
    app.save();

    return 0;
}