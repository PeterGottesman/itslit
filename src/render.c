#include "render.h"
#include "defs.h"
#include "ray.h"

void render_in_inventory(SDL_Renderer *renderer, int index);
void render_placeable(SDL_Renderer *renderer, int x, int y);
void render_light_source(SDL_Renderer *renderer, int x, int y);
void render_ray(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);

void render_level(SDL_Renderer *renderer, level_t *level)
{
    int x, y;
    for (int i = 0; i < level->num_light_sources; ++i)
    {
	x = level->light_sources[i].x;
	y = level->light_sources[i].y;
	render_light_source(renderer, x, y);
    // render_ray(renderer, level->light_sources[i].x, level->light_sources[i].y, 0, 0);
    // render_ray(renderer, level->light_sources[i].x, level->light_sources[i].y, 0, HEIGHT);
    // render_ray(renderer, level->light_sources[i].x, level->light_sources[i].y, WIDTH, 0);
    // render_ray(renderer, level->light_sources[i].x, level->light_sources[i].y, WIDTH, HEIGHT);
	render_placeable(renderer, 50, 50);
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

void render_ray(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    point_t* dest_point = cast_ray(x1, y1, x2, y2);
    SDL_RenderDrawLine(renderer, x1, y1, dest_point->x, dest_point->y);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

}
