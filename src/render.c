#include "render.h"
#include "defs.h"

void render_in_inventory(SDL_Renderer *renderer, int index);
void render_placeable(SDL_Renderer *renderer, int x, int y);
void render_light_source(SDL_Renderer *renderer, int x, int y);

void render_level(SDL_Renderer *renderer, level_t *level)
{
    int x, y;
    for (int i = 0; i < level->num_light_sources; ++i)
    {
	x = level->light_sources[i].x;
	y = level->light_sources[i].y;
	render_light_source(renderer, x, y);
    }

    for (int i = 0; i < level->num_placeables; ++i)
    {
	x = level->placeables[i].x;
	y = level->placeables[i].y;
	if (x >= 0 && y >= 0)
	{
	    render_placeable(renderer, x, y);
	}
	else
	{
	    render_in_inventory(renderer, i);
	}
    }
}

void render_in_inventory(SDL_Renderer *renderer, int index)
{
    render_placeable(renderer,
		     index * (RENDERABLE_SIZE+10) + 10,
		     HEIGHT-RENDERABLE_SIZE-5);
}

void render_light_source(SDL_Renderer *renderer, int x, int y)
{
    filledCircleColor(renderer, x, y, 2, 0xffffffff);
}

void render_placeable(SDL_Renderer *renderer, int x, int y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = RENDERABLE_SIZE;
    rect.h = RENDERABLE_SIZE;
    SDL_RenderFillRect(renderer, &rect);
}

