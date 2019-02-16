#include "SDL2/SDL.h"
#include "window.h"
#include "game.h"

void endfunc(void)
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    uint32_t subsystems = SDL_INIT_VIDEO;
    if (SDL_Init(subsystems) != 0)
    {
        SDL_Log("Could not init SDL: %s", SDL_GetError());
        return 1;
    }

    if (CreateWindow() != 0)
    {
        return 1;
    }

    // Init here

    gameloop();

    atexit(endfunc);
    return 0;
}
