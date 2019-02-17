#include "defs.h"
#include "ui.h"
#include "render.h"
#include <SDL2/SDL.h>

void draw_ui(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x99);
    SDL_RenderFillRect(renderer, &(SDL_Rect){.x = 0, .y = GAME_HEIGHT, .w = WIDTH, .h = 3});
}
