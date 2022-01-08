module;
#include <SDL.h>
export module presenter;
import types;

export class Presenter {
   public:
    Presenter(const char* name, u16 width, u16 height)
        : window(nullptr), renderer(nullptr), texture(nullptr) {
        // Propogating errors (w/o exceptions) is such a drag. Just add assertions and keep them in the release builds :/
        int init = SDL_Init(SDL_INIT_VIDEO);
        asrt(init >= 0);

        window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        asrt(window != nullptr);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        asrt(renderer != nullptr);

        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
        asrt(texture != nullptr);
    }

    ~Presenter() {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool is_running() const {
        bool running = true;
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
        return running;
    }

    //void operator()(const RectangularArray<Color>& frame) {
    //    SDL_UpdateTexture(texture, nullptr, frame.data(), frame.get_width() * sizeof(Color));
    //    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    //    SDL_RenderPresent(renderer);
    //}

   private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};
