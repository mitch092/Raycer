#include "SdlInit.h"
#include <iostream>

int main(int argc, char *args[]) {
    (void)argc;
    (void)args;

    auto sdlInit = SdlInit::InitializeSdl();
    if (sdlInit.has_value()) {
        std::cout << "SDL successfully initialized." << std::endl;
        return EXIT_SUCCESS;
    } else {
        std::cout << "SDL failed to initialize with error code: " << sdlInit.error() << std::endl;
        return EXIT_FAILURE;
    }
}
