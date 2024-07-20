#include "includes.h" 

int main(int argc, char* argv[]) {
    const int width = 800, height = 600;
    std::string nowUnix = lars::logic::getUnixMS();
    if (nowUnix.size() < 16) {
        nowUnix.resize(16, '0');
    }
    if (nowUnix.size() > 16) {
        nowUnix.resize(16);
    }
    SecByteBlock key = lars::logic::strToSbb(nowUnix);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << nowUnix;
    SDL_Window* window = SDL_CreateWindow("UwU you've been pwn'd by a gay, a furry, and a hacker",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        std::cout << "Window creation error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Event loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    // Clean up and free resources
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
