#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "level.h"

/* float square_verts[] = */
/* { */
/* //   x  ,  y */
/*     0.0f, 0.0f, */
/*     1.0f, 0.0f, */
/*     0.0f, 1.0f, */
/*     1.0f, 1.0f */
/* }; */

/* void render_shape(SDL_Renderer *renderer, shape_t shape); */
void render_level(SDL_Renderer *renderer, level_t *level);
