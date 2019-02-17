#pragma once

#include <stdlib.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "level.h"

struct gamestate
{
    int playing;
    SDL_Window *window;
    SDL_Renderer *renderer;
    level_t *cur_level;
};

void init_game(struct gamestate *state);
void gameloop(struct gamestate state);
