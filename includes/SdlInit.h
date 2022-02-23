#ifndef SDLINIT_H
#define SDLINIT_H

#include "tl/expected.hpp"
#include <SDL.h>
#include <string>

class SdlInit {
   public:
    static tl::expected<SdlInit, std::string> InitializeSdl() {
        return SDL_Init(SDL_INIT_VIDEO) >= 0 ? tl::expected<SdlInit, std::string>(SdlInit()) : tl::make_unexpected(std::string(SDL_GetError()));
    }

    ~SdlInit() {
        SDL_Quit();
    }

   private:
    SdlInit() = default;
};

#endif
