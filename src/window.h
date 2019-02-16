#pragma once

#include <string.h>
#include "SDL2/SDL.h"
#include "defs.h"

char* title;

SDL_Window *window;
SDL_Renderer *renderer;

int CreateWindow(void);
