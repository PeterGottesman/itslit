#include "SDL2/SDL.h"
#include "game.h"
#include "level.h"

void endfunc(void)
{

    SDL_Quit();
}

int main(int argc, char *argv[])
{
    uint32_t subsystems = SDL_INIT_VIDEO;
    if (SDL_Init(subsystems) != 0)
    {
        SDL_Log("Caould not init SDL: %s", SDL_GetError());
        return 1;
    }

    struct gamestate state;
    init_game(&state);

    // Init here
    state.cur_level = load_level("./sample_level.txt");
    
    gameloop(state);

    SDL_DestroyWindow(state.window);
    atexit(endfunc);
    return 0;
}
