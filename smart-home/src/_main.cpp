#include "App.h"

int main(int argc, char* argv[]) {
    try {
        smart_home::App app(argc, argv);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
